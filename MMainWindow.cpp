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
	QPainter* clean = new QPainter(this);
	QPen cleanpen;
	cleanpen.setColor(QColor(245, 245, 245, 245));
	clean->setPen(cleanpen);
	clean->setBrush(QColor(245, 245, 245, 245));
	clean->drawRect(this->rect());
	delete clean;
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
		if (*State == songliststate)
		{
			//if (ptr.value()->chapterKey() != *Chapter)
			//{
			//	ptr.value()->hide();
			//}
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
			ChapterList->value(ChapterNumList->value(*CenterChapter))->setCoverColor(Qt::transparent);
			ChapterList->value(ChapterNumList->value(*CenterChapter))->show();
			paint->setFont(QFont(FONT_1, 50 * this->visualProportion(), -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter))->lineColor());
			paint->drawText(QRect(ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->x(), (ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->height() + 10), ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->width(), this->OriSize->height() * this->visualProportionY() - (ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter))->MVRect()->height() + 10)), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter + 1)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->setMMask(*MaskList->value("MOON_2"));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->setRect(2015, 425, 515, 750);
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->setCoverColor(QColor(0, 0, 0, 100));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->show();
			paint->setFont(QFont(FONT_1, 50 * this->visualProportion() * 2 / 3, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->lineColor());
			paint->drawText(QRect(ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->x(), (ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->height() + 10), ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->width(), this->OriSize->height() * this->visualProportionY() - (ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->MVRect()->height() + 10)), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter + 1))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter + 2)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->setMMask(*MaskList->value("MOON_3"));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->setRect(2455, 450, 415, 700);
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->setCoverColor(QColor(0, 0, 0, 175));
			ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->show();
			paint->setFont(QFont(FONT_1, 50 * this->visualProportion() / 2, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->lineColor());
			paint->drawText(QRect(ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->x(), (ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->height() + 10), ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->width(), this->OriSize->height() * this->visualProportionY() - (ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->MVRect()->height() + 10)), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter + 2))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter - 1)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->setMMask(*MaskList->value("MOON_4"));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->setRect(670, 425, 515, 750);
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->setCoverColor(QColor(0, 0, 0, 100));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->show();
			paint->setFont(QFont(FONT_1, 50 * this->visualProportion() * 2 / 3, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->lineColor());
			paint->drawText(QRect(ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->x(), (ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->height() + 10), ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->width(), this->OriSize->height() * this->visualProportionY() - (ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->MVRect()->height() + 10)), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter - 1))->text());
		}
		if (ChapterList->contains(ChapterNumList->value(*CenterChapter - 2)))
		{
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->setMMask(*MaskList->value("MOON_5"));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->setRect(330, 450, 415, 700);
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->setCoverColor(QColor(0, 0, 0, 175));
			ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->show();
			paint->setFont(QFont(FONT_1, 50 * this->visualProportion() / 2, -1));
			pen.setColor(ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->lineColor());
			paint->drawText(QRect(ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->x(), (ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->height() + 10), ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->width(), this->OriSize->height() * this->visualProportionY() - (ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->y() + ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->MVRect()->height() + 10)), Qt::AlignTop | Qt::AlignHCenter, ChapterList->value(ChapterNumList->value(*CenterChapter - 2))->text());
		}
	}
	if (*State == songliststate)
	{
		CellList->value("SongCheck")->setImage(ChapterList->value(*Chapter)->songList()->value(ChapterList->value(*Chapter)->songNumList()->value(1))->image());
		CellList->value("SongCheck")->setSongID(ChapterList->value(*Chapter)->songList()->value(ChapterList->value(*Chapter)->songNumList()->value(1))->songID());
	}
	delete paint;
}

void MMainWindow::wheelEvent(QWheelEvent* event)
{
	if (*State == chapterstate)
	{
		if (event->angleDelta().y() > 0 || event->angleDelta().x() > 0)
		{
			qint64 CenterChapter_ = *CenterChapter;
			delete CenterChapter;
			CenterChapter = new qint64(CenterChapter_ + 1);
		}
		else if (event->angleDelta().y() < 0 || event->angleDelta().x() < 0)
		{
			qint64 CenterChapter_ = *CenterChapter;
			delete CenterChapter;
			CenterChapter = new qint64(CenterChapter_ - 1);
		}
	}
}

