#include"InfinityHeaven.h"

InfinityHeaven_Class::InfinityHeaven_Class(MWidget* parent)
	: QObject(parent)
{
	QPixmap backImage(".\\Grass.png");
	parent->setBackImage(backImage);
	parent->setShowBackImage(true);
	parent->setShowBackBackImage(true);
	parent->setBackCoverColor(QColor(0, 0, 0, 196));
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