#include "MFormerCalculator.h"
#include "MWidget.h"
#include "MCheckDot.h"

MFormerCalculator::MFormerCalculator(MWidget *parent)
	: QWidget(parent)
{
	Parent = parent;
	Show = new bool(true);
	Image = new QPixmap(".\\MOONIGHT_Front_Little.png");
	Mask = new QPixmap(".\\MOONIGHT_Mask_Front.png");
	Score = new qint64(0);
	ScoreText = new QString("0");
	MusicName = new QString("Unkown");
	Combo = new qint64(0);
	ComboText = new QString(QString::number(*Combo));
	Accuracy = new qreal(100.00);
	AccuracyText = new QString(QString::number(*Accuracy, 'f', 2) + "%");
	Check = new qint32(strictperfect);
	CheckText = new QString("");
	MoonPoint = new QPoint(1600, 150);
	VMoonPoint = new QPoint(MoonPoint->x() * Parent->visualProportion(), MoonPoint->y() * Parent->visualProportion());
	MoonRadium = new qreal(100);
	VMoonRadium = new qreal(*MoonRadium * Parent->visualProportion());
	Deviation = new qreal(100);
	Type = new QString("Miss");
}

void MFormerCalculator::paintEvent(QPaintEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Message_::MFormer Calculator paints";
	this->setGeometry(0, (Parent->height() - Parent->width() * 9 / 16) / 2, Parent->width(), Parent->width() * 9 / 16);//，以屏幕宽度为基准，设定16：9中央绘制区域，保证在不同尺寸的比例正常的设备上谱面的比例一样
	QPainter* paint = new QPainter(this);
	QPainter* text = new QPainter(this);
	QPen textpen;
	textpen.setColor(QColor(255, 255, 255, 255));
	text->setPen(textpen);
	if (*Show)
	{
		paint->drawPixmap(this->rect(), *Image);
		textpen.setColor(QColor(255, 255, 255, 255));
		text->setPen(textpen);
		text->setFont(QFont("Microsoft YaHei Ui", 48 * (Parent->visualProportion()), -1));
		text->drawText(QRect(qint32(985 * (Parent->visualProportion())), qint32(52 * (Parent->visualProportion())), qint32(500 * (Parent->visualProportion())), qint32(96 * (Parent->visualProportion()))), Qt::AlignRight | Qt::AlignBottom, *ScoreText);
		text->drawText(QRect(qint32(1715 * (Parent->visualProportion())), qint32(52 * (Parent->visualProportion())), qint32(500 * (Parent->visualProportion())), qint32(96 * (Parent->visualProportion()))), Qt::AlignLeft | Qt::AlignBottom, *ComboText);
		text->setFont(QFont("Microsoft YaHei Ui", ((36 * (Parent->visualProportion()) < 1.5 * 351 * (Parent->visualProportion()) / MusicName->size()) ? (36 * (Parent->visualProportion())) : (1.5 * 351 * (Parent->visualProportion()) / MusicName->size())), -1));
		//qDebug() << "\tMOONOTUSYSTEM::_Debug_::" << 36 * (Parent->visualProportion()) << "\t" << 351 * Parent->visualProportion() / MusicName->size() << "\t" << ((36 * (Parent->visualProportion()) < 351 * (Parent->visualProportion()) / MusicName->size()) ? (36 * (Parent->visualProportion())) : (351 * (Parent->visualProportion()) / MusicName->size()));
		text->drawText(QRect(qint32(1135 * (Parent->visualProportion())), qint32(164 * (Parent->visualProportion())), qint32(351 * (Parent->visualProportion())), qint32(72 * (Parent->visualProportion()))), Qt::AlignRight | Qt::AlignTop, *MusicName);
		text->drawText(QRect(qint32(1714 * (Parent->visualProportion())), qint32(164 * (Parent->visualProportion())), qint32(351 * (Parent->visualProportion())), qint32(72 * (Parent->visualProportion()))), Qt::AlignLeft | Qt::AlignTop, *AccuracyText);
		QPainter* moon = new QPainter(this);
		QPen moonpen;
		moonpen.setColor(QColor(255, 209, 86, 155));
		moonpen.setWidth(1);
		moon->setPen(moonpen);
		moon->setBrush(Qt::transparent);
		QPainterPath moonpath;
		moonpath.moveTo(QPoint(1600 * (Parent->visualProportion()), 50 * (Parent->visualProportion())));
		if (Parent->pausing())
		{
			paint->fillRect(this->rect(), QColor(0, 0, 0, 155));
		}
		if ((*Type) == "Full")
		{
			moonpen.setColor(QColor(255, 209, 86, 155));
			moonpen.setWidth(1);
			moon->setPen(moonpen);
			moon->setBrush(QColor(255, 209, 86, 155));
			moon->drawEllipse(QPointF(1600 * (Parent->visualProportion()), 150 * (Parent->visualProportion())), 100 * (Parent->visualProportion()), 100 * (Parent->visualProportion()));
		}
		else if ((*Type) == "Miss")
		{
			moonpen.setColor(QColor(255, 209, 86, 155));
			moonpen.setWidth(1);
			moon->setPen(moonpen);
			moon->setBrush(Qt::transparent);
			moon->drawEllipse(QPointF(1600 * (Parent->visualProportion()), 150 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())));
		}
		else if ((*Type) == "Fast")
		{
			moonpen.setColor(QColor(255, 209, 86, 155));
			moonpen.setWidth(1);
			moon->setPen(moonpen);
			moon->drawEllipse(QPointF(1600 * (Parent->visualProportion()), 150 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())));
			moonpath.cubicTo(QPointF(1600 * (Parent->visualProportion()), 50 * (Parent->visualProportion())), QPointF((1500 + 200 * (*Deviation)) * (Parent->visualProportion()), 150 * (Parent->visualProportion())), QPointF(1600 * (Parent->visualProportion()), 250 * (Parent->visualProportion())));
			moonpath.arcTo(QRect(1500 * (Parent->visualProportion()), 50 * (Parent->visualProportion()), 200 * (Parent->visualProportion()), 200 * (Parent->visualProportion())), -90, 180);
			moonpen.setColor(Qt::transparent);
			moon->setPen(moonpen);
			moon->setBrush(QColor(255, 209, 86, 155));
			//moon->drawChord(QRect(1500 * (Parent->visualProportion()), 50 * (Parent->visualProportion()), 200 * (Parent->visualProportion()), 200 * (Parent->visualProportion())), 90 * 16, -180 * 16);
			moon->drawPath(moonpath);
			qDebug() << "MOONOTUSYSTEM::_Debug_::" << *Deviation;
		}
		else if ((*Type) == "Slow")
		{
			moonpen.setColor(QColor(255, 209, 86, 155));
			moonpen.setWidth(1);
			moon->setPen(moonpen);
			moon->drawEllipse(QPointF(1600 * (Parent->visualProportion()), 150 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())), qreal(100 * (Parent->visualProportion())));
			moonpath.cubicTo(QPointF(1600 * (Parent->visualProportion()), 50 * (Parent->visualProportion())), QPointF((1700 - 200 * (*Deviation)) * (Parent->visualProportion()), 150 * (Parent->visualProportion())), QPointF(1600 * (Parent->visualProportion()), 250 * (Parent->visualProportion())));
			moonpath.arcTo(QRect(1500 * (Parent->visualProportion()), 50 * (Parent->visualProportion()), 200 * (Parent->visualProportion()), 200 * (Parent->visualProportion())), -90, -180);
			moonpen.setColor(Qt::transparent);
			moon->setPen(moonpen);
			moon->setBrush(QColor(255, 209, 86, 155));
			//moon->drawChord(QRect(1500 * (Parent->visualProportion()), 50 * (Parent->visualProportion()), 200 * (Parent->visualProportion()), 200 * (Parent->visualProportion())), 90 * 16, 180 * 16);
			moon->drawPath(moonpath);
		}
		textpen.setColor(QColor(255, 255, 255, 255));
		text->setPen(textpen);
		text->setFont(QFont("Microsoft YaHei Ui", 36 * (Parent->visualProportion()), -1));
		text->drawText(QRect(qint32(1480 * (Parent->visualProportion())), qint32(225 * (Parent->visualProportion())), qint32(240 * (Parent->visualProportion())), qint32(50 * (Parent->visualProportion()))), Qt::AlignHCenter | Qt::AlignVCenter, *CheckText);
	}

	event->accept();
}

