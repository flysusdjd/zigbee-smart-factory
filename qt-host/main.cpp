#include "serialledctr.h"
#include <QApplication>
#include <QDebug>
 #include <QTextCodec>
#include "control.h"
int main(int argc, char *argv[])
{


    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication a(argc, argv);
    SerialLedCtr w;
    w.show();
    return a.exec();
}
