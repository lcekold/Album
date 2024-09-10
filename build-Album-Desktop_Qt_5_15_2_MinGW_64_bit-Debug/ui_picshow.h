/********************************************************************************
** Form generated from reading UI file 'picshow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICSHOW_H
#define UI_PICSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <picbutton.h>

QT_BEGIN_NAMESPACE

class Ui_PicShow
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    PicButton *previousBtn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    PicButton *nextBtn;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *PicShow)
    {
        if (PicShow->objectName().isEmpty())
            PicShow->setObjectName(QString::fromUtf8("PicShow"));
        PicShow->resize(854, 544);
        horizontalLayout = new QHBoxLayout(PicShow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(PicShow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(80, 0));
        widget->setMaximumSize(QSize(80, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        previousBtn = new PicButton(widget);
        previousBtn->setObjectName(QString::fromUtf8("previousBtn"));

        verticalLayout->addWidget(previousBtn);


        gridLayout->addWidget(widget, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        widget_2 = new QWidget(PicShow);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(80, 0));
        widget_2->setMaximumSize(QSize(80, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        nextBtn = new PicButton(widget_2);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));

        verticalLayout_2->addWidget(nextBtn);


        gridLayout->addWidget(widget_2, 1, 5, 1, 1);

        label = new QLabel(PicShow);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 3, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(PicShow);

        QMetaObject::connectSlotsByName(PicShow);
    } // setupUi

    void retranslateUi(QDialog *PicShow)
    {
        PicShow->setWindowTitle(QCoreApplication::translate("PicShow", "Dialog", nullptr));
        previousBtn->setText(QString());
        nextBtn->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PicShow: public Ui_PicShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICSHOW_H
