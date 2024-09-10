#include "prosetpage.h"
#include "ui_prosetpage.h"
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>
ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);
    //注册域
    registerField("proPath",ui->lineEdit_2);
    registerField("proName*",ui->lineEdit);
    // 当文本框内容发生改变时触发 completeChanged 槽函数
    connect(ui->lineEdit,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);
    connect(ui->lineEdit_2,&QLineEdit::textEdited,this,&ProSetPage::completeChanged);
    // 获取当前路径并设置为 lineEdit_2 的文本
    QString curPath=QDir::currentPath();
    ui->lineEdit_2->setText(curPath);
    // 将光标移动到 lineEdit_2 文本框的最后
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());
    // 为 lineEdit_2 和 lineEdit 启用清除按钮功能
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit->setClearButtonEnabled(true);
}

ProSetPage::~ProSetPage()
{
    delete ui;
}

//获取用户填入的项目配置的名称和路径s
void ProSetPage::GetProSettings(QString &name, QString &path)
{
    name=ui->lineEdit->text();
    path=ui->lineEdit_2->text();
}

bool ProSetPage::isComplete() const
{
    //若两个lineEdit内的内容都为空，则返回false，确认按钮为灰色（不可选中）
    if(ui->lineEdit->text()==""||ui->lineEdit_2->text()==""){
        return false;
    }

    //判断目录是否存在
    QDir dir(ui->lineEdit_2->text());
    if(!dir.exists()){
        ui->tips->setText("project path is not exists");
        return false;
    }

    //判断路径是否存在
    QString absFilePath = dir.absoluteFilePath(ui->lineEdit->text());
    QDir dist_dir(absFilePath);
    if(dist_dir.exists()){
        ui->tips->setText("project has exists,change path or name");
        return false;
    }

    ui->tips->setText("");
    return QWizardPage::isComplete();
}

//当点击了browse按钮
void ProSetPage::on_pushButton_clicked()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);  //设置为打开一个目录模式
    file_dialog.setWindowTitle("选择导入的文件夹");
    //默认为当前路径
    auto path=QDir::currentPath();
    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);  //使用详情的方式展示出来

    //使用QStringList存储选中的文件路径
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames=file_dialog.selectedFiles();
    }

    //若长度<=0直接返回
    if(fileNames.length()<=0){
        return;
    }

    //导入路径
    QString import_path=fileNames.at(0);
    ui->lineEdit_2->setText(import_path);


}

