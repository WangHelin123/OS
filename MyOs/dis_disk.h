#ifndef DIS_DISK_H
#define DIS_DISK_H

#include <QWidget>

namespace Ui {
class dis_disk;
}

class dis_disk : public QWidget
{
    Q_OBJECT

public:
    explicit dis_disk(QWidget *parent = nullptr);
    ~dis_disk();

    void dis_file(int count,int row,int com,int flag);
    void dis_exch(int count,int row,int com,int flag);
private:
    Ui::dis_disk *ui;
};

#endif // DIS_DISK_H
