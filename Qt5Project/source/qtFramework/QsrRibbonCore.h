#ifndef QSR_RIBBON_CORE_H
#define QSR_RIBBON_CORE_H

#include <QObject>
#include <QToolBar>
#include <QList>
#include <QLabel>
#include <QAction>
#include <QPainter>
#include <QStyleOption>
#include <QAbstractNativeEventFilter>

    

/*
*  当前的程序主要是运行在windows系统下， 如果运行在Linux下还需要进行优化，比如主界面的外框等
*/

// 从大于0的开始， RIBBON开始的是控件，三级的归属于二级
//（暂时还没有使用）
enum RIBBON_OBJECT_TYPE  // RIBBON 对象
{
	RIBBON_OBJECTITEM = 0,
    RIBBON_TITLEBAR_QuickAccessBar,   // 标题栏上左侧的 快捷图标
	RIBBON_TITLEBAR_Title,            // 标题栏的 标题
	RIBBON_TITLEBAR_UserInfo,         // 标题栏上的 用户信息
	RIBBON_TITLEBAR_StanderdButton,   // 标题栏上的 右侧按钮
	RIBBON_TITLEBAR, // 以上是标题栏的内容
	RIBBON_MENUBAR_WidgetActionLeft,  // 比如word中的“文件”按钮
	RIBBON_MENUBAR_WidgetActionRight, // 右侧的按钮
	RIBBON_MENUBAR, // 以上是菜单栏的内容
	RIBBON_TOOLBAR_GroupWidget, // 工具栏的控件容器（如 word中的“段落”为一组）
	RIBBON_TOOLBAR_IconWidget,  // 大图标缩略图
	RIBBON_TOOLBAR_Saperator,   // 工具栏控件容器中的分隔线
	RIBBON_TOOLBAR,// 以上是工具栏的内容
	RIBBON_CONTRAL_Control // 具体的控件
};

#include <QPushButton>

/** @brief   Ribbon操作.
*  @details  一个操作对应一个图标，或者控件
*/
typedef QWidget ribbonAction;


/** @brief   Ribbon Widget 的基类.
*  @details  为了实现Qss对QWidget的重绘
*/
class      RobbonWidget :public QWidget
{
public:
	RobbonWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~RobbonWidget();

protected:
	virtual void paintEvent(QPaintEvent *event);

private:

};

//////////////////////////////////////////////////////////////////////////

// 需要自定义一套按钮，用来显示/隐藏 图标、文字， 参考之前实现的那个按钮的代码
/** @brief   RibbonControlBase 控件基类.
*  @details  
*/
class      RibbonControlBase
{
public:
	RibbonControlBase();
	~RibbonControlBase();

	/** @brief   设置控件在GroupWidget中的位置，有两套位置可以设置.
	*   @details 如果只有一种布局则不需要设置index参数.
	*/
	void setGroupPos(QPoint tPos, int index = -1);
	QPoint groupPos(int index);

    virtual void setText(QString &text) {};
    virtual void setIcon(const QIcon &icon) {};
    virtual void setEnabled(bool &tEnabled) {};


private:
	QPoint m_pos0, m_pos1;

};



/** @brief   RibbonPushButton 普通Ribbon按钮类.
*  @details
*/
class      RibbonToolButton : public QPushButton, public RibbonControlBase
{
	Q_OBJECT
public:
	RibbonToolButton(QWidget *parent = Q_NULLPTR);
	RibbonToolButton(const QString &text, QWidget *parent = Q_NULLPTR);
	RibbonToolButton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
	~RibbonToolButton();

	void setTxtVisible(bool tVal);
	bool txtVisible();

	/** @brief   对齐方式. */
	void setAlignment(Qt::Alignment flag);

	/** @brief   设置Action.  //放弃使用： 不再接受从外部赋值 */
    //void setAction(QAction* tAction);
	/** @brief   获取Action. 用于从Ribbon风格切换到传统样式的菜单工具栏等 */
    QAction* getAction();

    virtual void setText(QString &text);
    virtual void setIcon(const QIcon &icon);
    virtual void setEnabled(bool &tEnabled);

private:
	QString m_text;
	bool m_txtVisible;

	/** @brief   Action指针，从外部指定.  */
    QAction* m_action;

// private:
// 	RIBBON_OBJECT_TYPE m_objType;
};

/** @brief   RibbonPushButton 大的Ribbon按钮类.
*  @details
*/
class      RibbonToolButtonBig : public RobbonWidget, public RibbonControlBase
{
	Q_OBJECT
public:
	RibbonToolButtonBig(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);
	~RibbonToolButtonBig();

	QPushButton* pushButton() const;
	QLabel* label() const;
	void setExtentIconVisible(bool tVal);

