#pragma once
#include"MCenter.h"

class MCheckDot;

class MCheckDotLine
{
private:
	MCheckDot* Parent;
	bool* Visuable;
	qreal* Width;
	qreal* Angel;
	QColor* DotLineColor;
	qreal* VWidth;

public:
	MCheckDotLine(MCheckDot* parent = nullptr);
	~MCheckDotLine();

	void setVisuable(bool visuable);
	bool visuable();
	void setWidth(qreal width);
	qreal width();
	void setAngel(qreal angle);
	qreal angle();
	void setDotLineColor(QColor color);
	void setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	QColor dotLineColor();
	qreal vWidth();
	MCheckDot*& MParent();
};
