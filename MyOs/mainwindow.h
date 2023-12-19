#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <deque>
#include "thread.h"
#include "file.h"
#include "memory.h"
#include "disk.h"
#include "directory.h"
#include "add_dir.h"
#include "add_file.h"
#include "dis_disk.h"
#include "dis_mem.h"
#include "dis_dir.h"
#include "dis_openfile.h"
//#include "use_que.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    //生成一个线程，判断能否进入内存
    void mem_thread();

    //唤醒的函数
    void wake_up();

    void update_path_info(); //刷新目录路径显示

    void update_dir_file(); //刷新主界面

    int get_dir_num(); //得到当前目录下目录项个数

    deque<file*> find_del_node(file *search_node); //找到所有需要删除的结点



    Memory *mymemory=new Memory;
    Disk mydisk;
    Directory mydirectory;
    deque<Thread*> fail_que; //存放线程的阻塞队列
    deque<dis_openfile*> dis_que;
    deque<Thread*> win_que; //成功进入内存的线程
    deque<file*> need_del_node;
    dis_disk mydis_disk; //显示外存信息
    dis_mem mydis_mem; //显示内存信息
    dis_dir mydis_dir; //显示当前目录结构


    string dir_name[100]; //目录名
    int dir_num=0; //目录数量

private slots:
    void on_btn_root_clicked(); //返回根目录

    void on_btn_back_clicked(); //返回上一级目录

    void on_btn_newdir_clicked(); //新建空目录

    void on_btn_newfile_clicked(); //新建文件

    void on_btn_delete_clicked(); //删除

    void on_btn_dir_clicked(); //展示该目录下目录结构

    void on_btn_mem_clicked(); //展示内存

    void on_btn_disk_clicked(); //展示外存磁盘

    void on_btn_exit_clicked(); //退出

    void on_btn_open_clicked(); //打开文件

                                //重命名






    void on_btn_wake_clicked();

private:
    Ui::MainWindow *ui;

    add_dir myadd_dir;
    add_file myadd_file;




};
#endif // MAINWINDOW_H
