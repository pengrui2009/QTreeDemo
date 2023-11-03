
#include "qmytableviewbtndelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QToolTip>
#include <QDebug>

QMyTableViewBtnDelegate::QMyTableViewBtnDelegate(QStringList btnNames, QWidget *parent)
    : QStyledItemDelegate(parent),
      m_btnNames(btnNames)
{
}

QMyTableViewBtnDelegate::~QMyTableViewBtnDelegate()
{

}

void QMyTableViewBtnDelegate::drawPushButton(QPainter* painter, const QStyleOptionViewItem& option, const QString&qsWndText) const
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

void QMyTableViewBtnDelegate::drawCheckBox(QPainter* painter, const QStyleOptionViewItem& option, const QString& qsWndText) const
{
    QStyleOptionButton styleOptBtn;
    styleOptBtn.rect = option.rect;// 设置按钮占据的矩形
    styleOptBtn.icon = qApp->style()->standardIcon(QStyle::SP_DesktopIcon);// 设置按钮图标
    styleOptBtn.iconSize = QSize(32, 32);
    styleOptBtn.text = QString("CheckBox%1").arg(qsWndText);// 设置复选按钮标题
    styleOptBtn.state = QStyle::State_Enabled | QStyle::State_Raised;// 设置按钮状态
    styleOptBtn.direction = Qt::LeftToRight; // 设置按钮水平布局，如果改为Qt::RightToLeft，则按钮图标在按钮标题右侧。
    styleOptBtn.features = QStyleOptionButton::None | QStyleOptionButton::Flat;// 设置按钮风格特点为普通扁平按钮
    qApp->style()->drawControl(QStyle::CE_CheckBox, &styleOptBtn, painter);// 绘制按钮
}

void QMyTableViewBtnDelegate::drawSlider(QPainter* painter, const QStyleOptionViewItem& option) const
{
    QStyleOptionSlider styleOptnSlider;
    styleOptnSlider.rect = option.rect;// 设置按钮占据的矩形
    styleOptnSlider.state = QStyle::State_Enabled;// 设置按钮状态
    styleOptnSlider.minimum = 0; // 设置滑块最小值
    styleOptnSlider.maximum = 100;// 设置滑块最大值
    styleOptnSlider.sliderPosition = 50;// 设置滑块当前值
    qApp->style()->drawComplexControl(QStyle::CC_Slider, &styleOptnSlider, painter); // 绘制滑杆控件
}


TreeItem *QMyTableViewBtnDelegate::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    // return rootItem;
    return nullptr;
}
// 绘制按钮
void QMyTableViewBtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return;
    }

    auto nRowIndex = index.row();
    auto nColIndex = index.column();
    auto wndText = QString("%1").arg(nRowIndex);
    qDebug() << "nRowIndex:" << nRowIndex;

    TreeItem *item = getItem(index);
    qDebug() << "childCount:" << item->childCount();

    if (item->childCount() ==  0)
    {
        return;
    }

    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index);

    // 计算按钮显示区域
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
}

// 响应按钮事件 - 划过、按下
bool QMyTableViewBtnDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
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

