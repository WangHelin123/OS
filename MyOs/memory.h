#ifndef MEMORY_H
#define MEMORY_H
#include "file.h"
#include <deque>

struct mem_of_file
{
    file file_in_mem;
    deque<int> block_index; //内存块号
    deque<int> block_num; //外存盘块号
};
struct block_mem
{
    int blc=-1;    //盘块号
    int is_protected=0;  //该内存块是否被保护，1为保护，0为未保护
    int mem;
    file file_in_mem;
};

class Memory
{
public:
    Memory();

    //为执行线程获得的文件数据分配8个内存块
    void alloc_mem(file *cur_file);

    //回收内存，执行线程结束后回收其文件数据所占用的内存
    void recl_mem(file *cur_file);

    //为需要分配内存的数据寻找空闲内存块，没有空闲内存时给出提示
    deque<int> find_leisure(int need_size);

    //页表管理，记录页面在内存块对应关系，提供数据块进入模拟内存的访问修改情况
    void page_table();

    //FIFO全局置换
    void FIFO(file *cur_file,int need_num,int cur_num);

    //返回空闲块个数
    int leisure_num();

    //结构体深拷贝
    void mem_deep_copy(mem_of_file *mymem,file *cur_file,deque<int> ql);

    //是否缺页
    bool is_lack(int block_num);

    //找文件
    mem_of_file* find_file(block_mem bm);

    //得到内存块号
    int get_mem_num(int block_num);

    //分配的时候文件大小小于八页，那就按实际的分配，反正也要被其他的用

    //上一页下一页，返回是否缺页（去队列里面查）
        //需要的盘块号队列中有没有，有的话不缺页，没有的话缺页
    //一个64大小结构体数组保存信息：是否被保护，是否被占用，外存盘块号码

    //一个队列，进入的元素是进入内存的页面结构体，先进先出依据

    //每次展示一页的内容

    //是否缺页，如果缺页，是否有空闲，有空闲则分配空闲，入队，无空闲换出再入队；不缺页展示下一页，保护信息转移

    block mem_area[64]; //256B内存空间
    int is_leisure[64]; //标志内存块是否空闲
    block_mem mem_state[64];  //显示所有内存块的状态
    deque<mem_of_file*> page_info;  //文件相关信息
    deque<block_mem> fifo_que;  //先进先出置换

private:


};



#endif // MEMORY_H