    virtual void setText(QString &text) {};
    virtual void setIcon(const QIcon &icon){};
    virtual void setEnabled(bool &tEnabled){};


signals:
    void triggered(bool checked = false);

private:
	QPushButton* m_pushButton;
	QLabel* m_label, *m_label_extent;
};


// class      ribbonAction: public QWidget
// {
// 	Q_OBJECT
// public:
// 	ribbonAction();
// 	~ribbonAction() {};
// 
// private:
// 
// 
// };

//基类
// class      QsrRibbonObject
// {
// public:
// 	QsrRibbonObject() {};
// 	~QsrRibbonObject() {};
// };

class      QsrRibbonQuickAccessToolBar : /*public QsrRibbonObject,*/ public QToolBar
{
	Q_OBJECT
public:
	QsrRibbonQuickAccessToolBar() ;
	~QsrRibbonQuickAccessToolBar() {};
};

/** @brief   标题栏.
*  @details  标题栏的组成(从左到右): 快捷工具栏，标题控件，用户信息控件，系统按钮（放置系统按钮：设置、最小化、最大化、关闭）
*/
class      QsrRibbonTitleBar : /*public QsrRibbonObject ,*/ public RobbonWidget
{
	Q_OBJECT
public:
	QsrRibbonTitleBar();
	~QsrRibbonTitleBar();

	/** @brief  设置窗口标题.
	*
	*  @details 设置窗口标题.
	*  @param   title 窗口的标题.
	*  @return  .
	*/
	void setTitle(QString title);
	QString getTitle();

	/** @brief  设置工具条的文字. */
	void setToolsText(QString txt);

	void addQuickAction(QAction *action);
	void addSysAction(QAction* action);

	void setUserInfo(QString txt);

private:
	QLabel* m_titleLable1, m_ToolsLabel, m_titleLable2;
	QLabel* m_userInfoLabel;
	QsrRibbonQuickAccessToolBar* m_quickAccessToolBar, *m_systemButton;
};


/** @brief   Ribbon 操作组.
*  @details  Ribbon 操作组
*/
#include <QGridLayout>
#include <QActionGroup>
class      QtbGroupWidget :  public RobbonWidget
{
	Q_OBJECT
public:
	QtbGroupWidget();
	~QtbGroupWidget();

	void setTitle(QString tTitle);
	void addAction(ribbonAction* rAct, int row, int col, int rowSpan = 1, int columnSpan = 1, Qt::Alignment alignment = Qt::Alignment());
	void addAction(RibbonToolButton* rAct, int row, int col, int rowSpan /*= 1*/, int columnSpan /*= 1*/, Qt::Alignment alignment /*= Qt::Alignment()*/);

    QActionGroup* getActionGroup() const;
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	QGridLayout* m_gridLayout;
	QLabel* m_groupTitleLabel;

    QActionGroup* m_actionGroup;
};

/** @brief   Ribbon菜单栏.
*  @details  Ribbon菜单栏
*/
#include <QMap>
#include <QHBoxLayout>
#include <QTabBar>
#include <QTabWidget>
#include <QStackedWidget>
class      QtbMenuBar : /*public QsrRibbonObject ,*/ public RobbonWidget
{
	Q_OBJECT
public:
	QtbMenuBar();
	~QtbMenuBar();

	/** @brief   增加操作按钮.  */
	void addAction(ribbonAction* tAction,int tIndex);
	/** @brief   增加菜单. menuName是唯一的，也是显示的 */
	void addMenu(QString menuName);

	/** @brief   增加扩展型菜单. menuName是全局唯一的，showName是显示的可以重复 */
//     void addExtendedMenu(QString menuName, QString showName);
	void setMenuVisible(QString menuName, bool tIsVisible);
	bool isMenuVisible(QString menuName);

	QtbGroupWidget* addGroup(QString menuName, QString txtGroupTitle);
    void menuReady(QString menuName);

	void setExtentBtnIcon(QIcon icoExtent, QIcon icoHide);

	bool isToolBarVisible();
public slots:
	void setToolBarVisible(bool tVal);

private slots:
    /** @brief   Ribbon工具栏折叠/展开按钮的操作.  */
	void onExtentToggled();
	void onCurrentTabChenged(int index);

protected:
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);

private:
    /** @brief   菜单栏的TabBar.  */
    QTabBar* m_menuTabBar;
    QTabBar* m_ExtentedMenuTabBar;
    /** @brief   Ribbon菜单的主layout.  */
	QHBoxLayout* m_layout;
    /** @brief   Ribbon菜单的主layout.  */
	QMap<QString, RobbonWidget*> m_StaWidMap;

    /* 暂时不提供扩展型的可变菜单*/
