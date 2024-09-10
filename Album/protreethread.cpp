#include "protreethread.h"
#include <QDir>
#include "const.h"
#include "protreeitem.h"
ProTreeThread::ProTreeThread(const QString &src_path,
                             const QString &dist_path,
                             QTreeWidgetItem *parent_item,
                             int file_count, QTreeWidget *self,
                             QTreeWidgetItem *root, QObject *parent)
    :QThread(parent),_src_path(src_path),_dist_path(dist_path),
    _file_count(file_count),_parent_item(parent_item),_self(self),
    _root(root),_bstop(false)
{

}

ProTreeThread::~ProTreeThread()
{

}

void ProTreeThread::run()
{
    CreateProTree(_src_path,_dist_path,_parent_item,_file_count,_self,_root);
    if(_bstop){  //停止了
        auto path=dynamic_cast<ProTreeItem*>(_root)->GetPath();  //获取路径
        auto index=_self->indexOfTopLevelItem(_root); //获取根节点的索引
        delete _self->takeTopLevelItem(index);  //删掉根节点的索引
        QDir dir(path);
        dir.removeRecursively();  //清除文件夹
        return;
    }

    emit SigFinishProgress(_file_count);  //发送完成信号
}


//创造目录树结构，参数分别是：源地址、目的地址、父节点、文件数目、文件本身、根节点、前一个节点
void ProTreeThread::CreateProTree(const QString &src_path, const QString &dist_path, QTreeWidgetItem *parent_item, int &file_count, QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem *preItem)
{
    if(_bstop){
        return;
    }
    bool needcopy=true; //是否需要拷贝,如果是同一个路径则不需要拷贝，如果不是同一个路径则需要拷贝，即源路径和目的路径的关系
    if(src_path==dist_path){  //源路径和目的路径相同
        needcopy=false;  //不需要拷贝
    }

    QDir import_dir(src_path);  //根据源路径生成一个导入的路径
    QStringList nameFilters;
    import_dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);  //过滤掉.和..，留下来文件夹和文件
    import_dir.setSorting(QDir::Name); //按照文件夹的名字来排序
    QFileInfoList list=import_dir.entryInfoList();  //返回过滤之后所有有效的文件和文件夹

    //遍历文件夹下的所有文件
    for(int i=0;i<list.size();i++){
        if(_bstop){ //若收到停止信号则停止
            return;
        }

        QFileInfo fileInfo=list.at(i);  //获取到这个文件
        bool bIsDir=fileInfo.isDir(); //判断是否是目录
        if(bIsDir){  //如果是目录(文件夹)
            if(_bstop){
                return;
            }

            file_count++;
            emit SigUpdateProgress(file_count);

            QDir dist_dir(dist_path); //使用目的路径构建一个文件夹
            QString sub_dist_path=dist_dir.absoluteFilePath(fileInfo.fileName());
            QDir sub_dist_dir(sub_dist_path);  //将子文件夹的路径转换为一个目录
            if(!sub_dist_dir.exists()){  //判断子文件夹目录是否存在
                //如果不存在则创建
                bool ok = sub_dist_dir.mkpath(sub_dist_path);
                if(!ok){  //若创建失败则跳过
                    continue;
                }
            }
            //添加文件夹
            auto * item=new ProTreeItem(parent_item,fileInfo.fileName(),sub_dist_path,
                                         root,TreeItemDir);

            item->setData(0,Qt::DisplayRole,fileInfo.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.png"));
            item->setData(0,Qt::ToolTipRole,sub_dist_path);

            //将这个文件夹下面的文件拷贝过来(递归调用)
            CreateProTree(fileInfo.absoluteFilePath(),sub_dist_path,
                          item,file_count,self,root,preItem);
        }else{ //如果是文件
            if(_bstop){  //若收到静止信号则停止
                return;
            }

            const QString& suffix=fileInfo.completeSuffix(); //取出完整的后缀
            if(suffix!="png"&&suffix!="jpeg"&&suffix!="jpg"){ //如果不是图片文件
                continue;//直接跳过
            }

            file_count++; //文件满足要求则个数++
            emit SigUpdateProgress(file_count); //传递信号
            if(!needcopy){ //如果不需要拷贝
                continue;  //直接跳过
            }

            QDir dist_dir(dist_path);  //目的文件夹
            QString dist_file_path = dist_dir.absoluteFilePath(fileInfo.fileName());//拼接地址，将目的文件夹路径和需要拷贝的文件名进行拼接
            if(!QFile::copy(fileInfo.absoluteFilePath(),dist_file_path)){  //判断拼接操作是否成功
                continue; //失败就跳过
            }

            auto * item = new ProTreeItem(parent_item, fileInfo.fileName(),
                                         dist_file_path, root,TreeItemPic);

            item->setData(0,Qt::DisplayRole,fileInfo.fileName()); //文件名
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/pic.png"));
            item->setData(0,Qt::ToolTipRole,dist_file_path); //提示路径信息

            if(preItem){  //若前一个节点不为空则链接起来
                auto * pre_proitem=dynamic_cast<ProTreeItem*>(preItem);
                pre_proitem->SetNextItem(item);
            }
            //链接，双向的
            item->SetPreItem(preItem);
            preItem=item;
        }
    }
}

void ProTreeThread::SlotCancelProgress()
{
    this->_bstop=true;
}

