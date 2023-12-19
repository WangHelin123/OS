#ifndef CREATE_USR_H
#define CREATE_USR_H

#include "file.h"
#include <QWidget>

namespace Ui {
class create_usr;
}

class create_usr : public QWidget
{
    Q_OBJECT

public:
    explicit create_usr(QWidget *parent = nullptr);
    ~create_usr();

private slots:
    void on_btn_exit_clicked();

    void on_btn_create_clicked();

private:
    Ui::create_usr *ui;
};

#endif // CREATE_USR_H
