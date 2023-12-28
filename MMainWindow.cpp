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
	touch->setRect(1570, 1570, 60, 60);
	touch->setType(ellipsecell);
	touch->setLineWidth(6);
	touch->setLineColor(QColor(0, 0, 0, 50));
	touch->setEllpiseCenter(30, 30);
	touch->setRadium(30);
	this->addCell("Touch", touch);
}

void MMainWindow::UiAnimation()
{
	if (*State == startstate)
	{
		
	}
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

