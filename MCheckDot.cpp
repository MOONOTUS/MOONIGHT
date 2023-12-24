#include"MCheckDot.h"
#include"MWidget.h"

MCheckDot::MCheckDot(MWidget *parent)
	: QPushButton(parent)
{
	this->Parent = parent;//存储parent
	Digonal = new qreal(qPow((qPow(WIDTH, 2) + qPow(HEIGHT, 2)), 0.5));
	DotColor = new QColor(217, 150, 229, 255);//初始化判定点颜色
	DotKeyColor = new QColor(DotColor->red(), DotColor->green(), DotColor->blue(), DotColor->alpha() * 2 / 3);//初始化判定键文本颜色
	Width = new qreal(10.0);//初始化判定点圆圈逻辑宽度
	Radium = new qreal(50.0);//初始化判定点逻辑半径
	Visuable = new bool(true);//初始化判定点可见性为真
	Point = new QPoint(WIDTH / 2, HEIGHT / 2);//初始化判定点逻辑坐标
	VPoint = new QPoint(Point->x() * Parent->visualProportion(), Point->y() * Parent->visualProportion());
	DotLine = new MCheckDotLine(this);//初始化轨道线
	NoteList = new QMap<qint64, MNote*>;//初始化音符容器
	NextTime = new qint64(0);//没用的初始化
	NoteCheckList = new QMap<qint64, qint32>;//初始化判定结果容器
	KeyVisuable = new bool(false);//初始化判定键文本可见性为假
	KeyPressingList = new QSet<qint32>;//初始化正在按键列表
	HoldPressing = new bool(false);//初始化hold按下状态为假
	HoldPressed = new qint64(0);//没用的初始化
	Speed = new qreal(500.0);//初始化音符逻辑速度
	VSpeed = new qreal(*Speed * Parent->visualProportion());//初始化音符视觉速度
	LineRadium = new qreal(*Digonal);//初始化轨道线逻辑长度
	VLineRadium = new qreal(*LineRadium * Parent->visualProportion());//初始化轨道线视觉长度
	NoteCheckAnimationList = new QMap<qint64, qint32>;
	this->setGeometry(0,0,parent->width(),parent->height());//设定初始绘制区域
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);//设定尺寸可变性
	this->setFont(QFont("Microsoft YaHei Ui", *Radium, *Width - 2));//设定文本字体

	parent->MParent()->connect//连接触发信号和判定槽
	(
		this,
		SIGNAL(touched()),
		this,
		SLOT(check()),
		Qt::DirectConnection
	);
	parent->MParent()->connect//连接hold音符专有的释放信号和hold专有的释放判定槽
	(
		this,
		SIGNAL(released()),
		this,
		SLOT(aftercheck()),
		Qt::DirectConnection
	);
	parent->MParent()->connect//连接掉落信号和掉落判定槽
	(
		this,
		SIGNAL(misschecked()),
		this,
		SLOT(misscheck()),
		Qt::DirectConnection
	);
	parent->MParent()->connect
	(
		parent,
		SIGNAL(keyPressDown(QKeyEvent*)),
		this,
		SLOT(press(QKeyEvent*)),
		Qt::DirectConnection
	);
	parent->MParent()->connect
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
	this->setGeometry(0, (Parent->height() - Parent->width() * 9 / 16) / 2, Parent->width(), Parent->width() * 9 / 16);//，以屏幕宽度为基准，设定16：9中央绘制区域，保证在不同尺寸的比例正常的设备上谱面的比例一样
	DotLine->setWidth(DotLine->width());//刷新轨道线的视觉宽度
	for (QMap<qint64, MNote*>::iterator listptr = NoteList->begin(); listptr != NoteList->end(); ++listptr)//刷新各个音符的视觉尺寸
	{
		listptr.value()->setRadium(listptr.value()->radium());
		listptr.value()->setWidth(listptr.value()->width());
	}
	VPoint = new QPoint(Point->x() * this->size().width() / Parent->oriSize().width(), Point->y() * this->size().height() / Parent->oriSize().height());//刷新视觉坐标
	VWidth = new qreal(*Width * Parent->visualProportion());//刷新视觉线宽
	VRadium = new qreal(*Radium * Parent->visualProportion());//刷新视觉半径
	VSpeed = new qreal(*Speed * Parent->visualProportion());//刷新视觉速度
	VLineRadium = new qreal(*LineRadium * Parent->visualProportion());//刷新轨道线视觉长度
	this->setFont(QFont("Microsoft YaHei Ui", *VRadium, *VWidth - 2));//刷新字体视觉样式
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);

	if (DotLine->visuable())//绘制轨道线
	{
		paintDotLine(paint);
	}
	if (*Visuable)//绘制判定点
	{
		paintDot(paint);
	}
	if (!NoteCheckAnimationList->isEmpty())
	{
		paintCheckAnimation(paint);
	}
	if (NoteList->contains(*NextTime) || *HoldPressing)//绘制音符
	{
		paintNote(paint);
		if (NoteList->contains(*NextTime) && NoteList->value(*NextTime)->time() - Parent->time() < -250)//掉落信号的发送
		{
			emit(misschecked());
		}
		if (NoteList->contains(*NextTime) && NoteList->value(*NextTime)->type() == cat)//对于cat音符，只要接近判定时保持触发状态即进行判定
		{
			if (Parent->keyPressingList()->contains(*Key) && NoteList->value(*NextTime)->time() - Parent->time() <= 50)
			{
				emit(touched());
			}
		}
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
	qDebug() << "\tMOONOTUSYSTEM_::_Data_::_*NextTime_::" << *NextTime;
	event->accept();
}

