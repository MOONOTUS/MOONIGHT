#include"MWidget.h"
#include"MCheckDot.h"
#include"MCheckDotLine.h"

MCheckDotLine::MCheckDotLine(MCheckDot* parent)
{
	Parent = parent;//�洢parernt
	DotLineColor = new QColor(parent->dotColor());//��ʼ������ߵ���ɫ
	Visuable = new bool(parent->visuable());//��ʼ������ߵĿɼ���
	setWidth(parent->width() - 2);//��ʼ������ߵ��߼���Ⱥ��Ӿ����
	Angel = new qreal(90);//��ʼ������ߵĽǶ�
}

MCheckDotLine::~MCheckDotLine()
{
	delete Visuable;
	delete Width;
	delete Angel;
	delete DotLineColor;
	delete VWidth;
}

void MCheckDotLine::setVisuable(bool visuable)
{
	Visuable = new bool(visuable);
}

bool MCheckDotLine::visuable()
{
	return *Visuable;
}

void MCheckDotLine::setWidth(qreal width)
{
	Width = new qreal(width);
	VWidth = new qreal(*Width * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}
qreal MCheckDotLine::width()
{
	return *Width;
}

void MCheckDotLine::setAngel(qreal angel)
{
	Angel = new qreal(angel);
}

qreal MCheckDotLine::angle()
{
	return *Angel;
}

void MCheckDotLine::setDotLineColor(QColor color)
{
	DotLineColor = new QColor(color);
}

void MCheckDotLine::setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	DotLineColor = new QColor(R, G, B, A);
}

QColor MCheckDotLine::dotLineColor()
{
	return *DotLineColor;
}

qreal MCheckDotLine::vWidth()
{
	return *VWidth;
}

MCheckDot*& MCheckDotLine::MParent()
{
	return Parent;
}