#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>

class DeadLock
{
private:
    std::mutex m1;
    std::mutex m2;
    int x = 0;

public:
    void myfunc(int t)
    {
        if (t == 1)
        {
            using namespace std::literals::chrono_literals;
            std::chrono::milliseconds ms = 2000ms;
            std::cout << "Thread calling " << std::this_thread::get_id() << " and t = " << t << '\n';
            m1.lock();
            std::this_thread::sleep_for(ms);
            m2.lock();
            x += 1;
            std::this_thread::sleep_for(ms);
        }
        else
        {
            std::cout << "Thread calling " << std::this_thread::get_id() << " and t = " << t << '\n';
            using namespace std::literals::chrono_literals;
            std::chrono::milliseconds ms = 1000ms;
            //std::this_thread::sleep_for(ms);
            m2.lock();
            std::this_thread::sleep_for(ms);
            m1.lock();
            x += 1;
            std::this_thread::sleep_for(ms);
        }
        // std::lock_guard<std::mutex> lockM1(m1);
        // std::lock_guard<std::mutex> lockM2(m2);
        m1.unlock();
        m2.unlock();
    };
    
    void callMyFunc()
    {
        std::thread t1(myfunc, this, 1);
        std::thread t2(myfunc, this, 2);
        t1.join();
        t2.join();
    };

    void printx()
    {
        std::cout << x << '\n';
    };
};