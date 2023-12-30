#include "MPivot.h"

QSize* MMainWindow::OriSize = new QSize(WIDTH, HEIGHT);
qint32* MMainWindow::StateNowSetUp = new qint32(startstate);
qint64* MMainWindow::ChapterSum = new qint64(0);

MMainWindow::MMainWindow(QWidget *parent)
	: QWidget(parent)
{
	Parent = parent;
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
	ChapterList = new QMap<QString, MCell*>;
	ChapterNumList = new QMap< qint64, QString>;
	Chapter = new QString("");
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
	for (QMap<QString, MCell*>::iterator ptr = CellList->begin(); ptr != CellList->end(); ++ptr)
	{
		if (ptr.value()->linkState() != *State && ptr.value()->isVisible())
		{
			ptr.value()->hide();
		}
		else if (ptr.value()->linkState() == *State && !ptr.value()->isVisible())
		{
			ptr.value()->show();
		}
	}
}

void MMainWindow::timeAdd_ms()
{
	delete time_ms;
	time_ms = new qint64(UiTime->elapsed());
}

void MMainWindow::UiSetUp()
{
	nowSetUp(startstate);
	MCell* logo = new MCell(this);
	logo->setRect(400, 0, 2400, 1350);
	logo->setType(imagecell);
	logo->setImage(".\\MOONIGHT_Beta_Little.png");
	this->addCell("Logo", logo);
	MCell* touch = new MCell(this);
	touch->setRect(1490, 1490, 210, 210);
	touch->setType(ellipsecell);
	touch->setLineWidth(20);
	touch->setLineColor(QColor(0, 0, 0, 50));
	touch->setEllipseCenter(105, 105);
	touch->setRadium(80);
	this->addCell("Touch", touch);
	MCell* tip = new MCell(this);
	tip->setRect(1300, 1400, 600, 60);
	tip->setType(textcell);
	tip->setFont(QFont("Microsoft YaHei Ui", 50, -1));
	tip->setLineColor(QColor(0, 0, 0, 50));
	tip->setText("Touch To Start");
	this->addCell("Tip", tip);
	connect
	(
		CellList->value("Touch"),
		SIGNAL(clicked()),
		this,
		SLOT(statechange_start_to_chapter())
	);
	nowSetUp(chapterstate);
	this->addChapter("Spirit", "摇光", QPixmap(".\\MOONIGHT_Beta_Little.png"));
}

void MMainWindow::UiAnimation()
{
	if (*State == startstate)
	{
		CellList->value("Touch")->setRadium(80 + 10 * qSin(qreal(*time_ms)/1000));
		CellList->value("Touch")->setLineWidth(20 + 10 * qCos(qreal(*time_ms)/300));
		CellList->value("Tip")->setRect(1300, 1400 - 10 * qSin(qreal(*time_ms) / 1000) - 10 * qCos(qreal(*time_ms) / 300), CellList->value("Tip")->MRect()->width(), CellList->value("Tip")->MRect()->height());
	}
}

void MMainWindow::statechange_start_to_chapter()
{
	delete State;
	State = new qint32(chapterstate);
}

void MMainWindow::statechange_chapter_to_songlist(QString chapterkey)
{
	delete State;
	State = new qint32(songliststate);
	Chapter = new QString(chapterkey);
}

void MMainWindow::addCell(QString key, MCell* cell, qint32 linkstate)
{
	cell->setLinkState(linkstate);
	CellList->insert(key, cell);
}

void MMainWindow::addChapter(QString key, QString chaptername, QPixmap chaptercover)
{
	MCell* newchapter = new MCell(this);
	newchapter->setType(chaptercell);
	//newchapter->setRect(-1000, -1000, -1000, -1000);
	newchapter->setRect(0, 0, 1000, 1000);
	newchapter->setImage(chaptercover);
	newchapter->setText(chaptername);
	newchapter->setLineColor(QColor(255, 255, 255, 150));
	qint64 ChapterSum_ = *MMainWindow::ChapterSum;
	delete MMainWindow::ChapterSum;
	MMainWindow::ChapterSum = new qint64(ChapterSum_ + 1);
	this->addCell(key, newchapter, chapterstate);
	ChapterList->insert(key, newchapter);
	ChapterNumList->insert(*MMainWindow::ChapterSum, key);
	connect
	(
		newchapter,
		SIGNAL(Mclicked(QString)),
		this,
		SLOT(statechange_chapter_to_songlist(QString))
	);
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

QWidget*& MMainWindow::MParent()
{
	return Parent;
}

void MMainWindow::nowSetUp(qint32 nowsetup)
{
	delete StateNowSetUp;
	MMainWindow::StateNowSetUp = new qint32 (nowsetup);
}