#pragma once

#include"Mcenter.h"
#include "ui_MOONIGHT_Qt.h"

class MOONIGHT_Qt : public QMainWindow
{
    Q_OBJECT

public:
    MOONIGHT_Qt(QWidget *parent = nullptr);
    ~MOONIGHT_Qt();

public slots:
    Ui::MOONIGHT_QtClass* Ui();

private:
    Ui::MOONIGHT_QtClass ui;
};
