#include"MPivot.h"

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
	VRect = new QRect(0, 0, 0, 0);
	EllipseCenter = nullptr;
	VEllipseCenter = nullptr;
	XRadium = nullptr;
	VXRadium = nullptr;
	YRadium = nullptr;
	VYRadium = nullptr;
	Line = nullptr;
	VLine = nullptr;
	LineWidth = nullptr;
	VLineWidth = nullptr;
	PainterPath = nullptr;
	VPainterPath = nullptr;
	Text = nullptr;
	LineColor = nullptr;
	FillColor = nullptr;

	connect
	(
		ParentMMainWindow->uiFlushTime(),
		SIGNAL(timeout()),
		this,
		SLOT(Mupdate())
	);
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
	VRect = new QRect(0, 0, 0, 0);
	Image = nullptr;
	EllipseCenter = nullptr;
	VEllipseCenter = nullptr;
	XRadium = nullptr;
	VXRadium = nullptr;
	YRadium = nullptr;
	VYRadium = nullptr;
	Line = nullptr;
	VLine = nullptr;
	LineWidth = nullptr;
	VLineWidth = nullptr;
	PainterPath = nullptr;
	VPainterPath = nullptr;
	Text = nullptr;
	LineColor = nullptr;
	FillColor = nullptr;

	connect
	(
		ParentMWidget->mainTime(),
		SIGNAL(timeout()),
		this,
		SLOT(Mupdate())
	);
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
//#define rectcell 0x001
//#define ellipsecell 0x002
//#define linecell 0x003
//#define painterpathcell 0x004
//#define textcell 0x005
	QPainter* paint = new QPainter(this);
	QPen pen;
	this->setRect(*Rect);
	if (*Visuable)
	{
		if (*Type == imagecell)
		{
			if (Image != nullptr)
			{
				qDebug() << "MOONOTUSYSTEM::_Message_::ImageCell paints";
				paint->drawPixmap(this->rect(), *Image);
			}
		}
		if (*Type == ellipsecell)
		{
			if (VEllipseCenter != nullptr && VXRadium != nullptr && VYRadium != nullptr)
			{
				qDebug() << "MOONOTUSYSTEM::_Message_::EllipseCell paints";
				this->setEllipseCenter(*EllipseCenter);
				this->setRadium(*XRadium, *YRadium);
				if (*IfLine)
				{
					if (LineWidth != nullptr)
					{
						this->setLineWidth(*LineWidth);
						pen.setWidth(*VLineWidth);
					}
					if (LineColor != nullptr)
					{
						pen.setColor(*LineColor);
					}
				}
				else
				{
					pen.setColor(Qt::transparent);
				}
				paint->setPen(pen);
				if (*IfFill)
				{
					if (FillColor != nullptr)
					{
						paint->setBrush(*FillColor);
					}
				}
				else
				{
					paint->setBrush(Qt::transparent);
				}
				paint->drawEllipse(QPointF(*VEllipseCenter), *VXRadium, *VYRadium);
			}
		}
	}
	delete paint;

	event->accept();
}

