#pragma once
#include"MCenter.h"

class MWidget;

class MCell  : public QPushButton //统合元件类
{
	Q_OBJECT

#define imagecell 0x111
#define rectcell 0x001
#define ellipse 0x010

public:
	MCell(MWidget *parent);
	~MCell();

private:
	MWidget* Parent;
	qint32* Type;
	QPoint* Point;
	QPixmap* Image;
	bool* Visuable;
	QRect* Rect;
	qreal* Radium;

public:
	void setPoint(QPoint point);
	void setPoint(qreal x, qreal y);
	void setImage(QString path);
	void setImage(QPixmap& image);
	void setImage(QPixmap* image);
	void setVisuable(bool visuable);;
	void setRect(QRect rect);
	void setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height);
	void setRadium(qreal radium);
	QPixmap image();
	QPoint point();
	bool visuable();
	void draw();
	MWidget*& MParent();
};
