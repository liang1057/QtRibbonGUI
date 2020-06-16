#include <QHBoxLayout>
#include <QPushButton>
#include <QDockWidget>
#include <QFileDialog>


#include "QsfMainWindow.h"
#include "QsrRibbonCore.h"
#include "SgfParamManager.h"

#define RIBBON_STYLE_QSS "../userData/RibbonStyle.qss"

RobbonWidget::RobbonWidget(QWidget *parent /* = Q_NULLPTR */, Qt::WindowFlags f /* = Qt::WindowFlags() */)
	:QWidget(parent,f)
{
    setObjectName("RobbonWidget");
}

RobbonWidget::~RobbonWidget()
{
}

void RobbonWidget::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QsrRibbonTitleBar::QsrRibbonTitleBar()
{
	setObjectName("RibbonTitleBar");
	QHBoxLayout* titleLayout = new QHBoxLayout();
	titleLayout->setMargin(0);
	titleLayout->setSpacing(0);
	this->setLayout(titleLayout);

	titleLayout->addSpacing(10); // 10pix
	m_quickAccessToolBar = new QsrRibbonQuickAccessToolBar();
	titleLayout->addWidget(m_quickAccessToolBar);
	titleLayout->addStretch();

	m_titleLable1 = new QLabel();
	m_titleLable1->setStyleSheet("color:white;");
	m_titleLable1->setObjectName("RibbonTitleBarLabel1");
	titleLayout->addWidget(m_titleLable1);
	titleLayout->addStretch();

    
    m_userInfoLabel = new QLabel(QByteArray::fromHex("6c69616e6731303537403136332e636f6d").data());//("liang1057@163.com");
	m_userInfoLabel->setStyleSheet("color:white;");
	titleLayout->addWidget(m_userInfoLabel);
	
	m_systemButton = new QsrRibbonQuickAccessToolBar();
	titleLayout->addWidget(m_systemButton);
}

QsrRibbonTitleBar::~QsrRibbonTitleBar()
{
	delete m_quickAccessToolBar;
	m_quickAccessToolBar = NULL;
}

/** @brief  设置窗口标题.
*
*  @details 设置窗口标题.
*  @param   title 窗口的标题.
*  @return  .
*/
void QsrRibbonTitleBar::setTitle(QString title)
{
	QWidget::setWindowTitle(title);
	m_titleLable1->setText(title);
	m_titleLable1->setAlignment(Qt::AlignCenter);
}

QString QsrRibbonTitleBar::getTitle()
{
	return this->windowTitle();
}

/** @brief  设置工具条的文字. */
void QsrRibbonTitleBar::setToolsText(QString txt)
{
	m_ToolsLabel.setText(txt);
}

void QsrRibbonTitleBar::addQuickAction(QAction *action)
{
	m_quickAccessToolBar->addAction(action);
}

void QsrRibbonTitleBar::addSysAction(QAction* action)
{
	QList<QAction*> tList = m_systemButton->actions();
	if (tList.count() == 0)
		m_systemButton->addAction(action);
	else
	{
		m_systemButton->insertAction(tList[0], action);
	}
}

void QsrRibbonTitleBar::setUserInfo(QString txt)
{
	m_userInfoLabel->setText(txt);
}

// QList<QT_NAMESPACE::QAction>* QsrRibbonTitleBar::getActionList(bool isLeft/*=true*/)
// {
// 
// }

// /** @brief   获取快捷工具栏 . */
// QsrRibbonQuickAccessToolBar* QsrRibbonTitleBar::quickAccessToolBar()
// {
// 	return m_quickAccessToolBar;
// }
// 




