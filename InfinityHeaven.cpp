#include"InfinityHeaven.h"

InfinityHeaven_Class::InfinityHeaven_Class(MWidget* parent)
	: QObject(parent)
{
	parent->addToTitle("Infinity Heaven");
	QPixmap backImage(".\\Infinity_Heaven_Phigros.png");
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

	MNote::setAutoNoteType(click);

	parent->checkDotList()->value("M")->addNote(275);
	parent->checkDotList()->value("M")->addNote(937.5);
	parent->checkDotList()->value("M")->addNote(1875);
	parent->checkDotList()->value("M")->addNote(2437.5);
	parent->checkDotList()->value("M")->addNote(3375);
	parent->checkDotList()->value("M")->addNote(3937.5);
	parent->checkDotList()->value("M")->addNote(4875);
	parent->checkDotList()->value("M")->addNote(5437.5);
	parent->checkDotList()->value("M")->addNote(5625);
	parent->checkDotList()->value("M")->addNote(5812.5);
	parent->checkDotList()->value("M")->addNote(6000);
	parent->checkDotList()->value("M")->addNote(6187.5);
	parent->checkDotList()->value("M")->addNote(6375);
	parent->checkDotList()->value("M")->addNote(6937.5);
	parent->checkDotList()->value("M")->addNote(7875);
	parent->checkDotList()->value("M")->addNote(8437.5);
	parent->checkDotList()->value("M")->addNote(8625);
	parent->checkDotList()->value("M")->addNote(8812.5);
	parent->checkDotList()->value("M")->addNote(9000);
	parent->checkDotList()->value("M")->addNote(9187.5);
	parent->checkDotList()->value("M")->addNote(9375);
	parent->checkDotList()->value("M")->addNote(9937.5);
	parent->checkDotList()->value("M")->addNote(10875);
	parent->checkDotList()->value("M")->addNote(11437.5);
	parent->checkDotList()->value("M")->addNote(11625);
	parent->checkDotList()->value("M")->addNote(11812.5);
	parent->checkDotList()->value("M")->addNote(12000);
	parent->checkDotList()->value("M")->addNote(12187.5);
	parent->checkDotList()->value("M")->addNote(12375);
	parent->checkDotList()->value("M")->addNote(12656.25);
	parent->checkDotList()->value("M")->addNote(12937.5);
	parent->checkDotList()->value("M")->addNote(13125);
	parent->checkDotList()->value("M")->addNote(13312.5);
	parent->checkDotList()->value("M")->addNote(13500);
	parent->checkDotList()->value("M")->addNote(13875);
	parent->checkDotList()->value("M")->addNote(14156.25);
	parent->checkDotList()->value("M")->addNote(14437.5);
	parent->checkDotList()->value("M")->addNote(14625);
	parent->checkDotList()->value("M")->addNote(14812.5);
	parent->checkDotList()->value("M")->addNote(15000);
	parent->checkDotList()->value("M")->addNote(15375);
	parent->checkDotList()->value("M")->addNote(15656.25);
	parent->checkDotList()->value("M")->addNote(15937.5);
	parent->checkDotList()->value("M")->addNote(16125);
	parent->checkDotList()->value("M")->addNote(16312.5);
	parent->checkDotList()->value("M")->addNote(16500);
	parent->checkDotList()->value("M")->addNote(16687.5);
	parent->checkDotList()->value("M")->addNote(17062.5);
	parent->checkDotList()->value("M")->addNote(17343.75);
	parent->checkDotList()->value("M")->addNote(17625);
	parent->checkDotList()->value("M")->addNote(17812.5);
	parent->checkDotList()->value("M")->addNote(18000);
	parent->checkDotList()->value("M")->addNote(18187.5);
	parent->checkDotList()->value("M")->addNote(18562.5);
	parent->checkDotList()->value("M")->addNote(18843.75);
	parent->checkDotList()->value("M")->addNote(19125);
	parent->checkDotList()->value("M")->addNote(19312.5);
	parent->checkDotList()->value("M")->addNote(19500);
	parent->checkDotList()->value("M")->addNote(19687.5);
	parent->checkDotList()->value("M")->addNote(20062.5);
	parent->checkDotList()->value("M")->addNote(20343.75);
	parent->checkDotList()->value("M")->addNote(20625);
	parent->checkDotList()->value("M")->addNote(20812.5);
	parent->checkDotList()->value("M")->addNote(21000);
	parent->checkDotList()->value("M")->addNote(21187.5);
	parent->checkDotList()->value("M")->addNote(21375);
	parent->checkDotList()->value("M")->addNote(21750);
	parent->checkDotList()->value("M")->addNote(23250);
	parent->checkDotList()->value("M")->addNote(23625);
	parent->checkDotList()->value("M")->addNote(24000);
	parent->checkDotList()->value("M")->addNote(24375);

	parent->checkDotList()->value("V2")->addNote(24562.5, hold, 29062.5 - 24562.5);

	MNote::setAutoNoteType(cat);

	parent->checkDotList()->value("V")->addNote(24562.5);
	parent->checkDotList()->value("V")->addNote(24750);
	parent->checkDotList()->value("V")->addNote(24843.75);
	parent->checkDotList()->value("V")->addNote(24937.5);
	parent->checkDotList()->value("V")->addNote(25125);
	parent->checkDotList()->value("V")->addNote(25218.75);
	parent->checkDotList()->value("V")->addNote(25312.5);
	parent->checkDotList()->value("V")->addNote(25500);
	parent->checkDotList()->value("V")->addNote(25593.75);
	parent->checkDotList()->value("V")->addNote(25687.5);
	parent->checkDotList()->value("V")->addNote(25875);
	parent->checkDotList()->value("V")->addNote(25968.75);
	parent->checkDotList()->value("V")->addNote(26062.5);
	parent->checkDotList()->value("V")->addNote(26250);
	parent->checkDotList()->value("V")->addNote(26343.75);
	parent->checkDotList()->value("V")->addNote(26437.5);
	parent->checkDotList()->value("V")->addNote(26625);
	parent->checkDotList()->value("V")->addNote(26718.75);
	parent->checkDotList()->value("V")->addNote(26812.5);
	parent->checkDotList()->value("V")->addNote(27000);
	parent->checkDotList()->value("V")->addNote(27093.75);
	parent->checkDotList()->value("V")->addNote(27187.5);
	parent->checkDotList()->value("V")->addNote(27375);
	parent->checkDotList()->value("V")->addNote(27468.75);
	parent->checkDotList()->value("V")->addNote(27562.5);
	parent->checkDotList()->value("V")->addNote(27750);
	parent->checkDotList()->value("V")->addNote(27843.75);
	parent->checkDotList()->value("V")->addNote(27937.5);
	parent->checkDotList()->value("V")->addNote(28125);
	parent->checkDotList()->value("V")->addNote(28218.75);
	parent->checkDotList()->value("V")->addNote(28312.5);
	parent->checkDotList()->value("V")->addNote(28500);
	parent->checkDotList()->value("V")->addNote(28593.75);
	parent->checkDotList()->value("V")->addNote(28687.5);
	parent->checkDotList()->value("V")->addNote(28875);
	parent->checkDotList()->value("V")->addNote(28968.75);
	parent->checkDotList()->value("V")->addNote(29062.5);

	MNote::setAutoNoteType(click);

	parent->checkDotList()->value("M")->addNote(29250);
	parent->checkDotList()->value("M")->addNote(29437.5);
	parent->checkDotList()->value("M")->addNote(29625);
	parent->checkDotList()->value("M")->addNote(29812.5);
	parent->checkDotList()->value("M")->addNote(30000);
	parent->checkDotList()->value("M")->addNote(30187.5);
	parent->checkDotList()->value("M")->addNote(30375);
	parent->checkDotList()->value("M")->addNote(30562.5);

	parent->checkDotList()->value("V2")->addNote(30750, hold, 35343.75 - 30750);

	MNote::setAutoNoteType(cat);

	parent->checkDotList()->value("V")->addNote(30750);
	parent->checkDotList()->value("V")->addNote(30843.75);
	parent->checkDotList()->value("V")->addNote(30937.5);
	parent->checkDotList()->value("V")->addNote(31125);
	parent->checkDotList()->value("V")->addNote(31218.75);
	parent->checkDotList()->value("V")->addNote(31312.5);
	parent->checkDotList()->value("V")->addNote(31500);
	parent->checkDotList()->value("V")->addNote(31593.75);
	parent->checkDotList()->value("V")->addNote(31687.5);
	parent->checkDotList()->value("V")->addNote(31875);
	parent->checkDotList()->value("V")->addNote(31968.75);
	parent->checkDotList()->value("V")->addNote(32062.5);
	parent->checkDotList()->value("V")->addNote(32250);
	parent->checkDotList()->value("V")->addNote(32343.75);
	parent->checkDotList()->value("V")->addNote(32437.5);
	parent->checkDotList()->value("V")->addNote(32625);
	parent->checkDotList()->value("V")->addNote(32718.75);
	parent->checkDotList()->value("V")->addNote(32812.5);
	parent->checkDotList()->value("V")->addNote(33000);
	parent->checkDotList()->value("V")->addNote(33093.75);
	parent->checkDotList()->value("V")->addNote(33187.5);
	parent->checkDotList()->value("V")->addNote(33375);
	parent->checkDotList()->value("V")->addNote(33468.75);
	parent->checkDotList()->value("V")->addNote(33562.5);
	parent->checkDotList()->value("V")->addNote(33750);
	parent->checkDotList()->value("V")->addNote(33843.75);
	parent->checkDotList()->value("V")->addNote(33937.5);
	parent->checkDotList()->value("V")->addNote(34125);
	parent->checkDotList()->value("V")->addNote(34218.75);
	parent->checkDotList()->value("V")->addNote(34312.5);
	parent->checkDotList()->value("V")->addNote(34500);
	parent->checkDotList()->value("V")->addNote(34593.75);
	parent->checkDotList()->value("V")->addNote(34687.5);
	parent->checkDotList()->value("V")->addNote(34875);
	parent->checkDotList()->value("V")->addNote(34968.75);
	parent->checkDotList()->value("V")->addNote(35062.5);
	parent->checkDotList()->value("V")->addNote(35250);
	parent->checkDotList()->value("V")->addNote(35343.75);

	MNote::setAutoNoteType(click);

	parent->checkDotList()->value("M")->addNote(35437.5);
	parent->checkDotList()->value("M")->addNote(35625);
	parent->checkDotList()->value("M")->addNote(35812.5);
	parent->checkDotList()->value("M")->addNote(36000);
	parent->checkDotList()->value("M")->addNote(36187.5);
	parent->checkDotList()->value("M")->addNote(36375);
	parent->checkDotList()->value("M")->addNote(36562.5);
	parent->checkDotList()->value("M")->addNote(36750);
	parent->checkDotList()->value("M")->addNote(36937.5);
	parent->checkDotList()->value("M")->addNote(37125);
	parent->checkDotList()->value("M")->addNote(37406.25);
	parent->checkDotList()->value("M")->addNote(37687.5);
	parent->checkDotList()->value("M")->addNote(38062.5);
	parent->checkDotList()->value("M")->addNote(38250);
	parent->checkDotList()->value("M")->addNote(38437.5);
	parent->checkDotList()->value("M")->addNote(38625);
	parent->checkDotList()->value("M")->addNote(38812.5);
	parent->checkDotList()->value("M")->addNote(39093.75);
	parent->checkDotList()->value("M")->addNote(39375);
	parent->checkDotList()->value("M")->addNote(39750);
	parent->checkDotList()->value("M")->addNote(39937.5);
	parent->checkDotList()->value("M")->addNote(40125);
	parent->checkDotList()->value("M")->addNote(40312.5);
	parent->checkDotList()->value("M")->addNote(40500);
	parent->checkDotList()->value("M")->addNote(40781.25);
	parent->checkDotList()->value("M")->addNote(41062.5);
	parent->checkDotList()->value("M")->addNote(41250);
	parent->checkDotList()->value("M")->addNote(41437.5);
	parent->checkDotList()->value("M")->addNote(41625);
	parent->checkDotList()->value("M")->addNote(41812.5);
	parent->checkDotList()->value("M")->addNote(42093.75);
	parent->checkDotList()->value("M")->addNote(42375);
	parent->checkDotList()->value("M")->addNote(42562.5);
	parent->checkDotList()->value("M")->addNote(42750);
	parent->checkDotList()->value("M")->addNote(42937.5);
	parent->checkDotList()->value("M")->addNote(43125);
	parent->checkDotList()->value("M")->addNote(43406.25);
	parent->checkDotList()->value("M")->addNote(43687.5);
	parent->checkDotList()->value("M")->addNote(44062.5);
	parent->checkDotList()->value("M")->addNote(44250);
	parent->checkDotList()->value("M")->addNote(44437.5);
	parent->checkDotList()->value("M")->addNote(44625);
	parent->checkDotList()->value("M")->addNote(44812.5);
	parent->checkDotList()->value("M")->addNote(45093.75);
	parent->checkDotList()->value("M")->addNote(45375);
	parent->checkDotList()->value("M")->addNote(45750);
	parent->checkDotList()->value("M")->addNote(45937.5);
	parent->checkDotList()->value("M")->addNote(46125);
	parent->checkDotList()->value("M")->addNote(46312.5);
	parent->checkDotList()->value("M")->addNote(46500);
	parent->checkDotList()->value("M")->addNote(46781.25);
	parent->checkDotList()->value("M")->addNote(47062.5);
	parent->checkDotList()->value("M")->addNote(47250);
	parent->checkDotList()->value("M")->addNote(47437.5);
	parent->checkDotList()->value("M")->addNote(47625);
	parent->checkDotList()->value("M")->addNote(47812.5);
	parent->checkDotList()->value("M")->addNote(48093.75);
	parent->checkDotList()->value("M")->addNote(48375);
	parent->checkDotList()->value("M")->addNote(48750);
	parent->checkDotList()->value("M")->addNote(48937.5);
	parent->checkDotList()->value("M")->addNote(49125);

	parent->checkDotList()->value("M")->setPoint(1700, -50);
	parent->checkDotList()->value("M")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("M")->dotLine()->setAngle(90);

	parent->checkDotList()->value("V")->setPoint(1500, 1850);
	parent->checkDotList()->value("V")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("V")->dotLine()->setAngle(-90);

	parent->checkDotList()->value("V2")->setPoint(1500, 1850);
	parent->checkDotList()->value("V2")->dotLine()->setDownVisuable(false);
	parent->checkDotList()->value("V2")->dotLine()->setAngle(-90);

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
	w->Ui()->central->mainTime()->start();
	w->Ui()->central->litTime()->start();
	w->Ui()->central->disTime()->restart();
	qDebug() << "\tMOONOTUSystem::_Message_::Timer of central start";
	w->connect
	(
		w->Ui()->central->mainTime(),
		SIGNAL(timeout()),
		IF,
		SLOT(InfinityHeaven()),
		Qt::DirectConnection
	);
	w->Ui()->central->show();
}

