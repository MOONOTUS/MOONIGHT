﻿#pragma once
#include<QtWidgets/QtWidgets>
#include<QtCore/QtCore>
#include<QtGui/QtGui>
#include<QtMultimedia/QtMultiMedia>

#define phi 3.1415926535897932384626433
#define WIDTH 3200
#define HEIGHT 1800
#define FONT_1 "Microsoft YaHei Ui Light"
#define FONT_2 "Microsoft YaHei Ui"

QImage blurred(const QPixmap& image, const QRect& rect, qint32 radius, bool alphaOnly = false);
void GaussiamBlur(qint32 r, qreal variance, QImage& img);