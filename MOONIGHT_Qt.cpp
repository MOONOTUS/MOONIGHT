#include "MOONIGHT_Qt.h"

MOONIGHT_Qt::MOONIGHT_Qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MOONIGHT_Qt::~MOONIGHT_Qt()
{}

Ui::MOONIGHT_QtClass* MOONIGHT_Qt::Ui()
{
    return &ui;
}