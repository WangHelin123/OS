#include "add_file.h"
#include "ui_add_file.h"
#include "file.h"
add_file::add_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_file)
{
    ui->setupUi(this);
}

add_file::~add_file()
{
    delete ui;
}

void add_file::on_btn_confr_clicked()
{
    additem.name=ui->le_filename->text().toUtf8().data();
    QString text=ui->te_filecon->toPlainText();
    additem.file_size=text.length();
    char *ch;
    ch=text.toLatin1().data();
    for(int i=0;i<text.length();i++)
    {
        additem.file_data[i]=ch[i];
    }

    this->hide();
    ui->le_filename->clear();
    ui->te_filecon->clear();
    yesorno=1;
}
