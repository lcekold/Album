#include "protreewidget.h"
#include <QDir>
#include "protreeitem.h"
#include "const.h"
#include <QHeaderView>
#include <QDebug>
#include <QApplication>
#include <QMenu>
#include <QFileDialog>
#include "removeprodialog.h"
#include "slideshowdialog.h"
ProTreeWidget::ProTreeWidget(QWidget *parent)
    :QTreeWidget(parent),_active_item(nullptr),_right_btn_item(nullptr),_dialog_progress(nullptr),_selected_item(nullptr)
    ,_thread_create_pro(nullptr),_thread_open_pro(nullptr),_open_progressdlg(nullptr)
{
    this->header()->hide();
    connect(this,&ProTreeWidget::itemPressed,this,&ProTreeWidget::SlotItemPressed); //鼠标点击了item触发信号
    //创建菜单项动作
    _action_import=new QAction(QIcon(":/icon/import.png"),tr("导入文件"),this);
    _action_setstart=new QAction(QIcon(":/icon/core.png"),tr("设置活动项目"),this);
    _action_closepro=new QAction(QIcon(":/icon/close.png"),tr("关闭项目"),this);
    _action_slideshow=new QAction(QIcon(":/icon/slideshow.png"),tr("轮播图播放"),this);
    connect(_action_import,&QAction::triggered,this,&ProTreeWidget::SlotImport);  //导入文件槽函数
    connect(_action_setstart,&QAction::triggered,this,&ProTreeWidget::SlotSetActive); //设置活动项目槽函数
    connect(_action_closepro,&QAction::triggered,this,&ProTreeWidget::SlotClosePro);  //关闭项目槽函数
    connect(this,&ProTreeWidget::itemDoubleClicked,this,&ProTreeWidget::SlotDoubleClickItem); //当item被双击后发出信号，
    connect(_action_slideshow,&QAction::triggered,this,&ProTreeWidget::SlotSlideShow);

    _player=new QMediaPlayer(this);
    _playlist=new QMediaPlaylist(this);
    _playlist->setPlaybackMode(QMediaPlaylist::Loop);
    _player->setPlaylist(_playlist);
}

//让创建的文件夹显示在界面左侧
void ProTreeWidget::AddProToTree(const QString &name, const QString &path)
{
    QDir dir(path);
    QString file_path = dir.absoluteFilePath(name);
    if(_set_path.find(file_path)!=_set_path.end()){ //若已经存在
        return;
    }
    //使用QDir对象创建一个表示项目目录的新QDir实例
    QDir pro_dir(file_path);
    //检查项目目录是否已经存在
    if(!pro_dir.exists()){
        bool enable=pro_dir.mkpath(file_path);//如果不存在，则尝试使用mkpath()方法创建该目录。如果创建失败，函数返回。
        if(!enable){
            return;
        }
    }

    _set_path.insert(file_path);
    auto * item = new ProTreeItem(this,name,file_path,TreeItemPro);
    //设置项目在树中的显示名称、图标以及工具提示（显示完整的文件路径）。
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
    item->setData(0,Qt::ToolTipRole,file_path);
    this->addTopLevelItem(item);
}

//处理鼠标右键点击item发出的信号
void ProTreeWidget::SlotItemPressed(QTreeWidgetItem *pressedItem, int column)
{
    if(QGuiApplication::mouseButtons()==Qt::RightButton){  //如果右键点击item
        QMenu menu(this);
        int itemtype=pressedItem->type(); //返回目录的类型（根目录，文件夹或里面的文件）
        if(itemtype==TreeItemPro){   //右键点击的是否是根目录
            _right_btn_item=pressedItem;
            //添加菜单
            menu.addAction(_action_import);
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.addAction(_action_slideshow);
            menu.exec(QCursor::pos()); //运行菜单,位置是鼠标右键，即鼠标右键点击后触发菜单
        }
    }
}

void ProTreeWidget::SlotDoubleClickItem(QTreeWidgetItem *doubleItem, int col)
{
    if(QGuiApplication::mouseButtons()==Qt::LeftButton){ //判断双击的是否是左键
        auto * tree_doubleItem=dynamic_cast<ProTreeItem*>(doubleItem); //将doubleItem的类型转变为子类的ProTreeItem类型
        if(!tree_doubleItem){
            return;
        }

        int itemtype=tree_doubleItem->type(); //判断item的类型
        if(itemtype==TreeItemPic){
            if(itemtype==TreeItemPic){  //判断点击的是否是图片类型
                emit SigUpdateSelected(tree_doubleItem->GetPath());
                _selected_item=doubleItem;
            }
        }
    }
}

