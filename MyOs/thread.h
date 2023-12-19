#ifndef THREAD_H
#define THREAD_H
#include "file.h"
#include "memory.h"
#include "disk.h"
#include "directory.h"
#include <deque>
class Thread
{
public:
    Thread();

    //数据生成线程
        //得到文件数据和文件其他信息
        //分配到磁盘中
        //目录中创建目录项
    void gen_thread();

    //删除数据线程
        //在目录中删除
        //在磁盘上删除
    void del_thread();

    //执行线程
        //数据调入内存
    void run_thread();

    //执行换页函数
    void run_fifo(int need_num,int cur_num);

    //调出内存
    void move_out();


    file *cur_file;



private:


};

#endif // THREAD_H
