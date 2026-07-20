#include<iostream>
#include<ctime>
#include<vector>
#define size 128*1024
using std::cout;
using std::endl;

template<class T>
class pool
{
public:
    T* New()
    {
        T* obj =nullptr;
        if(_freelist==nullptr)
        {
            if(_remaining_size<sizeof(T))
            {
                _memory =(char*)std::malloc(size);
                if(_memory==nullptr)
                {
                    throw std::bad_alloc();
                }
                _remaining_size =size;
            }
            obj =(T*)_memory;
            size_t obj_size =sizeof(T)>sizeof(void*)?sizeof(T):sizeof(void*);
            _memory+=obj_size;
            _remaining_size-=obj_size;
        }
        else
        {
            obj =(T*)_freelist;
            _freelist =*(void**)_freelist;
        }
        new (obj)T;//初始化对象
        return obj;
    }
    void Delete(T* ptr)
    {
        ptr->~T();//清理对象

        *(void**)ptr =_freelist;
        _freelist =ptr;

    }
private:
    char* _memory =nullptr;//指向内存块
    size_t _remaining_size =0;//剩余空间大小
    void* _freelist =nullptr;//管理被delete的内存空间的自由链表
};
struct TreeNode
{
    int _val;
    TreeNode* _left;
    TreeNode* _right;
    TreeNode()
        :_val(0)
        , _left(nullptr)
        , _right(nullptr)
    {}
};
void TestObjectPool()
{
    // 申请释放的轮次
    const size_t Rounds = 3;
    // 每轮申请释放多少次
    const size_t N = 100000; 
    size_t begin1 = clock();
    std::vector<TreeNode*> v1;
    v1.reserve(N);
    for (size_t j = 0; j < Rounds; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            v1.push_back(new TreeNode);
        }
        for (int i = 0; i < N; ++i)
        {
            delete v1[i];
        }
        v1.clear();
    }
    size_t end1 = clock();
    pool<TreeNode> TNPool;
    size_t begin2 = clock();
    std::vector<TreeNode*> v2;
    v2.reserve(N);
    for (size_t j = 0; j < Rounds; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            v2.push_back(TNPool.New());
        }
        for (int i = 0; i < N; ++i)
        {
            TNPool.Delete(v2[i]);
        }
        v2.clear();
    }
    size_t end2 = clock();
    cout <<"new cost time:" <<end1 - begin1 << endl;
    cout <<"object pool cost time:" <<end2 - begin2 << endl;
}