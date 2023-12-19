#include "directory.h"

Directory::Directory()
{
    root_dir = new file;
    root_dir->father=nullptr;
    root_dir->firstchild=nullptr;
    root_dir->sibling=nullptr;
    root_dir->name="root";
    cur_dir = root_dir;
}


//新建文件
void Directory::new_dir(file *cur_file)
{
    cur_file->firstchild=nullptr;
    cur_file->sibling=nullptr;
    cur_file->father=cur_dir;

    file *search_dir=cur_dir->firstchild;
    if(search_dir==nullptr)
    {
        cur_dir->firstchild=cur_file;
    }
    else
    {
        while(search_dir->sibling!=nullptr)
        {
            search_dir=search_dir->sibling;
        }
        search_dir->sibling=cur_file;
    }

}

//删除目录
void Directory::delete_dir(file *cur_file)
{
    file *search_dir=cur_dir->firstchild;
    if(search_dir==cur_file)
    {
        cur_dir->firstchild=search_dir->sibling;
        search_dir->sibling=nullptr;
        delete search_dir;
    }
    else
    {
        while(search_dir->sibling!=cur_file)
        {
            search_dir=search_dir->sibling;
        }
        search_dir->sibling=cur_file->sibling;
        delete cur_file;
    }
}

//进入某个目录
void Directory::cd(file *cur_file)
{
    cur_dir=cur_file;
    path_info.push_back(cur_file->name);
}

//返回上一级目录
void Directory::cd_back()
{
    cur_dir=cur_dir->father;
    path_info.pop_back();
}
