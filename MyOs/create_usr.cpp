#include "create_usr.h"
#include "ui_create_usr.h"
#include <QMessageBox>
create_usr::create_usr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_usr)
{
    ui->setupUi(this);
}

create_usr::~create_usr()
{
    delete ui;
}

void create_usr::on_btn_exit_clicked()
{
    this->hide();

}

void create_usr::on_btn_create_clicked()
{
    string name;
    string password;
    string confirm;

    name=ui->le_usr->text().toUtf8().data();
    password=ui->le_password->text().toUtf8().data();
    confirm=ui->le_confirm->text().toUtf8().data();

    unsigned int n=usrs.size();
    int flag=0;

    for(unsigned int i=0;i<n;i++)
    {
        if(name==usrs.front().usr_name)
        {
            flag=1;
        }
        usrs.push_back(usrs.front());
        usrs.pop_front();
    }

    if(flag==0)
    {
        if(confirm!=password)
        {
            QMessageBox::information(nullptr,"警告","两次密码输入不一致，请重新输入");
        }
        else
        {
            usr_info *myusr=new usr_info;
            myusr->usr_name=name;
            myusr->password=password;
            usrs.push_back(*myusr);
            QMessageBox::information(nullptr,"提示","创建成功，您可以选择继续创建或者退出");
            ui->le_usr->clear();
            ui->le_confirm->clear();
            ui->le_password->clear();
//            connect(ui->btn_create,&QPushButton::clicked,this,&QWidget::close);
        }
    }
    else
    {
        QMessageBox::information(nullptr,"警告","该用户已存在，请重新输入用户名");
//        connect(ui->btn_create,&QPushButton::clicked,this,&QWidget::close);
    }

}
