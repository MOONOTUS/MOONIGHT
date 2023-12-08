#include"MCheckDot.h"
#include"MWidget.h"

MCheckDot::MCheckDot(MWidget *parent)
	: QPushButton(parent)
{
	this->Parent = parent;
	DotColor = new QColor(217, 150, 229, 255);
	DotKeyColor = new QColor(DotColor->red(), DotColor->green(), DotColor->blue(), DotColor->alpha() * 2 / 3);
	Width = new qreal(6.0);
	Radium = new qreal(30.0);
	Visuable = new bool(true);
	Point = new QPoint(parent->width() / 2, parent->height() / 2);
	DotLine = new MCheckDotLine(this);
	NoteList = new QMap<qint64, MNote*>;
	NoteCheckList = new QMap<qint64, qint32*>;
	KeyVisuable = new bool(false);
	this->setGeometry(0,0,parent->width(),parent->height());
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setFont(QFont("Microsoft YaHei Ui", *Radium, *Width - 2));

	connect
	(
		this,
		SIGNAL(touched()),
		this,
		SLOT(check())
	);

}

MCheckDot::~MCheckDot()
{}



void MCheckDot::paintEvent(QPaintEvent* event)
{
	this->setGeometry(0, (Parent->height() - Parent->width() * 9 / 16) / 2, Parent->width(), Parent->width() * 9 / 16);
	DotLine->setWidth(DotLine->width());
	for (QMap<qint64, MNote*>::iterator listptr = NoteList->begin(); listptr != NoteList->end(); ++listptr)
	{
		listptr.value()->setRadium(listptr.value()->radium());
		listptr.value()->setWidth(listptr.value()->width());
	}
	VPoint = new QPoint(Point->x() * this->size().width() / Parent->oriSize().width(), Point->y() * this->size().height() / Parent->oriSize().height());
	VWidth = new qreal(*Width * Parent->width() / Parent->oriSize().width());
	VRadium = new qreal(*Radium * Parent->width() / Parent->oriSize().width());
	this->setFont(QFont("Microsoft YaHei Ui", *VRadium, *VWidth - 2));
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);

	if (DotLine->visuable())
	{
		paintDotLine(paint);
	}
	if (*Visuable)
	{
		paintDot(paint);
	}
	//if (!NoteList->isEmpty())
	//{
	//	paintNote(paint);
	//}

	event->accept();
}

void MCheckDot::keyPressEvent(QKeyEvent* key)
{
	if (key->key() == *Key)
	{
		emit(touched());
	}
}

void MCheckDot::paintDot(QPainter* paint)
{
	QPen pen;
	pen.setWidth(*VWidth);
	pen.setColor(*DotColor);
	paint->setPen(pen);
	paint->drawEllipse(*VPoint, qint32(*VRadium), qint32(*VRadium));
	if (*KeyVisuable)
	{
		paint->setFont(font());
		pen.setColor(*DotKeyColor);
		paint->setPen(pen);
		paint->drawText(QRect(VPoint->x() - QFontMetricsF(font()).maxWidth() * KeyText->size() / 2, VPoint->y() - QFontMetricsF(font()).height() / 2, QFontMetricsF(font()).maxWidth() * KeyText->size(), QFontMetricsF(font()).height()), Qt::AlignHCenter | Qt::AlignVCenter, *KeyText);
		//paint->drawText(QRect(VPoint->x(), VPoint->y(), QFontMetricsF(font()).maxWidth() * KeyText->size(), QFontMetricsF(font()).height()), *KeyText);
	}
}

void MCheckDot::paintDotLine(QPainter* paint)
{
	QLineF lineU, lineD;
	QLineF line01, line02;
	line01.setP1(*VPoint);
	line02.setP1(*VPoint);
	line01.setAngle(-DotLine->angle());
	line02.setAngle(-(DotLine->angle() - 180));
	line01.setLength(*VRadium);
	line02.setLength(*VRadium);
	lineU.setP1(line01.p2());
	lineD.setP1(line02.p2());
	lineU.setAngle(-DotLine->angle());
	lineD.setAngle(-(DotLine->angle() - 180));
	lineU.setLength(2500);
	lineD.setLength(2500);
	QPen pen;
	pen.setWidth(DotLine->vWidth());
	pen.setColor(DotLine->dotLineColor());
	paint->setPen(pen);
	paint->drawLine(lineU);
	paint->drawLine(lineD);
}

void MCheckDot::setDotLine(MCheckDotLine& dotline)
{
	DotLine = new MCheckDotLine(dotline);
}

MCheckDotLine*& MCheckDot::dotLine()
{
	return DotLine;
}

void MCheckDot::setVisuable(bool visuable)
{
	Visuable = new bool(visuable);
}

bool MCheckDot::visuable()
{
	return *Visuable;
}

void MCheckDot::setPoint(QPoint& point)
{
	Point = new QPoint(point);
}

void MCheckDot::setPoint(qreal x, qreal y)
{
	Point = new QPoint(x, y);
}

QPoint MCheckDot::point()
{
	return *Point;
}

void MCheckDot::setRadium(qreal r)
{
	Radium = new qreal(r);
}

qreal MCheckDot::radium()
{
	return *Radium;
}

void MCheckDot::setWidth(qreal width)
{
	Width = new qreal(width);
}

qreal MCheckDot::width()
{
	return *Width;
}

void MCheckDot::setDotColor(QColor color)
{
	DotColor = new QColor(color);
}

void MCheckDot::setDotColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	DotColor = new QColor(R, G, B, A);
}

QColor MCheckDot::dotColor()
{
	return *DotColor;
}

void MCheckDot::setDotKeyColor(QColor color)
{
	DotKeyColor = new QColor(color);
}

void MCheckDot::setDotKeyColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	DotKeyColor = new QColor(R, G, B, A);
}

QColor MCheckDot::dotKeyColor()
{
	return *DotKeyColor;
}

void MCheckDot::setKey(qint32 key, QString keytext)
{
	Key = new qint32(key);
	KeyText = new QString(keytext);
}

qint32 MCheckDot::key()
{
	return *Key;
}

QString MCheckDot::keyText()
{
	return *KeyText;
}

QMap<qint64, MNote*>*& MCheckDot::notelist()
{
	return NoteList;
}

MWidget*& MCheckDot::MParent()
{
	return Parent;
}

void MCheckDot::setKeyVisuable(bool visuable)
{
	KeyVisuable = new bool(visuable);
}

bool MCheckDot::keyVisuable()
{
	return *KeyVisuable;
}

qint32 MCheckDot::check()
{
	return 0;
}