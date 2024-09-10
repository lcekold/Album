#include "picshow.h"
#include "ui_picshow.h"


PicShow::PicShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PicShow)
{
    ui->setupUi(this);
    ui->previousBtn->SetIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press.png");
    ui->nextBtn->SetIcons(":/icon/next.png",
                          ":/icon/next_hover.png",
                          ":/icon/next_press.png");

    QGraphicsOpacityEffect * opacity_pre=new QGraphicsOpacityEffect(this);
    opacity_pre->setOpacity(0); //将透明度设置为完全透明
    ui->previousBtn->setGraphicsEffect(opacity_pre); //给previousBtn按钮设置透明度

    QGraphicsOpacityEffect * opacity_next=new QGraphicsOpacityEffect(this);
    opacity_next->setOpacity(0); //将透明度设置为完全透明
    ui->nextBtn->setGraphicsEffect(opacity_next); //给previousBtn按钮设置透明度

    //当鼠标移动到图片位置的时候显示previousBtn和nextBtn，当移出的时候隐藏
    _animation_show_pre=new QPropertyAnimation(opacity_pre,"opacity",
                                               this);
    _animation_show_pre->setEasingCurve(QEasingCurve::Linear); //设置一个曲线（渐变）
    _animation_show_pre->setDuration(500); //动画时长(500ms)

    _animation_show_next=new QPropertyAnimation(opacity_next,"opacity",
                                                 this);
    _animation_show_next->setEasingCurve(QEasingCurve::Linear); //设置一个曲线（渐变）
    _animation_show_next->setDuration(500); //动画时长(500ms)

    connect(ui->nextBtn,&QPushButton::clicked,this,&PicShow::SigNextClicked); //“下一个”按钮被点击后，发送信号
    connect(ui->previousBtn,&QPushButton::clicked,this,&PicShow::SigPreClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

void PicShow::ReloadPic()
{
    if(_selected_path!=""){  //非空的情况下重新加载
        const auto &width=ui->gridLayout->geometry().width();
        const auto &height=ui->gridLayout->geometry().height();
        _pix_map.load(_selected_path);
        _pix_map=_pix_map.scaled(width,height,Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
    }
}

bool PicShow::event(QEvent *event)
{
    switch(event->type()){ //判断事件类型
    case QEvent::Enter:
        ShowPreNextBtns(true);
        break;
    case QEvent::Leave:
        ShowPreNextBtns(false);
        break;
    default:
        break;

    }

    return QDialog::event(event);  //通过子类调用基类的成员函数(通过作用域来调用)
}

void PicShow::ShowPreNextBtns(bool b_show)
{
    if(!b_show&&_b_btnvisible){//表示需要隐藏按钮
        _animation_show_pre->stop(); //停止动画
        _animation_show_pre->setStartValue(1); //设置开始值,1表示完全可见
        _animation_show_pre->setEndValue(0); //表示不显示
        _animation_show_pre->start(); //开始动画

        _animation_show_next->stop(); //停止动画
        _animation_show_next->setStartValue(1); //设置开始值,1表示完全可见
        _animation_show_next->setEndValue(0); //表示不显示
        _animation_show_next->start(); //开始动画

        _b_btnvisible=false;

        return;
    }

    if(b_show&&!_b_btnvisible){//表示需要显示按钮
        _animation_show_pre->stop(); //停止动画
        _animation_show_pre->setStartValue(0); //设置开始值,0表示隐藏
        _animation_show_pre->setEndValue(1); //表示显示
        _animation_show_pre->start(); //开始动画

        _animation_show_next->stop(); //停止动画
        _animation_show_next->setStartValue(0); //设置开始值,0表示隐藏
        _animation_show_next->setEndValue(1); //表示显示
        _animation_show_next->start(); //开始动画

        _b_btnvisible=true;

        return;
    }
}

void PicShow::SlotSelectedItem(const QString &path)
{
    _selected_path=path; //更新路径
    _pix_map.load(path); //加载图片
    auto width=this->width()-20; //获取PicShow的宽度，并且留有20的margin
    auto height=this->height()-20; //高度
    _pix_map=_pix_map.scaled(width,height,Qt::KeepAspectRatio); //对图片进行一个等比例的拉伸,KeepAspectRatio表示图片比例不变
    ui->label->setPixmap(_pix_map);
}

void PicShow::SlotUpdatePic(const QString &_path)
{
    _selected_path=_path; //更新路径
    if(_selected_path!=""){
        const auto &width=ui->gridLayout->geometry().width();
        const auto &height=ui->gridLayout->geometry().height();
        _pix_map.load(_selected_path);
        _pix_map=_pix_map.scaled(width,height,Qt::KeepAspectRatio);
        ui->label->setPixmap(_pix_map);
    }
}

void PicShow::SlotDeleteItem()
{
    _selected_path="";
}