QtbMenuBar::QtbMenuBar()
{
	setObjectName("RibbonMenuBar");
	QVBoxLayout* tVB = new QVBoxLayout();
	tVB->setSpacing(0);
	tVB->setContentsMargins(0, 0, 0, 0);
	setLayout(tVB);

	m_layout = new QHBoxLayout();
	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);
    tVB->addLayout(m_layout);
    
	m_toolBarStackedWid = new QStackedWidget();
	m_toolBarStackedWid->setObjectName("RibbonMenuStackeWidget");
	m_menuTabBar = new QTabBar;
	m_menuTabBar->setMinimumHeight(32);
	m_menuTabBar->setObjectName("RibbonMenuTabBar");
	m_layout->addWidget(m_menuTabBar);

    /* 暂时不提供扩展型的可变菜单
    m_ExtentedMenuTabBar = new QTabBar;
    m_ExtentedMenuTabBar->setObjectName("RibbonExtentedMenuTabBar");
    m_ExtentedMenuTabBar->addTab("");
    m_ExtentedMenuTabBar->setTabEnabled(0, false);
    m_layout->addWidget(m_ExtentedMenuTabBar);
//     m_extentedWidget = new QWidget();
//     m_layout->addWidget(m_extentedWidget);
//     m_layoutExtented = new QHBoxLayout();
//     m_layoutExtented->setContentsMargins(0, 0, 0, 0);
//     m_layoutExtented->setSpacing(0);
//     m_extentedWidget->setLayout(m_layoutExtented);
    */
	m_layout->addStretch();

	m_extentBtn = new RibbonToolButton();
	m_layout->addWidget(m_extentBtn);
	m_toolBarVisible = true;
	QObject::connect(m_extentBtn, SIGNAL(clicked()), this, SLOT(onExtentToggled()));


	tVB->addWidget(m_toolBarStackedWid);

	m_toolBarStackedWid->setMaximumHeight(96);
	m_toolBarStackedWid->setMinimumHeight(96);
	m_toolBarStackedWid->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

	connect(m_menuTabBar, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChenged(int)));
	return;
}

QtbMenuBar::~QtbMenuBar()
{

}

void QtbMenuBar::addAction(ribbonAction* tAction,int tIndex)
{
	m_layout->insertWidget(tIndex, tAction);
}

/** @brief   增加菜单.  */
void QtbMenuBar::addMenu(QString menuName)
{
	 // 添加一个tab标签
    int tabIndex = m_menuTabBar->addTab(menuName);

    // 下方Ribbon工具条上添加相应的显示widget作为Group的载体
	RobbonWidget* tempWid = new RobbonWidget();
	m_toolBarStackedWid->addWidget(tempWid);
	m_StaWidMap.insert(menuName, tempWid);

    // 这是显示widget用的横向布局
	QHBoxLayout* tempHB = new QHBoxLayout();
	tempHB->setSpacing(0);
	tempHB->setContentsMargins(0, 0, 0, 0);
	tempWid->setLayout(tempHB);

    RobbonWidget* lastWid = new RobbonWidget();
    QHBoxLayout* lastHB = new QHBoxLayout();
    lastWid->setLayout(lastHB);
	lastHB->addStretch();

    tempHB->addWidget(lastWid);

	return;
}

