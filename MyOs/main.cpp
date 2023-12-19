#include "mainwindow.h"
#include "disk.h"
#include "page_login.h"
#include "create_usr.h"
#include <QApplication>
#include "memory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    usr_info *init_usr=new usr_info;
    init_usr->usr_name="1";
    init_usr->password="1";
    usrs.push_back(*init_usr);

    yesorno=0;

    MainWindow w;
    page_login login;
    create_usr c;
    login.show();
    auto f1 = [&]()
    {
        w.show();
    };
    auto f2 = [&]()
    {
        c.show();
    };
    w.connect(&login,&page_login::sendLoginSuccess,&w,f1);
    c.connect(&login,&page_login::sendCreateSuccess,&c,f2);
    return a.exec();

}