MFormerCalculator::~MFormerCalculator()
{
	delete Parent;
	delete Image;
	delete Mask;
	delete Score;
	delete ScoreText;
	delete MusicName;
	delete Combo;
	delete ComboText;
	delete Accuracy;
	delete AccuracyText;
	delete Check;
	delete MoonPoint;
	delete VMoonPoint;
	delete MoonRadium;
	delete VMoonRadium;
}

void MFormerCalculator::setImage(QString path)
{
	Image = new QPixmap(path);
}

void MFormerCalculator::setMask(QString path)
{
	Mask = new QPixmap(path);
}

void MFormerCalculator::setImage(QPixmap image)
{
	Image = new QPixmap(image);
}

void MFormerCalculator::setMask(QPixmap image)
{
	Mask = new QPixmap(image);
}

void MFormerCalculator::setScore(qint64 score)
{
	Score = new qint64(score);
	ScoreText = new QString(QString::number(*Score));
}

void MFormerCalculator::setMusicName(QString name)
{
	MusicName = new QString(name);
}

void MFormerCalculator::setCombo(qint64 combo)
{
	Combo = new qint64(combo);
	ComboText = new QString(QString::number(*Combo));
}

void MFormerCalculator::setAccuracy(qreal accuracy)
{
	Accuracy = new qreal(accuracy);
	AccuracyText = new QString(QString::number(*Accuracy, 'f', 2) + "%");
}

void MFormerCalculator::setCheck(qint32 check)
{
	Check = new qint32(check);
}

void MFormerCalculator::setCheckText(QString checktext)
{
	CheckText = new QString(checktext);
}

QPoint MFormerCalculator::vMoonPoint()
{
	return *VMoonPoint;
}

qreal MFormerCalculator::vMoonRadium()
{
	return *VMoonRadium;
}

MWidget*& MFormerCalculator::MParent()
{
	return Parent;
}

void MFormerCalculator::setShow(bool show)
{
	Show = new bool(show);
}

bool MFormerCalculator::ifShow()
{
	return *Show;
}

void MFormerCalculator::setDeviation(qreal deviation)
{
	Deviation = new qreal(deviation);
}

qreal MFormerCalculator::deviation()
{
	return *Deviation;
}

void MFormerCalculator::setType(QString type)
{
	Type = new QString(type);
}

QString MFormerCalculator::type()
{
	return *Type;
}