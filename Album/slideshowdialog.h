#ifndef SLIDESHOWDIALOG_H
#define SLIDESHOWDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
namespace Ui {
class SlideShowDialog;
}

class SlideShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlideShowDialog(QWidget *parent,QTreeWidgetItem* first_item,
                            QTreeWidgetItem* last_item);
    ~SlideShowDialog();

private:
    Ui::SlideShowDialog *ui;
    QTreeWidgetItem* _first_item;
    QTreeWidgetItem* _last_item;
public slots:
    void SlotSlideNext();
    void SlotSlidePre();
};

#endif // SLIDESHOWDIALOG_H
