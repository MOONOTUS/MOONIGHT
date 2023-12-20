#include"MCheckDot.h"
#include"MWidget.h"

MCheckDot::MCheckDot(MWidget *parent)
	: QPushButton(parent)
{
	this->Parent = parent;//�洢parent
	DotColor = new QColor(217, 150, 229, 255);//��ʼ���ж�����ɫ
	DotKeyColor = new QColor(DotColor->red(), DotColor->green(), DotColor->blue(), DotColor->alpha() * 2 / 3);//��ʼ���ж����ı���ɫ
	Width = new qreal(6.0);//��ʼ���ж���ԲȦ�߼����
	Radium = new qreal(30.0);//��ʼ���ж����߼��뾶
	Visuable = new bool(true);//��ʼ���ж���ɼ���Ϊ��
	Point = new QPoint(parent->width() / 2, parent->height() / 2);//��ʼ���ж����߼�����
	DotLine = new MCheckDotLine(this);//��ʼ�������
	NoteList = new QMap<qint64, MNote*>;//��ʼ����������
	NextTime = new qint64(0);//û�õĳ�ʼ��
	NoteCheckList = new QMap<qint64, qint32>;//��ʼ���ж��������
	KeyVisuable = new bool(false);//��ʼ���ж����ı��ɼ���Ϊ��
	KeyPressingList = new QSet<qint32>;//��ʼ�����ڰ����б�
	HoldPressing = new bool(false);//��ʼ��hold����״̬Ϊ��
	HoldPressed = new qint64(0);//û�õĳ�ʼ��
	Speed = new qreal(100.0);//��ʼ�������߼��ٶ�
	VSpeed = new qreal(*Speed * parent->width() / parent->oriSize().width());//��ʼ�������Ӿ��ٶ�
	LineRadium = new qreal(2500.0);//��ʼ��������߼�����
	VLineRadium = new qreal(*LineRadium * parent->width() / parent->oriSize().width());//��ʼ��������Ӿ�����
	this->setGeometry(0,0,parent->width(),parent->height());//�趨��ʼ��������
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);//�趨�ߴ�ɱ���
	this->setFont(QFont("Microsoft YaHei Ui", *Radium, *Width - 2));//�趨�ı�����

	parent->MParent()->connect//���Ӵ����źź��ж���
	(
		this,
		SIGNAL(touched()),
		this,
		SLOT(check()),
		Qt::DirectConnection
	);
	parent->MParent()->connect//����hold����ר�е��ͷ��źź�holdר�е��ͷ��ж���
	(
		this,
		SIGNAL(released()),
		this,
		SLOT(aftercheck()),
		Qt::DirectConnection
	);
	parent->MParent()->connect//���ӵ����źź͵����ж���
	(
		this,
		SIGNAL(misschecked()),
		this,
		SLOT(misscheck()),
		Qt::DirectConnection
	);
	connect
	(
		parent,
		SIGNAL(keyPressDown(QKeyEvent*)),
		this,
		SLOT(press(QKeyEvent*)),
		Qt::DirectConnection
	);
	connect
	(
		parent,
		SIGNAL(keyReleaseUp(QKeyEvent*)),
		this,
		SLOT(release(QKeyEvent*)),
		Qt::DirectConnection
	);
}

MCheckDot::~MCheckDot()
{
	delete DotLine;
	delete NoteList;
	delete NextTime;
	delete NoteCheckList;
	delete Visuable;
	delete Point;
	delete Radium;
	delete Width;
	delete DotColor;
	delete DotKeyColor;
	delete Key;
	delete KeyText;
	delete KeyVisuable;
	delete VPoint;
	delete VRadium;
	delete VWidth;
	delete KeyPressingList;
	delete HoldPressing;
	delete HoldPressed;
	delete Speed;
	delete VSpeed;
	delete LineRadium;
	delete VLineRadium;
}



