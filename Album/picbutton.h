#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include<QPixmap>
#include <QEvent>
class PicButton : public QPushButton
{
public:
    PicButton(QWidget *parent=nullptr);
    //给按钮设置图片
    void SetIcons(const QString& normal,
                  const QString& hover,const QString& pressed);  //正常状态下的图片，悬浮状态下图片，点击状态下图片
protected:
    //点击事件
    bool event(QEvent *e) override;
private:
    void setNormalIcon();  //设置正常状态下的图片的函数
    void setHoverIcon();//设置悬浮状态下的图片的函数
    void setPressIcon(); //设置点击状态下的图片的函数
    QString _normal;  //正常加载的图片路径
    QString _hover; //加载悬浮时的图片路径
    QString _pressed; //点击时的图片路径
};

#endif // PICBUTTON_H
