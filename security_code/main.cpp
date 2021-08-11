// deadlocks
#include <iostream>
#include <memory>
#include "deadlocks.hpp"

int main()
{
    DeadLock dl;
    dl.callMyFunc(); // will reproduce a deadlock
    dl.printx();
}