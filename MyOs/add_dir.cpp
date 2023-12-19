#include "add_dir.h"
#include "ui_add_dir.h"
#include <QMessageBox>
add_dir::add_dir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_dir)
{
    ui->setupUi(this);
}

add_dir::~add_dir()
{
    delete ui;
}

void add_dir::on_btn_confr_clicked()
{
    additem.name=ui->le_dirname->text().toUtf8().data();
    this->hide();
    ui->le_dirname->clear();
    yesorno=1;
}
