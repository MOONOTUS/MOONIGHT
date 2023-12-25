#include "MCell.h"
#include "MMainWindow.h"
#include "MWidget.h"

MCell::MCell(MMainWindow* parent)
	: QPushButton(parent)
{
	ParentMMainWindow = parent;
	ParentMWidget = nullptr;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
}

MCell::MCell(MWidget *parent)
	: QPushButton(parent)
{
	ParentMWidget = parent;
	ParentMMainWindow = nullptr;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
}

MCell::~MCell()
{}

void paintEvent(QPaintEvent* event)
{

	event->accept();
}

void MCell::setPoint(QPoint point)
{
	Point = new QPoint(point);
}

void MCell::setPoint(qreal x, qreal y)
{
	Point = new QPoint(x, y);
}

void MCell::setImage(QString path)
{
	Image = new QPixmap(path);
}

void MCell::setImage(QPixmap image)
{
	Image = new QPixmap(image);
}

void MCell::setImage(QPixmap* image)
{
	Image = image;
}

void MCell::setVisuable(bool visuable)
{
	Visuable = new bool(visuable);
}

void MCell::setRect(QRect rect)
{
	Rect = new QRect(rect);
}

void MCell::setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height)
{
	Rect = new QRect(lefttopx, lefttopy, width, height);
}

void MCell::setRadium(qreal xradium, qreal yradium)
{
	XRadium = new qreal(xradium);
	YRadium = new qreal(yradium);
}

void MCell::setRadium(qreal radium)
{
	XRadium = new qreal(radium);
	YRadium = new qreal(radium);
}

void MCell::setLine(QLine line)
{
	Line = new QLine(line);
}

void MCell::setLine(QPoint start, QPoint end)
{
	Line = new QLine(start, end);
}

void MCell::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
	Line = new QLine(x1, y1, x2, y2);
}

void MCell::setPainterPath(QPainterPath painterpath)
{
	PainterPath = new QPainterPath(painterpath);
}

void MCell::setText(QString text)
{
	Text = new QString(text);
}

QPixmap MCell::image()
{
	return *Image;
}

QPoint MCell::point()
{
	return *Point;
}

bool MCell::visuable()
{
	return *Visuable;
}

void MCell::draw()
{
	//None
}

MMainWindow*& MCell::MParentMMainWindow()
{
	return ParentMMainWindow;
}

MWidget*& MCell::MParentMWidget()
{
	return ParentMWidget;
}

