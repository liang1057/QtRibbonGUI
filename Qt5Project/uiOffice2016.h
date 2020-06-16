#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#pragma once

#include <QTextEdit>
#include "QsrRibbonCore.h"

// 一个例子
class uiOffice2016 : public QtbMainWindow
{
	Q_OBJECT
public:
	uiOffice2016();
	~uiOffice2016();

private:
	QString m_menuImg, m_menuTable;

private slots:
    void onImgClicked();
};



// 另一个例子
#define APP_MAIN_WINDOW "APP_MAIN_WINDOW"
#define APP_TITLE_BAR "APP_TITLE_BAR"
#define APP_MENU_BAR "APP_MENU_BAR"

#define DOCK_PROJCET "DOCK_PROJCET"  // 工区
#define DOCK_OUTPUT "DOCK_OUTPUT"  // 输出
#define DOCK_RM_SETTING "DOCK_RM_SETTING"  // 监控选型
// 下面是单炮分析的Dock窗口资源
#define DOCK_SHOT_A_TRACE "DOCK_SHOT_A_TRACE"    // 辅助道
#define DOCK_SHOT_ENERGY_TRACE "DOCK_SHOT_ENERGY_TRACE"  // 单道能量
#define DOCK_SHOT_ENERGY_LINE "DOCK_SHOT_ENERGY_LINE"    // 测线能量
#define DOCK_SHOT_FFT "DOCK_SHOT_FFT"       // 频谱统计
#define DOCK_SHOT_SN "DOCK_SHOT_SN"         // 信噪比
// 2019-04-15
#define TREE_WIDGET_AI_DATA "TREE_WIDGET_AI_DATA"
#define MENU_DATA_SEGY "MENU_DATA_SEGY" // 菜单名称
#define MENU_DATA_HOR  "MENU_DATA_HOR"
#define MENU_DATA_SAMPLES "MENU_DATA_SAMPLES"
#define MENU_TRAIN_DATA "MENU_TRAIN_DATA"
#define MENU_TRAIN_MODEL "MENU_TRAIN_MODEL"
#define MENU_TRAIN_TRAIN "MENU_TRAIN_TRAIN"
#define MENU_APP_DATA "MENU_APP_DATA"
#define MENU_APP_MODEL "MENU_APP_MODEL"
#define MENU_APP_PREDICT "MENU_APP_PREDICT"
#define TREE_DATA "TREE_DATA"
#define TREE_DATA_SEGY "TREE_DATA_SEGY"
#define TREE_DATA_HOR "TREE_DATA_HOR"
#define TREE_DATA_SAMPLEWELL "TREE_DATA_SAMPLEWELL"
#define WORK_WIDGET_DATA "WORK_WIDGET_DATA"
#define WORK_WIDGET_TRAIN "WORK_WIDGET_TRAIN"
#define WORK_WIDGET_PREDICT "WORK_WIDGET_PREDICT"
#define WORK_WIDGET_RESULT "WORK_WIDGET_RESULT"
class uiTEST_MainWindow : public QtbMainWindow
{
    Q_OBJECT
public:
    uiTEST_MainWindow();
    ~uiTEST_MainWindow();


private:
    void doLayout(bool isSave);
    void initTitleBar();
    void initMenuBar();
    void initDockWidget();
    void initWorkTabWidget();

    QsfWorkWindow* m_chartWindow;
    QsfWorkWindow* m_mapWindow;

    QActionGroup* m_actGroupTestPage;

    QTextEdit* m_outputEdit;

    /** @brief  显示进度的控件指针.    **/
    static void* progressUI;
    /** @brief  显示扫描记录的控件指针.    **/
    //static void* progressLogUI;
    /** @brief  显示进度的回调方法.    **/
    static bool getDataProgress(int value);
    /** @brief  扫描函数的静态指针.    **/
    static void* pScaner;

    QWidget * m_widget;
    QWidget * m_generateWid;
    QWidget* m_traineWid;

    private slots:

    void onCloseWorkTab(int tabIndex);
    void onAbout();
    void onSupport();
    void on_generate_toggled();
    void on_train_toggled();
    void on_predict_toggled();
protected:
    void closeEvent(QCloseEvent * event);

};
