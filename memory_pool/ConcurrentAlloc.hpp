#include "common.h"
#include "Thread_Cache.hpp"
static void* ConcurrentAlloc(size_t size)
{   
    if(PThread_Cache_TLS==nullptr)
    {
        PThread_Cache_TLS = new Thread_Cache;
    }
    cout<<std::this_thread::get_id()<<":"<<PThread_Cache_TLS<<endl;

    return PThread_Cache_TLS->Allocate(size);
}
static void ConcurrentFree(void* ptr,size_t size)
{
    cout<<std::this_thread::get_id()<<":"<<PThread_Cache_TLS<<endl;
    assert(PThread_Cache_TLS);
    PThread_Cache_TLS->Deallocate(ptr,size);
}