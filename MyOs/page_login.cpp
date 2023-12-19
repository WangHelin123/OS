#include "page_login.h"
#include "ui_page_login.h"
#include <QMessageBox>
page_login::page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_login)
{
    ui->setupUi(this);
}

page_login::~page_login()
{
    delete ui;
}

void page_login::on_btn_login_clicked()
{
    unsigned int n=usrs.size();
    int flag=0;
    for(unsigned int i=0;i<n;i++)
    {
        if(usrs.front().usr_name==ui->le_usr->text().toUtf8().data())
        {
            flag=1;
            if(usrs.front().password!=ui->le_password->text().toUtf8().data())
            {
                flag=2;
            }

        }
        usrs.push_back(usrs.front());
        usrs.pop_front();
        if(flag==1)
        {
            break;
        }
    }
    if(flag==0)
    {
        QMessageBox::information(nullptr,"警告","该用户不存在");
    }
    else if(flag==1)
    {
        emit sendLoginSuccess();
        ui->le_usr->clear();
        ui->le_password->clear();
    }
    else
    {
        QMessageBox::information(nullptr,"警告","密码错误");
    }

}

void page_login::on_btn_newusr_clicked()
{
    emit sendCreateSuccess();
}

void __attribute__((noreturn)) page_login::on_btn_exit_clicked()
{
    exit(0);
}
