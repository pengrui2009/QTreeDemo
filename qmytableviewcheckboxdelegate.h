#ifndef QMYTABLEVIEWCHECKBOXDELEGATE_H
#define QMYTABLEVIEWCHECKBOXDELEGATE_H

#include <QObject>
#include <QCheckBox>
#include <QItemDelegate>
#include <QStyledItemDelegate>

class QMyTableViewCheckboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QMyTableViewCheckboxDelegate(QObject *parent=0);
    ~QMyTableViewCheckboxDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

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


};

#endif // QMYTABLEVIEWCHECKBOXDELEGATE_H
