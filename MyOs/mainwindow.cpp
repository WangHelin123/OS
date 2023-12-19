#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_path_info->setText(QString::fromStdString("root"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//生成一个线程，判断内存空间是否够，能否执行线程
void MainWindow::mem_thread()
{
    Thread *cur_thread;

    //对线程内容初始化一下

    if(mymemory->leisure_num()>=8)
    {
        win_que.push_back(cur_thread);
//        cur_thread->gen_thread();
    }
    else
    {
        fail_que.push_back(cur_thread);
    }
}

//唤醒线程
void MainWindow::wake_up()
{
//    if(mymemory->leisure_num()>=8)
//    {
//        win_que.push_back(fail_que->front());
//        fail_que->pop_front();
//    }
}


void MainWindow::on_btn_root_clicked()
{
    mydirectory.cur_dir=mydirectory.root_dir;
    mydirectory.path_info.clear();
    update_dir_file();
    update_path_info();
}

void MainWindow::on_btn_back_clicked()
{
    if(mydirectory.cur_dir==mydirectory.root_dir)
    {
        QMessageBox::information(nullptr,"警告","已是根目录");
    }
    else
    {
        mydirectory.path_info.pop_back();
        mydirectory.cur_dir=mydirectory.cur_dir->father;
        update_dir_file();
        update_path_info();
    }
}

void MainWindow::on_btn_newdir_clicked()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    file *add_dir=new file;
    myadd_dir.exec();

    add_dir->name=additem.name;
    add_dir->owner=usrs.back().usr_name;
    add_dir->create_time=current_date.toUtf8().data();
    add_dir->is_file=false;
    add_dir->in_memory=false;
    add_dir->file_size=0;


    int flag=0;
    for(int i=0;i<100;i++)
    {
        if(dir_name[i]==additem.name)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        dir_name[dir_num]=additem.name;
        dir_num++;
        mydirectory.new_dir(add_dir);
    }
    else
    {
        if(yesorno==1)
        {
            QMessageBox::information(nullptr,"警告","名称已经存在，请重新添加");
        }
    }

    update_dir_file();
    update_path_info();
    yesorno=0;


}

void MainWindow::on_btn_newfile_clicked()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    file *add_dir=new file;
    myadd_file.exec();

    add_dir->name=additem.name;
    add_dir->owner=usrs.back().usr_name;
    add_dir->create_time=current_date.toUtf8().data();
    add_dir->file_struct="continuity";
    add_dir->file_size=additem.file_size;
    for(int i=0;i<1000;i++)
    {
        add_dir->file_data[i]=additem.file_data[i];
    }

    add_dir->is_file=true;
    add_dir->in_memory=false;

    int flag=0;
    for(int i=0;i<100;i++)
    {
        if(dir_name[i]==additem.name)
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        dir_name[dir_num]=additem.name;
        dir_num++;
        mydirectory.new_dir(add_dir);
        mydisk.wirte_disk(add_dir);
    }
    else
    {
        if(yesorno==1)
        {
            QMessageBox::information(nullptr,"警告","名称已经存在，请重新添加");
        }
    }

    update_dir_file();
    update_path_info();
    yesorno=0;

}

void MainWindow::on_btn_delete_clicked()
{
//    int i = ui->tableWidget->currentRow();
//    if(i>=0)
//    {
//       QString id = ui->tableWidget->item(i,0)->text();
//       m_ptrhossql->deldoctor(id);
//       dis_doctor();
//       QMessageBox::information(nullptr,"信息","删除成功");
//    }
    int cr=ui->tableWidget->currentRow();
    string cr_name;
    if(cr>=0)
    {
        cr_name=ui->tableWidget->item(cr,1)->text().toUtf8().data(); //目录和文件也不能重名
    }
    file *search_node=mydirectory.cur_dir->firstchild;
    while(search_node->name!=cr_name)
    {
        search_node=search_node->sibling;
    }

    for(int j=0;j<100;j++)
    {
        if(dir_name[j]==search_node->name)
        {
            dir_name[j]="***********";
        }
    }


    if(search_node->is_file)
    {
        if(search_node->in_memory)
        {
            //正在内存中不能删除
            QMessageBox::information(nullptr,"警告","文件正在内存中，删除失败");
        }
        else
        {
            //调用磁盘部分删除数据的函数，传入参数cur_file
            mydisk.delete_f(search_node);

            //调用目录部分删除文件的函数，传入参数cur_file
            mydirectory.delete_dir(search_node);

        }
    }
    else
    {
        //目录下的数据都删除了
        need_del_node=find_del_node(search_node);
        while(!need_del_node.empty())
        {

            file *del_node=new file;
            del_node=need_del_node.back();
            mydisk.delete_f(del_node);
            need_del_node.pop_back();
            delete del_node;
        }


        //只在目录中删掉就行
        mydirectory.delete_dir(search_node);

    }
    update_dir_file();
}

