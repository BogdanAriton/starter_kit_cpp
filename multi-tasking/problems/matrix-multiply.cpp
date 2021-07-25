/*

Multiply to matrices and making use of parallelism.
A 4x2 matrix x 2x3 matrix will produce a 4x3 matrix - because the number of columns in the first matrix is the same as the number of rows in the second matrix

   | 1 2 | 
A= | 4 5 |
   | 3 6 |

B = | 5 8 3 |
    | 9 1 6 |

C i,j = a i,0 * b 0,j + a i,1 * b1,j

*/

#include <thread>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>

/* sequential implementation of matrix multiply */
void sequential_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                                long ** B, size_t num_rows_b, size_t num_cols_b,
							    long ** C) {
    for (size_t i=0; i<num_rows_a; i++) {
        for (size_t j=0; j<num_cols_b; j++) {
			C[i][j] = 0; // initialize result cell to zero
            for (size_t k=0; k<num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
		}
	}
}

/* the action is simple - we just add two multiplication - and this will not take long
    The problem is going through both matrix - so we could divide the number of row and the number of line by the number of processors and just separate them 
    we can have segments of rows and columns for each matrix A and B 
    ex: 1000 is the number of rows in a which is the same as the number of cols in b
        -> silos = 1000 / 8 = 125 silos
        this means that we do a while loop through each silo and pass it to each thread for execution

        - one portion will be to grab the first 125 rows with 125 cols and pass it to the function
        - the second one will be to grab the next 125 cols on the same line of the rows until we reached the end of the silos
        - and we do this again for the next 125 rows until we don't have more rows and cols left
        - now the problem is that we might a perfect split - thus the last interval we pick from where we left of and until the end for each column and row

    Iteration example:
    i = 0 -> 125
        for each i  
        j = 0 -> 125

    i = i+1 -> i+1+125  j = 125 -> j = j + 1 + 125

    the function will 

   | 1 2 3 4 5 5 6 7 .. 1000 | 
A= | 4 5 3 5 7 8 9 1 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   .. 1000

   | 1 2 3 4 5 5 6 7 .. 1000 | 
B= | 4 5 3 5 7 8 9 1 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   | 3 6 1 3 8 7 4 2 .. 1000 |
   .. 1000
*/
void per_processor_action(long ** A, size_t startA, size_t num_rows_a, size_t num_cols_a,
                              long ** B, size_t startB, size_t num_rows_b, size_t num_cols_b,
							  long** C)
{
    for (size_t i = startA; i < num_rows_a; ++i)
    {
        for (size_t j = startB; j < num_cols_b; ++j)
        {
            C[i][j] = 0; // initialize result cell to zero
            for (size_t k=startA; k<num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* parallel implementation of matrix multiply */
constexpr int NUMBER_OF_CORES = 8;
void parallel_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                              long ** B, size_t num_rows_b, size_t num_cols_b,
							  long ** C) {
    size_t silos = num_cols_a / NUMBER_OF_CORES; // = num_rows_b / NUMBER_OF_CORES
    size_t row_a_silos;
    if (num_rows_a < NUMBER_OF_CORES) row_a_silos = 0;
    else if (num_rows_a == NUMBER_OF_CORES) row_a_silos = 1;
    else row_a_silos = num_rows_a / NUMBER_OF_CORES;
    
    size_t col_b_silos;
    if (num_cols_b < NUMBER_OF_CORES) col_b_silos = 0;
    else if (num_cols_b == NUMBER_OF_CORES) col_b_silos = 1;
    else col_b_silos = num_cols_b / NUMBER_OF_CORES;

    int action = 1;
    size_t row_start = 0;
    size_t col_start = 0;
    size_t num_cols_b_end = col_b_silos;
    size_t num_rows_a_end = row_a_silos;

    while (action <= NUMBER_OF_CORES)
    {
        std::thread threads[NUMBER_OF_CORES];
        for (int i = 0; i < NUMBER_OF_CORES; ++i)
        {
            threads[i] = std::thread(per_processor_action, &A, row_start, num_rows_a_end, silos, &B, col_start, silos, num_cols_b_end, &C);
            if ((num_cols_b_end + silos) > num_cols_b)
            {
                num_cols_b_end += (num_cols_b - num_cols_b_end)-1;
            }
            else
            {
                num_cols_b_end += col_b_silos;
                col_start += col_b_silos;
            }
            
        }

        for (auto &c : threads)
        {
            c.join();
        }

        action++;
    }
}

int main() {
	const int NUM_EVAL_RUNS = 3;
	const size_t NUM_ROWS_A = 1000;
	const size_t NUM_COLS_A = 1000;
	const size_t NUM_ROWS_B = NUM_COLS_A;
	const size_t NUM_COLS_B = 1000;

    // intialize A with values in range 1 to 100    
    long ** A = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    if (A == NULL) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        A[i] = (long *)malloc(NUM_COLS_A * sizeof(long));
        if (A[i] == NULL) {
            exit(2);
        }
        for (size_t j=0; j<NUM_COLS_A; j++) {
            A[i][j] = rand() % 100 + 1;
        }
    }

    // intialize B with values in range 1 to 100   
    long ** B = (long **)malloc(NUM_ROWS_B * sizeof(long *));
    if (B == NULL) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_B; i++) {
        B[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if (B[i] == NULL) {
            exit(2);
        }
        for (size_t j=0; j<NUM_COLS_B; j++) {
            B[i][j] = rand() % 100 + 1;
        }
    }

	// allocate arrays for sequential and parallel results
    long ** sequential_result = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    long ** parallel_result = (long **)malloc(NUM_ROWS_A * sizeof(long *));
    if ((sequential_result == NULL) || (parallel_result == NULL)) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        sequential_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        parallel_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if ((sequential_result[i] == NULL) || (parallel_result[i] == NULL)) {
            exit(2);
        }
    }

    printf("Evaluating Sequential Implementation...\n");
	std::chrono::duration<double> sequential_time(0);
    sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
	std::chrono::duration<double> parallel_time(0);
    parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
	
    // // verify sequential and parallel results
    // for (size_t i=0; i<NUM_ROWS_A; i++) {
    //     for (size_t j=0; j<NUM_COLS_B; j++) {
    //         if (sequential_result[i][j] != parallel_result[i][j]) {
    //             printf("ERROR: Result mismatch at row %ld, col %ld!\n", i, j);
    //         }
    //     }
    // }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count()*1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count()*1000);
    printf("Speedup: %.2f\n", sequential_time/parallel_time);
    printf("Efficiency %.2f%%\n", 100*(sequential_time/parallel_time)/std::thread::hardware_concurrency());
}
