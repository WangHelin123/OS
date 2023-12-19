#include "dis_openfile.h"
#include "ui_dis_openfile.h"
#include "memory.h"
#include <QMessageBox>
dis_openfile::dis_openfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dis_openfile)
{
    ui->setupUi(this);
}

dis_openfile::~dis_openfile()
{
    delete ui;
}

void dis_openfile::closeEvent(QCloseEvent *)
{
    ui->te_con->clear();
    ui->tableWidget->clear();
    //关闭文件了，撤销内存，唤醒
    mydi->delete_e(cur_file); //删除对换区相对应的数据
    myme->recl_mem(cur_file); //回收内存
//    if(!fail_que.empty())
//    {

//        dis_que.front()->set_con(fail_que.front()->cur_file);

//        dis_que.pop_front();
//        fail_que.pop_front();
//    }

}

void dis_openfile::set_con(file *cur_file)
{
    cur_page=1;
    ui->label_filename->setText(QString::fromStdString("文件名："+cur_file->name));
    if(flag==1)
    {
        //将该显示的显示上去
        QString str;
        char c[40];
        for(int i=0;i<40;i++)
        {
            c[i]=' ';
        }
        for(int i=0;i<min(cur_file->file_size,40);i++)
        {
            c[i]=cur_file->file_data[i];

        }
        str=QString::fromLocal8Bit(c,40);
        ui->te_con->setText(str);
        str.clear();
        ui->tableWidget->setColumnCount(4);
        QStringList lstr;
        lstr<<"页号"<<"是否在内存中"<<"磁盘块号"<<"分配内存块号";
        ui->tableWidget->setHorizontalHeaderLabels(lstr);//表头
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读
        int setrow=0;
        if(((cur_file->file_size)%40)==0)
        {
            setrow=(cur_file->file_size)/40;
        }
        else
        {
            setrow=((cur_file->file_size)/40)+1;
        }
        all_page=setrow;    //当前访问号码
        ui->tableWidget->setRowCount(setrow);

        mem_of_file *cur_info=myme->page_info.front();
        unsigned int n=myme->page_info.size();
        for(unsigned int i=0;i<n;i++)
        {
            if((cur_info->file_in_mem.name==cur_file->name)&&(cur_info->file_in_mem.start_num=cur_file->start_num))
            {
                cur_info=myme->page_info.front();
            }
            myme->page_info.push_back(myme->page_info.front());
            myme->page_info.pop_front();
        }

        for(int i=0;i<setrow;i++)
        {
            long x=i;
            QString a=QString::number(x,10);
            long y=cur_file->start_num+i;
            QString b=QString::number(y,10);
            int flag=0;

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(a));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(b));

            long mem_number=-1;
            for(int j=0;j<64;j++)
            {
                if(myme->mem_state[j].blc==(cur_file->start_num+i))
                {
                    flag=1;
                    mem_number=myme->mem_state[j].mem;
                }
            }
            QString c=QString::number(mem_number,10);
            if(flag==0)
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("否")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
            else
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("是")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
        }

    }
    else
    {
        ui->te_con->setText(QString::fromStdString("系统繁忙，正在尝试打开文件，请等待"));
        ui->te_con->setAlignment(Qt::AlignCenter);
        ui->te_con->setFont(QFont("宋体",12));
    }
}

void dis_openfile::init_value(Memory *m, Disk *d,file* search_node)
{
    myme=m;
    mydi=d;
    cur_file=search_node;
//    fail_que=que1;
//    dis_que=que2;
}

