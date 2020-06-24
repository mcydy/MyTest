#include <thread>
#include <mutex>
#include <iostream>

/** 互斥量
*/
static std::mutex s_mutexA;
static std::mutex s_mutexB;

void FunA()
{
    s_mutexA.lock();
    // 为了让B线程能够先获得s_mutexB
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"funA get s_mutexB"<<std::endl;
    s_mutexB.lock();
    std::cout<<"funA here"<<std::endl;

    // 运行不到这里
    s_mutexB.unlock();
    s_mutexA.unlock();
}

void FunB()
{
    s_mutexB.lock();
    // 为了让A线程能够先获得s_mutexA
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"funB get s_mutexA"<<std::endl;
    s_mutexA.lock();
    std::cout<<"funB here"<<std::endl;

    // 运行不到这里
    s_mutexA.unlock();
    s_mutexB.unlock();
}

int main()
{
    std::thread A(FunA);
    std::thread B(FunB);
    getchar();
    return 1;
}