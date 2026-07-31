#pragma once
#include "common.h"
class SizeClass
{
public:
// 整体控制在最多10%
// 左右的内碎⽚浪费
// [1,128]                 8byte对⻬       freelist[0,16) 
// [128+1,1024]            16byte对⻬      freelist[16,72) 
// [1024+1,8*1024]         128byte对⻬     freelist[72,128)         
// [8*1024+1,64*1024]       1024byte对⻬    freelist[128,184)
// [64*1024+1,256*1024]    8*1024byte对⻬  freelist[184,208)
    static inline size_t _RoundUP(size_t size,size_t align_num)
    {
        return (size+align_num-1)&~(align_num-1);
    }
    static inline size_t RoundUP(size_t size)
    {
        if(size<=128)
        {
            return _RoundUP(size,8);
        }
        else if(size<=1024)
        {
            return _RoundUP(size,16);
        }
        else if(size<=8*1024)
        {
            return _RoundUP(size,128);
        }
        else if(size<=64*1024)
        {
            return _RoundUP(size,1024);
        }
        else
        {
            return _RoundUP(size,1024*8);
        }
    }
    static inline size_t _Index(size_t size,size_t align)
    {
        return (size+1<<align-1)>>align-1;
    }
    static inline size_t Index(size_t size)
    {
        static int group_size[5] ={16,56,56,56,24};
         if(size<=128)
        {
            return _Index(size,3);
        }
        else if(size<=1024)
        {
            return _Index(size-128,4)+group_size[0];
        }
        else if(size<=8*1024)
        {
            return _Index(size-1024,7)+group_size[0]+group_size[1];
        }
        else if(size<=64*1024)
        {
            return _Index(size-1024*8,10)+group_size[0]+group_size[1]+group_size[2];
        }
        else
        {
            return _Index(size-1024*64,13)+group_size[0]+group_size[1]+group_size[2]+group_size[3];
        }
    }
};