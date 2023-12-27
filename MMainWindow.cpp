#include "MMainWindow.h"

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
	MCell* cell_1 = new MCell(this);
	cell_1->setRect(400, 0, 2400, 1350);
	cell_1->setType(imagecell);
	cell_1->setImage(".\\MOONIGHT_Beta_Little.png");
	this->addCell("Logo", cell_1);
}

void MMainWindow::UiAnimation()
{
	if (*State == startstate)
	{
		//CellList->value("Logo")->setRect(CellList->value("Logo")->MRect()->x(), CellList->value("Logo")->MRect()->y(), CellList->value("Logo")->MRect()->width() - 1, CellList->value("Logo")->MRect()->height() - 1);
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

qreal MMainWindow::visualProportion()
{
	return qreal(qreal(this->width()) / qreal(this->OriSize->width()));
}

qreal MMainWindow::visualProportionX()
{
	return qreal(qreal(this->width()) / qreal(this->OriSize->width()));
}

qreal MMainWindow::visualProportionY()
{
	return qreal(qreal(this->height()) / qreal(this->OriSize->height()));
}