//void MCheckDot::keyPressEvent(QKeyEvent* event)
//{
//	if (!event->isAutoRepeat())
//	{
//		qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard Press";
//		KeyPressingList->insert(event->key());//向按键列表中添加按下的键
//		if (NoteList->contains(*NextTime))//触发信号的发送
//		{
//			if (NoteList->value(*NextTime)->time() - Parent->time() <= 250 && NoteList->value(*NextTime)->time() - Parent->time() >= -250)//只对时间差小于250ms的第一个音符进行判定
//			{
//				if (NoteList->value(*NextTime)->type() == click || NoteList->value(*NextTime)->type() == hold)//对于click音符和hold音符，只在触发开始时进行判定
//				{
//					if (event->key() == *Key)
//					{
//						emit(touched());
//					}
//				}
//				else if (NoteList->value(*NextTime)->type() == beat)//对于beat音符，只在保持触发的前提下beat音符的额外键触发开始时进行判定
//				{
//					if ((KeyPressingList->contains(*Key) && (event->key() == NoteList->value(*NextTime)->beatKey())))
//					{
//						emit(touched());
//					}
//				}
//				else if (NoteList->value(*NextTime)->type() == cat)//对于cat音符，只要接近判定时保持触发状态即进行判定
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
//		KeyPressingList->remove(event->key());//从按键列表中删除松开的键
//		if (*HoldPressing && !KeyPressingList->contains(*Key))//如果有hold正被按下且触发状态已经结束，则发送释放信号
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
	if (NoteList->contains(*NextTime))//触发信号的发送
	{
		if (NoteList->value(*NextTime)->time() - Parent->time() <= 160 && NoteList->value(*NextTime)->time() - Parent->time() >= -250)//只对处在判断区间的第一个音符进行判定
		{
			if (NoteList->value(*NextTime)->type() == click || NoteList->value(*NextTime)->type() == hold)//对于click音符和hold音符，只在触发开始时进行判定
			{
				if (event->key() == *Key)
				{
					emit(touched());
				}
			}
			else if (NoteList->value(*NextTime)->type() == beat)//对于beat音符，只在保持触发的前提下beat音符的额外键触发开始时进行判定
			{
				if ((Parent->keyPressingList()->contains(*Key) && (event->key() == NoteList->value(*NextTime)->beatKey())))
				{
					emit(touched());
				}
			}
			else if (NoteList->value(*NextTime)->type() == cat)//对于cat音符，只要接近判定时保持触发状态即进行判定
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
	qDebug() << "MOONOTUSYSTEM::_Message_::Keyboard release slot runs";
	if (*HoldPressing && !Parent->keyPressingList()->contains(*Key))//如果有hold正被按下且触发状态已经结束，则发送释放信号
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
	QPen pen;
	pen.setWidth(DotLine->vWidth());
	pen.setColor(DotLine->dotLineColor());
	paint->setPen(pen);
	if (DotLine->upVisuable())
	{
		line01.setP1(*VPoint);
		line01.setAngle(DotLine->upAngle());
		line01.setLength(*VRadium);
		lineU.setP1(line01.p2());
		lineU.setAngle(DotLine->upAngle());
		lineU.setLength(*VLineRadium);
		paint->drawLine(lineU);
	}
	if (DotLine->downVisuable())
	{
		line02.setP1(*VPoint);
		line02.setAngle(DotLine->downAngle());
		line02.setLength(*VRadium);
		lineD.setP1(line02.p2());
		lineD.setAngle(DotLine->downAngle());
		lineD.setLength(*VLineRadium);
		paint->drawLine(lineD);
	}
}

void MCheckDot::paintCheckAnimation(QPainter* paint)
{
	for (QMap<qint64, qint32>::iterator listptr = NoteCheckAnimationList->begin(); listptr != NoteCheckAnimationList->end();)
	{
		if (listptr.key() < (Parent->time() - 300))
		{
			NoteCheckAnimationList->erase(listptr++);
		}
		else
		{
			if (listptr.value() == miss)
			{
				QPen pen;
				pen.setColor(QColor(255, 25, 0, 60));//朱红
				pen.setWidth((100 + (listptr.key() - Parent->time()) / 3));
				paint->setPen(pen);
				paint->drawEllipse(*VPoint, qint32(*VRadium + (Parent->time() - listptr.key())) / 2, qint32(*VRadium + (Parent->time() - listptr.key())) / 2);
			}
			if (listptr.value() == strictperfect)
			{
				QPen pen;
				pen.setColor(QColor(255, 209, 86, 60));//夕霞
				pen.setWidth((100 + (listptr.key() - Parent->time()) / 3));
				paint->setPen(pen);
				paint->drawEllipse(*VPoint, qint32(*VRadium + (Parent->time() - listptr.key())) / 2, qint32(*VRadium + (Parent->time() - listptr.key())) / 2);
			}
			else if (listptr.value() == preperfect || listptr.value() == lagperfect)
			{
				QPen pen;
				pen.setColor(QColor(224, 212, 254, 60));//晚云
				pen.setWidth((100 + (listptr.key() - Parent->time()) / 3));
				paint->setPen(pen);
				paint->drawEllipse(*VPoint, qint32(*VRadium + (Parent->time() - listptr.key()) / 2), qint32(*VRadium + (Parent->time() - listptr.key())) / 2);
			}
			else if (listptr.value() == pregood || listptr.value() == laggood)
			{
				QPen pen;
				pen.setColor(QColor(255, 178, 162, 60));//海日
				pen.setWidth((100 + (listptr.key() - Parent->time()) / 3));
				paint->setPen(pen);
				paint->drawEllipse(*VPoint, qint32(*VRadium + (Parent->time() - listptr.key()) / 2), qint32(*VRadium + (Parent->time() - listptr.key())) / 2);
			}
			if (listptr.value() == prebad || listptr.value() == lagbad)
			{
				QPen pen;
				pen.setColor(QColor(86, 143, 168, 60));//沉沦
				pen.setWidth((100 + (listptr.key() - Parent->time()) / 3));
				paint->setPen(pen);
				paint->drawEllipse(*VPoint, qint32(*VRadium + (Parent->time() - listptr.key()) / 2), qint32(*VRadium + (Parent->time() - listptr.key())) / 2);
			}
			listptr++;
		}
	}
}

void MCheckDot::paintNote(QPainter* paint)//待实现的绘制音符的函数
{
	if (*NextTime == -1)
	{
		qDebug() << "\tMOONOTUSYSTEM::_Message_::NoteList ends";
	}
	else if (NoteList->contains(*NextTime))
	{
		qint64* NextTimeTemp = new qint64(*NextTime);
		while (*NextTime != -1 && (NoteList->contains(*NextTime)) && ((((NoteList->value(*NextTime)->time() - Parent->time()) * (*Speed)) / 1000) <= (*Digonal - (NoteList->value(*NextTime)->radium()))))
		{
			qDebug() << "\tMOONOTUS::_Message_::Note paints";
			NoteList->value(*NextTime)->setWidth(NoteList->value(*NextTime)->width());
			NoteList->value(*NextTime)->setRadium(NoteList->value(*NextTime)->radium());
			if (*HoldPressing && NoteList->value(*HoldPressed)->visuable())
			{
				paintHoldNote(paint);
			}
			if (NoteList->value(*NextTime)->visuable())
			{
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
			}
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		NextTime = new qint64(*NextTimeTemp);
		delete NextTimeTemp;
	}
	if (*HoldPressing)
	{
		if (NoteList->value(*HoldPressed)->vEndTime() < Parent->time())
		{
			HoldPressing = new bool(false);
			HoldPressed = new qint64(0);
		}
		else
		{
			paintHoldNote(paint);
		}
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
}

void MCheckDot::paintClickNote(QPainter* paint)//绘制click音符
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

void MCheckDot::paintCatNote(QPainter* paint)//绘制cat音符
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

void MCheckDot::paintBeatNote(QPainter* paint)//绘制beat音符
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

void MCheckDot::paintHoldNote(QPainter* paint_)//绘制hold音符
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
	if(*HoldPressing)
	{
		qDebug() << "\tMOONOTUSYSTEM::_Message_::Hold note which is pressed paints";
		NoteCheckAnimationList->insert(Parent->time(),strictperfect);
		NoteList->value(*HoldPressed)->setVTime(Parent->time());
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
	VSpeed = new qreal(*Speed * Parent->visualProportion());
}

qreal MCheckDot::speed()
{
	return *Speed;
}

void MCheckDot::setLineRadium(qreal lineradium)
{
	LineRadium = new qreal(lineradium);
	VLineRadium = new qreal(*LineRadium * Parent->visualProportion());
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
		if (NoteList->value(*NextTime)->type() == cat)//针对cat音符的判定
		{
			qDebug() << "\tMOONOTUSYSTEM::_Message_::Perfect check of cat";
			NoteCheckAnimationList->insert(Parent->time(),strictperfect);
			NoteCheckList->insert(*NextTime, strictperfect);
			Parent->addCheck(strictperfect);
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		else if (NoteList->value(*NextTime)->type() == hold)//针对hold音符的判定
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::StrictPerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),strictperfect);
				NoteCheckList->insert(*NextTime, strictperfect);
				Parent->addCheck(strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PrePerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),preperfect);
				NoteCheckList->insert(*NextTime, preperfect);
				Parent->addCheck(preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagPerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),lagperfect);
				NoteCheckList->insert(*NextTime, lagperfect);
				Parent->addCheck(lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreGood checks";
				NoteCheckAnimationList->insert(Parent->time(),pregood);
				NoteCheckList->insert(*NextTime, pregood);
				Parent->addCheck(pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagGood checks";
				NoteCheckAnimationList->insert(Parent->time(),laggood);
				NoteCheckList->insert(*NextTime, laggood);
				Parent->addCheck(laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreBad checks";
				NoteCheckAnimationList->insert(Parent->time(),prebad);
				NoteCheckList->insert(*NextTime, prebad);
				Parent->addCheck(prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagBad checks";
				NoteCheckAnimationList->insert(Parent->time(),lagbad);
				NoteCheckList->insert(*NextTime, lagbad);
				Parent->addCheck(lagbad);
			}
			HoldPressing = new bool(true);
			HoldPressed = new qint64(*NextTime);
			NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
		}
		else//针对click和beat音符的判定
		{
			if (((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 50)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::StrictPerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),strictperfect);
				NoteCheckList->insert(*NextTime, strictperfect);
				Parent->addCheck(strictperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PrePerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),preperfect);
				NoteCheckList->insert(*NextTime, preperfect);
				Parent->addCheck(preperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -50 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -80)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagPerfect checks";
				NoteCheckAnimationList->insert(Parent->time(),lagperfect);
				NoteCheckList->insert(*NextTime, lagperfect);
				Parent->addCheck(lagperfect);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreGood checks";
				NoteCheckAnimationList->insert(Parent->time(),pregood);
				NoteCheckList->insert(*NextTime, pregood);
				Parent->addCheck(pregood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -80 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -120)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagGood checks";
				NoteCheckAnimationList->insert(Parent->time(),laggood);
				NoteCheckList->insert(*NextTime, laggood);
				Parent->addCheck(laggood);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) > 120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) <= 160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::PreBad checks";
				NoteCheckAnimationList->insert(Parent->time(),prebad);
				NoteCheckList->insert(*NextTime, prebad);
				Parent->addCheck(prebad);
			}
			else if (((NoteList->value(*NextTime)->time()) - (Parent->time())) < -120 && ((NoteList->value(*NextTime)->time()) - (Parent->time())) >= -160)
			{
				qDebug() << "\tMOONOTUSYSTEM::_Message_::LagBad checks";
				NoteCheckAnimationList->insert(Parent->time(),lagbad);
				NoteCheckList->insert(*NextTime, lagbad);
				Parent->addCheck(lagbad);
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
	if (((NoteList->value(*HoldPressed)->endTime()) - (Parent->time())) > 160)//hold音符的释放判定
	{
		qDebug()<<"\tMOONOTUSYSTEM::_Message_::Miss check of hold's after";
		NoteCheckAnimationList->insert(Parent->time(), miss);
		NoteCheckList->remove(*HoldPressed);
		NoteCheckList->insert(*HoldPressed, miss);
		Parent->addCheck(miss);
		HoldPressing = new bool(false);
		HoldPressed = new qint64(0);
	}
}

