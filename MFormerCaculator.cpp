#include "MFormerCaculator.h"
#include "MWidget.h"
#include "MCheckDot.h"

MFormerCaculator::MFormerCaculator(MWidget *parent)
	: QWidget(parent)
{
	Parent = parent;
	Image = new QPixmap();
	Mask = new QPixmap();
	Score = new qint64(0);
	ScoreText = new QString(QString::number(*Score));
	MusicName = new QString("Unkown");
	Combo = new qint64(0);
	ComboText = new QString(QString::number(*Combo));
	Accuracy = new qreal(100.00);
	AccuracyText = new QString(QString::number(*Accuracy) + "%");
	Check = new qint32(strictperfect);
	MoonPoint = new QPoint(1600, 150);
	VMoonPoint = new QPoint(MoonPoint->x() * Parent->visualProportion(), MoonPoint->y() * Parent->visualProportion());
	MoonRadium = new qreal(100);
	VMoonRadium = new qreal(*MoonRadium * Parent->visualProportion());
}

MFormerCaculator::~MFormerCaculator()
{}
