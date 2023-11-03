#ifndef QMYTABLEVIEWBTNDELEGATE_H
#define QMYTABLEVIEWBTNDELEGATE_H


#include <QObject>
#include <QPushButton>
#include<QStyledItemDelegate>

#include "treeitem.h"

class QMyTableViewBtnDelegate: public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QMyTableViewBtnDelegate(QStringList btnNames, QWidget *parent = 0);
    ~QMyTableViewBtnDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

signals:
    void editData(const QModelIndex &index);
    void deleteData(const QModelIndex &index);

private:
    QPoint m_mousePoint;  // 鼠标位置
    int m_nType;  // 按钮状态：0-划过 1-按下
    QStringList m_btnNames;

    void drawPushButton(QPainter* painter, const QStyleOptionViewItem& option, const QString&qsWndText) const;
    void drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QString& qsWndText) const;
    void drawSlider(QPainter* painter, const QStyleOptionViewItem& option) const;

    TreeItem *getItem(const QModelIndex &index) const;
};



#endif // QMYTABLEVIEWBTNDELEGATE_H
