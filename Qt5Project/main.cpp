#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QTextCodec>
#include <QtWidgets/QApplication>
#include "uiOffice2016.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    std::locale::global(std::locale(""));

    QApplication a(argc, argv);
    uiOffice2016 w1;
    w1.show();

    uiTEST_MainWindow w2;
    w2.show();
    return a.exec();
}
