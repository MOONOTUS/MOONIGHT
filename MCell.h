#pragma once
#include"MCenter.h"

class MWidget;

class MCell  : public QPushButton //统合元件类
{
	Q_OBJECT

#define imagecell 0x111
#define rectcell 0x001
#define ellipcell 0x002
#define linecell 0x003
#define pathcell 0x004
#define textcell 0x005

public:
	MCell(MWidget *parent);
	~MCell();

private:
	MWidget* Parent;

	qint32* Type;

	QPoint* Point;
	QPixmap* Image;
	QRect* Rect;
	qreal* Radium;
	QLine* Line;
	QPainterPath* Path;
	QString* Text;

	bool* Visuable;
	bool* IfLine;
	bool* IfFill;

	QColor* LineColor;
	QColor* FillColor;

public:
	void setPoint(QPoint point);
	void setPoint(qreal x, qreal y);
	void setImage(QString path);
	void setImage(QPixmap image);
	void setImage(QPixmap* image);
	void setVisuable(bool visuable);;
	void setRect(QRect rect);
	void setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height);
	void setRadium(qreal xradium, qreal yradium);
	void setRadium(qreal radium);
	void setLine(QLine line);
	void setLine(QPoint start, QPoint end);
	void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
	void setPath(QPainterPath path);
	void setText(QString text);

	QPixmap image();
	QPoint point();
	bool visuable();
	void draw();
	MWidget*& MParent();
};
