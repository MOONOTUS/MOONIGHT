﻿#pragma once
#include"MCenter.h"

class MMainWindow;
class MWidget;

class MCell  : public QPushButton //统合元件类
{
	Q_OBJECT

#define imagecell 0x111
#define rectcell 0x001
#define ellipsecell 0x002
#define linecell 0x003
#define painterpathcell 0x004
#define textcell 0x005

protected:
	void paintEvent(QPaintEvent* event);

public slots:
	void Mupdate();

public:
	MCell(MMainWindow* parent = nullptr);
	MCell(MWidget* parent = nullptr);
	~MCell();

private:
	MMainWindow* ParentMMainWindow;
	MWidget* ParentMWidget;

	qint32* Type;

	QRect* Rect;
	QRect* VRect;

	QPixmap* Image;
	QPixmap* PathImage;
	QPoint* EllipseCenter;
	QPoint* VEllipseCenter;
	qreal* XRadium;
	qreal* VXRadium;
	qreal* YRadium;
	qreal* VYRadium;
	QLine* Line;
	QLine* VLine;
	qreal* LineWidth;
	qreal* VLineWidth;
	QPainterPath* PainterPath;
	QPainterPath* VPainterPath;
	QString* Text;

	bool* Visuable;
	bool* IfLine;
	bool* IfFill;

	QColor* LineColor;
	QColor* FillColor;

public:
	void setType(qint32 type);
	void setImage(QString path);
	void setImage(QPixmap image);
	void setImage(QPixmap* image);
	void setVisuable(bool visuable);;
	void setRect(QRect rect);
	void setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height);
	void setEllipseCenter(QPoint center);
	void setEllipseCenter(qreal x, qreal y);
	void setRadium(qreal xradium, qreal yradium);
	void setRadium(qreal radium);
	void setLine(QLine line);
	void setLine(QPoint start, QPoint end);
	void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
	void setLineWidth(qreal width);
	void setPainterPath(QPainterPath painterpath);
	void setText(QString text);
	void setIfLine(bool ifline);
	void setIfFill(bool iffill);
	void setLineColor(QColor color);
	void setLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	void setFillColor(QColor color);
	void setFillColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	
	QPixmap image() const;
	bool visuable() const;
	qreal lineWidth() const;
	
	QRect* MRect();
	MMainWindow*& MParentMMainWindow();
	MWidget*& MParentMWidget();
};
