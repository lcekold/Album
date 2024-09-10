/********************************************************************************
** Form generated from reading UI file 'slideshowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDESHOWDIALOG_H
#define UI_SLIDESHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <picanimationwid.h>
#include <picbutton.h>
#include <picstatebtn.h>
#include "prelistwid.h"

QT_BEGIN_NAMESPACE

class Ui_SlideShowDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *slideShow;
    QGridLayout *gridLayout;
    QWidget *slidenextwid;
    QHBoxLayout *horizontalLayout_3;
    PicButton *slidenextBtn;
    QWidget *slideprewid;
    QHBoxLayout *horizontalLayout_4;
    PicButton *slidepreBtn;
    PicAnimationWid *picAnimation;
    QHBoxLayout *horizontalLayout_2;
    PicStateBtn *playBtn;
    PicButton *closeBtn;
    QWidget *preShow;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    PreListWid *preListWidget;

    void setupUi(QDialog *SlideShowDialog)
    {
        if (SlideShowDialog->objectName().isEmpty())
            SlideShowDialog->setObjectName(QString::fromUtf8("SlideShowDialog"));
        SlideShowDialog->resize(811, 505);
        verticalLayout = new QVBoxLayout(SlideShowDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slideShow = new QWidget(SlideShowDialog);
        slideShow->setObjectName(QString::fromUtf8("slideShow"));
        gridLayout = new QGridLayout(slideShow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        slidenextwid = new QWidget(slideShow);
        slidenextwid->setObjectName(QString::fromUtf8("slidenextwid"));
        slidenextwid->setMinimumSize(QSize(80, 0));
        slidenextwid->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_3 = new QHBoxLayout(slidenextwid);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        slidenextBtn = new PicButton(slidenextwid);
        slidenextBtn->setObjectName(QString::fromUtf8("slidenextBtn"));

        horizontalLayout_3->addWidget(slidenextBtn);


        gridLayout->addWidget(slidenextwid, 1, 2, 1, 1);

        slideprewid = new QWidget(slideShow);
        slideprewid->setObjectName(QString::fromUtf8("slideprewid"));
        slideprewid->setMinimumSize(QSize(80, 0));
        slideprewid->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_4 = new QHBoxLayout(slideprewid);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        slidepreBtn = new PicButton(slideprewid);
        slidepreBtn->setObjectName(QString::fromUtf8("slidepreBtn"));

        horizontalLayout_4->addWidget(slidepreBtn);


        gridLayout->addWidget(slideprewid, 1, 0, 1, 1);

        picAnimation = new PicAnimationWid(slideShow);
        picAnimation->setObjectName(QString::fromUtf8("picAnimation"));

        gridLayout->addWidget(picAnimation, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        playBtn = new PicStateBtn(slideShow);
        playBtn->setObjectName(QString::fromUtf8("playBtn"));

        horizontalLayout_2->addWidget(playBtn);

        closeBtn = new PicButton(slideShow);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));

        horizontalLayout_2->addWidget(closeBtn);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);


        verticalLayout->addWidget(slideShow);

        preShow = new QWidget(SlideShowDialog);
        preShow->setObjectName(QString::fromUtf8("preShow"));
        horizontalLayout = new QHBoxLayout(preShow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(preShow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 120));
        widget->setMaximumSize(QSize(16777215, 120));
        preListWidget = new PreListWid(widget);
        preListWidget->setObjectName(QString::fromUtf8("preListWidget"));
        preListWidget->setGeometry(QRect(10, 10, 16777215, 110));
        preListWidget->setMinimumSize(QSize(0, 110));
        preListWidget->setMaximumSize(QSize(16777215, 110));
        preListWidget->setFlow(QListView::LeftToRight);

        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(preShow);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 1);

        retranslateUi(SlideShowDialog);

        QMetaObject::connectSlotsByName(SlideShowDialog);
    } // setupUi

    void retranslateUi(QDialog *SlideShowDialog)
    {
        SlideShowDialog->setWindowTitle(QCoreApplication::translate("SlideShowDialog", "Dialog", nullptr));
        slidenextBtn->setText(QString());
        slidepreBtn->setText(QString());
        playBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SlideShowDialog: public Ui_SlideShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOWDIALOG_H
