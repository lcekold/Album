#ifndef PICSTATEBTN_H
#define PICSTATEBTN_H

#include <QPushButton>

class PicStateBtn : public QPushButton
{
public:
    PicStateBtn(QWidget *parent);
    void SetIcons(const QString& normal,const QString& hover,const QString&pressed,
                  const QString& normal_2,const QString& hover_2,const QString&pressed_2); //第一行为播放按钮设置图标，第二行为暂停按钮设置图标
    virtual ~PicStateBtn(){}
protected:
    bool event(QEvent *event);
private:
    void setNormalIcon();
    void setHoverIcon();
    void setPressIcon();

    void setNormal2Icon();
    void setHover2Icon();
    void setPress2Icon();

    QString _normal;
    QString _hover;
    QString _pressed;
    QString _normal_2;
    QString _pressed_2;
    QString _hover_2;
    int _cur_state;
public slots:
    void SlotStart();
    void SlotStop();
};

#endif // PICSTATEBTN_H