void MCheckDot::misscheck()
{
	qDebug() << "\tMOONOTUSYSTEM::_Message_::Miss check start";
	if (NoteList->contains(*NextTime))//掉落判定
	{
		qDebug() << "\tMOONOTUSYSTEM::_Message_::Miss checks";
		NoteCheckAnimationList->insert(Parent->time(), miss);
		NoteCheckList->insert(*NextTime, miss);
		Parent->addCheck(miss);
		NextTime = new qint64(NoteList->value(*NextTime)->nextTime());
	}
	else
	{
		qDebug() << "\tMOONOTUSYSTEM::_Error_::Do not exist that NoteList->value(*NextTime)";
	}
}

void MCheckDot::addNote(qint64 time, qint64 nexttime, qint32 type, qint64 timelength, qint32 beatkey, QString beatkeytext)//提供给谱面编辑师用于快速快速添加新音符
{
	MNote* newNote = new MNote(this);
	newNote->setTime(time);
	newNote->setNextTime(nexttime);
	newNote->setType(type);
	newNote->setTimeLength(timelength);
	newNote->setBeatKey(beatkey, beatkeytext);
	NoteList->insert(time, newNote);
}

void MCheckDot::addNote(QColor notecolor, qint64 time, qint64 nexttime, qint32 type, qint64 timelength, qint32 beatkey, QString beatkeytext)//提供给谱面编辑师用于快速快速添加新音符
{
	MNote* newNote = new MNote(this);
	newNote->setTime(time);
	newNote->setNextTime(nexttime);
	newNote->setType(type);
	newNote->setTimeLength(timelength);
	newNote->setBeatKey(beatkey, beatkeytext);
	newNote->setNoteColor(notecolor);
	NoteList->insert(time, newNote);
}

void MCheckDot::addNote(QColor notecolor, QColor linecolor, qint64 time, qint64 nexttime, qint32 type, qint64 timelength, qint32 beatkey, QString beatkeytext)//提供给谱面编辑师用于快速快速添加新音符
{
	MNote* newNote = new MNote(this);
	newNote->setTime(time);
	newNote->setNextTime(nexttime);
	newNote->setType(type);
	newNote->setTimeLength(timelength);
	newNote->setBeatKey(beatkey, beatkeytext);
	newNote->setNoteColor(notecolor);
	newNote->setLineColor(linecolor);
	NoteList->insert(time, newNote);
}
