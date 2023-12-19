#ifndef DIS_DIR_H
#define DIS_DIR_H

#include <QWidget>
#include "file.h"
#include <QTreeWidget>
#include <deque>
#include <QCloseEvent>
namespace Ui {
class dis_dir;
}

class dis_dir : public QWidget
{
    Q_OBJECT

public:
    explicit dis_dir(QWidget *parent = nullptr);
    ~dis_dir();

    void closeEvent(QCloseEvent *);

    void dis_tree(file *cur_node);

    void level_trav(file *cur_node);

    QTreeWidgetItem *father_node;
    QTreeWidgetItem *top_node;

private:
    Ui::dis_dir *ui;
};

#endif // DIS_DIR_H
