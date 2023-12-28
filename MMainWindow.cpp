#include "MPivot.h"

QSize* MMainWindow::OriSize = new QSize(WIDTH, HEIGHT);

MMainWindow::MMainWindow(QWidget *parent)
	: QWidget(parent)
{
	State = new qint32(startstate);
	UiTimeFlush = new QTimer(this);
	UiTimeFlush->stop();
	UiTimeFlush->setInterval(1);
	UiTimeFlush->setSingleShot(false);
	UiTimeFlush->start();
	UiFlushTime = new QTimer(this);
	UiFlushTime->stop();
	UiFlushTime->setInterval(10);
	UiFlushTime->setSingleShot(false);
	UiFlushTime->start();
	UiTime = new QElapsedTimer();
	time_ms = new qint64(0);
	CellList = new QMap<QString, MCell*>;
	Parent = parent;
	UiSetUp();
	UiTime->start();

	connect
	(
		UiTimeFlush,
		SIGNAL(timeout()),
		this,
		SLOT(timeAdd_ms()),
		Qt::DirectConnection
	);
	connect
	(
		UiFlushTime,
		SIGNAL(timeout()),
		this,
		SLOT(UiAnimation()),
		Qt::DirectConnection
	);
	connect
	(
		UiTimeFlush,
		SIGNAL(timeout()),
		this,
		SLOT(repaint()),
		Qt::DirectConnection
	);
}

MMainWindow::~MMainWindow()
{}

void MMainWindow::paintEvent(QPaintEvent* event)
{

}

void MMainWindow::timeAdd_ms()
{
	delete time_ms;
	time_ms = new qint64(UiTime->elapsed());
}

void MMainWindow::UiSetUp()
{
	MCell* logo = new MCell(this);
	logo->setRect(400, 0, 2400, 1350);
	logo->setType(imagecell);
	logo->setImage(".\\MOONIGHT_Beta_Little.png");
	this->addCell("Logo", logo);
	MCell* touch = new MCell(this);
	touch->setRect(1500, 1500, 200, 200);
	touch->setType(ellipsecell);
	touch->setLineWidth(20);
	touch->setLineColor(QColor(0, 0, 0, 50));
	touch->setEllipseCenter(100, 100);
	touch->setRadium(75);
	this->addCell("Touch", touch);
	connect
	(
		CellList->value("Touch"),
		SIGNAL(clicked()),
		this,
		SLOT(Test())
	);
}

void MMainWindow::UiAnimation()
{
	if (*State == startstate)
	{
		CellList->value("Touch")->setRadium(75 + 10 * qSin(qreal(*time_ms)/1000));
		CellList->value("Touch")->setLineWidth(20 + 10 * qCos(qreal(*time_ms)/300));
	}
}

void MMainWindow::Test()
{
	MOONIGHT_Play(1);
}

void MMainWindow::addCell(QString key, MCell* cell)
{
	CellList->insert(key, cell);
}

QMap<QString, MCell*>*& MMainWindow::cellList()
{
	return CellList;
}

qreal MMainWindow::visualProportion() const
{
	return qreal(qreal(this->width()) / qreal(this->OriSize->width()));
}

qreal MMainWindow::visualProportionX() const
{
	return qreal(qreal(this->width()) / qreal(this->OriSize->width()));
}

qreal MMainWindow::visualProportionY() const
{
	return qreal(qreal(this->height()) / qreal(this->OriSize->height()));
}

QTimer*& MMainWindow::uiFlushTime()
{
	return UiFlushTime;
}