void MMainWindow::timeAdd_ms()
{
	delete time_ms;
	time_ms = new qint64(UiTime->elapsed());
}

void MMainWindow::play(qint64 id)
{
	MOONIGHT_Play(id, this);
}

void MMainWindow::UiSetUp()
{
	nowSetUp(startstate);
	MCell* logo = new MCell(this);
	logo->setType(imagecell);
	logo->setRect(400, 0, 2400, 1350);
	logo->setImage(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Beta_Little.png");
	this->addCell("Logo", logo);
	MCell* touch = new MCell(this);
	touch->setType(ellipsecell);
	touch->setRect(1490, 1490, 210, 210);
	touch->setPressable(true);
	touch->setLineWidth(20);
	touch->setLineColor(QColor(0, 0, 0, 50));
	touch->setEllipseCenter(105, 105);
	touch->setRadium(80);
	this->addCell("Touch", touch);
	MCell* tip = new MCell(this);
	tip->setType(textcell);
	tip->setRect(1300, 1400, 600, 60);
	tip->setFont(QFont(FONT_2, 50, -1));
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
	ChapterSetUp();
	nowSetUp(songliststate);
	MCell* songstart = new MCell(this);
	songstart->setRect(800, 350, 2900, 1630);
	songstart->setPressable(true);
	songstart->setType(imagecell);
	songstart->setMMask(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Mask_Night.png");
	songstart->setIfMask(true);
	songstart->setImage(".\\resource\\MOONOTUSYSTEM\\Grass.png");
	songstart->setCoverImage(".\\resource\\MOONOTUSYSTEM\\MOONIGHT_Cover_Night.png");
	songstart->setIfImageCover(true);
	connect
	(
		songstart,
		SIGNAL(Mclicked(qint64)),
		this,
		SLOT(play(qint64))
	);
	this->addCell("SongCheck", songstart);
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

void MMainWindow::ChapterSetUp()
{
	nowSetUp(songliststate);
	ChapterList->value("Spirit")->addSong(1000000000000, "Infinity Heaven", "无限天堂 | Infinity Heaven", ".\\music\\image\\Infinity_Heaven_Phigros.png");
	ChapterList->value("Spirit")->songList()->value("Infinity Heaven")->setRect(0, 70, 3200, 270);
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
	newchapter->setPressable(true);
	if (qreal(qreal(chaptercover.width()) / qreal(chaptercover.height())) > qreal(1.0))//自适应模块，自动以合适的方案将图片裁剪为1：1的比例
	{
		chaptercover = chaptercover.copy((chaptercover.width() - chaptercover.height()) / 2, 0, chaptercover.height(), chaptercover.height());
	}
	else if (qreal(qreal(chaptercover.width()) / qreal(chaptercover.height())) < qreal(1.0))
	{
		chaptercover = chaptercover.copy(0, (chaptercover.height() - chaptercover.width()) / 2, chaptercover.width(), chaptercover.width());
	}
	newchapter->setImage(chaptercover);
	newchapter->setText(chaptername);
	newchapter->setLineColor(QColor(0, 0, 0, 255));
	newchapter->setIfMask(true);
	newchapter->setChapterKey(key);
	newchapter->setCoverColor(Qt::transparent);
	newchapter->setIfCover(true);
	qint64 ChapterSum_ = *MMainWindow::ChapterSum;
	delete MMainWindow::ChapterSum;
	MMainWindow::ChapterSum = new qint64(ChapterSum_ + 1);
	connect
	(
		newchapter,
		SIGNAL(clicked()),
		newchapter,
		SLOT(CenterChapterChangeTo())
	);
	connect
	(
		newchapter,
		SIGNAL(Mclicked(QString)),
		this,
		SLOT(statechange_chapter_to_songlist(QString))
	);
	this->addCell(key, newchapter, chapterstate);
	ChapterList->insert(key, newchapter);
	ChapterNumList->insert(*MMainWindow::ChapterSum, key);
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

void MMainWindow::setCenterChapter(qint64 centerchapter)
{
	delete CenterChapter;
	CenterChapter = new qint64(centerchapter);
}

QMap<qint64, QString>*& MMainWindow::chapterNumList()
{
	return ChapterNumList;
}

qint64 MMainWindow::centerChapter()
{
	return *CenterChapter;
}