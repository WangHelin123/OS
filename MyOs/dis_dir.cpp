#include "dis_dir.h"
#include "ui_dis_dir.h"

dis_dir::dis_dir(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dis_dir)
{
    ui->setupUi(this);

    ui->treeWidget->clear();    //QTreeWidget清空
    ui->treeWidget->setFrameStyle(QFrame::NoFrame);  //框架样式
    ui->treeWidget->setHeaderLabel("目录结构");  //设置头的标题
    ui->treeWidget->setHeaderHidden(true);     //tree widget头标题是否显示,此处隐藏标题
    ui->treeWidget->setColumnCount(1);    //tree widget展示的列数
//    Global_item->setIcon(0, QIcon(":/new/prefix1/image/begintesting.png")); //为节点添加图标

}

dis_dir::~dis_dir()
{
    delete ui;
}

void dis_dir::closeEvent(QCloseEvent *)
{
    ui->treeWidget->clear();
}

void dis_dir::dis_tree(file *cur_node)
{
    //添加顶层节点
    QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->treeWidget);
    topItem->setText(0,QString::fromStdString(cur_node->name));
    ui->treeWidget->addTopLevelItem(topItem);
    father_node=topItem;
    top_node=topItem;
    level_trav(cur_node);
    ui->treeWidget->expandAll();
}

void dis_dir::level_trav(file *cur_node)
{
    deque<QTreeWidgetItem*> tree_que;
    deque<file*> que;
    tree_que.push_back(father_node);
    que.push_back(cur_node);
    while(!que.empty())
    {
        file *lev_node=que.front();

        father_node=tree_que.front();
        tree_que.pop_front();
        que.pop_front();
        lev_node=lev_node->firstchild;
        while(lev_node!=nullptr)
        {
            QStringList ql;
            ql<<QString::fromStdString(lev_node->name);
            QTreeWidgetItem * addnode=new QTreeWidgetItem(ql);
            father_node->addChild(addnode);

            tree_que.push_back(addnode);
            que.push_back(lev_node);
            lev_node=lev_node->sibling;
        }

    }
}
