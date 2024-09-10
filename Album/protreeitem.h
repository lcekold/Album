#ifndef PROTREEITEM_H
#define PROTREEITEM_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
///////////////   重写Item
class ProTreeItem : public QTreeWidgetItem
{
public:
    ProTreeItem(QTreeWidget* view,const QString& name,const QString& path,int type=Type);
    ProTreeItem(QTreeWidgetItem* parent,const QString& name,const QString& path,
                QTreeWidgetItem* root,int type=Type);

    const QString& GetPath();  //获取路径
    QTreeWidgetItem* GetRoot();
    void SetPreItem(QTreeWidgetItem * item); //前项节点
    void SetNextItem(QTreeWidgetItem * item);
    ProTreeItem* GetPreItem();//获取前一个节点
    ProTreeItem* GetNextItem(); //获取后一个节点
    ProTreeItem* GetLastPicChild();//返回最后一个孩子节点
    ProTreeItem* GetFirstPicChild(); //获取第一个孩子的图片节点
private:
    QString _path;
    QString _name;
    QTreeWidgetItem * _root; //存储根节点
    QTreeWidgetItem * _pre_item;  // 存储前一个节点（可以使用链表实现）
    QTreeWidgetItem * _next_item; //存储后一个节点
};

#endif // PROTREEITEM_H