//导入文件的槽函数
void ProTreeWidget::SlotImport()
{
    QFileDialog file_dialog;//点击导入文件后弹出对话框
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle(tr("选择导入的文件夹"));
    QString path="";
    if(!_right_btn_item){ //判断右键点击的目录是否为空
        qDebug()<<"_right_btn_item is empty"<<endl;
        //path=QDir::currentPath(); //给一个默认值，即当前目录，防止有问题
        return;
    }

    path=dynamic_cast<ProTreeItem*>(_right_btn_item)->GetPath(); //获取右键点击的该item的路径
    file_dialog.setDirectory(path);  //设置默认路径为右键点击的该item的路径
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;  //用QStringList来缓存读取到的文件
    if(file_dialog.exec()){
        fileNames=file_dialog.selectedFiles();//获取选中的文件信息
    }

    if(fileNames.length()<=0){  //若没有文件被选中
        return;
    }

    QString import_path=fileNames.at(0);  //取第一个文件夹
    int file_count=0;  //file_count存储文件的个数
    _dialog_progress=new QProgressDialog(this);  //创建一个模态对话框（进度条） 好处：1.可以避免内存泄露，对话框完成之后可以手动销毁
    //进度条用于显示文件载入项目的进度
    _thread_create_pro=std::make_shared<ProTreeThread>(std::ref(import_path),std::ref(path),_right_btn_item,
                                                         file_count,this,_right_btn_item,nullptr); //创建线程

    connect(_thread_create_pro.get(),&ProTreeThread::SigUpdateProgress,
            this,&ProTreeWidget::SlotUpdateProgress);  //更新进度条

    connect(_thread_create_pro.get(),&ProTreeThread::SigFinishProgress,
            this,&ProTreeWidget::SlotFinishProgress);

    connect(_dialog_progress,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCancelProgress);

    connect(this,&ProTreeWidget::SigCancelProgress,_thread_create_pro.get(),&ProTreeThread::SlotCancelProgress);

    _thread_create_pro->start();  //启动线程
    //对进度条进行初始化
    _dialog_progress->setWindowTitle("Please wait...");
    _dialog_progress->setFixedWidth(PROGRESS_WIDTH); //初始化进度条
    _dialog_progress->setRange(0,PROGRESS_WIDTH); //设置进度条波动的范围
    _dialog_progress->exec();  //让对话框进行一个模态的显示

    //由于进度条显示往往伴随着耗时的操作，因此为了避免影响ui界面的显示，因此把进度条伴随的操作放在其它线程中进行，这样就可以互不影响

}


//设置活动项目槽函数
void ProTreeWidget::SlotSetActive()
{
    if(!_right_btn_item){ //若右键没有点击item
        return;
    }

    QFont nullFont;
    nullFont.setBold(false);  //将字体设置为不是粗体

    if(_active_item){
        _active_item->setFont(0,nullFont); //以前有活动项目了，则把活动项目的字体设置为普通字体
    }

    _active_item=_right_btn_item; //将活动项目设置为当前右键的项目
    nullFont.setBold(true);
    _active_item->setFont(0,nullFont);  //将当前活动项目字体设置为粗体
}


//关闭项目槽函数
void ProTreeWidget::SlotClosePro()
{
    //添加一个删除的对话框
    RemoveProDialog remove_pro_dialog;
    auto res=remove_pro_dialog.exec();
    if(res!=QDialog::Accepted){
        return;
    }

    bool b_remove=remove_pro_dialog.IsRemoved(); //判断勾选的状态
    auto index_right_btn=this->indexOfTopLevelItem(_right_btn_item); //返回右键选中的项目在Item中的索引
    auto * protreeitem=dynamic_cast<ProTreeItem*>(_right_btn_item);  //得到当前右键的条目
    auto * selecteditem=dynamic_cast<ProTreeItem*>(_selected_item); //选择（鼠标左键单击）的条目
    auto delete_path=protreeitem->GetPath(); //获取要删除的路径
    if(b_remove){  //是否删除本地文件
        QDir delete_dir(delete_path); //通过删除路径来构造一个目录
        delete_dir.removeRecursively(); //根据目录来递归的删除
    }

    if(protreeitem==_active_item){ //若右键的条目和当前激活的条目（活动项目）是同一个的话
        _active_item=nullptr;
    }

    if(selecteditem && protreeitem == selecteditem->GetRoot()){ //若右侧显示的图片是在要被关闭的项目下的文件
        selecteditem=nullptr;
        _selected_item=nullptr;
        emit SigClearSelected(); //发送给picshow进行处理
    }

    delete this->takeTopLevelItem(index_right_btn);  //删除右键击中需要关闭项目的条目
    _right_btn_item=nullptr;
}

//更新进度条的槽函数
void ProTreeWidget::SlotUpdateProgress(int count)
{
    if(!_dialog_progress){  //若对话框为空则直接返回
        return;
    }

    if(count>=PROGRESS_MAX){ //count值大，就拿百分比来进行设置
        _dialog_progress->setValue(count%PROGRESS_MAX); //更新进度条值
    }else{  //count值小，就直接拿count来进行设置
        _dialog_progress->setValue(count);
    }
}

void ProTreeWidget::SlotFinishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);  //完成就把进度条设置为最大
    _dialog_progress->deleteLater();  //把对话框删除
}

//进度条取消的操作
void ProTreeWidget::SlotCancelProgress()
{
    emit SigCancelProgress(); //发送取消信号,用来通知线程
    delete _dialog_progress;//删除进度条
    _dialog_progress=nullptr;
}

