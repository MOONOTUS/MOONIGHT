#include"MWidget.h"
#include"MNote.h"
#include"MCheckDot.h"

MNote::MNote(MCheckDot* parent)
{
	Parent = parent;
	Radium = new qreal(parent->radium() - 2);
	Width = new qreal(2.0);
	Type = new qint32(catch);
	NoteColor = new QColor(parent->dotColor());
	Visuable = new bool(parent->visuable());
	BeatKey = new qint32(Qt::Key_0);
	BeatKeyText = new QString("0");
}

MNote::~MNote()
{}

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

void MNote::setWidth(qreal width)
{
	Width = new qreal(width);
	VWidth = new qreal(*Width * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}

qreal MNote::width()
{
	return *Width;
}

void MNote::setNoteColor(QColor color)
{
	NoteColor = new QColor(color);
}

void MNote::setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	NoteColor = new QColor(R, G, B, A);
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
}

qint64 MNote::time()
{
	return *Time;
}

MCheckDot*& MNote::MParent()
{
	return Parent;
}