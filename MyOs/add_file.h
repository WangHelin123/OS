#ifndef ADD_FILE_H
#define ADD_FILE_H

#include <QDialog>

namespace Ui {
class add_file;
}

class add_file : public QDialog
{
    Q_OBJECT

public:
    explicit add_file(QWidget *parent = nullptr);
    ~add_file();

private slots:
    void on_btn_confr_clicked();

private:
    Ui::add_file *ui;
};

#endif // ADD_FILE_H
