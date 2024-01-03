﻿#include "MPivot.h"

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
	CenterChapter = new qint64(1);
	MaskList = new QMap<QString, QPixmap*>;
	MaskList->insert("MOON_1", new QPixmap(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Moon_1.png"));
	MaskList->insert("MOON_2", new QPixmap(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Moon_2.png"));
	MaskList->insert("MOON_3", new QPixmap(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Moon_3.png"));
	MaskList->insert("MOON_4", new QPixmap(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Moon_4.png"));
	MaskList->insert("MOON_5", new QPixmap(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Moon_5.png"));
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
		UiFlushTime,
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
	QPainter* paint = new QPainter(this);
	QPen pen;
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
	if (*State == chapterstate)
	{
		for (QMap<qint64, QString>::iterator ptr = ChapterNumList->begin(); ptr != ChapterNumList->end() && ChapterList->value(ptr.value())->isVisible(); ++ptr)
		{
			ChapterList->value(ptr.value())->hide();
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter))->setMMask(*MaskList->value("MOON_1"));
			ChapterList->value(ChapterNumList->value(*CenterChapter))->setRect(1200, 400, 800, 800);
			ChapterList->value(ChapterNumList->value(*CenterChapter))->show();
			paint->setFont(QFont("Microsoft YaHei Ui", 50 * this->visualProportion(), -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter))->lineColor());
			paint->drawText(QRect(1200 * this->visualProportionX(), 1250 * this->visualProportionY(), 800 * this->visualProportionX(), 550 * this->visualProportionY()), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter + 1)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->setMMask(*MaskList->value("MOON_2"));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->setRect(2015, 425, 515, 750);
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->show();
			paint->setFont(QFont("Microsoft YaHei Ui", 50 * this->visualProportion() * 2 / 3, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->lineColor());
			paint->drawText(QRect(2015 * this->visualProportionX(), 1205 * this->visualProportionY(), 515 * this->visualProportionX(), 495 * this->visualProportionY()), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter + 2)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->setMMask(*MaskList->value("MOON_3"));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->setRect(2455, 450, 415, 700);
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->show();
			paint->setFont(QFont("Microsoft YaHei Ui", 50 * this->visualProportion() / 2, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->lineColor());
			paint->drawText(QRect(2455 * this->visualProportionX(),1170 * this->visualProportionY(), 415 * this->visualProportionX(), 530 * this->visualProportionY()), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter - 1)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->setMMask(*MaskList->value("MOON_4"));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->setRect(670, 425, 515, 750);
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->show();
			paint->setFont(QFont("Microsoft YaHei Ui", 50 * this->visualProportion() * 2 / 3, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->lineColor());
			paint->drawText(QRect(670 * this->visualProportionX(), 1205 * this->visualProportionY(), 515 * this->visualProportionX(), 495 * this->visualProportionY()), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter - 2)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->setMMask(*MaskList->value("MOON_5"));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->setRect(330, 450, 415, 700);
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->show();
			paint->setFont(QFont("Microsoft YaHei Ui", 50 * this->visualProportion() / 2, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->lineColor());
			paint->drawText(QRect(330 * this->visualProportionX(), 1170 * this->visualProportionY(), 415 * this->visualProportionX(), 530 * this->visualProportionY()), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->text());
		}
	}
	delete paint;
}

void MMainWindow::wheelEvent(QWheelEvent* event)
{
	if (*State == chapterstate)
	{
		if (event->angleDelta().y() > 0 || event->angleDelta().x() > 0)
		{
			if (ChapterNumList->contains(*CenterChapter) && ChapterList->contains(ChapterNumList->value(*CenterChapter)))
			{
				if (connect(ChapterList->value(ChapterNumList->value(*CenterChapter)), SIGNAL(Mclicked(QString)), this, SLOT(statechange_chapter_to_songlist(QString))))
				{
					disconnect
					(
						ChapterList->value(ChapterNumList->value(*CenterChapter)),
						SIGNAL(Mclicked(QString)),
						this,
						SLOT(statechange_chapter_to_songlist(QString))
					);
				}
			}
			qint64 CenterChapter_ = *CenterChapter;
			delete CenterChapter;
			CenterChapter = new qint64(CenterChapter_ + 1);
			if (ChapterNumList->contains(*CenterChapter) && ChapterList->contains(ChapterNumList->value(*CenterChapter)))
			{
				connect
				(
					ChapterList->value(ChapterNumList->value(*CenterChapter)),
					SIGNAL(Mclicked(QString)),
					this,
					SLOT(statechange_chapter_to_songlist(QString))
				);
			}
		}
		else if (event->angleDelta().y() < 0 || event->angleDelta().x() < 0)
		{
			if (ChapterNumList->contains(*CenterChapter) && ChapterList->contains(ChapterNumList->value(*CenterChapter)))
			{
				if (connect(ChapterList->value(ChapterNumList->value(*CenterChapter)), SIGNAL(Mclicked(QString)), this, SLOT(statechange_chapter_to_songlist(QString))))
				{
					disconnect
					(
						ChapterList->value(ChapterNumList->value(*CenterChapter)),
						SIGNAL(Mclicked(QString)),
						this,
						SLOT(statechange_chapter_to_songlist(QString))
					);
				}
			}
			qint64 CenterChapter_ = *CenterChapter;
			delete CenterChapter;
			CenterChapter = new qint64(CenterChapter_ - 1);
			if (ChapterNumList->contains(*CenterChapter) && ChapterList->contains(ChapterNumList->value(*CenterChapter)))
			{
				connect
				(
					ChapterList->value(ChapterNumList->value(*CenterChapter)),
					SIGNAL(Mclicked(QString)),
					this,
					SLOT(statechange_chapter_to_songlist(QString))
				);
			}
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
	logo->setImage(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Beta_Little.png");
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
	this->addChapter("Spirit", "摇光 | Spirit", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test1", "Test1", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test2", "Test2", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test3", "Test3", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test4", "Test4", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test5", "Test5", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test6", "Test6", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test7", "Test7", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test8", "Test8", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test9", "Test9", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test10", "Test10", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test11", "Test11", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test12", "Test12", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test13", "Test13", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test14", "Test14", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test15", "Test15", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
	this->addChapter("Test16", "Test16", QPixmap(".\\resource\\MOONOTUSYSTEM\\Grass.png"));
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
	qDebug() << "MOONOTUSYSTEM::_Message_::State changes <startstate to chapterstate>";
	delete State;
	State = new qint32(chapterstate);
}

void MMainWindow::statechange_chapter_to_songlist(QString chapterkey)
{
	qDebug() << "MOONOTUSYSTEM::_Message_::State changes <chapterstate to songliststate>" << chapterkey;
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
	newchapter->setRect(0, 0, 0, 0);
	if (qreal(qreal(backImage->width()) / qreal(backImage->height())) > qreal(qreal(16.0) / qreal(9.0)))//自适应模块，自动以合适的方案将图片裁剪为16：9的比例
	{
		QPixmap backImage_(*backImage);
		delete backImage;
		backImage = new QPixmap(backImage_.copy((backImage_.width() - backImage_.height() * 16 / 9) / 2, 0, backImage_.height() * 16 / 9, backImage_.height()));
	}
	else if (qreal(qreal(backImage->width()) / qreal(backImage->height())) < qreal(qreal(16.0) / qreal(9.0)))
	{
		QPixmap backImage_(*backImage);
		delete backImage;
		backImage = new QPixmap(backImage_.copy(0, (backImage_.height() - backImage_.width() * 9 / 16) / 2, backImage_.width(), backImage_.width() * 9 / 16));
	}
	newchapter->setImage(chaptercover);
	newchapter->setText(chaptername);
	newchapter->setLineColor(QColor(0, 0, 0, 255));
	newchapter->setIfMask(true);
	newchapter->setChapterKey(key);
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