#include"MWidget.h"
#include"MNote.h"
#include"MCheckDot.h"

QColor* MNote::AutoNoteColor = new QColor(217, 150, 229, 255);
qint32* MNote::AutoNoteType = new qint32(click);
QColor* MNote::AutoLineColor = new QColor(217, 230, 229, 255);
QColor* MNote::AutoKeyColor = new QColor(217, 150, 229, 255);

MNote::MNote(MCheckDot* parent)
{
	Parent = parent;//存储parent
	Radium = new qreal(parent->radium() - 2);//初始化音符逻辑半径
	Width = new qreal(parent->width() - 2);//初始化音符视觉线宽
	VRadium = new qreal(*Radium * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符逻辑宽度
	VWidth = new qreal(*Width * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符的逻辑线宽
	Type = new qint32(*AutoNoteType);//初始化音符的类型
	NoteColor = new QColor(*AutoNoteColor);//初始化音符的颜色
	LineColor = new QColor(*AutoLineColor);
	KeyColor = new QColor(*AutoKeyColor);
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
	KeyColor = new QColor(note->keyColor());
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
	delete Visuable;
	Visuable = new bool(visuable);
}

bool MNote::visuable() const
{
	return *Visuable;
}

void MNote::setRadium(qreal r)
{
	delete Radium;
	Radium = new qreal(r);
	delete VRadium;
	VRadium = new qreal(*Radium * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}

qreal MNote::radium() const
{
	return *Radium;
}

qreal MNote::vRadium() const
{
	return *VRadium;
}

void MNote::setWidth(qreal width)
{
	delete Width;
	Width = new qreal(width);
	delete VWidth;
	VWidth = new qreal(*Width * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}

qreal MNote::width() const
{
	return *Width;
}

qreal MNote::vWidth() const
{
	return *VWidth;
}

void MNote::setNoteColor(QColor color)
{
	delete NoteColor;
	NoteColor = new QColor(color);
}

void MNote::setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete NoteColor;
	NoteColor = new QColor(R, G, B, A);
}

QColor MNote::noteColor() const
{
	return *NoteColor;
}

void MNote::setLineColor(QColor color)
{
	delete LineColor;
	LineColor = new QColor(color);
}

void MNote::setLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete LineColor;
	LineColor = new QColor(R, G, B, A);
}

QColor MNote::lineColor() const
{
	return *LineColor;
}

void MNote::setKeyColor(QColor color)
{
	delete KeyColor;
	KeyColor = new QColor(color);
}

void MNote::setKeyColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete KeyColor;
	KeyColor = new QColor(R, G, B, A);
}

QColor MNote::keyColor() const
{
	return *KeyColor;
}

void MNote::setType(qint32 type)
{
	delete Type;
	Type = new qint32(type);
}

void MNote::setBeatKey(qint32 key, QString keytext)
{
	delete BeatKey;
	BeatKey = new qint32(key);
	delete BeatKeyText;
	BeatKeyText = new QString(keytext);
}

qint32 MNote::beatKey() const
{
	return *BeatKey;
}

QString MNote::beatKeyText() const
{
	return *BeatKeyText;
}

qint32 MNote::type() const
{
	return *Type;
}

void MNote::setTime(qint64 time_ms)
{
	delete Time;
	Time = new qint64(time_ms);
	delete EndTime;
	EndTime = new qint64(*Time + *TimeLength);
	delete VTime;
	VTime = new qint64(*Time);
	delete VEndTime;
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::time() const
{
	return *Time;
}

void MNote::setTimeLength(qint64 time_ms)
{
	delete TimeLength;
	TimeLength = new qint64(time_ms);
	delete EndTime;
	EndTime = new qint64(*Time + *TimeLength);
	delete VTimeLength;
	VTimeLength = new qint64(*TimeLength);
	delete VEndTime;
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::timeLength() const
{
	return *TimeLength;
}

qint64 MNote::endTime() const
{
	return *EndTime;
}

void MNote::setVTime(qint64 time_ms)
{
	delete VTime;
	VTime = new qint64(time_ms);
}

qint64 MNote::vTime() const
{
	return *VTime;
}

void MNote::setVTimeLength(qint64 time_ms)
{
	delete VTimeLength;
	VTimeLength = new qint64(time_ms);
	delete VEndTime;
	VEndTime = new qint64(*VTime + *VTimeLength);
}

qint64 MNote::vTimeLength() const
{
	return *VTimeLength;
}

qint64 MNote::vEndTime() const
{
	return *VEndTime;
}

MCheckDot*& MNote::MParent()
{
	return Parent;
}

void MNote::setNextTime(qint64 time_ms)
{
	delete NextTime;
	NextTime = new qint64(time_ms);
}

qint64 MNote::nextTime() const
{
	return *NextTime;
}

void MNote::setSpeed(qreal speed)
{
	delete Speed;
	Speed = new qreal(speed);
	if (*Speed != -1)
	{
		delete VSpeed;
		VSpeed = new qreal((*Speed) * Parent->MParent()->visualProportion());
	}
}

qreal MNote::speed() const
{
	return *Speed;
}

qreal MNote::vSpeed() const
{
	return *VSpeed;
}

void MNote::setAutoNoteColor(QColor color)
{
	delete AutoNoteColor;
	AutoNoteColor = new QColor(color);
}

void MNote::setAutoNoteColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete AutoNoteColor;
	AutoNoteColor = new QColor(R, G, B, A);
}

QColor MNote::autoNoteColor()
{
	return *AutoNoteColor;
}

void MNote::setAutoNoteType(qint32 type)
{
	delete AutoNoteType;
	AutoNoteType = new qint32(type);
}

qint32 MNote::autoNoteType()
{
	return *AutoNoteType;
}

void MNote::setAutoLineColor(QColor color)
{
	delete AutoLineColor;
	AutoLineColor = new QColor(color);
}

void MNote::setAutoLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete AutoLineColor;
	AutoLineColor = new QColor(R, G, B, A);
}

QColor MNote::autoLineColor()
{
	return *AutoLineColor;
}

void MNote::setAutoKeyColor(QColor color)
{
	delete AutoKeyColor;
	AutoKeyColor = new QColor(color);
}

void MNote::setAutoKeyColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete AutoKeyColor;
	AutoKeyColor = new QColor(R, G, B, A);
}

QColor MNote::autoKeyColor()
{
	return *AutoKeyColor;
}