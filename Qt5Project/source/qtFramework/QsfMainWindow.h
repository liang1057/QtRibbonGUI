/************************************************************************
* 版权所有 (C) 梁振    Email:  liang1057@163.com.cn
* 
* 文件名称： QsMainWindow.h
* 内容摘要： 
* 其它说明： 无
* 当前版本： 0.1
* 作    者： Leon
* 完成日期： [2020/06/16]
* 
* 修改记录1：暂无
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/

#ifndef QSMAINWINDOW_H
#define QSMAINWINDOW_H

#include <QTabWidget>
#include <QMainWindow>
#include <QDragMoveEvent>

#include "SgfParamManager.h"
#include "QsfTitleBar.h"


/************************************************************************
类声明: 工作窗口
************************************************************************/
/** @brief     工作窗口.
*
*  @details   工作窗口的主体是Tab窗口.
*/
class      QsfWorkWindow : public QMainWindow 	
{
    Q_OBJECT
public:
    /** @brief 构造函数.
    *
    *  @details   构造函数.
    *  @param  parent 父指针.
    *  @param  flags flags.
    */
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	QsfWorkWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
#else
    QsfWorkWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
#endif 
    /** @brief     析构函数.
    *
    *  @details   析构函数,为了防止资源泄漏所以为virtual函数.
    */
    virtual ~QsfWorkWindow();

public:
    /** @brief    获取当前tab页Widget函数.
    *
    *  @details   获取当前tab页Widget函数.
    *  @return    当前Widget指针.
    */
    QWidget* getCurrentTabWidget();

    /** @brief    获取当前tab页SgfWidget函数.
    *
    *  @details   获取当前tab页SgfWidget函数.
    *  @return    当前SgfWidget指针.
    */
    QWidget * currentTabWidget();

    /** @brief     获取tabWidget函数.
    *
    *  @details   获取tabWidget函数.
    *  @return    SgfTabWidget指针.
    */
    QTabWidget* workSpace();

private:
    QTabWidget* m_workspace;
};

/************************************************************************
                  类声明:
************************************************************************/

/** @brief 
*
*  @details 
*/
/** 默认 布局文件名称 */
const QString MAINWINDOWLAYOUTFILE = "sw_mainframe.layout";
/** @brief 应用程序主窗口对象
*
*  @details 定义一个应用程序主窗口的宏对象,可在插件中访问主窗口资源.这是一个指针
*/
#define QSF_MainWindow ((QsfMainWindow*)(COREOBJECT(QsfMainWindow)))

#define QSF_MainWindow_GetParam(type, name) static_cast<type*>(GET_COREOBJECT(SgfParamManager)->getParamValue( string(name)))
#define QSF_MainWindow_GetParam(type, name) ((type*)(GET_COREOBJECT(SgfParamManager)->getParamValue( string(name))))

/**************************************************************************
*                             类声明                                     *
**************************************************************************/

/** @brief 应用程序主窗口类.
*
*  @details 平台应用程序框架服务-应用程序主窗口类
*/
class      QsfMainWindow : public QWidget //, public SgfParamManager
{
    Q_OBJECT
public:
    QsfMainWindow();
    ~QsfMainWindow();
    static void createMainWindow();

    QsfTitleBar* titleBar(){
        return m_titleBar;
    }
    QsfWorkWindow* workWindow(){
        return m_workWindow;
    }
    QTabWidget* tabMenuWidget(){
        return m_tableMenu;
    }

    /** @brief 创建DockWidget. */
    QDockWidget* createDockWidget(QString title, QString name, Qt::DockWidgetArea area);
    /** @brief 添加DockWidget. */
    void addDockWidget(QDockWidget* tDock, QString title, Qt::DockWidgetArea area);

    /** @brief 创建工作页Widget. */
    QWidget* createWorkWidget(QString title, QString name);
    /** @brief 添加工作页Widget. */
    void addWorkWidget(QWidget* workTab, QString title);

private:
    QsfWorkWindow* m_workWindow;
    QsfTitleBar* m_titleBar;
    QTabWidget* m_tableMenu;


protected:
    /** @brief  标题范围. */
    QRect m_titleRect;
    /** @brief  鼠标上一次的位置. */
    QPoint oldMousePos;
    /** @brief  鼠标单击. */
    void mousePressEvent(QMouseEvent *event);
    /** @brief  鼠标双击. */
    void mouseDoubleClickEvent ( QMouseEvent * event);
    /** @brief  鼠标拖动. */
    void mouseMoveEvent(QMouseEvent *event);
};


#endif // QsfMainWindow_H