void MainWindow::on_btn_dir_clicked()
{
    file *disp_node=new file;
    disp_node=mydirectory.cur_dir;
    mydis_dir.show();
    mydis_dir.dis_tree(disp_node);
}

void MainWindow::on_btn_mem_clicked()
{    
//    lstr<<"内存块号"<<"是否被使用"<<"使用内存的文件"<<"对应磁盘块号"<<"使用用户";
    int count=0;
    int mem_num;int is_use=0;QString filename;int disk_num;QString usrname;
    for(int i=0;i<64;i++)
    {
        if(mymemory->is_leisure[i]==0)
        {
            is_use=0;
        }
        else
        {
            is_use=1;
        }
        filename=QString::fromStdString(mymemory->mem_state[i].file_in_mem.name);
        mem_num=i;
        disk_num=mymemory->mem_state[i].blc;
        usrname=QString::fromStdString(mymemory->mem_state[i].file_in_mem.owner);
        mydis_mem.add_item(count,mem_num,is_use,filename,disk_num,usrname);
        count++;
    }


    mydis_mem.show();
}

void MainWindow::on_btn_disk_clicked()
{
    mydisk.Show_exch_extent();
    mydisk.Show_file_extent();
    int count_exch=0;
    int count_file=0;

    for(int i=1;i<=150;i++)
    {
        for(int j=1;j<=6;j++)
        {
            if(mydisk.disk_file_extent[count_file+1]==0)
            {
                mydis_disk.dis_file(count_file,i-1,j-1,0);
            }
            else
            {
                mydis_disk.dis_file(count_file,i-1,j-1,1);
            }
            count_file++;
        }
    }

    for(int i=1;i<=21;i++)
    {
        for(int j=1;j<=6;j++)
        {
            if((count_exch+1)>124)
            {
                break;
            }
            if(mydisk.disk_exch_extent[count_exch+1]==0)
            {
                mydis_disk.dis_exch(count_exch,i-1,j-1,0);
            }
            else
            {
                mydis_disk.dis_exch(count_exch,i-1,j-1,1);
            }
            count_exch++;
        }
    }

    mydis_disk.show();
}

void MainWindow::on_btn_exit_clicked()
{
    connect(ui->btn_exit,&QPushButton::clicked,this,&QWidget::close);
}

void MainWindow::on_btn_open_clicked()
{
    int cr=ui->tableWidget->currentRow();
    string cr_name;
    if(cr>=0)
    {
        cr_name=ui->tableWidget->item(cr,1)->text().toUtf8().data(); //目录和文件也不能重名
    }
    file *search_node=mydirectory.cur_dir->firstchild;
    while(search_node->name!=cr_name)
    {
        search_node=search_node->sibling;
    }
    dis_openfile *mydis_openfile=new dis_openfile;
    //多线程，线程阻塞
    if(search_node->is_file)
    {
        int need_e_num=0;
        if(((search_node->file_size)%40)==0)
        {
            need_e_num=(search_node->file_size)/40;
        }
        else
        {
            need_e_num=((search_node->file_size)/40)+1;
        }
        if(mydisk.Show_exch_extent()>=need_e_num)    //对换区未满
        {
            mydisk.read_disk(search_node);      //拷贝到对换区
            Thread *run_thread=new Thread;
            run_thread->cur_file=search_node;
            if(mymemory->leisure_num()>=8)
            {
                mymemory->alloc_mem(run_thread->cur_file);
//                win_que.push_back(run_thread);
                mydis_openfile->flag=1;
                mydis_openfile->show();
                mydis_openfile->init_value(mymemory,&mydisk,search_node);
                mydis_openfile->set_con(search_node);
            }
            else
            {
                fail_que.push_back(run_thread);
                dis_que.push_back(mydis_openfile);
                mydis_openfile->flag=0;
                mydis_openfile->show();
                mydis_openfile->init_value(mymemory,&mydisk,search_node);
                mydis_openfile->set_con(search_node);
            }
        }
        else    //对换区满了
        {
            QMessageBox::information(nullptr,"警告","系统资源不足，请稍后重试");
        }
    }
    else
    {
        mydirectory.cur_dir=search_node;
        mydirectory.path_info.push_back(search_node->name);
        update_dir_file();
        update_path_info();
    }
}

