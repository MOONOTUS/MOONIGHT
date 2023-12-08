#pragma once
#include"MCenter.h"

class MCheckDot;

class MNote
{
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
	MCheckDot*& MParent();
};