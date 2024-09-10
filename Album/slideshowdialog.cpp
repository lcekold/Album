#include "slideshowdialog.h"
#include "ui_slideshowdialog.h"
#include "preListwid.h"
#include "protreewidget.h"

SlideShowDialog::SlideShowDialog(QWidget *parent, QTreeWidgetItem *first_item,
                                 QTreeWidgetItem *last_item):
    QDialog(parent),_first_item(first_item),_last_item(last_item)
    ,ui(new Ui::SlideShowDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->slidepreBtn->SetIcons(":/icon/previous.png",
                              ":/icon/previous_hover.png",
                              ":/icon/previous_press");

    ui->slidenextBtn->SetIcons(":/icon/next.png",
                              ":/icon/next_hover.png",
                              ":/icon/next_press");

    ui->closeBtn->SetIcons(":/icon/closeshow.png",
                           ":/icon/closeshow_hover.png",
                           ":/icon/closeshow_press");

    ui->playBtn->SetIcons(":/icon/play.png",
                          ":/icon/play_hover.png",
                          ":/icon/play_press",
                          ":/icon/pause.png",
                          ":/icon/pause_hover.png",
                          ":/icon/pause_press");
    connect(ui->closeBtn,&QPushButton::clicked,this,&SlideShowDialog::close);
    connect(ui->slidenextBtn,&QPushButton::clicked,this,&SlideShowDialog::SlotSlideNext);
    connect(ui->slidepreBtn,&QPushButton::clicked,this,&SlideShowDialog::SlotSlidePre);

    auto * prelistWid = dynamic_cast<PreListWid*>(ui->preListWidget);
    connect(ui->picAnimation,&PicAnimationWid::SigUpPreList,
            prelistWid,&PreListWid::SlotUpPreList);

    connect(ui->picAnimation,&PicAnimationWid::SigSelectItem,
            prelistWid,&PreListWid::SlotUpSelect);

    connect(prelistWid,&PreListWid::SigUpSelectShow,
            ui->picAnimation,&PicAnimationWid::SlotUpSelectShow);

    connect(ui->playBtn,&PicStateBtn::clicked,
            ui->picAnimation,&PicAnimationWid::SlotStartOrStop);

    connect(ui->picAnimation,&PicAnimationWid::SigStart,
        ui->playBtn,&PicStateBtn::SlotStart); //点击播放按钮后进行的操作，将播放按钮变为暂停按钮
    connect(ui->picAnimation,&PicAnimationWid::SigStop,
        ui->playBtn,&PicStateBtn::SlotStop);//点击暂停按钮后进行的操作，将暂停按钮变为播放按钮


    auto * _protree_widget = dynamic_cast<ProTreeWidget*>(parent);
    connect(ui->picAnimation,&PicAnimationWid::SigStartMusic,
            _protree_widget,&ProTreeWidget::SlotStartMusic);

    connect(ui->picAnimation,&PicAnimationWid::SigStopMusic,
            _protree_widget,&ProTreeWidget::SlotStopMusic);
    ui->picAnimation->SetPixmap(_first_item);
    ui->picAnimation->Start();
}

SlideShowDialog::~SlideShowDialog()
{
    delete ui;
}

void SlideShowDialog::SlotSlideNext()
{
    ui->picAnimation->SlideNext();
}

void SlideShowDialog::SlotSlidePre()
{
    ui->picAnimation->SlidePre();
}
