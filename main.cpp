#include "MOONIGHT_Qt.h"
#include <QtWidgets/QApplication>
#include"InfinityHeaven.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MOONIGHT_Qt w;
    w.show();
    return a.exec();
}
