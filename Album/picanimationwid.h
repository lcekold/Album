#ifndef PICANIMATIONWID_H
#define PICANIMATIONWID_H
#include <QWidget>
#include <QTreeWidgetItem>
class PicAnimationWid : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWid(QWidget *parent = nullptr);
    ~PicAnimationWid();
    void SetPixmap(QTreeWidgetItem* item);
    void Start(); //表示开始动画
    void Stop();
    void SlideNext();
    void SlidePre();
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    void UpSelectPixmap(QTreeWidgetItem* item);
    float _factor; //因子，0~1.0之间，用于控制动画
    QTimer* _timer;
    QPixmap _pixmap1;
    QPixmap _pixmap2;
    QTreeWidgetItem *_cur_item; //表示当前的item是哪一个
    QMap<QString,QTreeWidgetItem*> _map_items; //播放过哪些图片
    bool _b_start; //状态，判断是否开始播放
public slots:
    void SlotUpSelectShow(QString path);
    void SlotStartOrStop();
private slots:
    void TimeOut();
signals:
    void SigUpPreList(QTreeWidgetItem *);
    void SigSelectItem(QTreeWidgetItem *);
    void SigStart();
    void SigStop();
    void SigStartMusic();
    void SigStopMusic();
};

#endif // PICANIMATIONWID_H
