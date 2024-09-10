#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include "wizard.h"
#include "protree.h"
#include <QFileDialog>
#include "protreewidget.h"
#include "picshow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setMinimumSize(1629,869);
    ui->setupUi(this);
    //创建菜单
    QMenu * menu_file = menuBar()->addMenu(tr("文件(&F)"));
    //创建项目动作
    QAction * act_create_pro = new QAction(QIcon(":/icon/createpro.png"),tr("创建项目"),this);
    act_create_pro->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));  // 创建快捷键
    menu_file->addAction(act_create_pro);
    //打开项目动作
    QAction* act_open_pro = new QAction(QIcon(":/icon/openpro.png"),tr("打开项目"),this);
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_O));
    menu_file->addAction(act_open_pro);

    //创建设置菜单
    QMenu* menu_set = menuBar()->addMenu(tr("设置(&S)"));
    //设置背景音乐
    QAction* act_music = new QAction(QIcon(":/icon/music.png"),tr("背景音乐"),this);
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_M));
    menu_file->addAction(act_music);

    //连接信号和槽,当创建项目按钮被点击后执行
    connect(act_create_pro,&QAction::triggered,this,&MainWindow::SlotCreatePro);
    //连接信号和槽，当打开项目按钮被点击后执行，连接打开项目槽函数
    connect(act_open_pro,&QAction::triggered,this,&MainWindow::SlotOpenPro);

    //添加左侧树形目录
    _protree=new ProTree();
    ui->proLayout->addWidget(_protree);

    //触发打开项目槽函数中的SigOpenPro信号
    QTreeWidget* tree_widget=dynamic_cast<ProTree*>(_protree)->GetTreeWidget();
    auto * pro_tree_widget=dynamic_cast<ProTreeWidget*>(tree_widget);
    connect(this,&MainWindow::SigOpenPro,pro_tree_widget,&ProTreeWidget::SlotOpenPro);

    //右侧显示图片
    _picshow=new PicShow();
    ui->picLayout->addWidget(_picshow);
    auto * pro_pic_show=dynamic_cast<PicShow*>(_picshow);
    connect(pro_tree_widget,&ProTreeWidget::SigUpdateSelected,pro_pic_show
            ,&PicShow::SlotSelectedItem);
    connect(pro_pic_show,&PicShow::SigNextClicked,pro_tree_widget //"下一个"按钮被点击
            ,&ProTreeWidget::SlotNextShow);
    connect(pro_pic_show,&PicShow::SigPreClicked,pro_tree_widget  //“上一个”按钮被点击
            ,&ProTreeWidget::SlotPreShow);
    connect(pro_tree_widget,&ProTreeWidget::SigUpdatePic,pro_pic_show
            ,&PicShow::SlotUpdatePic); //更新图片
    connect(pro_tree_widget,&ProTreeWidget::SigClearSelected,pro_pic_show
            ,&PicShow::SlotDeleteItem);

    connect(act_music,&QAction::triggered,
            pro_tree_widget,&ProTreeWidget::SlotSetMusic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    auto * pro_pic_show = dynamic_cast<PicShow*>(_picshow);
    pro_pic_show->ReloadPic(); //重新加载
    QMainWindow::resizeEvent(event);
}


//创建项目，创建项目的过程使用向导，创建后的结果显示在左侧树状结构中
void MainWindow::SlotCreatePro(bool)
{
    qDebug()<<"slot create pro triggered"<<endl;
    Wizard wizard(this);
    wizard.setWindowTitle(tr("创建项目"));
    auto * page = wizard.page(0);
    page->setTitle(tr("设置项目配置"));
    //连接信号和槽,把项目配置传回来todo....
    //当wizard触发SigProSettings时，将信号传给槽函数AddProToTree，执行槽函数中的操作
    connect(&wizard,&Wizard::SigProSettings,
            dynamic_cast<ProTree*>(_protree),&ProTree::AddProToTree);
    wizard.show();
    wizard.exec();  //执行
    //断开所有信号 todo....
    disconnect();
}

//打开项目槽函数
void MainWindow::SlotOpenPro(bool)
{
    //创建文件对话框
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory); //设置为目录模式
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    file_dialog.setDirectory(QDir::currentPath()); //设置打开时默认的目录
    file_dialog.setViewMode(QFileDialog::Detail); //显示的模式是详情模式
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames=file_dialog.selectedFiles(); //选中后获取
    }

    if(fileNames.length()<=0){
        return;
    }

    QString import_path=fileNames.at(0); //获取导入的路径
    emit SigOpenPro(import_path); //发送信号告诉TreeWidget导入的是哪个路径
}
