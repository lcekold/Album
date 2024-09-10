#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QThread>
#include "protreeitem.h"
#include <QTreeWidget>
/////线程中实现文件的复制和显示，即在目录树当中显示
class ProTreeThread : public QThread
{
    Q_OBJECT
public:
    explicit ProTreeThread(const QString &src_path,const QString& dist_path,QTreeWidgetItem* parent_item,
                           int file_count,QTreeWidget* self,QTreeWidgetItem* root,QObject* parent=nullptr);
    ~ProTreeThread();
protected:
    virtual void run();
private:
    void CreateProTree(const QString& src_path,const QString& dist_path,QTreeWidgetItem* parent_item
                       ,int &file_count,QTreeWidget* self,QTreeWidgetItem* root,QTreeWidgetItem* preItem=nullptr);//源路径，目的路径,父节点,self是左侧的整个树形界面

    QString _src_path; //原路径
    QString _dist_path;
    int _file_count;
    QTreeWidgetItem* _parent_item;  //当前节点的父节点
    QTreeWidget* _self;  //当前节点所在的widget
    QTreeWidgetItem* _root; //根节点
    bool _bstop; //控制线程退出的bool变量
public slots:
    void SlotCancelProgress();
signals:
    void SigUpdateProgress(int); //更新进度的信号
    void SigFinishProgress(int);  //完成之后发送的信号
};

#endif // PROTREETHREAD_H