/** @brief   增加扩展型菜单.  */
/* 暂时不提供扩展型的可变菜单
void QtbMenuBar::addExtendedMenu(QString menuName, QString showName)
{
    // 添加一个tab标签
    // int tabIndex = m_ExtentedMenuTabBar->addTab(menuName);

    // 下方Ribbon工具条上添加相应的显示widget作为Group的载体
    RobbonWidget* tempWid = new RobbonWidget();
    m_toolBarStackedWid->addWidget(tempWid);
    m_StaWidMap.insert(menuName, tempWid);
    tempWid->setWindowTitle(showName);

    QHBoxLayout* tempHB = new QHBoxLayout();
    tempHB->setSpacing(0);
    tempHB->setContentsMargins(0, 0, 0, 0);

    tempHB->addStretch();
    tempWid->setLayout(tempHB);

//     QPushButton* tBtn = new QPushButton(m_extentedWidget);
//     tBtn->setText(showName);
//     m_layoutExtented->addWidget(tBtn);
//     tBtn->setVisible(true);
//     tBtn->setCheckable(true);
//     tBtn->setObjectName("RibbonExtentedMenu");
//     m_extentedBtnMap.insert(menuName, tBtn);
    return;
}
*/
void QtbMenuBar::setMenuVisible(QString menuName, bool tIsVisible)
{
    QString tabTitle = "";
	if (m_StaWidMap.contains(menuName))
	{
		m_StaWidMap[menuName]->setVisible(tIsVisible);
        tabTitle = m_StaWidMap[menuName]->windowTitle();
	}

    if (tIsVisible == true)
    {
        for (int i = m_menuTabBar->count() - 1; i >= 0; i--)
        {
            if (menuName == m_menuTabBar->tabText(i))
                return;
        }
        m_menuTabBar->addTab(menuName);
    }
    else
    {
        for (int i = m_menuTabBar->count() - 1; i >= 0; i--)
        {
            if (menuName == m_menuTabBar->tabText(i))
                m_menuTabBar->removeTab(i);
        }
    }

    /*
    if (tabTitle.isEmpty())
        return;
//    m_extentedBtnMap[menuName]->setVisible(tIsVisible);
    if (tIsVisible == true)
    {
        int tabIndex = m_ExtentedMenuTabBar->addTab(tabTitle);
        //m_layoutExtented->addWidget();
    }
    else
    {
        
        for (int i = m_ExtentedMenuTabBar->count() - 1; i >= 0; i--)
        {
            if (tabTitle == m_ExtentedMenuTabBar->tabText(i))
                m_ExtentedMenuTabBar->removeTab(i);
        }
    }
    m_ExtentedMenuTabBar->setCurrentIndex(0);
    */
}

bool QtbMenuBar::isMenuVisible(QString menuName)
{
	if (m_StaWidMap.contains(menuName))
	{
		return m_StaWidMap[menuName]->isVisible();
	}
}

QtbGroupWidget* QtbMenuBar::addGroup(QString menuName, QString txtGroupTitle)
{
	if (m_StaWidMap.contains(menuName))
	{
		RobbonWidget* tempWid = m_StaWidMap[menuName]; //先找到menu的承载页
		QtbGroupWidget* newGW = new QtbGroupWidget();
		newGW->setTitle(txtGroupTitle);
		QHBoxLayout* tempHB = (QHBoxLayout*)(tempWid->layout());
		tempHB->insertWidget(tempHB->count()-1,newGW);
		return newGW;
	}
	else
	{
		return NULL;
	}
}

void QtbMenuBar::menuReady(QString menuName)
{
//     if (m_StaWidMap.contains(menuName))
//     {
//         RobbonWidget* tempWid = m_StaWidMap[menuName]; //先找到menu的承载页
//         RobbonWidget* lastWid = new QtbGroupWidget();
//         QHBoxLayout* tempHB = (QHBoxLayout*)(tempWid->layout());
//         tempHB->insertWidget(tempHB->count() - 1, newGW);
//         return newGW;
//     }
//     else
//     {
//         return NULL;
//     }
}

void QtbMenuBar::setExtentBtnIcon(QIcon icoExtent, QIcon icoHide)
{
	m_icoExtent = icoExtent;
	m_icoHide = icoHide;
	if (m_toolBarVisible)
		m_extentBtn->setIcon(m_icoHide);
	else
		m_extentBtn->setIcon(m_icoExtent);
}

void QtbMenuBar::setToolBarVisible(bool tVal)
{
	m_toolBarVisible = tVal;
	m_toolBarStackedWid->setVisible(m_toolBarVisible);
}

void QtbMenuBar::onExtentToggled()
{
	setToolBarVisible(!m_toolBarVisible);
	if (m_toolBarVisible)
		m_extentBtn->setIcon(m_icoHide);
	else
		m_extentBtn->setIcon(m_icoExtent);
}

void QtbMenuBar::onCurrentTabChenged(int index)
{
	m_toolBarStackedWid->setCurrentIndex(index);
	m_toolBarStackedWid->show();

    /* 暂时不提供扩展型的可变菜单
    for each (QPushButton* var in m_extentedBtnMap)
    {
        var->setChecked(false);
    }
    m_ExtentedMenuTabBar->setCurrentIndex(0);
    */
}

    /* 暂时不提供扩展型的可变菜单
void QtbMenuBar::onExtentedTabChenged()
{
    for each (QPushButton* var in m_extentedBtnMap)
    {
        var->setChecked(false);
    }
}
    */

