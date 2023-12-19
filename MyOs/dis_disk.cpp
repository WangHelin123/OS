#include "dis_disk.h"
#include "ui_dis_disk.h"

dis_disk::dis_disk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dis_disk)
{
    ui->setupUi(this);


    ui->tw_file->setColumnCount(6);
    ui->tw_file->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
    ui->tw_file->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读
    ui->tw_file->setRowCount(150);

    ui->tw_exchg->setColumnCount(6);
    ui->tw_exchg->setSelectionBehavior(QAbstractItemView::SelectRows);  //只选中行
    ui->tw_exchg->setEditTriggers(QAbstractItemView::NoEditTriggers);  //只读
    ui->tw_exchg->setRowCount(21);


}

dis_disk::~dis_disk()
{
    delete ui;
}

void dis_disk::dis_file(int count, int row, int com, int flag)
{
    long c=count;
    QString s=QString::number(c,10);
    ui->tw_file->setItem(row,com,new QTableWidgetItem(s));
    if(flag==0)
    {
        ui->tw_file->item(row,com)->setBackground(Qt::green);
    }
    else
    {
        ui->tw_file->item(row,com)->setBackground(Qt::red);
    }
}

void dis_disk::dis_exch(int count, int row, int com, int flag)
{
    long c=count;
    QString s=QString::number(c,10);
    ui->tw_exchg->setItem(row,com,new QTableWidgetItem(s));
    if(flag==0)
    {
        ui->tw_exchg->item(row,com)->setBackground(Qt::green);
    }
    else
    {
        ui->tw_exchg->item(row,com)->setBackground(Qt::red);
    }
}
