﻿#pragma once

#include"MCenter.h"
#include "ui_MOONIGHT_Qt.h"

class MOONIGHT_Qt : public QMainWindow
{
    Q_OBJECT

public:
    MOONIGHT_Qt(QWidget *parent = nullptr);
    ~MOONIGHT_Qt();
    Ui::MOONIGHT_QtClass* Ui();

public slots:

private:
    Ui::MOONIGHT_QtClass ui;
};
