#pragma once
#include <QtWidgets/QtWidgets>
#include<QtCore/QtCore>
#include<QtGui/QtGui>

#define phi 3.1415926535897932384626433

QImage blurred(const QPixmap& image, const QRect& rect, qint32 radius, bool alphaOnly = false);
void GaussiamBlur(qint32 r, qreal variance, QImage& img);