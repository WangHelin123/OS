#include "thread.h"

Thread::Thread()
{

}

//数据生成线程
    //得到文件数据和文件其他信息
    //分配到磁盘中
    //目录中创建目录项
//void Thread::gen_thread()
//{
//    if(cur_file->is_file)
//    {
//        //调用磁盘部分函数，传入参数cur_file，将文件存入磁盘
//    }

//    mydirectory.new_dir(cur_file);
//}

//删除数据线程
    //在目录中删除
    //在磁盘上删除
//void Thread::del_thread()
//{
//    if(cur_file->is_file)
//    {
//        if(cur_file->in_memory)
//        {
//            //正在内存中不能删除
//        }
//        else
//        {
//            //调用磁盘部分删除数据的函数，传入参数cur_file

//            //调用目录部分删除文件的函数，传入参数cur_file
//            mydirectory.delete_dir(cur_file);
//        }
//    }
//    else
//    {
//        //只在目录中删掉就行
//        mydirectory.delete_dir(cur_file);
//    }
//}

//执行线程
    //数据调入内存
void Thread::run_thread()
{
    //调用磁盘部分函数，将文件从文件区换到对换区

//    mymemory.alloc_mem(cur_file);//为文件分配内存

}

//执行换页函数
void Thread::run_fifo(int need_num,int cur_num)
{
//    mymemory.FIFO(cur_file,need_num,cur_num);
}

//调出内存
void Thread::move_out()
{
//    mymemory.recl_mem(cur_file); //回收内存

    //调用磁盘部分函数，如果文件被事先放到了对换区，那么需要将对换区该部分内容清除，变为空闲；
    //如果没放到文件区，函数无需操作
}
