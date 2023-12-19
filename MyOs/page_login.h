#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include "file.h"

namespace Ui {
class page_login;
}

class page_login : public QWidget
{
    Q_OBJECT

public:
    explicit page_login(QWidget *parent = nullptr);
    ~page_login();

private slots:
    void on_btn_login_clicked();

    void on_btn_newusr_clicked();

    void on_btn_exit_clicked();

signals:
     void sendLoginSuccess();

     void sendCreateSuccess();

private:
    Ui::page_login *ui;
};

#endif // PAGE_LOGIN_H
