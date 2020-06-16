#ifndef QRIBBIONGUI_H
#define QRIBBIONGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_qribbiongui.h"

class QRibbionGUI : public QMainWindow
{
    Q_OBJECT

public:
    QRibbionGUI(QWidget *parent = 0);
    ~QRibbionGUI();

private:
    Ui::QRibbionGUIClass ui;
};

#endif // QRIBBIONGUI_H
