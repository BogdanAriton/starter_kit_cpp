# Parallel computing architectures:

Widely used system for for classifying multiprocessor architecture is Flynn's Taxonomy:
It's based on the number of concurrent instructions or instruction streams and the number of data streams.

                # instruction stream
            #      SISD       MISD
            d
            s      SIMD       MIMD

# SISD - single instruction single data
    Can execute only one thing at a time.
# SIMD - single instruction multiple data
    Is used
# MISD - multiple instructions singe data
    Not practical
# MIMD - multiple instructions multiple data
    Most used.

# Memory
    !! shared memory !!
    all processors should be able to see if another processor is changing its memory space

Architecture:
    UMP - uniform memory access or NUMA - non uniform 
        - all processes have equal access to memory
    Types of UMA -> SMP (symmetric multiprocessor system)

## SMP
    Processors are connected to the memory through the System Bus
    This is the most common and important to learn architecture

# Cache coherency
    - each core has it's own cache (a very fast piece of memory that only that specific processor can access)

    The problem when a processor write something into it's local cache based on data from the shared memory then that data needs to be updated in the shared memory before other processors can grab it to make their changes.

    This is handled by the hardware! (inside the computer! :-))

# process
    Independent

# threads
    Independent path of execution through the program
    
    Lifecycle:
        new thread 
        runnable block
        terminated
    
## join()
    Waits for another thread to finish
    It blocks the current thread

## joinable()
    Returns whether a thread is joinable.

# detached
    Daemon thread - will not prevent the process from exiting
    When a process ends while daemon threads still execute these threads will also terminate - thus we have to think about what the threads could be doing during termination.
    .detach() will make the thread non-joinable.


# Heisenbug
    - it's a type of bug that doesn't appear while testing
    - this is about race conditions

# Sync mechanisms:
    - barriers - works on a specific number of threads to separate actions
        - boost::barrier is used with a wait on the start of the thread that should wait before acquiring the mutex and a wait after the mutex on the threads that need to go first which releases the wait.
            - thread 1 - wait
            - thread 2 - works and the release the wait which will let thread 1 to start working

    - latch - works with a count that releases the latch when it goes down to 0
        - boost::latch
        - the count can be set to the number of times an action can be made and the understand which thread will execute that first and it will work in a similar fashion to the barrier
            - now the thread that works will lock the mutex first and do the work and then decrements the count on the latch
            - when the count goes down to 0 then the other thread can finish their jobs

    - barriers and latches can be used when you know either the number of threads or the number of times an action can be made


# Async tasks
    - computational graph = a tool tha helps organize threads .. 
    - using a DAG (directed acyclic graphs) to determine the relation and dependencies between tasks
    - we need identify the 
        - critical paths = the longest path in the graph (meaning we will skip the nodes that are redundant and their time)
        - SPAN = the time of the tasks in the critical path (shortest possible execution time)
        - work = the total time it takes for all tasks to execute

    !!! Ideal Parallelism = WORK/SPAN (basically divide the longest by the shortest and you get what the time should take)
    example: WORK = 60 and SPAN = 40 then IP = WORK/SPAN = 60/40 = 1.33 = which can indicate that the program an work 33% faster with parallelism compared to the program that would run sequentially

# Thread Pool - design pattern
    - thread pool reuses existing threads
    - boost::asio::thread_pool - of course boost has a thread pool and it's part of ASIO framework! ASIO Rules

    boost::asio::thread_pool pool(4) - it will hold 4 threads
    for (int i = 0; i < 4; i++)
        pool[i] = std::thread(the_function_to_work_on, i); (the thread number)

    pool.join() - to join all threads at the end

## Future
    a place holder fir a result that will be available later
    mechanism for accessing the result of an asynchronous operation
    
    
    A way to use the future is to wait for the result a function that runs in a separate thread
    ex:
        #include <future>
        int func()
        {
            sleep(10)
            return 20;
        }

        int main()
        {
            std::future result = std::async(std::launch::async, func); // the launch::async will is the async condition = it tells it to run asynchronous 
            result.get(); // this gets back the result and waits if the result is not there yet
        }

# Speedup, latency and throughput
    Maximizing throughput - the number of task it can complete in a given time
        - week scaling - keeping the size constant, but bringing in more workers - accomplish 2xWork in the same time
        - strong scaling - when dividing the problem and gaining time - accomplish the same work in less time

    Latency
        - is measured in units of time and it represents the time it takes for a task to complete


# Designing parallel programs
    1. Partitioning - breaking the problem in a concrete chunks of work
        1.1 - Domain decomposition - it's considering how we can approach the data structure
            - blok decomposition, acyclic decomposition
        1.2 - Functional - it's based on action type 

    2. Communication
        - coordinate communication between tasks
        - this is considered when we share data
        Types: 
            Point to Point communication (undirected graph - when each task needs to communicate with small number of other tasks)
            Collective communication (when a task broadcasts a message to many other tasks)

    3. Agglomeration

        Thinks to think about:
            Granularity = computation / communication (if the task has a small computation work and spends more time communicating this might not be efficient)
            Load Balancing
            Fine Grained - Small Tasks
            Coarse-Grained - Large Tasks

        Combine the tasks if there are more tasks per process
        This has to be flexible
        Example: We have two cores and we decide to split the tasks in to two groups for each processor, if a new processor is introduced then we can't leverage it to help with the work
        thus the split was useless, thus when splitting we have to think about this division to be adjustable either at compile time or runtime

    4. Mapping
        Specify where each of the task will execute.
        Basically if you have 8 cores then you have 8 works that can be assigned work - that assignment is the mapping.
    
