#include "picanimationwid.h"
#include <QTimer>
#include "protreeitem.h"
#include <QPainter>
PicAnimationWid::PicAnimationWid(QWidget *parent)
    : QWidget{parent},_factor(0.0),_cur_item(nullptr),_b_start(false)
{
    _timer=new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&PicAnimationWid::TimeOut); //定时器到达终点后要执行的操作
}

PicAnimationWid::~PicAnimationWid()
{

}


//显示图片函数
void PicAnimationWid::SetPixmap(QTreeWidgetItem *item)
{
    if(!item){
        return;
    }

    auto * tree_item=dynamic_cast<ProTreeItem*>(item);
    auto path=tree_item->GetPath();
    _pixmap1.load(path);
    _cur_item=tree_item;

    if(_map_items.find(path)==_map_items.end()){ //若item曾经没有被显示过
        _map_items[path]=tree_item;
        //发送更新预览列表逻辑
        emit SigUpPreList(item);
    }

    emit SigSelectItem(item);

    auto * next_item=tree_item->GetNextItem();
    if(!next_item){
        return;
    }

    auto next_path=next_item->GetPath();
    _pixmap2.load(next_path);
    if(_map_items.find(next_path)==_map_items.end()){ //若item曾经没有被显示过
        _map_items[next_path]=next_item;
        //发送更新预览列表逻辑
        emit SigUpPreList(next_item);
    }
}

void PicAnimationWid::Start()
{
    emit SigStart(); //开始播放
    emit SigStartMusic(); //开始音乐
    _factor=0;
    _timer->start(25); //每隔25ms做一次更新
    _b_start=true;

}

void PicAnimationWid::Stop()
{
    emit SigStop(); //停止播放
    emit SigStopMusic(); //停止音乐
    _timer->stop(); //定时器停止
    _factor=0;
    _b_start=false;
}

void PicAnimationWid::SlideNext()
{
    Stop();
    if(!_cur_item){
        return;
    }

    auto * cur_pro_item=dynamic_cast<ProTreeItem*>(_cur_item);
    auto * next_item=cur_pro_item->GetNextItem(); //获取下一个Item
    if(!next_item){
        return;
    }
    SetPixmap(next_item);
    update();
}

void PicAnimationWid::SlidePre()
{
    Stop();
    if(!_cur_item){
        return;
    }
    auto * cur_pro_item=dynamic_cast<ProTreeItem*>(_cur_item);
    auto * pre_item=cur_pro_item->GetPreItem(); //获取前一个item
    if(!pre_item){
        return;
    }
    SetPixmap(pre_item);
    update();
}

void PicAnimationWid::paintEvent(QPaintEvent *event)
{
    if(_pixmap1.isNull()){
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true); //设置抗锯齿渲染效果，使绘制的图形边缘更加平滑
    QRect rect=geometry(); //获取当前控件的几何位置（位置和大小）l
    int w=rect.width();
    int h=rect.height();
    _pixmap1=_pixmap1.scaled(w,h,Qt::KeepAspectRatio); //将——pixmap1按比例缩放到控件的大小
    int alpha=255*(1.0f-_factor); //计算透明度，0表示完全透明，255表示完全不透明
    QPixmap alphaPixmap(_pixmap1.size());  //创建一个新的QPixmap对象alphaPixmap，大小与_pixmap1相同
    alphaPixmap.fill(Qt::transparent); //将alohaPixmap填充为透明

    QPainter p1(&alphaPixmap);  //创建一个新的对象p1，用于在alphaPixmap上绘制,p1负责画这个透明图片，实现图1的逐渐消失的效果
    p1.setCompositionMode(QPainter::CompositionMode_Source); //设置p1的组合模式为元模式，这意味着后续的绘制操作将直接在目标上应用
    p1.drawPixmap(0,0,_pixmap1);  //在alphaPixmap上绘制_pixmap1
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);  //设置p1的组合模式为目标模式，这意味着后续的绘制操作将与目标进行混合。
    p1.fillRect(alphaPixmap.rect(),QColor(0,0,0,alpha)); //在alphaPixmap上填充一个矩形，颜色为黑色，透明度为alpha。这将使_pixmap1逐渐变得透明。
    p1.end();//结束p1的绘制操作。

    int x=(w-_pixmap1.width())/2;
    int y=(h-_pixmap1.height())/2;
    painter.drawPixmap(x,y,alphaPixmap);

    if(_pixmap2.isNull()){
        return;
    }

    _pixmap2=_pixmap2.scaled(w,h,Qt::KeepAspectRatio);
    alpha=255*(_factor);
    QPixmap alphaPixmap2(_pixmap2.size());
    alphaPixmap2.fill(Qt::transparent);
    QPainter p2(&alphaPixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0,0,_pixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(alphaPixmap2.rect(),QColor(0,0,0,alpha)); //遮罩，从透明逐渐变为实的
    p2.end();
    x=(w-_pixmap2.width())/2;
    y=(h-_pixmap2.height())/2;
    painter.drawPixmap(x,y,alphaPixmap2);
}

void PicAnimationWid::UpSelectPixmap(QTreeWidgetItem *item)
{
    if(!item){
        return;
    }
    auto * tree_item=dynamic_cast<ProTreeItem*>(item);
    auto path=tree_item->GetPath();
    _pixmap1.load(path);
    _cur_item=tree_item;

    if(_map_items.find(path)==_map_items.end()){ //若map中没有该path对应的item
        _map_items[path]=tree_item;  //则添加到map中
    }

    auto * next_item=tree_item->GetNextItem();
    if(!next_item){
        return;
    }

    auto next_path=tree_item->GetPath();
    _pixmap2.load(next_path);
    if(_map_items.find(next_path)==_map_items.end()){
        _map_items[next_path]=next_item;
    }
}

void PicAnimationWid::SlotUpSelectShow(QString path)
{
    auto iter=_map_items.find(path);  //获取路径对应的item
    if(iter==_map_items.end()){
        return;
    }
    UpSelectPixmap(iter.value());
    update();
}

void PicAnimationWid::SlotStartOrStop()
{
    if(!_b_start){  //若播放没有开始
        _factor=0; //因子变为0
        _timer->start(25);
        _b_start=true;
        emit SigStartMusic();
    }else{  //若播放已经开始要变为暂停状态
        _timer->stop();
        _factor=0;
        update();
        _b_start=false;
        emit SigStopMusic();
    }
}

void PicAnimationWid::TimeOut()
{
    if(!_cur_item){ //若当前的item为空
        Stop();
        update(); //刷新界面
        return;
    }

    _factor=_factor+0.01; //更新因子
    if(_factor>=1){ //当因子到达最大值后，显示下一张图片
        _factor=0;
        auto *cur_pro_item=dynamic_cast<ProTreeItem*>(_cur_item);
        auto * next_pro_item=cur_pro_item->GetNextItem();
        if(!next_pro_item){ //若图片已经到头了，就停止动画同时刷新界面
            Stop();
            update();
            return;
        }

        SetPixmap(next_pro_item); //显示下一张图片
        update();
        return;
    }

    update();
}
