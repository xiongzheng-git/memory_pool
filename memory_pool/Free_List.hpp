#pragma once 
#include "common.h"
class Free_List
{
public:
    inline void*& NextPtr(void* ptr)
    {
        return *(void**)ptr;
    }
    void push(void* ptr)
    {
        assert(ptr);
        NextPtr(ptr) =_freelist;
        _freelist =ptr;
    }
    void* pop()
    {
        assert(_freelist);
        void* obj =_freelist;
        _freelist =NextPtr(_freelist);
        return obj;
    }
    bool empty()
    {
        return !_freelist;
    }
private:
    void* _freelist =nullptr;//管理被delete的内存空间的自由链表
};