void ProTreeWidget::SlotUpOpendateProgress(int count)
{
    if(!_open_progressdlg){  //若对话框为空则直接返回
        return;
    }

    if(count>=PROGRESS_MAX){ //count值大，就拿百分比来进行设置
        _open_progressdlg->setValue(count%PROGRESS_MAX); //更新进度条值
    }else{  //count值小，就直接拿count来进行设置
        _open_progressdlg->setValue(count);
    }
}

void ProTreeWidget::SlotFinishOpenProgress()
{
    _open_progressdlg->setValue(PROGRESS_MAX);  //完成就把进度条设置为最大
    _open_progressdlg->deleteLater();  //把对话框删除
}

void ProTreeWidget::SlotCancelOpenProgress()
{
    emit SigCancelOpenProgress(); //发送取消信号,用来通知线程
    delete _open_progressdlg;//删除进度条
    _open_progressdlg=nullptr;
}

//展示轮播图槽函数
void ProTreeWidget::SlotSlideShow()
{
    if(!_right_btn_item){
        return; //判断是否是右键点击
    }

    auto * right_pro_item=dynamic_cast<ProTreeItem*>(_right_btn_item);
    auto * last_child_item=right_pro_item->GetLastPicChild();
    if(!last_child_item){  //若最后一个节点为空也直接返回
        return;
    }

    auto * first_child_item=right_pro_item->GetFirstPicChild();
    if(!first_child_item){  //若第一个节点为空直接返回
        return;
    }
    qDebug()<<"first_child_item is "<<first_child_item->GetPath();
     qDebug()<<"last_child_item is "<<last_child_item->GetPath();
    _slide_show_dlg=std::make_shared<SlideShowDialog>(this,
                                                   first_child_item,last_child_item);
    _slide_show_dlg->setModal(true);
    _slide_show_dlg->showMaximized();
}

//打开项目槽函数
void ProTreeWidget::SlotOpenPro(const QString &path)
{
    if(_set_path.find(path)!=_set_path.end()){ //若之前已经打开过项目了
        return;
    }

    _set_path.insert(path);
    int file_count=0;
    QDir pro_dir(path); //把当前的导入路径构造为目录
    const QString proname=pro_dir.dirName(); //获取导入的路径

    _thread_open_pro=std::make_shared<OpenTreeThread>(path,file_count,this,nullptr);
    _thread_open_pro->start(); //启动线程

    _open_progressdlg = new QProgressDialog(this);  //创建进度条
    connect(_thread_open_pro.get(),&OpenTreeThread::SigUpdateProgress,
            this,&ProTreeWidget::SlotUpOpendateProgress);  //更新进度条

    connect(_thread_open_pro.get(),&OpenTreeThread::SigFinshProgress,
            this,&ProTreeWidget::SlotFinishOpenProgress);

    connect( _open_progressdlg,&QProgressDialog::canceled,this,&ProTreeWidget::SlotCancelOpenProgress);

    connect(this,&ProTreeWidget::SigCancelOpenProgress,_thread_open_pro.get(),&OpenTreeThread::SlotCancelProgress);

    //对进度条进行初始化
    _open_progressdlg->setWindowTitle("Please wait...");
    _open_progressdlg->setFixedWidth(PROGRESS_WIDTH); //初始化进度条
    _open_progressdlg->setRange(0,PROGRESS_WIDTH); //设置进度条波动的范围
    _open_progressdlg->exec();  //让对话框进行一个模态的显示

}

void ProTreeWidget::SlotNextShow()
{
    if(!_selected_item){
        return;
    }

    auto *curItem=dynamic_cast<ProTreeItem*>(_selected_item)->GetNextItem(); //获取下一个节点
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item=curItem;
    this->setCurrentItem(curItem); //高亮显示当前选中的item
}

void ProTreeWidget::SlotPreShow()
{
    if(!_selected_item){
        return;
    }

    auto *curItem=dynamic_cast<ProTreeItem*>(_selected_item)->GetPreItem(); //获取下一个节点
    if(!curItem){
        return;
    }

    emit SigUpdatePic(curItem->GetPath());
    _selected_item=curItem;
    this->setCurrentItem(curItem); //高亮显示当前选中的item
}

void ProTreeWidget::SlotSetMusic()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::ExistingFiles);
    file_dialog.setWindowTitle("选择音频文件");
    file_dialog.setDirectory(QDir::currentPath());
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.setNameFilter("(*.mp3)");
    QStringList fileNames;
    if(file_dialog.exec()){
        fileNames=file_dialog.selectedFiles();
    }else{
        return;
    }

    if(fileNames.length()<=0){
        return;
    }

    _playlist->clear();
    for(auto filename:fileNames){
        _playlist->addMedia(QUrl::fromLocalFile(filename));
    }

    if(_player->state()!=QMediaPlayer::PlayingState){
        _playlist->setCurrentIndex(0);
    }
}

void ProTreeWidget::SlotStartMusic()
{
    _player->play();
}

void ProTreeWidget::SlotStopMusic()
{
    _player->stop();
}