void QtbMenuBar::enterEvent(QEvent *event)
{
	QWidget::enterEvent(event);
	if (m_toolBarVisible == false)
		m_toolBarStackedWid->show();
}

void QtbMenuBar::leaveEvent(QEvent *event)
{
	QWidget::leaveEvent(event);
	//m_toolBarStackedWid->setVisible(m_toolBarVisible);
	if (m_toolBarVisible == false)
		m_toolBarStackedWid->setVisible(false);
}

bool QtbMenuBar::isToolBarVisible()
{
	return m_toolBarVisible;
}

/** @brief   Ribbon工具栏.
*  @details  Ribbon工具栏.
*/
QtbToolBar::QtbToolBar(/*QTabBar* tabBar*/)
{
	//this->setTabBar(tabBar);
}




QtbToolBar::~QtbToolBar()
{

}

void QtbToolBar::addMenu(QString txt)
{

}

/** @brief   主窗口.
*  @details
*/
QtbMainWindow::QtbMainWindow(QWidget *parent /* = Q_NULLPTR */, Qt::WindowFlags f /* = Qt::WindowFlags() */)
	:RobbonWidget(parent/*, Qt::FramelessWindowHint*/)
{
	setObjectName("RibbonMainWindow");
	resize(800, 600);
	QFile qssFile(RIBBON_STYLE_QSS);
	if (qssFile.exists())
	{
		if (qssFile.open(QFile::ReadOnly))
		{
			QString qssStr = QString(qssFile.readAll());
			setStyleSheet(qssStr);
		}
	}

	Qt::WindowFlags myWinFlags = 0;
	myWinFlags |= Qt::Window;
    myWinFlags |= Qt::FramelessWindowHint;
    //myWinFlags |= Qt::CustomizeWindowHint;

	setWindowFlags(myWinFlags);

// #ifdef Q_OS_WIN
//     HWND hwnd = reinterpret_cast<HWND>(this->winId());
// 
//     //const long style =  (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN);
//     const long style = WS_POPUP; //( | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN);
//     SetWindowLongPtr(hwnd, GWL_STYLE, style);
// 
//     const MARGINS shadow = { 1, 1, 1, 1 };
//     DwmExtendFrameIntoClientArea(hwnd, &shadow);
// 
//     SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
// #endif



	QVBoxLayout* tMainVB = new QVBoxLayout;
	tMainVB->setSpacing(0);
	tMainVB->setContentsMargins(1,1,1,1);
	this->setLayout(tMainVB);

	m_titleBar = new QsrRibbonTitleBar();
	tMainVB->addWidget(m_titleBar);

	m_menuBar = new QtbMenuBar();
	tMainVB->addWidget(m_menuBar);
    tMainVB->addSpacing(1);
	m_workWindow = new QsfWorkWindow;
	tMainVB->addWidget(m_workWindow);
}

QtbMainWindow::~QtbMainWindow()
{



}

QsrRibbonTitleBar* QtbMainWindow::titleBar()
{
	return m_titleBar;
}

QtbMenuBar* QtbMainWindow::menuBar()
{
	return m_menuBar;
}

/** @brief 创建DockWidget. */
QDockWidget * QtbMainWindow::createDockWidget(QString title, QString name, Qt::DockWidgetArea area)
{
	QDockWidget* tDock = new QDockWidget(title);
	SgfParamManager::GetInstance()->addParam(name.toStdString(), tDock);
	m_workWindow->addDockWidget(area, tDock);
// 	QWidget* docWid1 = new QWidget;
// 	tDock->setWidget(docWid1);
	return tDock;
}

