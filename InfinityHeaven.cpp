#include"InfinityHeaven.h"

InfinityHeaven_Class::InfinityHeaven_Class(MWidget* parent)
	: QObject(parent)
{
	QPixmap backImage(".\\Grass.png");
	parent->setBackImage(backImage);
	parent->setShowBackImage(true);
	parent->setShowBackBackImage(true);
	parent->setBackCoverColor(QColor(0, 0, 0, 196));
	parent->checkDotList()->insert("M", new MCheckDot(parent));
	parent->checkDotList()->value("M")->setKey(Qt::Key_M, "M");
	parent->checkDotList()->value("M")->setKeyVisuable(true);
	parent->checkDotList()->value("M")->addNote(4000, 4375, click);
	parent->checkDotList()->value("M")->addNote(4375, 4750, click);
	parent->checkDotList()->value("M")->addNote(4750, 5500, click);
	parent->checkDotList()->value("M")->addNote(5500, 5750, click);
	parent->checkDotList()->value("M")->addNote(5750, 6000, click);
	parent->checkDotList()->value("M")->addNote(6000, 6374, click);
	parent->checkDotList()->value("M")->addNote(6374, 6750, click);
	parent->checkDotList()->value("M")->addNote(6750, 7500, click);
	parent->checkDotList()->value("M")->addNote(7500, 7750, click);
	parent->checkDotList()->value("M")->addNote(7750, 8000, click);
	parent->checkDotList()->value("M")->addNote(8000, 8375, click);
	parent->checkDotList()->value("M")->addNote(8375, 8750, click);
	parent->checkDotList()->value("M")->addNote(8750, 9500, click);
	parent->checkDotList()->value("M")->addNote(9500, 9750, click);
	parent->checkDotList()->value("M")->addNote(9750, 10000, click);
	parent->checkDotList()->value("M")->addNote(10000, 10375, click);
	parent->checkDotList()->value("M")->addNote(10375, 10750, click);
	parent->checkDotList()->value("M")->addNote(10750, 11000, click);
	parent->checkDotList()->value("M")->addNote(11000, 11250, click);
	parent->checkDotList()->value("M")->addNote(11250, 11500, click);
	parent->checkDotList()->value("M")->addNote(11500, 11750, click);
	parent->checkDotList()->value("M")->addNote(11750, 12000, click);
	parent->checkDotList()->value("M")->addNote(12000, 12375, click);
	parent->checkDotList()->value("M")->addNote(12375, 12750, click);
	parent->checkDotList()->value("M")->addNote(12750, 13500, click);
	parent->checkDotList()->value("M")->addNote(13500, 14000, click);
	parent->checkDotList()->value("M")->addNote(14000, 14375, click);
	parent->checkDotList()->value("M")->addNote(14375, 14750, click);
	parent->checkDotList()->value("M")->addNote(14750, 15000, click);
	parent->checkDotList()->value("M")->addNote(15000, 15250, click);
	parent->checkDotList()->value("M")->addNote(15250, 15500, click);
	parent->checkDotList()->value("M")->addNote(15500, 15750, click);
	parent->checkDotList()->value("M")->addNote(15750, 16000, click);
	parent->checkDotList()->value("M")->addNote(16000, 16375, click);
	parent->checkDotList()->value("M")->addNote(16375, 16750, click);
	parent->checkDotList()->value("M")->addNote(16750, 17000, click);
	parent->checkDotList()->value("M")->addNote(17000, 17375, click);
	parent->checkDotList()->value("M")->addNote(17375, 17750, click);
	parent->checkDotList()->value("M")->addNote(17750, 18000, click);
	parent->checkDotList()->value("M")->addNote(18000, 18375, click);
	parent->checkDotList()->value("M")->addNote(18375, 18750, click);
	parent->checkDotList()->value("M")->addNote(18750, 19000, click);
	parent->checkDotList()->value("M")->addNote(19000, 19250, click);
	parent->checkDotList()->value("M")->addNote(19250, 19500, click);
	parent->checkDotList()->value("M")->addNote(19500, 19750, click);
	parent->checkDotList()->value("M")->addNote(19750, 20000, click);
	parent->checkDotList()->value("M")->addNote(20000, 20375, click);
	parent->checkDotList()->value("M")->addNote(20375, 20750, click);
	parent->checkDotList()->value("M")->addNote(20750, 21500, click);
	parent->checkDotList()->value("M")->addNote(21500, 21750, click);
	parent->checkDotList()->value("M")->addNote(21750, 22000, click);
	parent->checkDotList()->value("M")->addNote(22000, 22375, click);
	parent->checkDotList()->value("M")->addNote(22375, 22750, click);
	parent->checkDotList()->value("M")->addNote(22750, 23750, click);
	parent->checkDotList()->value("M")->addNote(23750, 24000, click);
	parent->checkDotList()->value("M")->addNote(24000, 24375, click);
	parent->checkDotList()->value("M")->addNote(24375, 24750, click);
	parent->checkDotList()->value("M")->addNote(24750, 25500, click);
	parent->checkDotList()->value("M")->addNote(25500, 26000, click);
	parent->checkDotList()->value("M")->addNote(26000, 26375, click);
	parent->checkDotList()->value("M")->addNote(26375, 26750, click);
	parent->checkDotList()->value("M")->addNote(26750, 27000, click);
	parent->checkDotList()->value("M")->addNote(27000, 27250, click);
	parent->checkDotList()->value("M")->addNote(27250, -1 , click);
	parent->checkDotList()->value("M")->setPoint(960, 700);
	parent->checkDotList()->value("M")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("M")->setNextTime(4000);
	parent->setDelay(3500);
	parent->checkDotList()->value("M")->setSpeed(500);
	parent->checkDotList()->value("M")->show();
	parent->repaint();
	parent->setMusicPath(".\\InfinityHeaven.ogg");
	this->parent = parent;
}

InfinityHeaven_Class::~InfinityHeaven_Class()
{}

void TestDemo_InfinityHeaven(MOONIGHT_Qt* w)
{
	InfinityHeaven_Class* IF = new InfinityHeaven_Class(w->Ui()->central);
	QCoreApplication::processEvents();
	w->Ui()->central->setTime(0);
	w->Ui()->mainTime->start();
	w->Ui()->litTime->start();
	w->Ui()->central->disTime()->restart();
	qDebug() << "MOONOTUSystem::_Message_::Timer of central start";
	w->connect
	(
		w->Ui()->mainTime,
		SIGNAL(timeout()),
		IF,
		SLOT(InfinityHeaven()),
		Qt::DirectConnection
	);
	w->connect
	(
		w->Ui()->litTime,
		SIGNAL(timeout()),
		w->Ui()->central,
		SLOT(repaint()),
		Qt::DirectConnection
	);
	w->Ui()->central->show();
}

void InfinityHeaven_Class::InfinityHeaven()
{
	parent->playMusic();
	parent->repaint();
}

MWidget*& InfinityHeaven_Class::Parent()
{
	return parent;
}






























































































