void InfinityHeaven_Class::InfinityHeaven()
{
	//由于Qt事件循环的阻塞特性，建议谱师以位置而非时刻作为动画依据
	if (parent->checkDotList()->value("M")->point().y() < 900)
	{
		QPoint newpoint(parent->checkDotList()->value("M")->point().x(), parent->checkDotList()->value("M")->point().y() + qreal(900 - parent->checkDotList()->value("M")->point().y()) / 10);
		parent->checkDotList()->value("M")->setPoint(newpoint);
	}
	if (parent->checkDotList()->value("V")->point().y() > 900)
	{
		QPoint newpoint(parent->checkDotList()->value("V")->point().x(), parent->checkDotList()->value("V")->point().y() - qreal(parent->checkDotList()->value("V")->point().y() - 900) / 10);
		parent->checkDotList()->value("V")->setPoint(newpoint);
	}
	if (parent->checkDotList()->value("V2")->point().y() > 900)
	{
		QPoint newpoint(parent->checkDotList()->value("V2")->point().x(), parent->checkDotList()->value("V2")->point().y() - qreal(parent->checkDotList()->value("V2")->point().y() - 900) / 10);
		parent->checkDotList()->value("V2")->setPoint(newpoint);
	}
	parent->playMusic();
}

MWidget*& InfinityHeaven_Class::Parent()
{
	return parent;
}
































































































































































































































































































































































































































































































































































































































































































































































































