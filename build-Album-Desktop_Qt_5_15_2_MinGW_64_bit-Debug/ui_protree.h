/********************************************************************************
** Form generated from reading UI file 'protree.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTREE_H
#define UI_PROTREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "protreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_ProTree
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_pro;
    ProTreeWidget *treeWidget;

    void setupUi(QDialog *ProTree)
    {
        if (ProTree->objectName().isEmpty())
            ProTree->setObjectName(QString::fromUtf8("ProTree"));
        ProTree->resize(536, 446);
        verticalLayout_2 = new QVBoxLayout(ProTree);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_pro = new QLabel(ProTree);
        label_pro->setObjectName(QString::fromUtf8("label_pro"));

        verticalLayout->addWidget(label_pro);

        treeWidget = new ProTreeWidget(ProTree);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 20);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ProTree);

        QMetaObject::connectSlotsByName(ProTree);
    } // setupUi

    void retranslateUi(QDialog *ProTree)
    {
        ProTree->setWindowTitle(QCoreApplication::translate("ProTree", "Dialog", nullptr));
        label_pro->setText(QCoreApplication::translate("ProTree", "\351\241\271\347\233\256\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProTree: public Ui_ProTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTREE_H
