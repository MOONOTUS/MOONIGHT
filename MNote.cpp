#include"MWidget.h"
#include"MNote.h"
#include"MCheckDot.h"

MNote::MNote(MCheckDot* parent)
{
	Parent = parent;//存储parent
	Radium = new qreal(parent->radium() - 2);//初始化音符逻辑半径
	Width = new qreal(parent->width() - 2);//初始化音符视觉线宽
	VRadium = new qreal(*Radium * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符逻辑宽度
	VWidth = new qreal(*Width * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符的逻辑线宽
	Type = new qint32(click);//初始化音符的类型为click
	NoteColor = new QColor(parent->dotColor());//初始化音符的颜色
	LineColor = new QColor(NoteColor->red(), NoteColor->green() + 80, NoteColor->blue(), NoteColor->alpha());
	Visuable = new bool(parent->visuable());//初始化音符的可见性
	BeatKey = new qint32(Qt::Key_Escape);//初始化beat音符专有的额外键
	BeatKeyText = new QString("0");//初始化beat音符专有的额外键文本
	Time = new qint64(0);//初始化音符的判定时间
	TimeLength = new qint64(0);//初始化hold音符专有的持续时长
	EndTime = new qint64(*Time + *TimeLength);//初始化hold音符专有的结束时间
	VTime = new qint64(*Time);
	VTimeLength = new qint64(*TimeLength);
	VEndTime = new qint64(*VTime + *VTimeLength);
	NextTime = new qint64(0);
	Speed = new qreal(-1);
	VSpeed = new qreal(-1);
}

MNote::MNote(MNote* note)
{
	Parent = note->MParent();
	Visuable = new bool(note->visuable());
	Radium = new qreal(note->radium());
	VRadium = new qreal(note->vRadium());
	Width = new qreal(note->width());
	VWidth = new qreal(note->vWidth());
	NoteColor = new QColor(note->noteColor());
	LineColor = new QColor(note->lineColor());
	Type = new qint32(note->type());
	BeatKey = new qint32(note->beatKey());
	BeatKeyText = new QString(note->beatKeyText());
	Time = new qint64(note->time());
	TimeLength = new qint64(note->timeLength());
	EndTime = new qint64(note->endTime());
	VTime = new qint64(note->vTime());
	VTimeLength = new qint64(note->vTimeLength());
	VEndTime = new qint64(note->vEndTime());
	NextTime = new qint64(note->nextTime());
	Speed = new qreal(note->speed());
	VSpeed = new qreal(note->vSpeed());
}

MNote::~MNote()
{
	delete Visuable;
	delete Radium;
	delete VRadium;
	delete Width;
	delete VWidth;
	delete NoteColor;
	delete LineColor;
	delete Type;
	delete BeatKey;
	delete BeatKeyText;
	delete Time;
	delete TimeLength;
	delete EndTime;
	delete NextTime;
}

void MNote::MNoteSet(bool visuable, qreal radium, qreal width, QColor color, qint32 type, qint64 time, qint64 nextTime, qint32 beatKey, QString beatKeyText, qint64 timeLength, qreal speed)
{
	setVisuable(visuable);
	if (!(radium == -1))
	{
		setRadium(radium);
	}
	if (!(width == -1))
	{
		setWidth(width);
	}
	if (!(color == Qt::transparent))
	{
		setNoteColor(color);
	}
	if (!(type == -1))
	{
		setType(type);
	}
	if (!(time == -1))
	{
		setTime(time);
	}
	if (!(nextTime == -1))
	{
		setNextTime(time);
	}
	if (!((beatKey == -1) || (beatKeyText == "")))
	{
		setBeatKey(beatKey, beatKeyText);
	}
	if (!(timeLength == -1))
	{
		setTimeLength(timeLength);
	}
	if (!(speed == -1))
	{
		setSpeed(speed);
	}
}

void MNote::setVisuable(bool visuable)
{
	Visuable = new bool(visuable);
}

bool MNote::visuable()
{
	return *Visuable;
}

void MNote::setRadium(qreal r)
{
	Radium = new qreal(r);
	VRadium = new qreal(*Radium * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}

qreal MNote::radium()
{
	return *Radium;
}

qreal MNote::vRadium()
{
	return *VRadium;
}

void MNote::setWidth(qreal width)
{
	Width = new qreal(width);
	VWidth = new qreal(*Width * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}

qreal MNote::width()
{
	return *Width;
}

qreal MNote::vWidth()
{
	return *VWidth;
}

void MNote::setNoteColor(QColor color)
{
	NoteColor = new QColor(color);
}

void MNote::setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	NoteColor = new QColor(R, G, B, A);
}

QColor MNote::noteColor()
{
	return *NoteColor;
}

void MNote::setLineColor(QColor color)
{
	LineColor = new QColor(color);
}

void MNote::setLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	LineColor = new QColor(R, G, B, A);
}

QColor MNote::lineColor()
{
	return *LineColor;
}

void MNote::setType(qint32 type)
{
	Type = new qint32(type);
}

void MNote::setBeatKey(qint32 key, QString keytext)
{
	BeatKey = new qint32(key);
	BeatKeyText = new QString(keytext);
}

qint32 MNote::beatKey()
{
	return *BeatKey;
}

QString MNote::beatKeyText()
{
	return *BeatKeyText;
}

qint32 MNote::type()
{
	return *Type;
}

void MNote::setTime(qint64 time_ms)
{
	Time = new qint64(time_ms);
	EndTime = new qint64(*Time + *TimeLength);
	VTime = new qint64(*Time);
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::time()
{
	return *Time;
}

void MNote::setTimeLength(qint64 time_ms)
{
	TimeLength = new qint64(time_ms);
	EndTime = new qint64(*Time + *TimeLength);
	VTimeLength = new qint64(*TimeLength);
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::timeLength()
{
	return *TimeLength;
}

qint64 MNote::endTime()
{
	return *EndTime;
}

void MNote::setVTime(qint64 time_ms)
{
	VTime = new qint64(time_ms);
}

qint64 MNote::vTime()
{
	return *VTime;
}

void MNote::setVTimeLength(qint64 time_ms)
{
	VTimeLength = new qint64(time_ms);
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::vTimeLength()
{
	return *VTimeLength;
}

qint64 MNote::vEndTime()
{
	return *VEndTime;
}

MCheckDot*& MNote::MParent()
{
	return Parent;
}

void MNote::setNextTime(qint64 time_ms)
{
	NextTime = new qint64(time_ms);
}

qint64 MNote::nextTime()
{
	return *NextTime;
}

void MNote::setSpeed(qreal speed)
{
	Speed = new qreal(speed);
	if (*Speed != -1)
	{
		VSpeed = new qreal((*Speed) * Parent->MParent()->visualProportion());
	}
}

qreal MNote::speed()
{
	return *Speed;
}

qreal MNote::vSpeed()
{
	return *VSpeed;
}