#pragma once
#include<QtCore>
#include<QtWidgets>
#include<QtGui>
#include<QtMath>

#define phi 3.1415926535897932384626433

QImage blurred(const QPixmap& image, const QRect& rect, qint32 radius, bool alphaOnly = false);
void GaussiamBlur(qint32 r, qreal variance, QImage& img);