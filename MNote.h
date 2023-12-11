#pragma once
#include"MCenter.h"

class MCheckDot;

class MNote
{
public:
#define click 0x01
#define catch 0x00
#define hold 0x10
#define beat 0x11

private:
	MCheckDot* Parent;
	bool* Visuable;
	qreal* Radium;  
	qreal* VRadium;
	qreal* Width;
	qreal* VWidth;
	QColor* NoteColor;
	qint32* Type;
	qint32* BeatKey;
	QString* BeatKeyText;
	qint64* Time;
	qint64* TimeLength;
	qint64* EndTime;
	qint64* NextTime;

public:
	MNote(MCheckDot* parent = nullptr);
	~MNote();

	void setVisuable(bool visuable);
	bool visuable();
	void setRadium(qreal r);
	qreal radium();
	void setWidth(qreal width);
	qreal width();
	void setNoteColor(QColor color);
	void setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	void setType(qint32 type);
	qint32 type();
	void setBeatKey(qint32 key, QString keytext);
	qint32 beatKey();
	QString beatKeyText();
	void setTime(qint64 time_ms);
	qint64 time();
	void setTimeLength(qint64 time_ms);
	qint64 timeLength();
	qint64 endTime();
	void setNextTime(qint64 time_ms);
	qint64 nextTime();
	MCheckDot*& MParent();
};