#include "MOONIGHT_Qt.h"

MOONIGHT_Qt::MOONIGHT_Qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect
    (
        ui.litTime,
        SIGNAL(timeout()),
        ui.central,
        SLOT(timeAdd_ms())
    );
}

MOONIGHT_Qt::~MOONIGHT_Qt()
{}

Ui::MOONIGHT_QtClass* MOONIGHT_Qt::Ui()
{
    return &ui;
}