﻿#include"MPivot.h"

MCell::MCell(MMainWindow* parent)
	: QPushButton(parent)
{
	ParentMMainWindow = parent;
	ParentMWidget = nullptr;
	Visuable = new bool(true);
	IfLine = new bool(true);
	IfFill = new bool(false);
	Type = new qint32(imagecell);
	LinkState = nullptr;
	Image = nullptr;
	PathImage = nullptr;
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
	ChapterKey = nullptr;
	Pressing = new bool(false);

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
	LinkState = nullptr;
	Rect = new QRect(0, 0, 0, 0);
	VRect = new QRect(0, 0, 0, 0);
	Image = nullptr;
	PathImage = nullptr;
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
	ChapterKey = nullptr;
	Pressing = new bool(false);

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
		else if (*Type == linecell)
		{
			qDebug() << "MOONOTUSYSTEM::_Message_::LineCell paints";
			if (*IfLine)
			{
				if (Line != nullptr)
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
					else
					{
						pen.setColor(Qt::transparent);
					}
					paint->setPen(pen);
					paint->drawLine(*Line);

				}
			}
		}
		else if (*Type == painterpathcell)
		{
			qDebug() << "MOONOTUSYSTEM::_Message_::PainterPathCell paints";
			if (PathImage != nullptr)
			{
				paint->drawPixmap(this->rect(), *PathImage);
			}
		}
		else if (*Type == textcell)
		{
			qDebug() << "MOONOTUSYSTEM::_Message_::TextCell paints";
			if (Text != nullptr)
			{
				if (ParentMMainWindow != nullptr)
				{
					paint->setFont(QFont(this->font().family(), this->font().pointSizeF() * ParentMMainWindow->visualProportion(), -1));
				}
				else if (ParentMWidget != nullptr)
				{
					paint->setFont(QFont(this->font().family(), this->font().pointSizeF() * ParentMWidget->visualProportion(), -1));
				}
				if (LineColor != nullptr)
				{
					pen.setColor(*LineColor);
				}
				else
				{
					pen.setColor(Qt::transparent);
				}
				paint->setPen(pen);
				paint->drawText(this->rect(), Qt::AlignHCenter | Qt::AlignVCenter, *Text);
			}
		}
		else if (*Type == chaptercell)
		{
			qDebug() << "MOONOTUSYSTEM::_Message_::ChapterCell paints";
			if (Image != nullptr)
			{
				paint->drawPixmap(this->rect(), *Image);
			}
			if (Text != nullptr)
			{
				if (ParentMMainWindow != nullptr)
				{
					paint->setFont(QFont(this->font().family(), this->font().pointSizeF() * ParentMMainWindow->visualProportion(), -1));
				}
				else if (ParentMWidget != nullptr)
				{
					paint->setFont(QFont(this->font().family(), this->font().pointSizeF() * ParentMWidget->visualProportion(), -1));
				}
				if (LineColor != nullptr)
				{
					pen.setColor(*LineColor);
				}
				else
				{
					pen.setColor(Qt::transparent);
				}
				paint->setPen(pen);
				if (ParentMMainWindow != nullptr)
				{
					paint->drawText(this->rect().x(), this->rect().y() - this->font().pointSizeF() * ParentMMainWindow->visualProportion(), this->rect().width(), this->font().pointSizeF()* ParentMMainWindow->visualProportion(), Qt::AlignLeft | Qt::AlignVCenter, *Text);
				}
				else if (ParentMWidget != nullptr)
				{
					paint->drawText(this->rect().x(), this->rect().y() - this->font().pointSizeF() * ParentMWidget->visualProportion(), this->rect().width(), this->font().pointSizeF()* ParentMWidget->visualProportion(), Qt::AlignLeft | Qt::AlignVCenter, *Text);
				}
			}
			if (*Pressing)
			{
				pen.setColor(Qt::transparent);
				paint->setBrush(QColor(0, 0, 0, 50));
				paint->drawRect(this->rect());
			}
		}
	}
	delete paint;

	event->accept();
}