void MainWindow::update_path_info()
{
    string pi="root";
    deque<string> pi_que=mydirectory.path_info;
    unsigned int n=pi_que.size();
    for(unsigned int i=0;i<n;i++)
    {
        pi=pi+" > "+pi_que.front();
        pi_que.pop_front();
    }

    ui->le_path_info->setText(QString::fromStdString(pi));
}

void MainWindow::update_dir_file()
{
    file *dis_cur=new file;
    dis_cur=mydirectory.cur_dir->firstchild;

    ui->tableWidget->setColumnCount(5);
    QStringList lstr;
    lstr<<"    "<<"文件名"<<"文件创建时间"<<"文件大小"<<"文件所有者";
    ui->tableWidget->setHorizontalHeaderLabels(lstr);//表头
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读
    ui->tableWidget->setRowCount(get_dir_num());

    int rcnt=0;
    while(dis_cur!=nullptr)
    {
        QLabel *l=new QLabel();
        if(dis_cur->is_file==false)
        {
            l->setPixmap(QPixmap(":/dir.png"));
        }
        else
        {
            l->setPixmap(QPixmap(":/file.png"));
        }

        l->setAlignment(Qt::AlignHCenter);
        ui->tableWidget->setCellWidget(rcnt,0,l);
        ui->tableWidget->setItem(rcnt,1,new QTableWidgetItem(QString::fromStdString(dis_cur->name)));
        ui->tableWidget->setItem(rcnt,2,new QTableWidgetItem(QString::fromStdString(dis_cur->create_time)));
        ui->tableWidget->setItem(rcnt,3,new QTableWidgetItem(QString::number(dis_cur->file_size)));
        ui->tableWidget->setItem(rcnt,4,new QTableWidgetItem(QString::fromStdString(dis_cur->owner)));

        rcnt++;
        dis_cur=dis_cur->sibling;
    }
}
int MainWindow::get_dir_num()
{
    file *dis_cur=new file;
    dis_cur=mydirectory.cur_dir->firstchild;
    int count=0;
    while(dis_cur!=nullptr)
    {
        count++;
        dis_cur=dis_cur->sibling;
    }
    return count;
}

deque<file*> MainWindow::find_del_node(file *search_node)
{
    deque<file*> re_que;
    deque<file*> que;
    if(search_node!=nullptr)
    {
        que.push_back(search_node);
        while(!que.empty())
        {
            file *lev_node=que.front();
            re_que.push_back(lev_node);
            que.pop_front();
            lev_node=lev_node->firstchild;
            while(lev_node!=nullptr)
            {
                que.push_back(lev_node);
                lev_node=lev_node->sibling;
            }

        }
    }

    return re_que;
}



void MainWindow::on_btn_wake_clicked()
{
    if(!fail_que.empty())
    {
        mymemory->alloc_mem(fail_que.front()->cur_file);

        dis_que.front()->flag=1;
        dis_que.front()->show();
        dis_que.front()->init_value(mymemory,&mydisk,fail_que.front()->cur_file);
        dis_que.front()->set_con(fail_que.front()->cur_file);

//        dis_que.front()->set_con(fail_que.front()->cur_file);

        dis_que.pop_front();
        fail_que.pop_front();
    }
    else
    {
        QMessageBox::information(nullptr,"警告","没有内容等待唤醒");
    }
}
