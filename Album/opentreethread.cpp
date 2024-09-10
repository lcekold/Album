#include "opentreethread.h"
#include <QDir>
#include "protreeitem.h"
#include "const.h"
OpenTreeThread::OpenTreeThread(const QString &src_path,int file_count,
                               QTreeWidget *self,QObject *parent)
    :QThread(parent),_bstop(false),_src_path(src_path),_file_count(file_count),
      _self(self),_root(nullptr)
{

}

void OpenTreeThread::OpenProTree(const QString &src_path, int &file_count, QTreeWidget *self)
{
    QDir src_dir(src_path);
    auto name=src_dir.dirName();
    auto * item=new ProTreeItem(self,name,src_path,TreeItemPro); //创建根节点
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
    item->setData(0,Qt::ToolTipRole,name);
    _root=item;
    RecursiveProTree(src_path,file_count,self,_root,item,nullptr); //递归调用
}

void OpenTreeThread::run()
{
    OpenProTree(_src_path,_file_count,_self);
    if(_bstop){
        auto path=dynamic_cast<ProTreeItem*>(_root)->GetPath();  //获取路径
        auto index=_self->indexOfTopLevelItem(_root); //获取根节点的索引
        delete _self->takeTopLevelItem(index);  //删掉根节点的索引
        QDir dir(path);
        dir.removeRecursively();  //清除文件夹
        return;
    }

    emit SigFinshProgress(_file_count);
}

void OpenTreeThread::RecursiveProTree(const QString &src_path, int &file_count, QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem *parent, QTreeWidgetItem *preitem)
{
    QDir src_dir(src_path);
    src_dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    src_dir.setSorting(QDir::Name);
    QFileInfoList list=src_dir.entryInfoList(); //返回当前目录里面遍历的结果（包含文件夹和文件）
    for(int i=0;i<list.size();i++){
        if(_bstop){  //判断是否停止
            return;
        }

        QFileInfo fileInfo = list.at(i); //获得文件
        bool bIsDir=fileInfo.isDir();  //是否是目录
        if(bIsDir){ //如果是目录
            if(_bstop){
                return;
            }
            file_count++;
            emit SigUpdateProgress(file_count); //更新进度条
            auto * item=new ProTreeItem(_root,fileInfo.fileName(),fileInfo.absoluteFilePath(),
                                         _root,TreeItemDir);
            item->setData(0,Qt::DisplayRole,fileInfo.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
            item->setData(0,Qt::ToolTipRole,fileInfo.absoluteFilePath());
            RecursiveProTree(fileInfo.absoluteFilePath(),file_count,
                             self,root,item,preitem);  //由于是文件夹，因此需要递归调用得到里面的文件
        }else{
            if(_bstop){
                return;
            }

            const QString& suffix=fileInfo.completeSuffix(); //获得文件后缀
            if(suffix!="png"&&suffix!="jpeg"&&suffix!="jpg"){  //过滤后缀
                continue;
            }
            file_count++;
            emit SigUpdateProgress(file_count);  //更新进度条

            auto * item =new ProTreeItem(_root,fileInfo.fileName(),fileInfo.absoluteFilePath(),
                                         _root,TreeItemPic);

            item->setData(0,Qt::DisplayRole,fileInfo.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/pic.png"));
            item->setData(0,Qt::ToolTipRole,fileInfo.absoluteFilePath());

            if(preitem){
                auto * pre_proitem=dynamic_cast<ProTreeItem*>(preitem);
                pre_proitem->SetNextItem(item);
            }
            item->SetPreItem(preitem);
            preitem=item;
        }
    }

    emit SigFinshProgress(file_count);
}

void OpenTreeThread::SlotCancelProgress()
{
    this->_bstop=true;
}
