#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "file.h"
#include <deque>
class Directory
{
public:
    Directory();

    //新建目录
    void new_dir(file *cur_file);

    //删除目录
    void delete_dir(file *cur_file);

    //进入某个目录
    void cd(file *cur_file);

    //返回上一级目录
    void cd_back();



    deque<string> path_info;    //路径信息
    file *root_dir;
    file *cur_dir;
};

#endif // DIRECTORY_H
