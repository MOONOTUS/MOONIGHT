#ifndef UI_MOONIGHT_Qt_H
#define UI_MOONIGHT_Qt_H

#include"MCenter.h"
#include"MWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MOONIGHT_QtClass
{
public:
    MWidget* main;//主界面
    MWidget *central;//提供给谱面编辑师的窗口
    QTimer* mainTime;//以10ms为周期的主计时器，用于实现动效
    QTimer* litTime;//以1ms为周期的计时器，用于曲谱计时

    void setupUi(QMainWindow *MOONIGHT_QtClass)
    {
        if (MOONIGHT_QtClass->objectName().isEmpty())
            MOONIGHT_QtClass->setObjectName("MOONIGHT_QtClass");
        MOONIGHT_QtClass->resize(960, 540);
        main = new MWidget(MOONIGHT_QtClass);
        main->setObjectName("mainWidget");
        MOONIGHT_QtClass->setCentralWidget(main);

        central= new MWidget();
        central->setObjectName("centralWidget");
        central->resize(960, 540);
        central->close();

        mainTime = new QTimer(central);
        mainTime->stop();
        litTime = new QTimer(central);
        litTime->stop();
        mainTime->setSingleShot(false);
        litTime->setSingleShot(false);
        mainTime->setInterval(10);
        mainTime->setInterval(1);

        retranslateUi(MOONIGHT_QtClass);

        QMetaObject::connectSlotsByName(MOONIGHT_QtClass);
    } // setupUi

    void retranslateUi(QMainWindow *MOONIGHT_QtClass)
    {
        MOONIGHT_QtClass->setWindowTitle(QCoreApplication::translate("MOONIGHT_QtClass", "MOONIGHT_Qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MOONIGHT_QtClass: public Ui_MOONIGHT_QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOONIGHT_Qt_H
