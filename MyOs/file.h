#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <deque>

using namespace std;

struct file
{
    string name; //文件名
    string owner; //文件所有者
    string create_time; //文件创建时间
    string file_struct; //文件结构
    string disk_address; //存放地址
    int file_size; //文件大小
    char file_data[1000]; //文件内容（字符串）
    int start_num; //数据开始盘号
    int start_num_e;//数据开始盘号（兑换区）
    bool is_file; //是否是文件，true则为文件，false则为目录
    bool in_memory; //是否在内存中，true已读入内存，false未读入内存
    //孩子兄弟表示法，sibling指向下一个兄弟，firstchild指向第一个孩子，father指向父节点
    struct file *sibling, *firstchild, *father;
};
struct block
{
    char data[40];
};
struct usr_info
{
    string usr_name;
    string password;
};

extern deque<usr_info> usrs; //建立用户信息
extern file additem;
extern int yesorno;

#endif // FILE_H