void MCell::Mupdate()
{
	this->setRect(*Rect);
	if (*Type == imagecell)
	{

	}
	if (*Type == ellipsecell)
	{
		if (VEllipseCenter != nullptr && VXRadium != nullptr && VYRadium != nullptr)
		{
			this->setEllipseCenter(*EllipseCenter);
			this->setRadium(*XRadium, *YRadium);
			if (LineWidth != nullptr)
			{
				this->setLineWidth(*LineWidth);
			}
		}
	}
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
	//自适应规则：X坐标依赖visualProportionX()，Y坐标依赖visualProportionY(),长度、范围等均依赖visualProportion()
	delete Rect;
	Rect = new QRect(rect);
	if (ParentMMainWindow != nullptr)
	{
		delete VRect;
		VRect = new QRect(Rect->x() * ParentMMainWindow->visualProportionX(), Rect->y() * ParentMMainWindow->visualProportionY(), Rect->width() * ParentMMainWindow->visualProportion(), Rect->height() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		delete VRect;
		VRect = new QRect(Rect->x() * ParentMWidget->visualProportionX(), Rect->y() * ParentMWidget->visualProportionY(), Rect->width() * ParentMWidget->visualProportion(), Rect->height() * ParentMWidget->visualProportion());
	}
	this->setGeometry(*VRect);
}

void MCell::setRect(qreal lefttopx, qreal lefttopy, qreal width, qreal height)
{
	delete Rect;
	Rect = new QRect(lefttopx, lefttopy, width, height);
	if (ParentMMainWindow != nullptr)
	{
		delete VRect;
		VRect = new QRect(Rect->x() * ParentMMainWindow->visualProportionX(), Rect->y() * ParentMMainWindow->visualProportionY(), Rect->width() * ParentMMainWindow->visualProportion(), Rect->height() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		delete VRect;
		VRect = new QRect(Rect->x() * ParentMWidget->visualProportionX(), Rect->y() * ParentMWidget->visualProportionY(), Rect->width() * ParentMWidget->visualProportion(), Rect->height() * ParentMWidget->visualProportion());
	}
	this->setGeometry(*VRect);
}

void MCell::setEllipseCenter(QPoint center)
{
	if (EllipseCenter != nullptr)
	{
		delete EllipseCenter;
	}
	EllipseCenter = new QPoint(center);
	if (VEllipseCenter != nullptr)
	{
		delete VEllipseCenter;
	}
	if (ParentMMainWindow != nullptr)
	{
		VEllipseCenter = new QPoint(EllipseCenter->x() * ParentMMainWindow->visualProportion(), EllipseCenter->y() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VEllipseCenter = new QPoint(EllipseCenter->x() * ParentMWidget->visualProportion(), EllipseCenter->y() * ParentMWidget->visualProportion());
	}
}

void MCell::setEllipseCenter(qreal x, qreal y)
{
	if (EllipseCenter != nullptr)
	{
		delete EllipseCenter;
	}
	EllipseCenter = new QPoint(x, y);
	if (VEllipseCenter != nullptr)
	{
		delete VEllipseCenter;
	}
	if (ParentMMainWindow != nullptr)
	{
		VEllipseCenter = new QPoint(EllipseCenter->x() * ParentMMainWindow->visualProportion(), EllipseCenter->y() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VEllipseCenter = new QPoint(EllipseCenter->x() * ParentMWidget->visualProportion(), EllipseCenter->y() * ParentMWidget->visualProportion());
	}
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
	if (VXRadium != nullptr)
	{
		delete VXRadium;
	}
	if (VYRadium != nullptr)
	{
		delete VYRadium;
	}
	if (ParentMMainWindow != nullptr)
	{
		VXRadium = new qreal(*XRadium * ParentMMainWindow->visualProportion());
		VYRadium = new qreal(*YRadium * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VXRadium = new qreal(*XRadium * ParentMWidget->visualProportion());
		VYRadium = new qreal(*YRadium * ParentMWidget->visualProportion());
	}
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
	if (VXRadium != nullptr)
	{
		delete VXRadium;
	}
	if (VYRadium != nullptr)
	{
		delete VYRadium;
	}
	if (ParentMMainWindow != nullptr)
	{
		VXRadium = new qreal(*XRadium * ParentMMainWindow->visualProportion());
		VYRadium = new qreal(*YRadium * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VXRadium = new qreal(*XRadium * ParentMWidget->visualProportion());
		VYRadium = new qreal(*YRadium * ParentMWidget->visualProportion());
	}
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

void MCell::setLineWidth(qreal width)
{
	if (LineWidth != nullptr)
	{
		delete LineWidth;
	}
	LineWidth = new qreal(width);
	if (VLineWidth != nullptr)
	{
		delete VLineWidth;
	}
	if (ParentMMainWindow != nullptr)
	{
		VLineWidth = new qreal(*LineWidth * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VLineWidth = new qreal(*LineWidth * ParentMWidget->visualProportion());
	}
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

QPixmap MCell::image() const
{
	return *Image;
}

bool MCell::visuable() const
{
	return *Visuable;
}

qreal MCell::lineWidth() const
{
	return *LineWidth;
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