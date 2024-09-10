#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QAction>
#include <QProgressDialog>
#include "protreethread.h"
#include "opentreethread.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
class SlideShowDialog;

/////////////// 重写QTreeWidget
class ProTreeWidget : public QTreeWidget
{
        Q_OBJECT
public:
    ProTreeWidget(QWidget *parent = nullptr);
    void AddProToTree(const QString& name,const QString & path);

private:
    QSet<QString> _set_path; //用于判断是否重名
    QTreeWidgetItem * _right_btn_item;  //右键点击的某个item
    QTreeWidgetItem * _active_item; //保存当前的启动项目（活动项目）
    QTreeWidgetItem * _selected_item;
    QAction * _action_import;  //菜单项：导入
    QAction * _action_setstart; //菜单项
    QAction * _action_closepro;  //菜单项：关闭项目
    QAction * _action_slideshow; //菜单项
    QProgressDialog * _dialog_progress;  //模态对话框
    QProgressDialog * _open_progressdlg; //打开项目的进度条
    std::shared_ptr<ProTreeThread> _thread_create_pro; //智能指针
    std::shared_ptr<OpenTreeThread>  _thread_open_pro; //打开项目的线程
    std::shared_ptr<SlideShowDialog> _slide_show_dlg;
    QMediaPlayer * _player;
    QMediaPlaylist * _playlist;
private slots:
    void SlotItemPressed(QTreeWidgetItem *item,int column);
    void SlotDoubleClickItem(QTreeWidgetItem *doubleItem,int col);
    void SlotImport();
    void SlotSetActive();
    void SlotClosePro();
    void SlotUpdateProgress(int count);
    void SlotFinishProgress();
    void SlotCancelProgress();

    void SlotUpOpendateProgress(int count);
    void SlotFinishOpenProgress();
    void SlotCancelOpenProgress();

    void SlotSlideShow();
public slots:
    void SlotOpenPro(const QString& path);
    void SlotNextShow();
    void SlotPreShow();
    void SlotSetMusic();
    void SlotStartMusic();
    void SlotStopMusic();
signals:
    void SigCancelProgress(); //发送取消信号
    void SigCancelOpenProgress();
    void SigUpdateSelected(const QString& );
    void SigUpdatePic(const QString& );
    void SigClearSelected();
};


#endif // PROTREEWIDGET_H