void MCell::MousePressEvent(QMouseEvent* event)
{
	if (!*Pressing)
	{
		delete Pressing;
		Pressing = new bool(true);
	}
}

void MCell::MouseReleaseEvent(QMouseEvent* event)
{
	if (*Pressing)
	{
		if (*Type == chaptercell)
		{
			emit(Mclicked(*ChapterKey));
		}
		delete Pressing;
		Pressing = new bool(false);
	}
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
	if (*Type == linecell)
	{
		if (Line != nullptr)
		{
			this->setLine(*Line);
		}
		if (LineWidth != nullptr)
		{
			this->setLineWidth(*LineWidth);
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
	if (VLine != nullptr)
	{
		delete VLine;
	}
	if (ParentMMainWindow != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMMainWindow->visualProportion(), Line->p1().y() * ParentMMainWindow->visualProportion(), Line->p2().x() * ParentMMainWindow->visualProportion(), Line->p2().y() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMWidget->visualProportion(), Line->p1().y() * ParentMWidget->visualProportion(), Line->p2().x() * ParentMWidget->visualProportion(), Line->p2().y() * ParentMWidget->visualProportion());
	}
}

void MCell::setLine(QPoint start, QPoint end)
{
	if (Line != nullptr)
	{
		delete Line;
	}
	Line = new QLine(start, end);
	if (VLine != nullptr)
	{
		delete VLine;
	}
	if (ParentMMainWindow != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMMainWindow->visualProportion(), Line->p1().y() * ParentMMainWindow->visualProportion(), Line->p2().x() * ParentMMainWindow->visualProportion(), Line->p2().y() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMWidget->visualProportion(), Line->p1().y() * ParentMWidget->visualProportion(), Line->p2().x() * ParentMWidget->visualProportion(), Line->p2().y() * ParentMWidget->visualProportion());
	}
}

void MCell::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
	if (Line != nullptr)
	{
		delete Line;
	}
	Line = new QLine(x1, y1, x2, y2);
	if (VLine != nullptr)
	{
		delete VLine;
	}
	if (ParentMMainWindow != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMMainWindow->visualProportion(), Line->p1().y() * ParentMMainWindow->visualProportion(), Line->p2().x() * ParentMMainWindow->visualProportion(), Line->p2().y() * ParentMMainWindow->visualProportion());
	}
	else if (ParentMWidget != nullptr)
	{
		VLine = new QLine(Line->p1().x() * ParentMWidget->visualProportion(), Line->p1().y() * ParentMWidget->visualProportion(), Line->p2().x() * ParentMWidget->visualProportion(), Line->p2().y() * ParentMWidget->visualProportion());
	}
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
	if (PathImage != nullptr)
	{
		delete PathImage;
	}
	PathImage = new QPixmap(Rect->width(), Rect->height());
	QPainter* pathpaint = new QPainter(PathImage);
	QPen pathpen;
	if (*IfLine)
	{
		if (LineWidth != nullptr)
		{
			pathpen.setWidth(*LineWidth);
		}
		if (LineColor != nullptr)
		{
			pathpen.setColor(*LineColor);
		}
	}
	else
	{
		pathpen.setColor(Qt::transparent);
	}
	if (*IfFill)
	{
		if (FillColor != nullptr)
		{
			pathpaint->setBrush(*FillColor);
		}
	}
	else
	{
		pathpaint->setBrush(Qt::transparent);
	}
	pathpaint->drawPath(painterpath);
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

void MCell::setLinkState(qint32 linkstate)
{
	if (LinkState != nullptr)
	{
		delete LinkState;
	}
	LinkState = new qint32(linkstate);
}

qint32 MCell::linkState()
{
	return *LinkState;
}

void MCell::setChapterKey(QString chapterkey)
{
	if (ChapterKey != nullptr)
	{
		delete ChapterKey;
	}
	ChapterKey = new QString(chapterkey);
}

QString MCell::chapterKey()
{
	return *ChapterKey;
}