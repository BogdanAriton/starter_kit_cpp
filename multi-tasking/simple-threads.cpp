#include <iostream>
#include <thread>

static bool is_finished = false;
void worker()
{
    while(!is_finished)
    {
        std::cout << "working..." << '\n';
    }
    
}

int main()
{
    std::thread t_worker(worker);

    std::cin.get();
    is_finished = true;

    t_worker.join();
    std::cin.get();

    
}