#ifndef OPENTREETHREAD_H
#define OPENTREETHREAD_H

#include <QThread>
#include<QTreeWidget>
class OpenTreeThread : public QThread
{
    Q_OBJECT
public:
    //源路径，文件数，属于哪个Treewidget
    explicit OpenTreeThread(const QString&src_path,int file_count,
                            QTreeWidget* self,QObject *parent = nullptr);
    void OpenProTree(const QString& src_path,int &file_count,QTreeWidget* self);
protected:
    virtual void run();
private:
    //递归创建目录树的函数
    void RecursiveProTree(const QString& src_path,int &file_count,QTreeWidget* self,
                          QTreeWidgetItem*root,QTreeWidgetItem* parent,QTreeWidgetItem* preitem);

    QString _src_path; //源路径
    int _file_count;  //导入多少文件的数量
    QTreeWidget* _self;
    bool _bstop; //控制是否停止
    QTreeWidgetItem * _root;//根节点
signals:
    void SigFinshProgress(int); //完成的时候发送信号
    void SigUpdateProgress(int); //通知对话框更新

public slots:
    void SlotCancelProgress();
};

#endif // OPENTREETHREAD_H
