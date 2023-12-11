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
	NextTime = new qint64(0);
	NoteCheckList = new QMap<qint64, qint32>;
	KeyVisuable = new bool(false);
	KeyPressingList = new QSet<qint32>;
	HoldPressing = new bool(false);
	Speed = new qreal(10.0);
	VSpeed = new qreal(*Speed * parent->width() / parent->oriSize().width());
	LineRadium = new qreal(2500.0);
	VLineRadium = new qreal(*LineRadium * parent->width() / parent->oriSize().width());
	this->setGeometry(0,0,parent->width(),parent->height());
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->setFont(QFont("Microsoft YaHei Ui", *Radium, *Width - 2));

	parent->MParent()->connect
	(
		this,
		SIGNAL(touched()),
		this,
		SLOT(check())
	);
	parent->MParent()->connect
	(
		this,
		SIGNAL(released()),
		this,
		SLOT(aftercheck())
	);
	parent->MParent()->connect
	(
		this,
		SIGNAL(misschecked()),
		this,
		SLOT(misscheck())
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
	VSpeed = new qreal(10.0 * Parent->width() / Parent->oriSize().width());
	VLineRadium = new qreal(*LineRadium * Parent->width() / Parent->oriSize().width());
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
	if (!NoteList->isEmpty())
	{
		paintNote(paint);
	}
	if (*NextTime - Parent->time() < -250)
	{
		emit(misschecked());
	}

	event->accept();
}

void MCheckDot::keyPressEvent(QKeyEvent* event)
{
	KeyPressingList->insert(event->key());
	if (KeyPressingList->contains(*Key))
	{
		emit(touched());
	}
	if (NoteList->contains(*NextTime))
	{
		if (NoteList->value(*NextTime)->type() == beat)
		{
			if ((KeyPressingList->contains(*Key) && KeyPressingList->contains(NoteList->value(*NextTime)->beatKey())) || (KeyPressingList->contains(*Key) && KeyPressingList->contains(NoteList->value(*NextTime)->beatKey())))
			{
				emit(touched());
			}
		}
		else
		{
			if (KeyPressingList->contains(*Key))
			{
				emit(touched());
			}
		}
	}
	else
	{
		qDebug() << "MOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)\n";
	}
	releaseKeyboard();
}

void MCheckDot::keyReleaseEvent(QKeyEvent* event)
{
	KeyPressingList->remove(event->key());
	if (HoldPressing)
	{
		HoldPressing = new bool(false);
		emit(released());
	}
	releaseKeyboard();
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
	line01.setAngle(DotLine->angle());
	line02.setAngle((DotLine->angle() - 180));
	line01.setLength(*VRadium);
	line02.setLength(*VRadium);
	lineU.setP1(line01.p2());
	lineD.setP1(line02.p2());
	lineU.setAngle(DotLine->angle());
	lineD.setAngle((DotLine->angle() - 180));
	lineU.setLength(2500);
	lineD.setLength(2500);
	QPen pen;
	pen.setWidth(DotLine->vWidth());
	pen.setColor(DotLine->dotLineColor());
	paint->setPen(pen);
	paint->drawLine(lineU);
	paint->drawLine(lineD);
}

void MCheckDot::paintNote(QPainter* paint)
{
	if (NoteList->contains(*NextTime))
	{
		qint64* NextTimeTemp = new qint64(*NextTime);
		while (NoteList->value(*NextTime)->time() * *Speed <= 2203 - NoteList->value(*NextTime)->radium())
		{
			switch (NoteList->value(*NextTime)->type())
			{
			case click:
				break;
			case catch:
				break;
			case hold:
				break;
			case beat:
				break;
			}
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		NextTime = new qint64(*NextTimeTemp);
	}
	else
	{
		qDebug() << "MOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)\n";
	}

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

QMap<qint64, MNote*>*& MCheckDot::noteList()
{
	return NoteList;
}

void MCheckDot::setNextTime(qint64 time_ms)
{
	NextTime = new qint64(time_ms);
}

qint64 MCheckDot::nextTime()
{
	return *NextTime;
}

QMap<qint64, qint32>*& MCheckDot::noteCheckList()
{
	return NoteCheckList;
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

void MCheckDot::setSpeed(qreal speed_px)
{
	Speed = new qreal(speed_px);
	VSpeed = new qreal(*Speed * Parent->width() / Parent->oriSize().width());
}

qreal MCheckDot::speed()
{
	return *Speed;
}

void MCheckDot::setLineRadium(qreal lineradium)
{
	LineRadium = new qreal(lineradium);
	VLineRadium = new qreal(*LineRadium * Parent->width() / Parent->oriSize().width());
}

qreal MCheckDot::lineRadium()
{
	return *LineRadium;
}

void MCheckDot::check()
{
	qDebug() << "MOONOTUSYSTEM::_MESSAGE_::Check runs\n";
	if (NoteList->contains(*NextTime))
	{
		qDebug() << "MOONOTUSYSTEM::_MESSAGE_::Check real runs\n";
		if (NoteList->value(*NextTime)->type() == catch)
		{
			if (NoteList->value(*NextTime)->time() == Parent->time())
			{
				NoteCheckList->insert(*NextTime, strictperfect);
				NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
			}
		}
		else if (NoteList->value(*NextTime)->type() == hold)
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				NoteCheckList->insert(*NextTime, strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				NoteCheckList->insert(*NextTime, preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				NoteCheckList->insert(*NextTime, lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				NoteCheckList->insert(*NextTime, pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				NoteCheckList->insert(*NextTime, laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 160 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 250)
			{
				NoteCheckList->insert(*NextTime, prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -160 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -250)
			{
				NoteCheckList->insert(*NextTime, lagbad);
			}
			HoldPressing = new bool(true);
			HoldPressed = new qint64(*NextTime);
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		else
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				NoteCheckList->insert(*NextTime, strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				NoteCheckList->insert(*NextTime, preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				NoteCheckList->insert(*NextTime, lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				NoteCheckList->insert(*NextTime, pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				NoteCheckList->insert(*NextTime, laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 160 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 250)
			{
				NoteCheckList->insert(*NextTime, prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -160 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -250)
			{
				NoteCheckList->insert(*NextTime, lagbad);
			}
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
	}
	else
	{
		qDebug() << "MOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)\n";
	}
}

void MCheckDot::aftercheck()
{
	if (((NoteList->value(*HoldPressed)->endTime()) - (Parent->time())) > 250)
	{
		NoteCheckList->remove(*HoldPressed);
		NoteCheckList->insert(*HoldPressed, miss);
	}
}

void MCheckDot::misscheck()
{
	if (NoteList->contains(*NextTime))
	{
		NoteCheckList->insert(*NextTime, miss);
		NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
	}
	else
	{
		qDebug() << "MOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)\n";
	}
}
