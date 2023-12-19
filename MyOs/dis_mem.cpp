#include "dis_mem.h"
#include "ui_dis_mem.h"

dis_mem::dis_mem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dis_mem)
{
    ui->setupUi(this);


    ui->tableWidget->setColumnCount(5);
    QStringList lstr;
    lstr<<"内存块号"<<"是否被使用"<<"使用内存的文件"<<"对应磁盘块号"<<"使用用户";
    ui->tableWidget->setHorizontalHeaderLabels(lstr);//表头
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读
    ui->tableWidget->setRowCount(64);
}

dis_mem::~dis_mem()
{
    delete ui;
}

void dis_mem::add_item(int count,int mem_num, int is_use, QString file_name, int disk_num, QString usrname)
{
    long x=mem_num;
    QString a=QString::number(x,10);
    x=disk_num;
    QString c=QString::number(x,10);
    QString b;
    if(is_use==0)
    {
        b=QString::fromUtf8("否");
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(""));
        ui->tableWidget->setItem(count,4,new QTableWidgetItem(""));
    }
    else
    {
        b=QString::fromUtf8("是");
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(file_name));
        ui->tableWidget->setItem(count,4,new QTableWidgetItem(usrname));
    }
    ui->tableWidget->setItem(count,0,new QTableWidgetItem(a));
    ui->tableWidget->setItem(count,1,new QTableWidgetItem(b));

    ui->tableWidget->setItem(count,3,new QTableWidgetItem(c));

}
