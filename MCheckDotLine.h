#pragma once
#include"MCenter.h"

class MCheckDot;

class MCheckDotLine
{
private:
	MCheckDot* Parent;//�洢parent��������Դ
	bool* Visuable;//������Ƿ�ɼ�
	qreal* Width;//����ߵ��߼����
	qreal* Angel;//����ߵĽǶ�
	QColor* DotLineColor;//����ߵ���ɫ��RGBA��
	qreal* VWidth;//����ߵ��Ӿ����

public:
	MCheckDotLine(MCheckDot* parent = nullptr);
	~MCheckDotLine();

	void setVisuable(bool visuable);//�趨������Ƿ�ɼ�
	bool visuable();//����*Visuable
	void setWidth(qreal width);//�趨����ߵ��߼����
	qreal width();//����*Width
	void setAngel(qreal angle);//�趨����ߵĽǶ�
	qreal angle();//����*Angle
	void setDotLineColor(QColor color);//�趨����ߵ���ɫ
	void setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨����ߵ���ɫ
	QColor dotLineColor();//����*DotLineColor
	qreal vWidth();//����*VWidth
	MCheckDot*& MParent();//����Parent��������Դ
};
