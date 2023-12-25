#include"MWidget.h"
#include"MCheckDot.h"
#include"MCheckDotLine.h"

QColor* MCheckDotLine::AutoLineColor = new QColor(217, 150, 229, 255);

MCheckDotLine::MCheckDotLine(MCheckDot* parent)
{
	Parent = parent;//存储parernt
	DotLineColor = new QColor(*AutoLineColor);//初始化轨道线的颜色
	Visuable = new bool(parent->visuable());//初始化轨道线的可见性
	UpVisuable = new bool(*Visuable);
	DownVisuable = new bool(*Visuable);
	setWidth(parent->width() - 2);//初始化轨道线的逻辑宽度和视觉宽度
	Angel = new qreal(90);//初始化轨道线的角度
	UpAngle = new qreal(*Angel);
	DownAngle = new qreal(*Angel - 180);

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
	UpVisuable = new bool(*Visuable);
	DownVisuable = new bool(*Visuable);
}

bool MCheckDotLine::visuable()
{
	return *Visuable;
}

void MCheckDotLine::setUpVisuable(bool visuable)
{
	UpVisuable = new bool(visuable);
}

bool MCheckDotLine::upVisuable()
{
	return *UpVisuable;
}

void MCheckDotLine::setDownVisuable(bool visuable)
{
	DownVisuable = new bool(visuable);
}

bool MCheckDotLine::downVisuable()
{
	return *DownVisuable;
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
	UpAngle = new qreal(*Angel);
	DownAngle = new qreal(*Angel - 180);
}

qreal MCheckDotLine::angle()
{
	return *Angel;
}

void MCheckDotLine::setUpAngle(qreal angle)
{
	UpAngle = new qreal(angle);
}

qreal MCheckDotLine::upAngle()
{
	return *UpAngle;
}

void MCheckDotLine::setDownAngle(qreal angle)
{
	DownAngle = new qreal(angle);
}

qreal MCheckDotLine::downAngle()
{
	return *DownAngle;
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

void MCheckDotLine::setAutoLineColor(QColor color)
{
	AutoLineColor = new QColor(color);
}

void MCheckDotLine::setAutoLineColor(qint32 R,qint32 G,qint32 B,qint32 A)
{
	AutoLineColor = new QColor(R, G, B, A);
}

QColor MCheckDotLine::autoLineColor()
{
	return *AutoLineColor;
}

MCheckDot*& MCheckDotLine::MParent()
{
	return Parent;
}