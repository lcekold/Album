#include "protreeitem.h"
#include "const.h"
ProTreeItem::ProTreeItem(QTreeWidget* view,const QString& name,
                         const QString& path,int type)
    :QTreeWidgetItem(view,type),_path(path),_name(name),_root(this),_pre_item(nullptr),_next_item(nullptr)
{

}

ProTreeItem::ProTreeItem(QTreeWidgetItem* parent,const QString& name,const QString& path,
                         QTreeWidgetItem* root,int type)
    :QTreeWidgetItem(parent,type),_path(path),_name(name),_root(root),_pre_item(nullptr),_next_item(nullptr)
{

}

//获取当前路径
const QString &ProTreeItem::GetPath()
{
    return _path;
}

//获取根目录
QTreeWidgetItem *ProTreeItem::GetRoot()
{
    return _root;
}

//设置前项节点
void ProTreeItem::SetPreItem(QTreeWidgetItem *item)
{
    _pre_item=item;
}

//设置后项节点
void ProTreeItem::SetNextItem(QTreeWidgetItem *item)
{
    _next_item = item;
}

ProTreeItem *ProTreeItem::GetPreItem()
{
    return dynamic_cast<ProTreeItem*>(_pre_item);
}

ProTreeItem *ProTreeItem::GetNextItem()
{
    return dynamic_cast<ProTreeItem*>(_next_item);
}

ProTreeItem *ProTreeItem::GetLastPicChild()
{
    if(this->type()==TreeItemPic){ //如果是图片类型
        return nullptr;
    }
    auto child_count=this->childCount();
    if(child_count==0){ //若子节点为0
        return nullptr;
    }

    for(int i = child_count-1;i>=0;i--){
        auto * last_child=this->child(i);
        auto * last_tree_item=dynamic_cast<ProTreeItem*>(last_child);
        int item_type=last_tree_item->type(); //得到这个item的类型
        if(item_type==TreeItemPic){ //若该项是图片，说明找到最后一个节点了
            return last_tree_item;
        }
        //如果是文件夹
        last_child=last_tree_item->GetLastPicChild(); //递归调用
        if(!last_child){  //如果没有找到最后一个节点
            continue;
        }
        last_tree_item=dynamic_cast<ProTreeItem*>(last_child);
        return last_tree_item; //找到最后一个孩子了，就返回
    }

    return nullptr; //实在找不到了，返回空
}

ProTreeItem *ProTreeItem::GetFirstPicChild()
{
    if(this->type()==TreeItemPic){ //若为图片类型，不存在子节点
        return nullptr;
    }

    auto child_count=this->childCount(); //获取字节点的数量
    if(child_count==0){
        return nullptr;
    }

    for(int i=0;i<child_count-1;i++){
        auto * first_child=this->child(i);
        auto * first_tree_child=dynamic_cast<ProTreeItem*>(first_child);
        auto item_type=first_tree_child->type();
        if(item_type==TreeItemPic){
            return first_tree_child;
        }

        first_child = first_tree_child->GetFirstPicChild();
        if(!first_child){
            continue;
        }

        first_tree_child=dynamic_cast<ProTreeItem*>(first_child);
        return first_tree_child;
    }
    return nullptr;
}