QWidget* QtbMainWindow::createWorkWidget(QString title, QString name)
{
    QWidget* tWidget = static_cast<QWidget*>(SgfParamManager::GetInstance()->getParamValue(name.toStdString()));
    if(tWidget==NULL)
    {
        tWidget = new QWidget();
        tWidget->setWindowTitle(title);
        SgfParamManager::GetInstance()->addParam(name.toStdString(), tWidget);
        m_workWindow->workSpace()->addTab(tWidget, title);
    }
	return tWidget;
}
void QtbMainWindow::addWorkWidget(QWidget* tWidget)
{
    m_workWindow->workSpace()->addTab(tWidget, tWidget->windowTitle());
}

void QtbMainWindow::mousePressEvent(QMouseEvent *event)
{
//     m_titleRect = m_titleBar->rect();
//     if (m_titleRect.contains(event->pos()))
//         oldMousePos = event->globalPos() - this->pos();
//     else
//         oldMousePos = QPoint(-1, -1);

    QWidget::mousePressEvent(event);
    m_titleRect = m_titleBar->rect();
    if (m_titleRect.contains(event->pos()))
    {
        if (!event->isAccepted()) {
#ifdef Q_OS_WIN
            ReleaseCapture();
            SendMessage(reinterpret_cast<HWND>(winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
#else
        if (m_titleRect.contains(event->pos()))
            oldMousePos = event->globalPos() - this->pos();
        else
            oldMousePos = QPoint(-1, -1);
#endif
    }
}

void QtbMainWindow::mouseDoubleClickEvent(QMouseEvent * event)
{
    m_titleRect = m_titleBar->rect();
    if (m_titleRect.contains(event->pos()))
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
    RobbonWidget::mouseDoubleClickEvent(event);
}

void QtbMainWindow::mouseMoveEvent(QMouseEvent *event)
{
// 	if (isMaximized())
// 		return;
// 
// 	if (m_titleRect.contains(oldMousePos))
// 		move(event->globalPos() - oldMousePos);
// 
// 	oldMousePos = event->globalPos() - this->pos();
}

void QtbMainWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	update();
}

void QtbMainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (this->isActiveWindow())
        p.setPen(QColor(60, 136, 193));
    else
        p.setPen(Qt::darkGray);

    

    p.drawRect(QRect(0,0,width()-1, height()-1));

}

void QtbMainWindow::onSkin()
{
    //QFile qssFile(RIBBON_STYLE_QSS);
    QString fileneame = QFileDialog::getOpenFileName(this, "换肤", "../bin/userdata");
    if (fileneame.isEmpty())
        return;
    QFile qssFile(fileneame);
	if (qssFile.exists())
	{
		if (qssFile.open(QFile::ReadOnly))
		{
			QString qssStr = QString(qssFile.readAll());
			setStyleSheet(qssStr);
		}
	}



}

/** @brief   Ribbon操作.
*  @details  一个操作对应一个图标，或者控件
*/
// ribbonAction::ribbonAction()
// {
// 
// }

/** @brief   Ribbon 操作组.
*  @details  Ribbon 操作组
*/
QtbGroupWidget::QtbGroupWidget()
{
    m_actionGroup = new QActionGroup(this);
	//this->setStyleSheet("background-color    : rgba(33, 140, 240, 255);");
	this->setObjectName("RibbonGroupWidget");
	//setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QVBoxLayout* groupLayout = new QVBoxLayout;
	groupLayout->setSpacing(0);
	groupLayout->setContentsMargins(5, 5, 5, 0);
	this->setLayout(groupLayout);
	m_gridLayout = new QGridLayout();
 	m_gridLayout->setSpacing(5);
 	m_gridLayout->setContentsMargins(0, 0, 0, 0);
	groupLayout->addLayout(m_gridLayout);
	groupLayout->addStretch();
	QHBoxLayout* titleLayout = new QHBoxLayout;
	titleLayout->setSpacing(0);
	titleLayout->setContentsMargins(5, 0, 5, 0);
	groupLayout->addLayout(titleLayout);
	//titleLayout->addStretch();
	m_groupTitleLabel = new QLabel();
	titleLayout->addWidget(m_groupTitleLabel);
	m_groupTitleLabel->setMaximumHeight(24);
	m_groupTitleLabel->setMinimumHeight(24);
	//m_groupTitleLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);


	// 右下角的按钮5
    QsfToolButton* popBtn = new QsfToolButton(); popBtn->setText(">");
	popBtn->setMaximumSize(QSize(24, 24));
	popBtn->setMinimumSize(QSize(24, 24));
	//m_groupTitleLabel->setLayout(titleLayout);
	//titleLayout->addStretch();
	titleLayout->addWidget(popBtn);
}

QtbGroupWidget::~QtbGroupWidget()
{
    delete m_actionGroup;
}
void QtbGroupWidget::paintEvent(QPaintEvent *event)
{
	RobbonWidget::paintEvent(event);

    // 绘制每个Group上的分隔线
	QPainter p(this);
	p.setPen(Qt::darkGray);
	p.drawLine(width() - 2, 5, width() - 2, height()-5);
}

void QtbGroupWidget::setTitle(QString tTitle)
{
	m_groupTitleLabel->setText(tTitle);
	m_groupTitleLabel->setAlignment(Qt::AlignCenter);
}

void QtbGroupWidget::addAction(ribbonAction* rAct, int row, int col, int rowSpan /*= 1*/, int columnSpan /*= 1*/, Qt::Alignment alignment /*= Qt::Alignment()*/)
{
	m_gridLayout->addWidget(rAct, row, col, rowSpan, columnSpan, alignment);
}
void QtbGroupWidget::addAction(RibbonToolButton* rAct, int row, int col, int rowSpan /*= 1*/, int columnSpan /*= 1*/, Qt::Alignment alignment /*= Qt::Alignment()*/)
{
	m_gridLayout->addWidget(rAct->window(), row, col, rowSpan, columnSpan, alignment);
}

QActionGroup* QtbGroupWidget::getActionGroup() const
{
    return m_actionGroup;
}


QsrRibbonQuickAccessToolBar::QsrRibbonQuickAccessToolBar()
{
	setObjectName("RibbonQuickAccessToolBar");
}



/** @brief   RibbonControlBase 控件基类.
*  @details
*/RibbonControlBase::RibbonControlBase()
{
}

RibbonControlBase::~RibbonControlBase()
{
}

void RibbonControlBase::setGroupPos(QPoint tPos, int index /*= -1*/)
{
	switch (index)
	{
	case -1:
		m_pos0 = tPos;
		m_pos1 = tPos;
		break;
	case 0:
		m_pos0 = tPos;
		break;
	case 1:
		m_pos1 = tPos;
		break;
	default:
		m_pos0 = tPos;
		m_pos1 = tPos;
		break;
	}

}

QPoint RibbonControlBase::groupPos(int index)
{
	if (index == 1)
		return m_pos1;
	else
		return m_pos0;
}


/** @brief   RibbonPushButton Ribbon按钮类.
*  @details
*/
RibbonToolButton::RibbonToolButton(QWidget *parent /*= Q_NULLPTR*/)
	: QPushButton(parent)
{
    setObjectName("RibbonToolButton");
    m_action = NULL;
	m_txtVisible = true;
	setMinimumHeight(24);
	setMinimumWidth(24);
	setStyleSheet("text-align : left;");
    m_action = new QAction();
    connect(this, SIGNAL(clicked(bool)), m_action, SIGNAL(triggered(bool)));
}

RibbonToolButton::RibbonToolButton(const QIcon &icon, const QString &text, QWidget *parent /*= Q_NULLPTR*/)
	:QPushButton(icon, text, parent)
{
    setObjectName("RibbonToolButton");
    m_text = text;
	m_txtVisible = true;
	setMinimumHeight(24);
	setStyleSheet("text-align : left;");
    m_action = new QAction(icon, text);
    connect(this, SIGNAL(clicked(bool)), m_action, SIGNAL(triggered(bool)));
}

RibbonToolButton::RibbonToolButton(const QString &text, QWidget *parent /*= Q_NULLPTR*/)
	:QPushButton(text, parent)
{
    setObjectName("RibbonToolButton");
    m_action = NULL;
    m_text = text;
	m_txtVisible = true;
	setMinimumHeight(24);
	setMaximumWidth(75);
	setStyleSheet("text-align : left;");
    m_action = new QAction(text);
    connect(this, SIGNAL(clicked(bool)), m_action, SIGNAL(triggered(bool)));
}

RibbonToolButton::~RibbonToolButton()
{
    // 没有释放action的操作
}

void RibbonToolButton::setTxtVisible(bool tVal)
{
	m_txtVisible = tVal;
	if (m_txtVisible)
		QPushButton::setText(m_text);
	else
        QPushButton::setText("");

	update();
}

bool RibbonToolButton::txtVisible()
{
	return m_txtVisible;
}

void RibbonToolButton::setAlignment(Qt::Alignment flag)
{
	QString str = "";
	switch (flag)
	{
	case Qt::AlignCenter:
		str = "center";
		break;
	case Qt::AlignLeft:
		str = "left";
		break;
	case Qt::AlignRight:
		str = "right";
		break;
	case Qt::AlignBottom:
		str = "bottom";
		break;
	case Qt::AlignTop:
		str = "top";
		break;
	default:
		str = "center";
		break;
	}
	setStyleSheet(QString("text-align : %1;").arg(str));
}

/** @brief   设置Action. */
// void RibbonToolButton::setAction(QAction* tAction)
// {
//     m_action = tAction;
//     this->setText(tAction->text());
//     this->setIcon(tAction->icon());
//     connect(this, SIGNAL(triggered(bool)), m_action, SIGNAL(triggered(bool)));
// }

/** @brief   获取Action. */
QAction* RibbonToolButton::getAction()
{
    return m_action;
}

void RibbonToolButton::setText(QString &text)
{
    m_action->setText(text);
    QPushButton::setText(text);
}

void RibbonToolButton::setIcon(const QIcon &icon)
{
    m_action->setIcon(icon);
    QPushButton::setIcon(icon);
}

void RibbonToolButton::setEnabled(bool &tEnabled)
{
    m_action->setEnabled(tEnabled);
    QPushButton::setEnabled(tEnabled);
}




RibbonToolButtonBig::RibbonToolButtonBig(const QIcon &icon, const QString &text, QWidget *parent)
{
	setObjectName("RibbonToolButton");
// 	this->resize(64, 54);
// 	this->setMaximumSize(QSize(64, 54));
// 	this->setMinimumSize(QSize(64, 54));

	QVBoxLayout* tVB = new QVBoxLayout;
	setLayout(tVB);
	tVB->setSpacing(0);
	tVB->setMargin(0);
	m_pushButton = new QPushButton();
	m_pushButton->setIcon(icon);
	m_pushButton->setIconSize(QSize(32, 32));
	tVB->addWidget(m_pushButton);
	m_label = new QLabel();
	m_label->setText(text);
	m_label->setMaximumHeight(18);
	m_label->setAlignment(Qt::AlignCenter);
	tVB->addWidget(m_label);

	m_label_extent = new QLabel;
	m_label_extent->setMaximumHeight(12);
	m_label_extent->setText("V");
	m_label_extent->setAlignment(Qt::AlignCenter);
	tVB->addWidget(m_label_extent);
	m_label_extent->setVisible(false);

    m_pushButton->setObjectName("RibbonToolButton");
    connect(m_pushButton, SIGNAL(clicked(bool)), this, SIGNAL(triggered(bool)));
}

RibbonToolButtonBig::~RibbonToolButtonBig()
{
	delete m_pushButton;
	delete m_label;
}

QPushButton* RibbonToolButtonBig::pushButton() const
{
	return m_pushButton;
}

QLabel* RibbonToolButtonBig::label() const
{
	return m_label;
}

void RibbonToolButtonBig::setExtentIconVisible(bool tVal)
{
	m_label_extent->setVisible(tVal);
}


