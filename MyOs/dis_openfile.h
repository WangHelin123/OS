#ifndef DIS_OPENFILE_H
#define DIS_OPENFILE_H

#include <QWidget>
#include "file.h"
#include <QCloseEvent>
#include "memory.h"
#include "disk.h"
#include "thread.h"
//#include "use_que.h"
namespace Ui {
class dis_openfile;
}

class dis_openfile : public QWidget
{
    Q_OBJECT

public:
    explicit dis_openfile(QWidget *parent = nullptr);
    ~dis_openfile();
    void closeEvent(QCloseEvent *);

    void set_con(file *cur_file);

    void init_value(Memory *m,Disk *d,file *search_node);

    int flag=0;
    Memory *myme=new Memory;
    Disk *mydi=new Disk;
    file *cur_file=new file;
    int all_page;
    int cur_page;

private slots:
    void on_btn_pre_clicked();

    void on_btn_next_clicked();

    void on_btn_update_clicked();



private:
    Ui::dis_openfile *ui;
};

#endif // DIS_OPENFILE_H
