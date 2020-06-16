/************************************************************************
* 版权所有 (C) 梁振    Email:  liang1057@163.com.cn
*
* 文件名称： QsfTitleBar.h
* 内容摘要： 自定义界面标题栏类
* 其它说明： 自定义界面的标题栏，按照Office Ribbon的扁平化策略实现了一个左侧按钮+中间标题+用户文本+右侧按钮 的布局
* 当前版本： 0.1
* 作    者： Leon
* 完成日期： [3/20/2013]
*
* 修改记录1：暂无
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容：
* 修改记录2：…
************************************************************************/

#ifndef QSF_TITLEBAR_H
#define QSF_TITLEBAR_H

#include <QtCore/QString>

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QHBoxLayout>
#include "QsfToolButton.h"
   
#include "QsfToolButton.h"

class      QsfTitleBar : public QWidget
{
    Q_OBJECT

public:
    QsfTitleBar(QWidget *parent = NULL);
    ~QsfTitleBar();

    /** @brief  设置窗口标题.
    *
    *  @details 设置窗口标题.
    *  @param   title 窗口的标题.
    *  @return  .
    */
    void setWindowTitle(QString title, Qt::Alignment tAlignment = Qt::AlignCenter);
    QString windowTitle();

    void addLeftAction(QPushButton* tAct);
    void addRightAction(QPushButton* tAct);

private:
    QLabel* m_titleLab;
    QIcon* m_icon;

    QList<QPushButton*> m_leftActions;
    QList<QPushButton*> m_rightActions;

    QHBoxLayout* m_layout, *layLeft, *layRight;

};

#endif //QSF_TITLEBAR_H