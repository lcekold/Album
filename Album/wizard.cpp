#include "wizard.h"
#include "ui_wizard.h"

////////////// Wizard里面有两个自定义子类：prosetpage和confirmpage，prosetpage是配置项目名称和路径的向导页，confirmpage是

Wizard::Wizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
{
    ui->setupUi(this);
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::done(int result)
{
    if(result == QDialog::Rejected){
        return QWizard::done(result);
    }

    QString name,path;
    ui->wizardPage1->GetProSettings(name,path);
    emit SigProSettings(name,path); //触发信号，信号中的参数为创建项目时填写的名称和路径/
    QWizard::done(result);
}