void MCheckDot::paintEvent(QPaintEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Message_::MCheckDot " << *KeyText << " paints";
	this->setGeometry(0, (Parent->height() - Parent->width() * 9 / 16) / 2, Parent->width(), Parent->width() * 9 / 16);//������Ļ���Ϊ��׼���趨16��9����������򣬱�֤�ڲ�ͬ�ߴ�ı����������豸������ı���һ��
	DotLine->setWidth(DotLine->width());//ˢ�¹���ߵ��Ӿ����
	for (QMap<qint64, MNote*>::iterator listptr = NoteList->begin(); listptr != NoteList->end(); ++listptr)//ˢ�¸����������Ӿ��ߴ�
	{
		listptr.value()->setRadium(listptr.value()->radium());
		listptr.value()->setWidth(listptr.value()->width());
	}
	VPoint = new QPoint(Point->x() * this->size().width() / Parent->oriSize().width(), Point->y() * this->size().height() / Parent->oriSize().height());//ˢ���Ӿ�����
	VWidth = new qreal(*Width * Parent->width() / Parent->oriSize().width());//ˢ���Ӿ��߿�
	VRadium = new qreal(*Radium * Parent->width() / Parent->oriSize().width());//ˢ���Ӿ��뾶
	VSpeed = new qreal(*Speed * Parent->width() / Parent->oriSize().width());//ˢ���Ӿ��ٶ�
	VLineRadium = new qreal(*LineRadium * Parent->width() / Parent->oriSize().width());//ˢ�¹�����Ӿ�����
	this->setFont(QFont("Microsoft YaHei Ui", *VRadium, *VWidth - 2));//ˢ�������Ӿ���ʽ
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);

	if (DotLine->visuable())//���ƹ����
	{
		paintDotLine(paint);
	}
	if (*Visuable)//�����ж���
	{
		paintDot(paint);
	}
	if (NoteList->contains(*NextTime) || *HoldPressing)//��������
	{
		paintNote(paint);
		if (NoteList->contains(*NextTime) && NoteList->value(*NextTime)->time() - Parent->time() < -250)//�����źŵķ���
		{
			emit(misschecked());
		}
		if (NoteList->contains(*NextTime) && NoteList->value(*NextTime)->type() == cat)//����cat������ֻҪ�ӽ��ж�ʱ���ִ���״̬�������ж�
		{
			if (Parent->keyPressingList()->contains(*Key) && NoteList->value(*NextTime)->time() - Parent->time() <= 50)
			{
				emit(touched());
			}
		}
	}
	qDebug() << "\tMOONOTUSYSTEM_::_Data_::_*NextTime_::" << *NextTime;
	event->accept();
}

//void MCheckDot::keyPressEvent(QKeyEvent* event)
//{
//	if (!event->isAutoRepeat())
//	{
//		qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard Press";
//		KeyPressingList->insert(event->key());//�򰴼��б�����Ӱ��µļ�
//		if (NoteList->contains(*NextTime))//�����źŵķ���
//		{
//			if (NoteList->value(*NextTime)->time() - Parent->time() <= 250 && NoteList->value(*NextTime)->time() - Parent->time() >= -250)//ֻ��ʱ���С��250ms�ĵ�һ�����������ж�
//			{
//				if (NoteList->value(*NextTime)->type() == click || NoteList->value(*NextTime)->type() == hold)//����click������hold������ֻ�ڴ�����ʼʱ�����ж�
//				{
//					if (event->key() == *Key)
//					{
//						emit(touched());
//					}
//				}
//				else if (NoteList->value(*NextTime)->type() == beat)//����beat������ֻ�ڱ��ִ�����ǰ����beat�����Ķ����������ʼʱ�����ж�
//				{
//					if ((KeyPressingList->contains(*Key) && (event->key() == NoteList->value(*NextTime)->beatKey())))
//					{
//						emit(touched());
//					}
//				}
//				else if (NoteList->value(*NextTime)->type() == cat)//����cat������ֻҪ�ӽ��ж�ʱ���ִ���״̬�������ж�
//				{
//					if (KeyPressingList->contains(*Key) && NoteList->value(*NextTime)->time() - Parent->time() <= 50)
//					{
//						emit(touched());
//					}
//				}
//			}
//		}
//		else
//		{
//			qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
//		}
//
//	}
//	releaseKeyboard();
//	event->accept();
//}
//
//void MCheckDot::keyReleaseEvent(QKeyEvent* event)
//{
//	if (!event->isAutoRepeat())
//	{
//		qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard Release";
//		KeyPressingList->remove(event->key());//�Ӱ����б���ɾ���ɿ��ļ�
//		if (*HoldPressing && !KeyPressingList->contains(*Key))//�����hold���������Ҵ���״̬�Ѿ������������ͷ��ź�
//		{
//			emit(released());
//		}
//
//	}
//	releaseKeyboard();
//	event->accept();
//}


