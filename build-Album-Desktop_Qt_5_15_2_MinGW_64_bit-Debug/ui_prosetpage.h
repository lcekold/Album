/********************************************************************************
** Form generated from reading UI file 'prosetpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROSETPAGE_H
#define UI_PROSETPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_ProSetPage
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *tips;

    void setupUi(QWizardPage *ProSetPage)
    {
        if (ProSetPage->objectName().isEmpty())
            ProSetPage->setObjectName(QString::fromUtf8("ProSetPage"));
        ProSetPage->resize(942, 603);
        gridLayout_2 = new QGridLayout(ProSetPage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(ProSetPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(ProSetPage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        lineEdit_2 = new QLineEdit(ProSetPage);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        pushButton = new QPushButton(ProSetPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 3, 1, 1);

        label_2 = new QLabel(ProSetPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        tips = new QLabel(ProSetPage);
        tips->setObjectName(QString::fromUtf8("tips"));

        gridLayout->addWidget(tips, 3, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ProSetPage);

        QMetaObject::connectSlotsByName(ProSetPage);
    } // setupUi

    void retranslateUi(QWizardPage *ProSetPage)
    {
        ProSetPage->setWindowTitle(QCoreApplication::translate("ProSetPage", "WizardPage", nullptr));
        label->setText(QCoreApplication::translate("ProSetPage", "Name:", nullptr));
        pushButton->setText(QCoreApplication::translate("ProSetPage", "browse", nullptr));
        label_2->setText(QCoreApplication::translate("ProSetPage", "Path:", nullptr));
        tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProSetPage: public Ui_ProSetPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROSETPAGE_H