//     QHBoxLayout* m_layoutExtented;
//     /** @brief   Ribbon扩展菜单的按钮.  */
//     QMap<QString, QPushButton*> m_extentedBtnMap;
//     QWidget* m_extentedWidget;

	QStackedWidget* m_toolBarStackedWid;

	/** @brief   折叠按钮.  */
	RibbonToolButton* m_extentBtn; 

	bool m_toolBarVisible;

	QIcon m_icoExtent, m_icoHide;

};

/** @brief   Ribbon工具栏.
*  @details  Ribbon工具栏.
*/
class      QtbToolBar : /*public QsrRibbonObject ,*/ public QTabWidget
{
	Q_OBJECT
public:
	QtbToolBar();
	~QtbToolBar();

	void addMenu(QString txt);
private:
// 	QTabBar m_menuTabBar;
// 	QHBoxLayout m_layout;
// 	QMap<QString, RobbonWidget*> m_menuLabelMap;
//	QTabWidget* m_toolTabWidget;
};



/** @brief   主窗口.
*  @details  
*/
#include <QDragMoveEvent>
class QsfWorkWindow;
class QDockWidget;
//#include "SgfParamManager.h"
class      QtbMainWindow :  public RobbonWidget //, public SgfParamManager
{
	Q_OBJECT
public:
	QtbMainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
	~QtbMainWindow();

	QsrRibbonTitleBar* titleBar();
	QtbMenuBar* menuBar();

	/** @brief 创建DockWidget. */
	QDockWidget* createDockWidget(QString title, QString name, Qt::DockWidgetArea area);

	/** @brief 创建工作页Widget. */
	QWidget* createWorkWidget(QString title, QString name);
	/** @brief 添加已有的widget作为工作页Widget. */
    void addWorkWidget(QWidget* tWidget);


private:
	QsrRibbonTitleBar* m_titleBar;
	QtbMenuBar* m_menuBar;

protected:

	/** @brief  标题范围. */
	QRect m_titleRect;

	/** @brief  工作窗口. */
	QsfWorkWindow* m_workWindow;


	/** @brief  鼠标上一次的位置. */
	QPoint oldMousePos;
	/** @brief  鼠标单击. */
	void mousePressEvent(QMouseEvent *event);
	/** @brief  鼠标上双击. */
	void mouseDoubleClickEvent(QMouseEvent * event);
	/** @brief  鼠标拖动. */
	void mouseMoveEvent(QMouseEvent *event);

	virtual void resizeEvent(QResizeEvent *event);

    virtual void paintEvent(QPaintEvent *event);


public slots:
	void onSkin();
};

/** @brief   主窗口借助dwmapi实现在windows下的拖动
*  @details  Linux下的暂时没有做实现。次出应当用宏来统一windows和linux
*/
#include <windowsx.h>
#include <dwmapi.h>
class NativeEventFilter : public QAbstractNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE
    {
#ifdef Q_OS_WIN
        if (eventType != "windows_generic_MSG")
            return false;

        MSG* msg = static_cast<MSG*>(message);
        QWidget* widget0 = QWidget::find(reinterpret_cast<WId>(msg->hwnd));
        if (widget0 == NULL)
            return false;

        QtbMainWindow* widget = static_cast<QtbMainWindow*>(widget0);
        if (!widget)
            return false;

        if (widget->isMaximized())
            return false;

        switch (msg->message) 
        {
        //         case WM_NCCALCSIZE: {  // 如果处理该消息，dock窗口或子窗口会有问题
        //             *result = 0;
        //             return true;
        //         }

            case WM_NCHITTEST: {
                const LONG borderWidth = 9;
                RECT winrect;
                GetWindowRect(msg->hwnd, &winrect);
                long x = GET_X_LPARAM(msg->lParam);
                long y = GET_Y_LPARAM(msg->lParam);

                // bottom left
                if (x >= winrect.left && x < winrect.left + borderWidth &&
                    y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOMLEFT;
                    return true;
                }

                // bottom right
                if (x < winrect.right && x >= winrect.right - borderWidth &&
                    y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOMRIGHT;
                    return true;
                }

                // top left
                if (x >= winrect.left && x < winrect.left + borderWidth &&
                    y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOPLEFT;
                    return true;
                }

                // top right
                if (x < winrect.right && x >= winrect.right - borderWidth &&
                    y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOPRIGHT;
                    return true;
                }

                // left
                if (x >= winrect.left && x < winrect.left + borderWidth)
                {
                    *result = HTLEFT;
                    return true;
                }

                // right
                if (x < winrect.right && x >= winrect.right - borderWidth)
                {
                    *result = HTRIGHT;
                    return true;
                }

                // bottom
                if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOM;
                    return true;
                }

                // top
                if (y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOP;
                    return true;
                }

                return false;
            }
            default:
                break;
        }

        return false;
#else
        return false;
#endif
    }
};






























#endif //QSF_TITLEBAR_H