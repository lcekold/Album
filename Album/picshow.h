#ifndef PICSHOW_H
#define PICSHOW_H

#include <QDialog>
#include <QGraphicsOpacityEffect> //透明度
#include <QPropertyAnimation> //属性动画

namespace Ui {
class PicShow;
}

class PicShow : public QDialog
{
    Q_OBJECT

public:
    explicit PicShow(QWidget *parent = nullptr);
    ~PicShow();
    void ReloadPic();
protected:
    bool event(QEvent *event) override;
private:
    void ShowPreNextBtns(bool b_show); //显示前后按钮 参数：是否隐藏
    Ui::PicShow *ui;
    QPropertyAnimation* _animation_show_pre; //控制前一个按钮的动画
    QPropertyAnimation* _animation_show_next;  //控制后一个按钮的动画
    bool _b_btnvisible; //存储当前按钮是显示状态还是不显示
    QString _selected_path;
    QPixmap _pix_map;//存储要加载的图片
public slots:
    void SlotSelectedItem(const QString& path);
    void SlotUpdatePic(const QString& _path);
    void SlotDeleteItem();
signals:
    void SigNextClicked();
    void SigPreClicked();
};

#endif // PICSHOW_H
