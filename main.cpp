#include "MOONIGHT_Qt.h"
#include <QtWidgets/QApplication>
#include"TestDemo.h"
#include"InfinityHeaven.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MOONIGHT_Qt w;
    w.show();
    TestDemo_InfinityHeaven(&w);//调用测试关卡
    return a.exec();
}
