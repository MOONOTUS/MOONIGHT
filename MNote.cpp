#include"MWidget.h"
#include"MNote.h"
#include"MCheckDot.h"

MNote::MNote(MCheckDot* parent)
{
	Parent = parent;//存储parent
	Radium = new qreal(parent->radium() - 2);//初始化音符逻辑半径
	Width = new qreal(2.0);//初始化音符视觉线宽
	VRadium = new qreal(*Radium * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符逻辑宽度
	VWidth = new qreal(*Width * Parent->MParent()->size().width() / Parent->MParent()->oriSize().width());//初始化音符的逻辑线宽
	Type = new qint32(catch);//初始化音符的类型为catch
	NoteColor = new QColor(parent->dotColor());//初始化音符的颜色
	Visuable = new bool(parent->visuable());//初始化音符的可见性
	BeatKey = new qint32(Qt::Key_Escape);//初始化beat音符专有的额外键
	BeatKeyText = new QString("0");//初始化beat音符专有的额外键文本
	Time = new qint64(0);//初始化音符的判定时间
	TimeLength = new qint64(0);//初始化hold音符专有的持续时长
	EndTime = new qint64(*Time + *TimeLength);//初始化hold音符专有的结束时间
}

MNote::~MNote()
{}

void MNote::MNoteSet(bool visuable, qreal radium, qreal width, QColor color, qint32 type, qint64 time, qint64 nextTime, qint32 beatKey, QString beatKeyText, qint64 timeLength)
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
}

qint64 MNote::time()
{
	return *Time;
}

void MNote::setTimeLength(qint64 time_ms)
{
	TimeLength = new qint64(time_ms);
	EndTime = new qint64(*Time + *TimeLength);
}

qint64 MNote::timeLength()
{
	return *TimeLength;
}

qint64 MNote::endTime()
{
	return *EndTime;
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