#include"InfinityHeaven.h"

InfinityHeaven_Class::InfinityHeaven_Class(MWidget* parent)
	: QObject(parent)
{
	parent->addToTitle("Infinity Heaven");
	QPixmap backImage(".\\Grass.png");
	parent->setShowLogo(false);
	parent->setBackImage(backImage);
	parent->setShowBackImage(true);
	parent->setShowBackBackImage(true);
	parent->setBackCoverColor(QColor(0, 0, 0, 196));

	parent->setMusicPath(".\\InfinityHeaven.ogg");

	parent->checkDotList()->insert("V2", new MCheckDot(parent));
	parent->checkDotList()->value("V2")->setKey(Qt::Key_V, "V");
	parent->checkDotList()->value("V2")->setKeyVisuable(true);

	parent->checkDotList()->insert("V", new MCheckDot(parent));
	parent->checkDotList()->value("V")->setKey(Qt::Key_V, "V");
	parent->checkDotList()->value("V")->setKeyVisuable(true);

	parent->checkDotList()->insert("M", new MCheckDot(parent));
	parent->checkDotList()->value("M")->setKey(Qt::Key_M, "M");
	parent->checkDotList()->value("M")->setKeyVisuable(true);

	parent->checkDotList()->value("M")->setNextTime(275);

	parent->checkDotList()->value("V")->setNextTime(24562.5);

	parent->checkDotList()->value("V2")->setNextTime(24562.5);

	parent->checkDotList()->value("M")->addNote(275,		937.5, click);
	parent->checkDotList()->value("M")->addNote(937.5,		1875, click);
	parent->checkDotList()->value("M")->addNote(1875,		2437.5, click);
	parent->checkDotList()->value("M")->addNote(2437.5,		3375, click);
	parent->checkDotList()->value("M")->addNote(3375,		3937.5, click);
	parent->checkDotList()->value("M")->addNote(3937.5,		4875, click);
	parent->checkDotList()->value("M")->addNote(4875,		5437.5, click);
	parent->checkDotList()->value("M")->addNote(5437.5,		5625, click);
	parent->checkDotList()->value("M")->addNote(5625,		5812.5, click);
	parent->checkDotList()->value("M")->addNote(5812.5,		6000, click);
	parent->checkDotList()->value("M")->addNote(6000,		6187.5, click);
	parent->checkDotList()->value("M")->addNote(6187.5,		6375, click);
	parent->checkDotList()->value("M")->addNote(6375,		6937.5, click);
	parent->checkDotList()->value("M")->addNote(6937.5,		7875, click);
	parent->checkDotList()->value("M")->addNote(7875,		8437.5, click);
	parent->checkDotList()->value("M")->addNote(8437.5,		8625, click);
	parent->checkDotList()->value("M")->addNote(8625,		8812.5, click);
	parent->checkDotList()->value("M")->addNote(8812.5,		9000, click);
	parent->checkDotList()->value("M")->addNote(9000,		9187.5, click);
	parent->checkDotList()->value("M")->addNote(9187.5,		9375, click);
	parent->checkDotList()->value("M")->addNote(9375,		9937.5, click);
	parent->checkDotList()->value("M")->addNote(9937.5,		10875, click);
	parent->checkDotList()->value("M")->addNote(10875,		11437.5, click);
	parent->checkDotList()->value("M")->addNote(11437.5,	11625, click);
	parent->checkDotList()->value("M")->addNote(11625,		11812.5, click);
	parent->checkDotList()->value("M")->addNote(11812.5,	12000, click);
	parent->checkDotList()->value("M")->addNote(12000,		12187.5, click);
	parent->checkDotList()->value("M")->addNote(12187.5,	12375, click);
	parent->checkDotList()->value("M")->addNote(12375,		12656.25, click);
	parent->checkDotList()->value("M")->addNote(12656.25,	12937.5, click);
	parent->checkDotList()->value("M")->addNote(12937.5,	13125, click);
	parent->checkDotList()->value("M")->addNote(13125,		13312.5, click);
	parent->checkDotList()->value("M")->addNote(13312.5,	13500, click);
	parent->checkDotList()->value("M")->addNote(13500,		13875, click);
	parent->checkDotList()->value("M")->addNote(13875,		14156.25, click);
	parent->checkDotList()->value("M")->addNote(14156.25,	14437.5, click);
	parent->checkDotList()->value("M")->addNote(14437.5,	14625, click);
	parent->checkDotList()->value("M")->addNote(14625,		14812.5, click);
	parent->checkDotList()->value("M")->addNote(14812.5,	15000, click);
	parent->checkDotList()->value("M")->addNote(15000,		15375, click);
	parent->checkDotList()->value("M")->addNote(15375,		15656.25, click);
	parent->checkDotList()->value("M")->addNote(15656.25,	15937.5, click);
	parent->checkDotList()->value("M")->addNote(15937.5,	16125, click);
	parent->checkDotList()->value("M")->addNote(16125,		16312.5, click);
	parent->checkDotList()->value("M")->addNote(16312.5,	16500, click);
	parent->checkDotList()->value("M")->addNote(16500, 16687.5, click);
	parent->checkDotList()->value("M")->addNote(16687.5, 17062.5, click);
	parent->checkDotList()->value("M")->addNote(17062.5, 17343.75, click);
	parent->checkDotList()->value("M")->addNote(17343.75, 17625, click);
	parent->checkDotList()->value("M")->addNote(17625, 17812.5, click);
	parent->checkDotList()->value("M")->addNote(17812.5, 18000, click);
	parent->checkDotList()->value("M")->addNote(18000, 18187.5, click);
	parent->checkDotList()->value("M")->addNote(18187.5, 18562.5, click);
	parent->checkDotList()->value("M")->addNote(18562.5, 18843.75, click);
	parent->checkDotList()->value("M")->addNote(18843.75, 19125, click);
	parent->checkDotList()->value("M")->addNote(19125, 19312.5, click);
	parent->checkDotList()->value("M")->addNote(19312.5, 19500, click);
	parent->checkDotList()->value("M")->addNote(19500, 19687.5, click);
	parent->checkDotList()->value("M")->addNote(19687.5, 20062.5, click);
	parent->checkDotList()->value("M")->addNote(20062.5, 20343.75, click);
	parent->checkDotList()->value("M")->addNote(20343.75, 20625, click);
	parent->checkDotList()->value("M")->addNote(20625, 20812.5, click);
	parent->checkDotList()->value("M")->addNote(20812.5, 21000, click);
	parent->checkDotList()->value("M")->addNote(21000, 21187.5, click);
	parent->checkDotList()->value("M")->addNote(21187.5, 21375, click);
	parent->checkDotList()->value("M")->addNote(21375, 21750, click);
	parent->checkDotList()->value("M")->addNote(21750, 23250, click);
	parent->checkDotList()->value("M")->addNote(23250, 23625, click);
	parent->checkDotList()->value("M")->addNote(23625, 24000, click);
	parent->checkDotList()->value("M")->addNote(24000, 24375, click);
	parent->checkDotList()->value("M")->addNote(24375, 29250, click);

	parent->checkDotList()->value("V2")->addNote(24562.5, 30750, hold, 29062.5 - 24562.5);

	parent->checkDotList()->value("V")->addNote(24562.5, 24750, cat);
	parent->checkDotList()->value("V")->addNote(24750, 24843.75, cat);
	parent->checkDotList()->value("V")->addNote(24843.75, 24937.5, cat);
	parent->checkDotList()->value("V")->addNote(24937.5, 25125, cat);
	parent->checkDotList()->value("V")->addNote(25125, 25218.75, cat);
	parent->checkDotList()->value("V")->addNote(25218.75, 25312.5, cat);
	parent->checkDotList()->value("V")->addNote(25312.5, 25500, cat);
	parent->checkDotList()->value("V")->addNote(25500, 25593.75, cat);
	parent->checkDotList()->value("V")->addNote(25593.75, 25687.5, cat);
	parent->checkDotList()->value("V")->addNote(25687.5, 25875, cat);
	parent->checkDotList()->value("V")->addNote(25875, 25968.75, cat);
	parent->checkDotList()->value("V")->addNote(25968.75, 26062.5, cat);
	parent->checkDotList()->value("V")->addNote(26062.5, 26250, cat);
	parent->checkDotList()->value("V")->addNote(26250, 26343.75, cat);
	parent->checkDotList()->value("V")->addNote(26343.75, 26437.5, cat);
	parent->checkDotList()->value("V")->addNote(26437.5, 26625, cat);
	parent->checkDotList()->value("V")->addNote(26625, 26718.75, cat);
	parent->checkDotList()->value("V")->addNote(26718.75, 26812.5, cat);
	parent->checkDotList()->value("V")->addNote(26812.5, 27000, cat);
	parent->checkDotList()->value("V")->addNote(27000, 27093.75, cat);
	parent->checkDotList()->value("V")->addNote(27093.75, 27187.5, cat);
	parent->checkDotList()->value("V")->addNote(27187.5, 27375, cat);
	parent->checkDotList()->value("V")->addNote(27375, 27468.75, cat);
	parent->checkDotList()->value("V")->addNote(27468.75, 27562.5, cat);
	parent->checkDotList()->value("V")->addNote(27562.5, 27750, cat);
	parent->checkDotList()->value("V")->addNote(27750, 27843.75, cat);
	parent->checkDotList()->value("V")->addNote(27843.75, 27937.5, cat);
	parent->checkDotList()->value("V")->addNote(27937.5, 28125, cat);
	parent->checkDotList()->value("V")->addNote(28125, 28218.75, cat);
	parent->checkDotList()->value("V")->addNote(28218.75, 28312.5, cat);
	parent->checkDotList()->value("V")->addNote(28312.5, 28500, cat);
	parent->checkDotList()->value("V")->addNote(28500, 28593.75, cat);
	parent->checkDotList()->value("V")->addNote(28593.75, 28687.5, cat);
	parent->checkDotList()->value("V")->addNote(28687.5, 28875, cat);
	parent->checkDotList()->value("V")->addNote(28875, 28968.75, cat);
	parent->checkDotList()->value("V")->addNote(28968.75, 29062.5, cat);
	parent->checkDotList()->value("V")->addNote(29062.5, 30750, cat);

	parent->checkDotList()->value("M")->addNote(29250, 29437.5, click);
	parent->checkDotList()->value("M")->addNote(29437.5, 29625, click);
	parent->checkDotList()->value("M")->addNote(29625, 29812.5, click);
	parent->checkDotList()->value("M")->addNote(29812.5, 30000, click);
	parent->checkDotList()->value("M")->addNote(30000, 30187.5, click);
	parent->checkDotList()->value("M")->addNote(30187.5, 30375, click);
	parent->checkDotList()->value("M")->addNote(30375, 30562.5, click);
	parent->checkDotList()->value("M")->addNote(30562.5, 35437.5, click);

	parent->checkDotList()->value("V2")->addNote(30750, -1, hold, 35343.75 - 30750);

	parent->checkDotList()->value("V")->addNote(30750, 30843.75, cat);
	parent->checkDotList()->value("V")->addNote(30843.75, 30937.5, cat);
	parent->checkDotList()->value("V")->addNote(30937.5, 31125, cat);
	parent->checkDotList()->value("V")->addNote(31125, 31218.75, cat);
	parent->checkDotList()->value("V")->addNote(31218.75, 31312.5, cat);
	parent->checkDotList()->value("V")->addNote(31312.5, 31500, cat);
	parent->checkDotList()->value("V")->addNote(31500, 31593.75, cat);
	parent->checkDotList()->value("V")->addNote(31593.75, 31687.5, cat);
	parent->checkDotList()->value("V")->addNote(31687.5, 31875, cat);
	parent->checkDotList()->value("V")->addNote(31875, 31968.75, cat);
	parent->checkDotList()->value("V")->addNote(31968.75, 32062.5, cat);
	parent->checkDotList()->value("V")->addNote(32062.5, 32250, cat);
	parent->checkDotList()->value("V")->addNote(32250, 32343.75, cat);
	parent->checkDotList()->value("V")->addNote(32343.75, 32437.5, cat);
	parent->checkDotList()->value("V")->addNote(32437.5, 32625, cat);
	parent->checkDotList()->value("V")->addNote(32625, 32718.75, cat);
	parent->checkDotList()->value("V")->addNote(32718.75, 32812.5, cat);
	parent->checkDotList()->value("V")->addNote(32812.5, 33000, cat);
	parent->checkDotList()->value("V")->addNote(33000, 33093.75, cat);
	parent->checkDotList()->value("V")->addNote(33093.75, 33187.5, cat);
	parent->checkDotList()->value("V")->addNote(33187.5, 33375, cat);
	parent->checkDotList()->value("V")->addNote(33375, 33468.75, cat);
	parent->checkDotList()->value("V")->addNote(33468.75, 33562.5, cat);
	parent->checkDotList()->value("V")->addNote(33562.5, 33750, cat);
	parent->checkDotList()->value("V")->addNote(33750, 33843.75, cat);
	parent->checkDotList()->value("V")->addNote(33843.75, 33937.5, cat);
	parent->checkDotList()->value("V")->addNote(33937.5, 34125, cat);
	parent->checkDotList()->value("V")->addNote(34125, 34218.75, cat);
	parent->checkDotList()->value("V")->addNote(34218.75, 34312.5, cat);
	parent->checkDotList()->value("V")->addNote(34312.5, 34500, cat);
	parent->checkDotList()->value("V")->addNote(34500, 34593.75, cat);
	parent->checkDotList()->value("V")->addNote(34593.75, 34687.5, cat);
	parent->checkDotList()->value("V")->addNote(34687.5, 34875, cat);
	parent->checkDotList()->value("V")->addNote(34875, 34968.75, cat);
	parent->checkDotList()->value("V")->addNote(34968.75, 35062.5, cat);
	parent->checkDotList()->value("V")->addNote(35062.5, 35250, cat);
	parent->checkDotList()->value("V")->addNote(35250, 35343.75, cat);
	parent->checkDotList()->value("V")->addNote(35343.75, -1, cat);

	parent->checkDotList()->value("M")->addNote(35437.5, 35625, click);
	parent->checkDotList()->value("M")->addNote(35625, 35812.5, click);
	parent->checkDotList()->value("M")->addNote(35812.5, 36000, click);
	parent->checkDotList()->value("M")->addNote(36000, 36187.5, click);
	parent->checkDotList()->value("M")->addNote(36187.5, 36375, click);
	parent->checkDotList()->value("M")->addNote(36375, 36562.5, click);
	parent->checkDotList()->value("M")->addNote(36562.5, 36750, click);
	parent->checkDotList()->value("M")->addNote(36750, 36937.5, click);
	parent->checkDotList()->value("M")->addNote(36937.5, 37125, click);
	parent->checkDotList()->value("M")->addNote(37125, 37406.25, click);
	parent->checkDotList()->value("M")->addNote(37406.25, 37687.5, click);
	parent->checkDotList()->value("M")->addNote(37687.5, 38062.5, click);
	parent->checkDotList()->value("M")->addNote(38062.5, 38250, click);
	parent->checkDotList()->value("M")->addNote(38250, 38437.5, click);
	parent->checkDotList()->value("M")->addNote(38437.5, 38625, click);
	parent->checkDotList()->value("M")->addNote(38625, 38812.5, click);
	parent->checkDotList()->value("M")->addNote(38812.5, 39093.75, click);
	parent->checkDotList()->value("M")->addNote(39093.75, 39375, click);
	parent->checkDotList()->value("M")->addNote(39375, 39750, click);
	parent->checkDotList()->value("M")->addNote(39750, 39937.5, click);
	parent->checkDotList()->value("M")->addNote(39937.5, 40125, click);
	parent->checkDotList()->value("M")->addNote(40125, 40312.5, click);
	parent->checkDotList()->value("M")->addNote(40312.5, 40500, click);
	parent->checkDotList()->value("M")->addNote(40500, 40781.25, click);
	parent->checkDotList()->value("M")->addNote(40781.25, 41062.5, click);
	parent->checkDotList()->value("M")->addNote(41062.5, 41250, click);
	parent->checkDotList()->value("M")->addNote(41250, 41437.5, click);
	parent->checkDotList()->value("M")->addNote(41437.5, 41625, click);
	parent->checkDotList()->value("M")->addNote(41625, 41812.5, click);
	parent->checkDotList()->value("M")->addNote(41812.5, 42093.75, click);
	parent->checkDotList()->value("M")->addNote(42093.75, 42375, click);
	parent->checkDotList()->value("M")->addNote(42375, 42562.5, click);
	parent->checkDotList()->value("M")->addNote(42562.5, 42750, click);
	parent->checkDotList()->value("M")->addNote(42750, 42937.5, click);
	parent->checkDotList()->value("M")->addNote(42937.5, 43125, click);
	parent->checkDotList()->value("M")->addNote(43125, 43406.25, click);
	parent->checkDotList()->value("M")->addNote(43406.25, 43687.5, click);
	parent->checkDotList()->value("M")->addNote(43687.5, 44062.5, click);
	parent->checkDotList()->value("M")->addNote(44062.5, 44250, click);
	parent->checkDotList()->value("M")->addNote(44250, 44437.5, click);
	parent->checkDotList()->value("M")->addNote(44437.5, 44625, click);
	parent->checkDotList()->value("M")->addNote(44625, 44812.5, click);
	parent->checkDotList()->value("M")->addNote(44812.5, 45093.75, click);
	parent->checkDotList()->value("M")->addNote(45093.75, 45375, click);
	parent->checkDotList()->value("M")->addNote(45375, 45750, click);
	parent->checkDotList()->value("M")->addNote(45750, 45937.5, click);
	parent->checkDotList()->value("M")->addNote(45937.5, 46125, click);
	parent->checkDotList()->value("M")->addNote(46125, 46312.5, click);
	parent->checkDotList()->value("M")->addNote(46312.5, 46500, click);
	parent->checkDotList()->value("M")->addNote(46500, 46781.25, click);
	parent->checkDotList()->value("M")->addNote(46781.25, 47062.5, click);
	parent->checkDotList()->value("M")->addNote(47062.5, 47250, click);
	parent->checkDotList()->value("M")->addNote(47250, 47437.5, click);
	parent->checkDotList()->value("M")->addNote(47437.5, 47625, click);
	parent->checkDotList()->value("M")->addNote(47625, 47812.5, click);
	parent->checkDotList()->value("M")->addNote(47812.5, 48093.75, click);
	parent->checkDotList()->value("M")->addNote(48093.75, 48375, click);
	parent->checkDotList()->value("M")->addNote(48375, 48750, click);
	parent->checkDotList()->value("M")->addNote(48750, 48937.5, click);
	parent->checkDotList()->value("M")->addNote(48937.5, 49125, click);
	parent->checkDotList()->value("M")->addNote(49125, -1, click);

	parent->checkDotList()->value("M")->setPoint(1700, 900);
	parent->checkDotList()->value("M")->dotLine()->setDownVisuable(false);

	parent->checkDotList()->value("V")->setPoint(1500, 900);
	parent->checkDotList()->value("V")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("V")->dotLine()->setAngel(-90);

	parent->checkDotList()->value("V2")->setPoint(1500, 900);
	parent->checkDotList()->value("V2")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("V2")->dotLine()->setAngel(-90);

	parent->setGapDelay(3000);
	parent->setFixDelay(100);

	parent->checkDotList()->value("M")->setSpeed(900);
	parent->checkDotList()->value("V")->setSpeed(900);
	parent->checkDotList()->value("M")->show();
	parent->checkDotList()->value("M")->show();

	parent->setMusicName("Infinity Heaven");

	parent->setover();//设定结束标志，必须写在构造函数最后，parent->repaint()之前

	parent->repaint();
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
































































































































































































































































































































































































































































































































































































































































































































































































