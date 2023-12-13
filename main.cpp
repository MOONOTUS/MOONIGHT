#include "MOONIGHT_Qt.h"
#include <QtWidgets/QApplication>
#include"TestDemo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MOONIGHT_Qt w;
    w.show();
    TestDemo_Rotate(&w);//µ÷ÓÃ²âÊÔ¹Ø¿¨
    return a.exec();
}