void dis_openfile::on_btn_pre_clicked()
{
    if(cur_page==1)
    {
        QMessageBox::information(nullptr,"警告","已经是第一页");
    }
    else
    {
        int need_num;int cur_num;
        cur_num=cur_page+cur_file->start_num-1;
        need_num=cur_num-1;
        cur_page--;
        myme->FIFO(cur_file,need_num,cur_num);
        //显示问题正确显示就行
        char c[40];
        for(int i=0;i<40;i++)
        {
            c[i]=' ';
        }
        QString str;
        for(int i=0;i<40;i++)
        {
            c[i]=cur_file->file_data[40*(cur_page-1)+i];
        }
        str=QString::fromLocal8Bit(c,40);
        ui->te_con->setText(str);
        str.clear();
        ui->tableWidget->setColumnCount(4);
        QStringList lstr;
        lstr<<"页号"<<"是否在内存中"<<"磁盘块号"<<"分配内存块号";
        ui->tableWidget->setHorizontalHeaderLabels(lstr);//表头
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读

        ui->tableWidget->setRowCount(all_page);

        mem_of_file *cur_info=myme->page_info.front();
        unsigned int n=myme->page_info.size();
        for(unsigned int i=0;i<n;i++)
        {
            if((cur_info->file_in_mem.name==cur_file->name)&&(cur_info->file_in_mem.start_num=cur_file->start_num))
            {
                cur_info=myme->page_info.front();
            }
            myme->page_info.push_back(myme->page_info.front());
            myme->page_info.pop_front();
        }

        for(int i=0;i<all_page;i++)
        {
            long x=i;
            QString a=QString::number(x,10);
            long y=cur_file->start_num+i;
            QString b=QString::number(y,10);
            int flag=0;

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(a));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(b));

            long mem_number=-1;
            for(int j=0;j<64;j++)
            {
                if(myme->mem_state[j].blc==(cur_file->start_num+i))
                {
                    flag=1;
                    mem_number=myme->mem_state[j].mem;
                }
            }
            QString c=QString::number(mem_number,10);
            if(flag==0)
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("否")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
            else
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("是")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
        }


    }



}

void dis_openfile::on_btn_next_clicked()
{

    if(cur_page==all_page)
    {
        QMessageBox::information(nullptr,"警告","已经是最后一页");
    }
    else
    {
        int need_num;int cur_num;
        cur_num=cur_page+cur_file->start_num-1;
        need_num=cur_num+1;
        cur_page++;
        myme->FIFO(cur_file,need_num,cur_num);
        //显示问题正确显示就行
        char c[40];
        for(int i=0;i<40;i++)
        {
            c[i]=' ';
        }
        QString str;
        for(int i=0;i<40;i++)
        {
            c[i]=cur_file->file_data[40*(cur_page-1)+i];
        }
        str=QString::fromLocal8Bit(c,40);
        ui->te_con->setText(str);

        ui->tableWidget->setColumnCount(4);
        QStringList lstr;
        lstr<<"页号"<<"是否在内存中"<<"磁盘块号"<<"分配内存块号";
        ui->tableWidget->setHorizontalHeaderLabels(lstr);//表头
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读

        ui->tableWidget->setRowCount(all_page);

        mem_of_file *cur_info=myme->page_info.front();
        unsigned int n=myme->page_info.size();
        for(unsigned int i=0;i<n;i++)
        {
            if((cur_info->file_in_mem.name==cur_file->name)&&(cur_info->file_in_mem.start_num=cur_file->start_num))
            {
                cur_info=myme->page_info.front();
            }
            myme->page_info.push_back(myme->page_info.front());
            myme->page_info.pop_front();
        }

        for(int i=0;i<all_page;i++)
        {
            long x=i;
            QString a=QString::number(x,10);
            long y=cur_file->start_num+i;
            QString b=QString::number(y,10);
            int flag=0;

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(a));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(b));

            long mem_number=-1;
            for(int j=0;j<64;j++)
            {
                if(myme->mem_state[j].blc==(cur_file->start_num+i))
                {
                    flag=1;
                    mem_number=myme->mem_state[j].mem;
                }
            }
            QString c=QString::number(mem_number,10);
            if(flag==0)
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("否")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
            else
            {
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString("是")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(c));
            }
        }
    }


}


void dis_openfile::on_btn_update_clicked()
{
    QString text=ui->te_con->toPlainText();
    char *ch;
    ch=text.toLatin1().data();
    for(int i=0;i<40;i++)
    {
        cur_file->file_data[40*(cur_page-1)+i]=ch[i];
    }

    //告诉开始盘块和文件指针，覆盖原来的数据
    mydi->rewirte_disk(cur_file);
    QMessageBox::information(nullptr,"提示","修改成功");
}
