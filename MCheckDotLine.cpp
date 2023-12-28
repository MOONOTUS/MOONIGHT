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
	Width = new qreal(parent->width() - 2);//初始化轨道线的逻辑宽度和视觉宽度
	VWidth = new qreal((*Width) * Parent->MParent()->visualProportion());
	Angle = new qreal(90);//初始化轨道线的角度
	UpAngle = new qreal(*Angle);
	DownAngle = new qreal(*Angle - 180);
}

MCheckDotLine::~MCheckDotLine()
{
	delete Visuable;
	delete Width;
	delete Angle;
	delete DotLineColor;
	delete VWidth;
}

void MCheckDotLine::setVisuable(bool visuable)
{
	delete Visuable;
	Visuable = new bool(visuable);
	delete UpVisuable;
	UpVisuable = new bool(*Visuable);
	delete DownVisuable;
	DownVisuable = new bool(*Visuable);
}

bool MCheckDotLine::visuable() const
{
	return *Visuable;
}

void MCheckDotLine::setUpVisuable(bool visuable)
{
	delete UpVisuable;
	UpVisuable = new bool(visuable);
}

bool MCheckDotLine::upVisuable() const
{
	return *UpVisuable;
}

void MCheckDotLine::setDownVisuable(bool visuable)
{
	delete DownVisuable;
	DownVisuable = new bool(visuable);
}

bool MCheckDotLine::downVisuable() const
{
	return *DownVisuable;
}

void MCheckDotLine::setWidth(qreal width)
{
	delete Width;
	Width = new qreal(width);
	delete VWidth;
	VWidth = new qreal(*Width * Parent->MParent()->width() / Parent->MParent()->oriSize().width());
}
qreal MCheckDotLine::width() const
{
	return *Width;
}

void MCheckDotLine::setAngle(qreal angle)
{
	delete Angle;
	Angle = new qreal(angle);
	delete UpAngle;
	UpAngle = new qreal(*Angle);
	delete DownAngle;
	DownAngle = new qreal(*Angle - 180);
}

qreal MCheckDotLine::angle() const
{
	return *Angle;
}

void MCheckDotLine::setUpAngle(qreal angle)
{
	delete UpAngle;
	UpAngle = new qreal(angle);
}

qreal MCheckDotLine::upAngle() const
{
	return *UpAngle;
}

void MCheckDotLine::setDownAngle(qreal angle)
{
	delete DownAngle;
	DownAngle = new qreal(angle);
}

qreal MCheckDotLine::downAngle() const
{
	return *DownAngle;
}

void MCheckDotLine::setDotLineColor(QColor color)
{
	delete DotLineColor;
	DotLineColor = new QColor(color);
}

void MCheckDotLine::setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	delete DotLineColor;
	DotLineColor = new QColor(R, G, B, A);
}

QColor MCheckDotLine::dotLineColor() const
{
	return *DotLineColor;
}

qreal MCheckDotLine::vWidth() const
{
	return *VWidth;
}

void MCheckDotLine::setAutoLineColor(QColor color)
{
	delete AutoLineColor;
	AutoLineColor = new QColor(color);
}

void MCheckDotLine::setAutoLineColor(qint32 R,qint32 G,qint32 B,qint32 A)
{
	delete AutoLineColor;
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