void MCheckDot::press(QKeyEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard press slot runs";
	if (NoteList->contains(*NextTime))//�����źŵķ���
	{
		if (NoteList->value(*NextTime)->time() - Parent->time() <= 250 && NoteList->value(*NextTime)->time() - Parent->time() >= -250)//ֻ��ʱ���С��250ms�ĵ�һ�����������ж�
		{
			if (NoteList->value(*NextTime)->type() == click || NoteList->value(*NextTime)->type() == hold)//����click������hold������ֻ�ڴ�����ʼʱ�����ж�
			{
				if (event->key() == *Key)
				{
					emit(touched());
				}
			}
			else if (NoteList->value(*NextTime)->type() == beat)//����beat������ֻ�ڱ��ִ�����ǰ����beat�����Ķ����������ʼʱ�����ж�
			{
				if ((Parent->keyPressingList()->contains(*Key) && (event->key() == NoteList->value(*NextTime)->beatKey())))
				{
					emit(touched());
				}
			}
			else if (NoteList->value(*NextTime)->type() == cat)//����cat������ֻҪ�ӽ��ж�ʱ���ִ���״̬�������ж�
			{
				if (Parent->keyPressingList()->contains(*Key) && NoteList->value(*NextTime)->time() - Parent->time() <= 50)
				{
					emit(touched());
				}
			}
		}
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
}

void MCheckDot::release(QKeyEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard Release";
	if (*HoldPressing && !Parent->keyPressingList()->contains(*Key))//�����hold���������Ҵ���״̬�Ѿ������������ͷ��ź�
	{
		emit(released());
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
	line01.setAngle(DotLine->angle());
	line02.setAngle((DotLine->angle() - 180));
	line01.setLength(*VRadium);
	line02.setLength(*VRadium);
	//ʹ�ù���ߵ�������ж���ԲȦ��
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

void MCheckDot::paintNote(QPainter* paint)//��ʵ�ֵĻ��������ĺ���
{
	if (*NextTime == -1)
	{
		qDebug() << "\tMOONOTUSYSTEM::_Message_::NoteList ends";
	}
	if (NoteList->contains(*NextTime))
	{
		qint64* NextTimeTemp = new qint64(*NextTime);
		while ( *NextTime != -1 && (((NoteList->contains(*NextTime) && (NoteList->value(*NextTime)->time()) * (*Speed)) / 1000) <= (2203 - (NoteList->value(*NextTime)->radium()))))
		{
			qDebug() << "\tMOONOTUS::_Message_::Note paints";
			NoteList->value(*NextTime)->setWidth(NoteList->value(*NextTime)->width());
			NoteList->value(*NextTime)->setRadium(NoteList->value(*NextTime)->radium());
			switch (NoteList->value(*NextTime)->type())
			{
			case click:
				paintClickNote(paint);
				break;
			case cat:
				paintCatNote(paint);
				break;
			case beat:
				paintBeatNote(paint);
				break;
			case hold:
				paintHoldNote(paint);
				break;
			default:
				qDebug() << "\tMOONOTUSYSTEM::_Error_::Unidentified type of note to be painted";
			}
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		NextTime = new qint64(*NextTimeTemp);
		delete NextTimeTemp;
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
	if (*HoldPressing)
	{
		if (NoteList->value(*HoldPressed)->endTime() < Parent->time())
		{
			HoldPressing = new bool(false);
			HoldPressed = new qint64(0);
		}
		else
		{
			paintHoldNote(paint);
		}
	}
}

void MCheckDot::paintClickNote(QPainter* paint)//����click����
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Click note paints";
	QLineF line0;
	line0.setP1(*VPoint);
	line0.setAngle(DotLine->angle());
	line0.setLength((NoteList->value(*NextTime)->vTime()-Parent->time())*(*VSpeed)/1000);
	QPen pen;
	pen.setWidth(NoteList->value(*NextTime)->vWidth());
	pen.setColor(NoteList->value(*NextTime)->lineColor());
	paint->setPen(pen);
	paint->setBrush(NoteList->value(*NextTime)->noteColor());
	paint->drawEllipse(line0.p2(), qint32(NoteList->value(*NextTime)->vRadium()), qint32(NoteList->value(*NextTime)->vRadium()));
}

void MCheckDot::paintCatNote(QPainter* paint)//����cat����
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Cat note paints";
	QLineF line0;
	line0.setP1(*VPoint);
	line0.setAngle(DotLine->angle());
	line0.setLength((NoteList->value(*NextTime)->vTime() - Parent->time()) * (*VSpeed) / 1000);
	QPen pen;
	pen.setWidth(NoteList->value(*NextTime)->vWidth());
	pen.setColor(NoteList->value(*NextTime)->lineColor());
	paint->setBrush(Qt::transparent);
	paint->setPen(pen);
	paint->drawEllipse(line0.p2(), qint32(NoteList->value(*NextTime)->vRadium()), qint32(NoteList->value(*NextTime)->vRadium()));
}

void MCheckDot::paintBeatNote(QPainter* paint)//����beat����
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Beat note paints";
	QLineF line0;
	line0.setP1(*VPoint);
	line0.setAngle(DotLine->angle());
	line0.setLength((NoteList->value(*NextTime)->vTime() - Parent->time()) * (*VSpeed) / 1000);
	QPen pen;
	pen.setWidth(NoteList->value(*NextTime)->vWidth());
	pen.setColor(NoteList->value(*NextTime)->lineColor());
	paint->setPen(pen);
	paint->setBrush(NoteList->value(*NextTime)->noteColor());
	paint->drawEllipse(line0.p2(), qint32(NoteList->value(*NextTime)->vRadium()), qint32(NoteList->value(*NextTime)->vRadium()));
	paint->setFont(font());
	paint->drawText(QRect(line0.p2().x() - QFontMetricsF(font()).maxWidth() * NoteList->value(*NextTime)->beatKeyText().size() / 2, line0.p2().y() - QFontMetricsF(font()).height() / 2, QFontMetricsF(font()).maxWidth() * NoteList->value(*NextTime)->beatKeyText().size(), QFontMetricsF(font()).height()), Qt::AlignHCenter | Qt::AlignVCenter, NoteList->value(*NextTime)->beatKeyText());
}

void MCheckDot::paintHoldNote(QPainter* paint_)//����hold����
{
	if (NoteList->contains(*NextTime))
	{
		if (NoteList->value(*NextTime)->type() == hold)
		{
			qDebug() << "\tMOONOTUSYSTEM::_Message_::Hold note paints";
			QPainter* paint = new QPainter(this);
			QLineF line01, line02, line03;
			line01.setP1(*VPoint);
			line01.setAngle(DotLine->angle());
			line01.setLength((NoteList->value(*NextTime)->vTime() - Parent->time()) * (*VSpeed) / 1000);
			line02.setP1(*VPoint);
			line02.setAngle(DotLine->angle());
			line02.setLength((NoteList->value(*NextTime)->vEndTime() - Parent->time()) * (*VSpeed) / 1000);
			QPen pen;
			pen.setWidth(NoteList->value(*NextTime)->vWidth());
			pen.setColor(NoteList->value(*NextTime)->lineColor());
			paint->setPen(pen);
			paint->setBrush(NoteList->value(*NextTime)->noteColor());
			paint->drawEllipse(line01.p2(), qint32(NoteList->value(*NextTime)->vRadium()), qint32(NoteList->value(*NextTime)->vRadium()));
			pen.setColor(Qt::transparent);
			paint->setPen(pen);
			paint->drawEllipse(line02.p2(), qint32(NoteList->value(*NextTime)->vRadium()), qint32(NoteList->value(*NextTime)->vRadium()));
			line03.setP1(line02.p2());
			line03.setLength(NoteList->value(*NextTime)->vRadium());
			line03.setAngle(DotLine->angle() + 90);
			pen.setColor(Qt::transparent);
			paint->setPen(pen);
			paint->translate(line03.p2());
			paint->rotate(90 - DotLine->angle());
			paint->drawRect(QRect(0, 0, NoteList->value(*NextTime)->vRadium() * 2, (NoteList->value(*NextTime)->vEndTime() - NoteList->value(*NextTime)->vTime()) * (*VSpeed) / 1000));
			delete paint;
		}

	}
	else if(*HoldPressing)
	{
		NoteList->value(*HoldPressed)->setVTime(Parent->time());
		qDebug() << "\tMOONOTUSYSTEM::_Message_::Hold note which is pressed paints";
		QPainter* paint = new QPainter(this);
		QLineF line01, line02, line03;
		line01.setP1(*VPoint);
		line01.setAngle(DotLine->angle());
		line01.setLength((NoteList->value(*HoldPressed)->vTime() - Parent->time()) * (*VSpeed) / 1000);
		line02.setP1(*VPoint);
		line02.setAngle(DotLine->angle());
		line02.setLength((NoteList->value(*HoldPressed)->vEndTime() - Parent->time()) * (*VSpeed) / 1000);
		QPen pen;
		pen.setWidth(NoteList->value(*HoldPressed)->vWidth());
		pen.setColor(NoteList->value(*HoldPressed)->lineColor());
		paint->setPen(pen);
		paint->setBrush(NoteList->value(*HoldPressed)->noteColor());
		paint->drawEllipse(line01.p2(), qint32(NoteList->value(*HoldPressed)->vRadium()), qint32(NoteList->value(*HoldPressed)->vRadium()));
		pen.setColor(Qt::transparent);
		paint->setPen(pen);
		paint->drawEllipse(line02.p2(), qint32(NoteList->value(*HoldPressed)->vRadium()), qint32(NoteList->value(*HoldPressed)->vRadium()));
		line03.setP1(line02.p2());
		line03.setLength(NoteList->value(*HoldPressed)->vRadium());
		line03.setAngle(DotLine->angle() + 90);
		pen.setColor(Qt::transparent);
		paint->setPen(pen);
		paint->translate(line03.p2());
		paint->rotate(90 - DotLine->angle());
		paint->drawRect(QRect(0, 0, NoteList->value(*HoldPressed)->vRadium() * 2, (NoteList->value(*HoldPressed)->vEndTime() - NoteList->value(*HoldPressed)->vTime()) * (*VSpeed) / 1000));
		delete paint;
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

void MCheckDot::setSpeed(qreal speed_px_ps)
{
	Speed = new qreal(speed_px_ps);
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
	qDebug() << "\tMOONOTUSYSTEM::_MESSAGE_::Check";
	if (NoteList->contains(*NextTime))
	{
		qDebug() << "\tMOONOTUSYSTEM::_MESSAGE_::Truely check";
		if (NoteList->value(*NextTime)->type() == cat)//���cat�������ж�
		{
			qDebug() << "\tMOONOTUSYSTEM::_Message_::Perfect check of cat";
			NoteCheckList->insert(*NextTime, strictperfect);
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		else if (NoteList->value(*NextTime)->type() == hold)//���hold�������ж�
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::StrictPerfect check";
				NoteCheckList->insert(*NextTime, strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PrePerfect check";
				NoteCheckList->insert(*NextTime, preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagPerfect check";
				NoteCheckList->insert(*NextTime, lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreGood check";
				NoteCheckList->insert(*NextTime, pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagGood check";
				NoteCheckList->insert(*NextTime, laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreBad check";
				NoteCheckList->insert(*NextTime, prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagBad check";
				NoteCheckList->insert(*NextTime, lagbad);
			}
			HoldPressing = new bool(true);
			HoldPressed = new qint64(*NextTime);
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		else//���click��beat�������ж�
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::StrictPerfect check";
				NoteCheckList->insert(*NextTime, strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PrePerfect check";
				NoteCheckList->insert(*NextTime, preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagPerfect check";
				NoteCheckList->insert(*NextTime, lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreGood check";
				NoteCheckList->insert(*NextTime, pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagGood check";
				NoteCheckList->insert(*NextTime, laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreBad check";
				NoteCheckList->insert(*NextTime, prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagBad check";
				NoteCheckList->insert(*NextTime, lagbad);
			}
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
}

void MCheckDot::aftercheck()
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Check of hold's after";
	if (((NoteList->value(*HoldPressed)->endTime()) - (Parent->time())) > 250)//hold�������ͷ��ж�
	{
		qDebug()<<"\tMOONOTUSYSTEM::_Message_::Miss check of hold's after";
		NoteCheckList->remove(*HoldPressed);
		NoteCheckList->insert(*HoldPressed, miss);
		HoldPressing = new bool(false);
		HoldPressed = new qint64(0);
	}
}

void MCheckDot::misscheck()
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Miss check start";
	if (NoteList->contains(*NextTime))//�����ж�
	{
		qDebug() << "\tMOONOTUSYSTEM::_Message_::Truely miss";
		NoteCheckList->insert(*NextTime, miss);
		NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
}
