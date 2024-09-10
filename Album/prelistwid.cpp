#include "prelistwid.h"
#include <QDebug>
#include "protreeitem.h"
#include "const.h"
#include <QPainter>
#include "prelistitem.h"
#include <QGuiApplication>
PreListWid::PreListWid(QWidget* parent):_global(0),QListWidget(parent),_last_index(17)
{
    this->setViewMode(QListWidget::IconMode); //只展示图标
    this->setIconSize(QSize(PREICON_SIZE,PREICON_SIZE));
    this->setSpacing(5);
    connect(this,&PreListWid::itemPressed,this,&PreListWid::SlotItemPressed);
}

PreListWid::~PreListWid()
{

}

void PreListWid::AddListItem(const QString &path)
{
    QPixmap src_pixmap(path);
    src_pixmap=src_pixmap.scaled(PREICON_SIZE,PREICON_SIZE,Qt::KeepAspectRatio);
    QPixmap dst_pixmap(QSize(PREICON_SIZE,PREICON_SIZE));
    dst_pixmap.fill(QColor(220,220,220,50));
    QPainter painter(&dst_pixmap);
    auto src_width=src_pixmap.width(); //原图的宽
    auto src_height=src_pixmap.height(); //原图的高

    auto dist_width=dst_pixmap.width();
    auto dist_height=dst_pixmap.height();
    auto x=(dist_width-src_width)/2;
    auto y=(dist_height-src_height)/2;
    painter.drawPixmap(x,y,src_pixmap);
    _global++;
    PreListItem * pItem=new PreListItem(QIcon(dst_pixmap),path,_global,this);
    pItem->setSizeHint(QSize(PREITEM_SIZE,PREITEM_SIZE));
    this->addItem(pItem);
    _set_items[path]=pItem; //将item增加到map中
    if(_global==1){
        _pos_origin=this->pos(); //若为第一个图片，存储一下
    }
}

void PreListWid::SlotUpPreList(QTreeWidgetItem *tree_item)
{
    if(!tree_item){
        qDebug()<<"tree_item is empty"<<endl;
        return;
    }

    auto* pro_item=dynamic_cast<ProTreeItem*>(tree_item);
    auto path=pro_item->GetPath();
    auto iter=_set_items.find(path);
    if(iter!=_set_items.end()){  //若item已经存在map中了
        qDebug()<<"path"<<path<<"exists"<<endl;
        return;
    }

    AddListItem(path); //画图

}

void PreListWid::SlotUpSelect(QTreeWidgetItem *tree_item)
{
    if(!tree_item){
        return;
    }

    auto * pro_item=dynamic_cast<ProTreeItem*>(tree_item);
    auto path=pro_item->GetPath();
    auto iter=_set_items.find(path);
    if(iter==_set_items.end()){ //如果item再map中了
        return;
    }


    auto * list_item=dynamic_cast<PreListItem*>(iter.value());
    auto index=list_item->GetIndex(); //获取索引

    if(index>17){  //大于17就翻页
        auto pos_cur=this->pos();
        this->move(pos_cur.x()-(index - _last_index)*100,pos_cur.y());
    }else{
        this->move(_pos_origin);
        _last_index=17;
    }

    this->setCurrentItem(iter.value());
}

void PreListWid::SlotItemPressed(QListWidgetItem *item)
{
    if(QGuiApplication::mouseButtons()!=Qt::LeftButton){
        return;
    }

    auto * list_item=dynamic_cast<PreListItem*>(item);
    auto cur_index=list_item->GetIndex();
    auto path=list_item->GetPath();
    this->setCurrentItem(item);
    emit SigUpSelectShow(path);
}
