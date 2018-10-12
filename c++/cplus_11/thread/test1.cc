#include <stdio.h>

#include <iostream>
#include <thread>

void thread_task()
{
    std::cout << "hello world" << std::endl;
}

int main(int argc, char const* argv[])
{
    std::thread t(thread_task);
    t.join();

    return 0;
}
