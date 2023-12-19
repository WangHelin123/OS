#ifndef DISK_H
#define DISK_H
#include <iostream>
#include "file.h"
using namespace  std;

struct disk_node//盘块结构,每块40b
{
    char data[40];
};
typedef struct free_disk//空闲盘区链节点结构
{
    int disk_n;//当前盘区首盘块号
    int length;//盘区长度
    free_disk *next_free;//指向下一盘区首盘块，即下一个链节点
}free_disk;

class Disk
{
public:

    Disk();//构造函数，初始化4kb硬盘
    int Show_file_extent();//显示空闲盘区(文件区)
    int Show_exch_extent();//显示空闲盘区(兑换区)
    void wirte_disk(file *f);//向文件区读入数据
    void read_disk(file *f);//从文件区读出数据
    void delete_f(file *f);//删除文件区数据
    void delete_e(file *f);//删除兑换区数据
    void rewirte_disk(file *f);//更新文件区数据

    disk_node disk_exchange[125];//模拟兑换区
    disk_node disk_file[901];//模拟文件区
    free_disk *free_list=new free_disk;//空闲文件区盘区链,首节点
    free_disk *free_end;//空闲文件区盘区链，尾节点
    free_disk *free_list_e=new free_disk;//空闲兑换区盘区链,首节点
    free_disk *free_end_e;//空闲兑换区盘区链，尾节点
    int disk_file_extent[901];//存放文件区空闲盘块信息的数组，且必须先使用Show函数更新信息
    int disk_exch_extent[125];//存放文件区空闲盘块信息的数组，且必须先使用Show函数更新信息
};

#endif // DISK_H


