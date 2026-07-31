#include"common.h"
#include"ConcurrentAlloc.hpp"

void Alloc1()
{
    for(int i=0;i<5;i++)
    {
        ConcurrentAlloc(9);
    }
}
void Alloc2()
{
    for(int i=0;i<5;i++)
    {
        ConcurrentAlloc(7);
    }
}
int main()
{
    std::thread t1(Alloc1);
    std::thread t2(Alloc2);
    t1.join();
    t2.join();
    return 0;
}