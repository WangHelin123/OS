#ifndef ADD_DIR_H
#define ADD_DIR_H

#include <QDialog>
#include "file.h"
namespace Ui {
class add_dir;
}

class add_dir : public QDialog
{
    Q_OBJECT

public:
    explicit add_dir(QWidget *parent = nullptr);
    ~add_dir();



private slots:
    void on_btn_confr_clicked();

private:
    Ui::add_dir *ui;
};

#endif // ADD_DIR_H
