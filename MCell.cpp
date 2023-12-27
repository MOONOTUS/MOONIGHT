#include"MCell.h"
#include"MMainWindow.h"
#include"MWidget.h"

MCell::MCell(MMainWindow* parent)
	: QPushButton(parent)
{
	ParentMMainWindow = parent;
	ParentMWidget = nullptr;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
	Type = new qint32(imagecell);
	Image = nullptr;
	Rect = new QRect(0, 0, 0, 0);
	EllpiseCenter = nullptr;
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
	Rect = new QRect(0, 0, 0, 0);
	Image = nullptr;
	EllpiseCenter = nullptr;
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
	delete Type;
	Type = new qint32(type);
}

void MCell::paintEvent(QPaintEvent* event)
{
	QPainter* paint = new QPainter(this);
	this->setRect(*Rect);
	if (*Visuable)
	{
		if (*Type == imagecell)
		{
			if (Image != nullptr)
			{
				paint->drawPixmap(this->rect(), *Image);
			}
		}
	}

	event->accept();
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
	delete Rect;
	Rect = new QRect(rect);
	if (ParentMMainWindow != nullptr)
	{
		VRect = new QRect(Rect->x() * ParentMMainWindow->visualProportionX(), Rect->y() * ParentMMainWindow->visualProportionY(), Rect->width() * ParentMMainWindow->visualProportionX(), Rect->height() * ParentMMainWindow->visualProportionX());
	}
	else if (ParentMWidget != nullptr)
	{
		VRect = new QRect(Rect->x() * ParentMWidget->visualProportionX(), Rect->y() * ParentMWidget->visualProportionY(), Rect->width() * ParentMWidget->visualProportionX(), Rect->height() * ParentMWidget->visualProportionX());
	}
	this->setGeometry(*VRect);
}

void MCell::setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height)
{
	delete Rect;
	Rect = new QRect(lefttopx, lefttopy, width, height);
	if (ParentMMainWindow != nullptr)
	{
		VRect = new QRect(Rect->x() * ParentMMainWindow->visualProportionX(), Rect->y() * ParentMMainWindow->visualProportionY(), Rect->width() * ParentMMainWindow->visualProportionX(), Rect->height() * ParentMMainWindow->visualProportionX());
	}
	else if (ParentMWidget != nullptr)
	{
		VRect = new QRect(Rect->x() * ParentMWidget->visualProportionX(), Rect->y() * ParentMWidget->visualProportionY(), Rect->width() * ParentMWidget->visualProportionX(), Rect->height() * ParentMWidget->visualProportionX());
	}
	this->setGeometry(*VRect);
}

void MCell::setEllpiseCenter(QPoint center)
{
	if (EllpiseCenter != nullptr)
	{
		delete EllpiseCenter;
	}
	EllpiseCenter = new QPoint(center);
}

void MCell::setEllpiseCenter(qreal x, qreal y)
{
	if (EllpiseCenter != nullptr)
	{
		delete EllpiseCenter;
	}
	EllpiseCenter = new QPoint(x, y);
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

bool MCell::visuable()
{
	return *Visuable;
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
	delete IfLine;
	IfLine = new bool(ifline);
}

void MCell::setIfFill(bool iffill)
{
	delete IfFill;
	IfFill = new bool(iffill);
}

void MCell::setLineColor(QColor color)
{
	if (LineColor != nullptr)
	{
		delete LineColor;
	}
	LineColor = new QColor(color);
}

void MCell::setLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	if (LineColor != nullptr)
	{
		delete LineColor;
	}
	LineColor = new QColor(R, G, B, A);

}

void MCell::setFillColor(QColor color)
{
	if (FillColor != nullptr)
	{
		delete FillColor;
	}
	FillColor = new QColor(color);
}

void MCell::setFillColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	if (FillColor != nullptr)
	{
		delete LineColor;
	}
	FillColor = new QColor(R, G, B, A);
}

QRect* MCell::MRect()
{
	return Rect;
}