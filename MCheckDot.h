#pragma once

#include"MCenter.h"
#include"MCheckDotLine.h"
#include"MNote.h"

class MWidget;

class MCheckDot  : public QPushButton
{
	Q_OBJECT

#define strictperfect 0x1111
#define preperfect 0x1011
#define lagperfect 0x0011
#define pregood 0x1010
#define laggood 0x0010
#define prebad 0x1001
#define lagbad 0x0001
#define miss 0x0000

protected:
	void paintEvent(QPaintEvent* event);
	void keyPressEvent(QKeyEvent* event);

	void paintDot(QPainter* paint);
	void paintDotLine(QPainter* paint);
	void paintNote(QPainter* paint);

signals:
	void touched();

public slots:
	void check();

private:
	MCheckDotLine* DotLine;
	QMap<qint64, MNote*>* NoteList;
	QMap<qint64, MNote*>::iterator* NoteListPtr;
	QMap<qint64, qint32*>* NoteCheckList;
	bool* Visuable;
	QPoint* Point;
	qreal* Radium;
	qreal* Width;
	QColor* DotColor;
	QColor* DotKeyColor;
	qint32* Key;
	QString* KeyText;
	MWidget* Parent;
	QPoint* VPoint;
	qreal* VRadium;
	qreal* VWidth;
	bool* KeyVisuable;


public:
	MCheckDot(MWidget *parent = nullptr);
	~MCheckDot();

	void setDotLine(MCheckDotLine& dotline);
	MCheckDotLine*& dotLine();
	void setVisuable(bool visuable);
	bool visuable();
	void setPoint(QPoint& point);
	void setPoint(qreal x, qreal y);
	QPoint point();
	void setRadium(qreal r);
	qreal radium();
	void setWidth(qreal width);
	qreal width();
	void setDotColor(QColor color);
	void setDotColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	QColor dotColor();
	void setDotKeyColor(QColor color);
	void setDotKeyColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	QColor dotKeyColor();
	void setKey(qint32 key, QString keytext);
	qint32 key();
	QString keyText();
	QMap<qint64, MNote*>*& noteList();
	void noteListFlush();
	QMap<qint64, qint32*>*& noteCheckList();
	MWidget*& MParent();
	void setKeyVisuable(bool visuable);
	bool keyVisuable();

};
