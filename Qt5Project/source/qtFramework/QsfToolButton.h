/************************************************************************
* 版权所有 (C) 梁振    Email:  liang1057@163.com.cn
* 
* 文件名称： QsfToolButton.h
* 内容摘要： 自定义界面按钮
* 其它说明： 如自定义界面中的最大、最小、关闭、换肤按钮等
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

#ifndef QSFTOOLBUTTON_H
#define QSFTOOLBUTTON_H

#include <QPushButton>
    
/************************************************************************
                  类声明:
************************************************************************/

/** @brief 自定义界面的按钮
*
*  @details 自定义界面的按钮类
*/
class      QsfToolButton: public QPushButton
{
    Q_OBJECT
public:
    enum ButtonMouseState  
    {  
        ButtonMouseDefault = 0,  
        ButtonMouseEnter,  
        ButtonMousePress,  
        ButtonMouseNone  
    }; 

public:

    QsfToolButton( QWidget * parent = 0 );
    ~QsfToolButton();

    void setIcon(QString icon, QString icon_hover, QString icon_pressed);
private:
    QIcon m_icon, m_icon_hover, m_icon_pressed;

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};
#endif // QSFTOOLBUTTON_H