#include "picbutton.h"
///////// 自定义按钮
PicButton::PicButton(QWidget *parent) {

}

void PicButton::SetIcons(const QString &normal,
                         const QString &hover, const QString &pressed)
{
    _normal=normal;
    _hover=hover;
    _pressed=pressed;

    QPixmap tmpPixmap;  //一个图片变量
    tmpPixmap.load(normal); //根据normal路径加载图片
    this->resize(tmpPixmap.size()); //将按钮的大小设置为与图片一致
    this->setIcon(tmpPixmap); //设置按钮正常情况下显示的图片
    //也可以使用setIcons直接设置按钮的正常、悬浮、点击图片，但无法实现定制化功能
    this->setIconSize(tmpPixmap.size());
}

bool PicButton::event(QEvent *e)
{
    switch(e->type()){
        case QEvent::Enter:
            setHoverIcon(); //设置为悬浮
            break;
        case QEvent::Leave:
            setNormalIcon(); //设置为普通状态
            break;
        case QEvent::MouseButtonPress:
            setPressIcon(); //设置为点击状态啊
            break;
        case QEvent::MouseButtonRelease:
            setHoverIcon(); //设置为悬浮状态
            break;
        default:
            break;
    }

    return QPushButton::event(e);
}

void PicButton::setNormalIcon()
{
    QPixmap tmpPixmap;  //一个图片变量
    tmpPixmap.load(_normal); //根据normal路径加载图片
    this->setIcon(tmpPixmap); //设置按钮正常情况下显示的图片
}

void PicButton::setHoverIcon()
{
    QPixmap tmpPixmap;  //一个图片变量
    tmpPixmap.load(_hover); //根据normal路径加载图片
    this->setIcon(tmpPixmap); //设置按钮正常情况下显示的图片
}

void PicButton::setPressIcon()
{
    QPixmap tmpPixmap;  //一个图片变量
    tmpPixmap.load(_pressed); //根据normal路径加载图片
    this->setIcon(tmpPixmap); //设置按钮正常情况下显示的图片
}
