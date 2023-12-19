#ifndef DIS_MEM_H
#define DIS_MEM_H

#include <QWidget>

namespace Ui {
class dis_mem;
}

class dis_mem : public QWidget
{
    Q_OBJECT

public:
    explicit dis_mem(QWidget *parent = nullptr);
    ~dis_mem();

    void add_item(int count,int mem_num,int is_use,QString file_name,int disk_num,QString usrname);

private:
    Ui::dis_mem *ui;
};

#endif // DIS_MEM_H
