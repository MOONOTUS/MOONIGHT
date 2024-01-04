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
	LinkState = nullptr;
	Image = nullptr;
	CoverImage = nullptr;
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
	CoverColor = nullptr;
	ChapterKey = nullptr;
	Pressing = new bool(false);
	Mask = nullptr;
	VMask = nullptr;
	IfMask = new bool(false);
	IfCover = new bool(false);
	IfImageCover = new bool(false);
	Pressable = new bool(false);
	SongList = new QMap<QString, MCell*>;
	SongNumList = new QMap<qint64, QString>;
	SongID = nullptr;
	SongSum = new qint64(0);

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
	CoverImage = nullptr;
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
	CoverColor = nullptr;
	ChapterKey = nullptr;
	Pressing = new bool(false);
	Mask = nullptr;
	VMask = nullptr;
	IfMask = new bool(false);
	IfCover = new bool(false);
	IfImageCover = new bool(false);
	Pressable = new bool(false);
	SongList = new QMap<QString, MCell*>;
	SongNumList = new QMap<qint64, QString>;
	SongID = nullptr;
	SongSum = new qint64(0);

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
			if (*IfImageCover)
			{
				if (CoverImage != nullptr)
				{
					paint->drawPixmap(this->rect(), *CoverImage);
				}
			}			
			if (*Pressing)
			{
				pen.setColor(QColor(0, 0, 0, 50));
				paint->setPen(pen);
				paint->setBrush(QColor(0, 0, 0, 50));
				paint->drawRect(this->rect());
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
			if (*Pressing)
			{
				pen.setColor(QColor(0, 0, 0, 50));
				paint->setPen(pen);
				paint->setBrush(QColor(0, 0, 0, 50));
				paint->drawRect(this->rect());
			}
		}
		else if (*Type == songcell)
		{
			qDebug() << "MOONOTUSYSTEM::_Message_::SongCell paints";
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
				if (*Pressing)
				{
					pen.setColor(QColor(0, 0, 0, 255));
					paint->setPen(pen);
					paint->drawText(this->rect(), Qt::AlignLeft | Qt::AlignVCenter, "   " + * Text);
				}
				else
				{
					pen.setColor(QColor(0, 0, 0, 200));
					paint->setPen(pen);
					paint->drawText(this->rect(), Qt::AlignLeft | Qt::AlignBottom, "   " + * Text);
				}
			}
		}
		if (*IfCover)
		{
			if (CoverColor != nullptr)
			{
				pen.setColor(*CoverColor);
				paint->setPen(pen);
				paint->setBrush(*CoverColor);
				paint->drawRect(this->rect());
			}
		}
	}
	delete paint;

	event->accept();
}

void MCell::mousePressEvent(QMouseEvent* event)
{
	if (!*Pressing && *Pressable)
	{
		delete Pressing;
		Pressing = new bool(true);
	}
	grabMouse();

	event->accept();
}

void MCell::mouseReleaseEvent(QMouseEvent* event)
{
	if (*Pressing)
	{
		if (ParentMMainWindow != nullptr)
		{
			if (*Type == chaptercell && ParentMMainWindow->chapterNumList()->key(*this->ChapterKey) == ParentMMainWindow->centerChapter())
			{
				if (ChapterKey != nullptr)
				{
					emit(Mclicked(*ChapterKey));
				}
			}
			else if (*Type == songcell || *Type == imagecell)
			{
				if (SongID != nullptr)
				{
					emit(Mclicked(*SongID));
				}
			}
			else
			{
				emit(clicked());
			}
		}
		else
		{
			emit(clicked());
		}
		delete Pressing;
		Pressing = new bool(false);
	}
	releaseMouse();

	event->accept();
}

