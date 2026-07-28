#pragma once
#include "common.h"
#include "Free_List.hpp"
#include "SizeClass.hpp"
class Thread_Cache
{
public:
    void* Allocate(size_t size)
    {
        assert(size<=MAX_BETYS);
        size_t Align_Size =SizeClass::RoundUP(size);
        size_t Index =SizeClass::Index(size);
        if(list[Index].empty())//nullptr 去central cache申请 
        {

        }
        else
        {
            return list[Index].pop();
        }
        return nullptr;
    }
    void Deallocate(void* ptr,size_t size)
    {
        size_t Index =SizeClass::Index(size);
        list[Index].push(ptr);
    }
private:
    Free_List list[FREE_LIST_SIZE];
};