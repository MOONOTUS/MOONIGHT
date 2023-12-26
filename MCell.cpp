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
	Type = new qint32(imagecell);
	Point = nullptr;
	Image = nullptr;
	Rect = nullptr;
	XRadium = nullptr;
	YRadium = nullptr;
	Line = nullptr;
	PainterPath = nullptr;
	Text = nullptr;
	LineColor = nullptr;
	FillColor = nullptr;
}

MCell::MCell(MWidget *parent)
	: QPushButton(parent)
{
	ParentMWidget = parent;
	ParentMMainWindow = nullptr;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
	Type = new qint32(imagecell);
	Point = nullptr;
	Image = nullptr;
	Rect = nullptr;
	XRadium = nullptr;
	YRadium = nullptr;
	Line = nullptr;
	PainterPath = nullptr;
	Text = nullptr;
	LineColor = nullptr;
	FillColor = nullptr;
}

MCell::~MCell()
{}

void MCell::setType(qint32 type)
{

}

void paintEvent(QPaintEvent* event)
{

	event->accept();
}

void MCell::setPoint(QPoint point)
{
	if (Point != nullptr)
	{
		delete Point;
	}
	Point = new QPoint(point);
}

void MCell::setPoint(qreal x, qreal y)
{
	if (Point != nullptr)
	{
		delete Point;
	}
	Point = new QPoint(x, y);
}

void MCell::setImage(QString path)
{
	if (Image != nullptr)
	{
		delete Image;
	}
	Image = new QPixmap(path);
}

void MCell::setImage(QPixmap image)
{
	if (Image != nullptr)
	{
		delete Image;
	}
	Image = new QPixmap(image);
}

void MCell::setImage(QPixmap* image)
{
	if (Image != nullptr)
	{
		delete Image;
	}
	Image = image;
}

void MCell::setVisuable(bool visuable)
{
	delete Visuable;
	Visuable = new bool(visuable);
}

void MCell::setRect(QRect rect)
{
	if (Rect != nullptr)
	{
		delete Rect;
	}
	Rect = new QRect(rect);
}

void MCell::setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height)
{
	if (Rect != nullptr)
	{
		delete Rect;
	}
	Rect = new QRect(lefttopx, lefttopy, width, height);
}

void MCell::setRadium(qreal xradium, qreal yradium)
{
	if (XRadium != nullptr)
	{
		delete XRadium;
	}
	if (YRadium != nullptr)
	{
		delete YRadium;
	}
	XRadium = new qreal(xradium);
	YRadium = new qreal(yradium);
}

void MCell::setRadium(qreal radium)
{
	if (XRadium != nullptr)
	{
		delete XRadium;
	}
	if (YRadium != nullptr)
	{
		delete YRadium;
	}
	XRadium = new qreal(radium);
	YRadium = new qreal(radium);
}

void MCell::setLine(QLine line)
{
	if (Line != nullptr)
	{
		delete Line;
	}
	Line = new QLine(line);
}

void MCell::setLine(QPoint start, QPoint end)
{
	if (Line != nullptr)
	{
		delete Line;
	}
	Line = new QLine(start, end);
}

void MCell::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
	if (Line != nullptr)
	{
		delete Line;
	}
	Line = new QLine(x1, y1, x2, y2);
}

void MCell::setPainterPath(QPainterPath painterpath)
{
	if (PainterPath != nullptr)
	{
		delete PainterPath;
	}
	PainterPath = new QPainterPath(painterpath);
}

void MCell::setText(QString text)
{
	if (Text != nullptr)
	{
		delete Text;
	}
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

void MCell::setIfLine(bool ifline)
{

}

void MCell::setIfFill(bool iffill)
{

}

void MCell::setLineColor(QColor color)
{

}

void MCell::setLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{

}

void MCell::setFillColor(QColor color)
{

}

void MCell::setFillColor(qint32 R, qint32 G, qint32 B, qint32 A)
{

}