void MCell::resizeEvent(QResizeEvent* event)
{
	if (Mask != nullptr)
	{
		if (VMask != nullptr)
		{
			delete VMask;
		}
		VMask = new QPixmap(this->rect().width(), this->rect().height());
		QPainter vmaskpaint(VMask);
		vmaskpaint.drawPixmap(VMask->rect(), *Mask);
	}
	if (*IfMask)
	{
		if (VMask != nullptr)
		{
			this->QWidget::setMask(QBitmap(*VMask));
		}
	}
	else
	{
		this->clearMask();
	}

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

void MCell::CenterChapterChangeTo()
{
	if (*Type == chaptercell)
	{
		if (ParentMMainWindow != nullptr)
		{
			ParentMMainWindow->setCenterChapter(ParentMMainWindow->chapterNumList()->key(*this->ChapterKey));
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

void MCell::setCoverImage(QString path)
{
	if (CoverImage != nullptr)
	{
		delete CoverImage;
	}
	CoverImage = new QPixmap(path);
}

void MCell::setCoverImage(QPixmap coverimage)
{
	if (CoverImage != nullptr)
	{
		delete CoverImage;
	}
	CoverImage = new QPixmap(coverimage);
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

void MCell::setIfCover(bool ifcover)
{
	delete IfCover;
	IfCover = new bool(ifcover);
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
		delete FillColor;
	}
	FillColor = new QColor(R, G, B, A);
}

void MCell::setCoverColor(QColor color)
{
	if (CoverColor != nullptr)
	{
		delete CoverColor;
	}
	CoverColor = new QColor(color);
}

void MCell::setCoverColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	if (CoverColor != nullptr)
	{
		delete CoverColor;
	}
	CoverColor = new QColor(R, G, B, A);
}

QRect* MCell::MRect()
{
	return Rect;
}

QRect* MCell::MVRect()
{
	return VRect;
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

void MCell::setMMask(QString path)
{
	if (Mask != nullptr)
	{
		delete Mask;
	}
	Mask = new QPixmap(path);
	if (VMask != nullptr)
	{
		delete VMask;
	}
	VMask = new QPixmap(this->rect().width(),this->rect().height());
	QPainter vmaskpaint(VMask);
	vmaskpaint.drawPixmap(VMask->rect(), *Mask);
	if (*IfMask)
	{
		if (VMask != nullptr)
		{
			this->QWidget::setMask(QBitmap(*VMask));
		}
	}
	else
	{
		this->clearMask();
	}
}

void MCell::setMMask(QPixmap image)
{
	if (Mask != nullptr)
	{
		delete Mask;
	}
	Mask = new QPixmap(image);
	if (VMask != nullptr)
	{
		delete VMask;
	}
	VMask = new QPixmap(this->rect().width(), this->rect().height());
	QPainter vmaskpaint(VMask);
	vmaskpaint.drawPixmap(VMask->rect(), *Mask);
	if (*IfMask)
	{
		if (VMask != nullptr)
		{
			this->QWidget::setMask(QBitmap(*VMask));
		}
	}
	else
	{
		this->clearMask();
	}
}

void MCell::setIfMask(bool ifmask)
{
	delete IfMask;
	IfMask = new bool(ifmask);
	if (*IfMask)
	{
		if (VMask != nullptr)
		{
			this->QWidget::setMask(QBitmap(*VMask));
		}
	}
	else
	{
		this->clearMask();
	}
}

QString MCell::text()
{
	if (Text != nullptr)
	{
		return *Text;
	}
	else
	{
		return "N/A";
	}
}

QColor MCell::lineColor()
{
	if (LineColor != nullptr)
	{
		return *LineColor;
	}
	else
	{
		return Qt::transparent;
	}
}

void MCell::setSongName(QString songname)
{
	if (Text != nullptr)
	{
		delete Text;
	}
	Text = new QString(songname);
}

void MCell::setSongID(qint64 songid)
{
	if (SongID != nullptr)
	{
		delete SongID;
	}
	SongID = new qint64(songid);
}

QString MCell::songName()
{
	if (Text != nullptr)
	{
		return *Text;
	}
	else
	{
		return "Unknown";
	}
}

qint64 MCell::songID()
{
	if (SongID != nullptr)
	{
		return *SongID;
	}
	else
	{
		return -1;
	}
}

QMap<QString, MCell*>*& MCell::songList()
{
	return SongList;
}

QMap<qint64, QString>*& MCell::songNumList()
{
	return SongNumList;
}

void MCell::addSong(qint64 songid, QString key, QString songname, QPixmap songcover)
{
	if (ParentMMainWindow != nullptr)
	{
		MCell* newsong = new MCell(this->ParentMMainWindow);
		newsong->setType(songcell);
		newsong->setPressable(true);
		newsong->setSongID(songid);
		newsong->setSongName(songname);
		newsong->setImage(songcover);
		newsong->setChapterKey(*this->ChapterKey);
		newsong->setFont(QFont(FONT_1, 150, -1));
		SongList->insert(key, newsong);
		qint64 SongSum_ = *SongSum;
		delete SongSum;
		SongSum = new qint64(SongSum_ + 1);
		SongNumList->insert(*SongSum, key);
		ParentMMainWindow->addCell(key, newsong, songliststate);
	}
	else if (ParentMWidget != nullptr)
	{
		MCell* newsong = new MCell(this->ParentMWidget);
		newsong->setType(songcell);
		newsong->setPressable(true);
		newsong->setSongID(songid);
		newsong->setSongName(songname);
		newsong->setImage(songcover);
		newsong->setChapterKey(*this->ChapterKey);
		newsong->setFont(QFont(FONT_1, 150, -1));
		SongList->insert(key, newsong);
		qint64 SongSum_ = *SongSum;
		delete SongSum;
		SongSum = new qint64(SongSum_ + 1);
		SongNumList->insert(*SongSum, key);
	}
}

void MCell::addSong(qint64 songid, QString key, QString songname, QString songcoverpath)
{
	if (ParentMMainWindow != nullptr)
	{
		MCell* newsong = new MCell(this->ParentMMainWindow);
		newsong->setType(songcell);
		newsong->setPressable(true);
		newsong->setSongID(songid);
		newsong->setSongName(songname);
		newsong->setImage(songcoverpath);
		newsong->setChapterKey(*this->ChapterKey);
		SongList->insert(key, newsong);
		newsong->setFont(QFont(FONT_1, 150, -1));
		qint64 SongSum_ = *SongSum;
		delete SongSum;
		SongSum = new qint64(SongSum_ + 1);
		SongNumList->insert(*SongSum, key);
		ParentMMainWindow->addCell(key, newsong, songliststate);
	}
	else if (ParentMWidget != nullptr)
	{
		MCell* newsong = new MCell(this->ParentMWidget);
		newsong->setType(songcell);
		newsong->setPressable(true);
		newsong->setSongID(songid);
		newsong->setSongName(songname);
		newsong->setImage(songcoverpath);
		newsong->setChapterKey(*this->ChapterKey);
		SongList->insert(key, newsong);
		newsong->setFont(QFont(FONT_1, 150, -1));
		qint64 SongSum_ = *SongSum;
		delete SongSum;
		SongSum = new qint64(SongSum_ + 1);
		SongNumList->insert(*SongSum, key);
	}
}

void MCell::setIfImageCover(bool ifimagecover)
{
	delete IfImageCover;
	IfImageCover = new bool(ifimagecover);
}

void MCell::setPressable(bool pressable)
{
	delete Pressable;
	Pressable = new bool(pressable);
}