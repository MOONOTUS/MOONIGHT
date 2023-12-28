#include "MOONIGHT_Qt.h"
#include"MOONIGHT_Player.h"

MOONIGHT_Qt::MOONIGHT_Qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    MOONIGHT_QtClass_Pivot::MOONIGHT_QtClass_Set(this);
}

MOONIGHT_Qt::~MOONIGHT_Qt()
{}

Ui::MOONIGHT_QtClass* MOONIGHT_Qt::Ui()
{
    return &ui;
}