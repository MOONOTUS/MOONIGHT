#pragma once
#include"MCenter.h"

class MCheckDot;

class MCheckDotLine //轨道线类
{
private:
	static QColor* AutoLineColor;

private:
	MCheckDot* Parent;//存储parent，用于溯源
	bool* Visuable;//轨道线是否可见
	qreal* Width;//轨道线的逻辑宽度
	qreal* Angle;//轨道线的角度
	qreal* UpAngle;//上部线角
	qreal* DownAngle;//下部线角
	bool* UpVisuable;//上部线可见性
	bool* DownVisuable;//下部线可见性
	QColor* DotLineColor;//轨道线的颜色（RGBA）
	qreal* VWidth;//轨道线的视觉宽度

public:
	MCheckDotLine(MCheckDot* parent = nullptr);
	~MCheckDotLine();

	inline void setVisuable(bool visuable);//设定轨道线是否可见
	inline bool visuable() const;//轨道线可见性
	inline void setUpVisuable(bool visuable);//设定上部轨道线可见性
	inline bool upVisuable() const;//上部轨道线可见性
	inline void setDownVisuable(bool visuable);//设定下部轨道线可见性
	inline bool downVisuable() const;//下部轨道线可见性
	inline void setWidth(qreal width);//设定轨道线的逻辑宽度
	inline qreal width() const;//轨道线逻辑宽度
	inline void setAngle(qreal angle);//设定轨道线的角度
	inline qreal angle() const;//轨道线角度
	inline void setUpAngle(qreal angle);//设定上部线角
	inline qreal upAngle() const;//上部线角
	inline void setDownAngle(qreal angle);//设定下部线角
	inline qreal downAngle() const;//下部线角
	inline void setDotLineColor(QColor color);//设定轨道线的颜色
	inline void setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定轨道线的颜色
	inline QColor dotLineColor() const;//返回*DotLineColor
	inline qreal vWidth() const;//返回*VWidth
	inline static void setAutoLineColor(QColor color);
	inline static void setAutoLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	inline static QColor autoLineColor() const;
	inline MCheckDot*& MParent();//返回Parent，用于溯源
};

