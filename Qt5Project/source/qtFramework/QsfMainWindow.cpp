#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QBitmap>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDockWidget>
#include <QTreeWidget>
#include <QStatusBar>

//#include "SgfPlatformCore.h"
//#include "SgfSingleCoreObjectImpl.h"
//#include "SgfCoreManager.h"

#include "QsfMainWindow.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
QsfWorkWindow::QsfWorkWindow(QWidget *parent /* = 0 */, Qt::WindowFlags flags /* = 0 */)
#else
QsfWorkWindow::QsfWorkWindow(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
#endif 

:QMainWindow(parent,flags)
{
    setObjectName("QsfWorkWindow");

	//允许嵌套dock
	setDockNestingEnabled(true);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    m_workspace = new QTabWidget;
    setCentralWidget(m_workspace);
    m_workspace->setTabsClosable(false);

    /*状态条*/
    QStatusBar* statusBar = new QStatusBar();
    statusBar->setObjectName("QsfStatuBar");
    this->setStatusBar(statusBar);

    this->setStatusTip("自定义程序框架  V1.0       作者: 梁振 liang1057@163.com");
}

QsfWorkWindow::~QsfWorkWindow()
{
    delete m_workspace;
}


QWidget* QsfWorkWindow::getCurrentTabWidget()
{
    if (m_workspace != NULL)
    {
        return m_workspace->currentWidget();
    }

    return NULL;
}

QWidget * QsfWorkWindow::currentTabWidget()
{
    return getCurrentTabWidget();
}

QTabWidget* QsfWorkWindow::workSpace()
{
    return m_workspace;
}

void QsfMainWindow::createMainWindow()
{
    //将参数管理器注册到核心中
    //REGIST_OBJECT(QsfMainWindow);
}

QsfMainWindow::QsfMainWindow()
{
    resize(800,600);
    int alpha = 255;
    this->setWindowOpacity(alpha);
    setObjectName("SYS_QsfMainWindow");

    Qt::WindowFlags myWinFlags = 0;
    myWinFlags |= Qt::FramelessWindowHint; // 不可调整大小
    myWinFlags |= Qt::CustomizeWindowHint;
    setWindowFlags(myWinFlags);
    //setAttribute(Qt::WA_TranslucentBackground); //背景透明

    QVBoxLayout* tMainVB = new QVBoxLayout;
    tMainVB->setSpacing(0);
    tMainVB->setContentsMargins(0,0,0,0);
    this->setLayout(tMainVB);

    m_titleBar = new QsfTitleBar;
    tMainVB->addWidget(m_titleBar);

    m_tableMenu = new QTabWidget;
    m_tableMenu->setMaximumHeight(150);
    tMainVB->addWidget(m_tableMenu);

    m_workWindow = new QsfWorkWindow;
    tMainVB->addWidget(m_workWindow);
}

QsfMainWindow::~QsfMainWindow()
{
    delete m_titleBar;
    delete m_workWindow;

    //清理参数管理器
}

QDockWidget* QsfMainWindow::createDockWidget( QString title, QString name, Qt::DockWidgetArea area )
{
    QDockWidget* tDock = new QDockWidget(title);

    SgfParamManager::GetInstance()->addParam(name.toStdString(), tDock);
    m_workWindow->addDockWidget(area, tDock);
    QWidget* docWid1 = new QWidget;
    tDock->setWidget(docWid1);
    return tDock;
}

void QsfMainWindow::addDockWidget( QDockWidget* tDock, QString title, Qt::DockWidgetArea area )
{
    m_workWindow->addDockWidget(area, tDock);
    QWidget* docWid1 = new QWidget;
    tDock->setWidget(docWid1);
}


QWidget* QsfMainWindow::createWorkWidget( QString title, QString name )
{
    QWidget* tWidget = new QWidget();
    tWidget->setWindowTitle(title);
    SgfParamManager::GetInstance()->addParam(name.toStdString(), tWidget);
    m_workWindow->workSpace()->addTab(tWidget, title);
    return tWidget;

}

    /** @brief 添加工作页Widget. */
void QsfMainWindow::addWorkWidget( QWidget* workTab, QString title )
{
    m_workWindow->workSpace()->addTab(workTab, title);
}

void QsfMainWindow::mousePressEvent( QMouseEvent *event )
{
	if (m_titleRect.contains(oldMousePos))
	{
		oldMousePos = event->globalPos() - this->pos();
		m_titleRect = m_titleBar->rect();
	}
}

void QsfMainWindow::mouseDoubleClickEvent( QMouseEvent * event )
{
	if (m_titleRect.contains(oldMousePos))
	{
		if (isMaximized())
		{
			showNormal();
		}
		else
		{
			showMaximized();
		}
		m_titleRect = m_titleBar->rect();
	}
	QWidget::mouseDoubleClickEvent(event);
}

void QsfMainWindow::mouseMoveEvent( QMouseEvent *event )
{
    if( isMaximized() )
        return;

    if (m_titleRect.contains(oldMousePos))
        move(event->globalPos()-oldMousePos);

    oldMousePos = event->globalPos() - this->pos();
}

