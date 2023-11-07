#include "qmytableviewcheckboxdelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QToolTip>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

QMyTableViewCheckboxDelegate::QMyTableViewCheckboxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


QMyTableViewCheckboxDelegate::~QMyTableViewCheckboxDelegate()
{

}

void QMyTableViewCheckboxDelegate::drawPushButton(QPainter* painter, const QStyleOptionViewItem& option, const QString&qsWndText) const
{
    QStyleOptionButton styleOptBtn;
    styleOptBtn.rect = option.rect; // 设置按钮占据的矩形
    styleOptBtn.icon = qApp->style()->standardIcon(QStyle::SP_DesktopIcon); // 设置按钮图标
    styleOptBtn.iconSize = QSize(32, 32);// 设置按钮图标尺寸
    styleOptBtn.text = QString("button%1").arg(qsWndText);// 设置按钮标题
    styleOptBtn.state = QStyle::State_Enabled | QStyle::State_Raised; // 设置按钮状态
    styleOptBtn.direction = Qt::LeftToRight; // 设置按钮水平布局，如果改为Qt::RightToLeft，则按钮图标在按钮标题右侧。
    styleOptBtn.features = QStyleOptionButton::None | QStyleOptionButton::Flat;// 设置按钮风格特点为普通扁平按钮
    qApp->style()->drawControl(QStyle::CE_PushButton, &styleOptBtn, painter); // 绘制按钮
}

void QMyTableViewCheckboxDelegate::drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QString& qsWndText) const
{
    QStyleOptionButton styleOptBtn;
    styleOptBtn.rect = option.rect;// 设置按钮占据的矩形
    styleOptBtn.icon = qApp->style()->standardIcon(QStyle::SP_DesktopIcon);// 设置按钮图标
    styleOptBtn.iconSize = QSize(32, 32);
    styleOptBtn.text = QString("%1").arg(qsWndText);// 设置复选按钮标题
    styleOptBtn.state = QStyle::State_Enabled | QStyle::State_Raised;// 设置按钮状态
    styleOptBtn.direction = Qt::LeftToRight; // 设置按钮水平布局，如果改为Qt::RightToLeft，则按钮图标在按钮标题右侧。
    styleOptBtn.features = QStyleOptionButton::None | QStyleOptionButton::Flat;// 设置按钮风格特点为普通扁平按钮
    qApp->style()->drawControl(QStyle::CE_CheckBox, &styleOptBtn, painter);// 绘制按钮
}

void QMyTableViewCheckboxDelegate::drawSlider(QPainter* painter, const QStyleOptionViewItem& option) const
{
    QStyleOptionSlider styleOptnSlider;
    styleOptnSlider.rect = option.rect;// 设置按钮占据的矩形
    styleOptnSlider.state = QStyle::State_Enabled;// 设置按钮状态
    styleOptnSlider.minimum = 0; // 设置滑块最小值
    styleOptnSlider.maximum = 100;// 设置滑块最大值
    styleOptnSlider.sliderPosition = 50;// 设置滑块当前值
    qApp->style()->drawComplexControl(QStyle::CC_Slider, &styleOptnSlider, painter); // 绘制滑杆控件
}

//TreeItem *QMyTableViewCheckboxDelegate::getItem(const QModelIndex &index) const
//{
//    if (index.isValid()) {
//        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
//        if (item)
//            return item;
//    }
//    // return rootItem;
//    return nullptr;
//}

// 重写paint()函数，实现自定义的绘制操作
void QMyTableViewCheckboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 获取单元格的值
    QVariant value = index.model()->data(index, Qt::DisplayRole);

    // 在单元格中绘制一个矩形和文本
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(option.rect.adjusted(1, 1, -1, -1));
    painter->drawText(option.rect, Qt::AlignCenter, value.toString());
    painter->restore();
}

QWidget *QMyTableViewCheckboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QComboBox *editor = new QComboBox(parent);
//    editor->addItem("优");
//    editor->addItem("良");
//    editor->addItem("一般");
//    editor->addItem("不合格");
//    return editor;
    // 获取当前列的数据
    QVariant data = index.model()->data(index, Qt::DisplayRole);

    // 如果是“Age”列，则创建一个QComboBox对象作为编辑器，并设置其选项和默认值
    if (index.column() == 4)
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItems(QStringList() << "10" << "20" << "30" << "40");
        return comboBox;
    }
    // 如果是“Gender”列，则创建一个QCheckBox对象作为编辑器，并设置其状态
    else if (index.column() == 2)
    {
        QCheckBox *checkBox = new QCheckBox(parent);
        checkBox->setChecked(data.toBool());
        return checkBox;
    }
    // 否则，创建一个QLineEdit对象作为编辑器，并设置其文本
    else
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        lineEdit->setText(data.toString());
        return lineEdit;
    }

}

void QMyTableViewCheckboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    QString str = index.model()->data(index, Qt::EditRole).toString();
//    QComboBox *comboBox = static_cast<QComboBox*>(editor);
//    comboBox->setCurrentText(str);
    // 获取当前列的数据
    QVariant  data = index.model()->data(index, Qt::DisplayRole);

    // 如果是“Age”列，则将当前项的文本设置为QComboBox的当前文本
    if (index.column() == 4)
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        int currentIndex = comboBox->findText(data.toString());
        comboBox->setCurrentIndex(currentIndex);
    }
    // 如果是“Gender”列，则将当前项的状态设置为QCheckBox的状态
    else if (index.column() == 2)
    {
        QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
        checkBox->setChecked(data.toBool());
    }
    // 否则，将当前项的文本设置为QLineEdit的文本
    else
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        lineEdit->setText(data.toString());
    }

}

void QMyTableViewCheckboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QComboBox *comboBox = static_cast<QComboBox*>(editor);
//    QString str = comboBox->currentText();
//    model->setData(index, str, Qt::EditRole);
    // 获取编辑器中的数据
    QVariant newData;
    if (index.column() == 4)
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        newData = comboBox->currentText();
    }
    else if (index.column() == 2)
    {
        QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
        newData = checkBox->isChecked();
        if(newData.toBool()){
            newData = "man";
        }else {
            newData = "woman";
        }
    }
    else
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        newData = lineEdit->text();
    }

    // 将数据保存到模型中
    model->setData(index, newData, Qt::EditRole);
}

void QMyTableViewCheckboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
#if 0
// 绘制按钮
void QMyTableViewCheckboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return;
    }

    auto nRowIndex = index.row();
    auto nColIndex = index.column();
    auto wndText = QString("%1").arg(nRowIndex);
    qDebug() << "nRowIndex:" << nRowIndex;

//    TreeItem *item = getItem(index);
//    qDebug() << "childCount:" << item->childCount();

//    if (item->childCount() ==  0)
//    {
//        return;
//    }

    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index);

    // 计算按钮显示区域
    drawCheckBox(painter, option, "选择数据");
#if 0
    int nCount = m_btnNames.count();

    int w = nCount != 0 ? option.rect.width() / nCount : 0;
    if(w < 0) {
        qDebug()<<"ButtonDelegate btns 太多了！";
        return;
    }

    for (int i = 0; i < nCount; ++i)
    {
        // 绘制按钮
        QStyleOptionButton button;
        button.rect =  option.rect.adjusted(4 + i*w , 4, -(w * ( nCount - i -1 ) + 4)  , -4);
        button.text = m_btnNames.at(i);
        button.state |= QStyle::State_Enabled;

        if (button.rect.contains(m_mousePoint))
        {
            if (m_nType == 0)
            {
                button.state |= QStyle::State_MouseOver;
            }
            else if (m_nType == 1)
            {
                button.state |= QStyle::State_Sunken;
            }
        }
        QPushButton pushBtn;
        if (i == nCount - 1)
        {
            pushBtn.setStyleSheet("QPushButton{border-width: 0px;\
                                position: absolute;\
                                left: 0px;\
                                top: 0px;\
                                max-width: 80px;\
                                width:80px;\
                                height: 30px;\
                                background: inherit;\
                                background-color: rgba(255, 255, 255, 0);\
                                border-width: 1px;\
                                border-style: solid;\
                                border-color: red;\
                                border-radius: 10px;\
                                font-size: 11px;\
                                color: red;}\
                                QPushButton:hover{background-color:red; color:#FFFFFF;}");
        }
        else
        {
            pushBtn.setStyleSheet("QPushButton{border-width: 0px;\
                                position: absolute;\
                                left: 0px;\
                                top: 0px;\
                                max-width:120px; \
                                width:120px;\
                                height: 30px;\
                                background: inherit;\
                                background-color: rgba(255, 255, 255, 0);\
                                border-width: 1px;\
                                border-style: solid;\
                                border-color: rgba(2, 182, 212, 1);\
                                border-radius: 10px;\
                                font-size: 11px;\
                                color: #000000;}\
                                QPushButton:hover{background-color:rgba(2, 182, 212, 1); color:#FFFFFF;}");
        }

        pushBtn.style()->drawControl(QStyle::CE_PushButton, &button, painter, &pushBtn);
    }
#endif

}
#endif

#if 0
// 响应按钮事件 - 划过、按下
bool QMyTableViewCheckboxDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    m_nType = -1;
    bool bRepaint = false;
    QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
    m_mousePoint = pEvent->pos();

    int nCount = m_btnNames.count();

    int w = nCount != 0 ? option.rect.width() / nCount : 0;
    if(w < 0) {
        qDebug()<<"ButtonDelegate btns 太多了！";
        return false;
    }

    // 还原鼠标样式
    QApplication::restoreOverrideCursor();

    for (int i = 0; i < nCount; ++i)
    {
        QStyleOptionButton button;
        button.rect =  option.rect.adjusted(4 + i*w , 4, -(w * ( nCount - i -1 ) + 4)  , -4);

        // 鼠标位于按钮之上
        if (!button.rect.contains(m_mousePoint))
            continue;

        bRepaint = true;
        switch (event->type())
        {
        // 鼠标滑过
        case QEvent::MouseMove:
        {
            // 设置鼠标样式为手型
            QApplication::setOverrideCursor(Qt::PointingHandCursor);

            m_nType = 0;

            QToolTip::showText(pEvent->globalPos(), m_btnNames.at(i));
            break;
        }
        // 鼠标按下
        case QEvent::MouseButtonPress:
        {
            m_nType = 1;
            break;
        }
        // 鼠标释放
        case QEvent::MouseButtonRelease:
        {
            switch (i)
            {
            case 0:
            {
                emit editData(index);
                break;
            }
            case 1:
            {
                emit deleteData(index);
                break;
            }
            default:
            break;
            }
        }
        default:
            break;
        }
    }

    return bRepaint;
}
#endif
