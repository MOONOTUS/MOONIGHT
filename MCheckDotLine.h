#pragma once
#include"MCenter.h"

class MCheckDot;

class MCheckDotLine
{
private:
	MCheckDot* Parent;//存储parent，用于溯源
	bool* Visuable;//轨道线是否可见
	qreal* Width;//轨道线的逻辑宽度
	qreal* Angel;//轨道线的角度
	qreal* UpAngle;
	qreal* DownAngle;
	bool* UpVisuable;
	bool* DownVisuable;
	QColor* DotLineColor;//轨道线的颜色（RGBA）
	qreal* VWidth;//轨道线的视觉宽度

public:
	MCheckDotLine(MCheckDot* parent = nullptr);
	~MCheckDotLine();

	void setVisuable(bool visuable);//设定轨道线是否可见
	bool visuable();//返回*Visuable
	void setUpVisuable(bool visuable);
	bool upVisuable();
	void setDownVisuable(bool visuable);
	bool downVisuable();
	void setWidth(qreal width);//设定轨道线的逻辑宽度
	qreal width();//返回*Width
	void setAngel(qreal angle);//设定轨道线的角度
	qreal angle();//返回*Angle
	void setUpAngle(qreal angle);
	qreal upAngle();
	void setDownAngle(qreal angle);
	qreal downAngle();
	void setDotLineColor(QColor color);//设定轨道线的颜色
	void setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定轨道线的颜色
	QColor dotLineColor();//返回*DotLineColor
	qreal vWidth();//返回*VWidth
	MCheckDot*& MParent();//返回Parent，用于溯源
};
