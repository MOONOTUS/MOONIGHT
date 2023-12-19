#include"TestDemo.h"

TestDemo_Rotate_Class::TestDemo_Rotate_Class(MWidget* parent)
	: QObject(parent)
{
	QPixmap backImage("D:\\Painting\\00013.png");
	parent->setBackImage(backImage);
	parent->setShowBackImage(true);
	parent->setShowBackBackImage(true);
	parent->setBackCoverColor(QColor(0, 0, 0, 196));
	parent->repaint();
	parent->checkDotList()->insert("M", new MCheckDot(parent));
	parent->checkDotList()->value("M")->setKey(Qt::Key_M, "M"); 
	parent->checkDotList()->value("M")->setKeyVisuable(true);
	parent->checkDotList()->insert("N", new MCheckDot(parent));
	parent->checkDotList()->value("N")->setKey(Qt::Key_N, "N");
	parent->checkDotList()->value("N")->setKeyVisuable(true);
	parent->checkDotList()->insert("1", new MCheckDot(parent));
	parent->checkDotList()->value("1")->setKey(Qt::Key_1, "1");
	parent->checkDotList()->value("1")->setKeyVisuable(true);
	parent->checkDotList()->insert("2", new MCheckDot(parent));
	parent->checkDotList()->value("2")->setKey(Qt::Key_2, "2");
	parent->checkDotList()->value("2")->setKeyVisuable(true);
	parent->checkDotList()->insert("3", new MCheckDot(parent));
	parent->checkDotList()->value("3")->setKey(Qt::Key_3, "3");
	parent->checkDotList()->value("3")->setKeyVisuable(true);
	parent->checkDotList()->insert("4", new MCheckDot(parent));
	parent->checkDotList()->value("4")->setKey(Qt::Key_4, "4");
	parent->checkDotList()->value("4")->setKeyVisuable(true);
	parent->checkDotList()->insert("O", new MCheckDot(parent));
	parent->checkDotList()->value("O")->setKey(Qt::Key_O, "O");
	parent->checkDotList()->value("O")->setKeyVisuable(true);
	MNote* newNote1 = new MNote(parent->checkDotList()->value("O"));
	MNote* newNote2 = new MNote(parent->checkDotList()->value("O"));
	MNote* newNote3 = new MNote(parent->checkDotList()->value("O"));
	MNote* newNote4 = new MNote(parent->checkDotList()->value("O"));
	MNote* newNote5 = new MNote(parent->checkDotList()->value("O"));
	parent->checkDotList()->value("O")->setNextTime(6000);
	newNote1->setTime(6000);
	newNote2->setTime(7000);
	newNote3->setTime(8000);
	newNote4->setTime(9000);
	newNote1->setNextTime(7000);
	newNote2->setNextTime(8000);
	newNote3->setNextTime(9000);
	newNote4->setNextTime(-1);
	newNote1->setType(click);
	newNote2->setType(cat);
	newNote3->setType(beat);
	newNote4->setType(hold);
	newNote3->setBeatKey(Qt::Key_G, "G");
	newNote4->setTimeLength(3000); 
	parent->checkDotList()->value("O")->noteList()->insert(6000, newNote1);
	parent->checkDotList()->value("O")->noteList()->insert(7000, newNote2);
	parent->checkDotList()->value("O")->noteList()->insert(8000, newNote3);
	parent->checkDotList()->value("O")->noteList()->insert(9000, newNote4);
	parent->checkDotList()->value("O")->setPoint(960, 540);
	parent->checkDotList()->value("O")->setRadium(0);
	parent->checkDotList()->value("M")->show();
	parent->checkDotList()->value("N")->show();
	parent->checkDotList()->value("1")->show();
	parent->checkDotList()->value("2")->show();
	parent->checkDotList()->value("3")->show();
	parent->checkDotList()->value("4")->show();
	parent->checkDotList()->value("O")->show();
	this->parent = parent;
	angel = new qreal(0.0);
	r = new qreal(0.0);
}

TestDemo_Rotate_Class::~TestDemo_Rotate_Class()
{}

void TestDemo_Rotate(MOONIGHT_Qt* w)
{
	TestDemo_Rotate_Class* r = new TestDemo_Rotate_Class(w->Ui()->central);
	QCoreApplication::processEvents();
	w->Ui()->central->setTime(0);
	w->Ui()->mainTime->start();
	w->Ui()->litTime->start();
	w->Ui()->central->disTime()->restart();
	w->connect
	(
		w->Ui()->mainTime,
		SIGNAL(timeout()),
		r,
		SLOT(rotateCheckDot())
	);
	w->Ui()->central->show();
}

void TestDemo_Rotate_Class::rotateCheckDot()
{
	qint32 alpha = 0;
	if (parent->time() <= 3000)
	{
		qreal* x = new qreal(*r * qCos(*angel));
		qreal* y = new qreal(*r * qSin(*angel));
		parent->checkDotList()->value("M")->dotLine()->setAngel(*angel * 180 / phi);
		QPoint newpoint = QPoint(parent->oriSize().width() / 2 + *x, parent->oriSize().height() / 2 + *y);
		parent->checkDotList()->value("M")->setPoint(newpoint);
		parent->checkDotList()->value("N")->dotLine()->setAngel(*angel * 180 / phi);
		newpoint = QPoint(parent->oriSize().width() / 2 - *x, parent->oriSize().height() / 2 - *y);
		parent->checkDotList()->value("N")->setPoint(newpoint);
		x = new qreal(*r * qCos(*angel + 15));
		y = new qreal(*r * qSin(*angel + 15));
		parent->checkDotList()->value("1")->dotLine()->setAngel(*angel * 180 / phi + 15);
		newpoint = QPoint(parent->oriSize().width() / 2 + *x, parent->oriSize().height() / 2 + *y);
		parent->checkDotList()->value("1")->setPoint(newpoint);
		parent->checkDotList()->value("2")->dotLine()->setAngel(*angel * 180 / phi + 15);
		newpoint = QPoint(parent->oriSize().width() / 2 - *x, parent->oriSize().height() / 2 - *y);
		parent->checkDotList()->value("2")->setPoint(newpoint);
		x = new qreal(*r * qCos(*angel - 15));
		y = new qreal(*r * qSin(*angel - 15));
		parent->checkDotList()->value("3")->dotLine()->setAngel(*angel * 180 / phi - 15);
		newpoint = QPoint(parent->oriSize().width() / 2 + *x, parent->oriSize().height() / 2 + *y);
		parent->checkDotList()->value("3")->setPoint(newpoint);
		parent->checkDotList()->value("4")->dotLine()->setAngel(*angel * 180 / phi - 15);
		newpoint = QPoint(parent->oriSize().width() / 2 - *x, parent->oriSize().height() / 2 - *y);
		parent->checkDotList()->value("4")->setPoint(newpoint);
		parent->repaint();
		QCoreApplication::processEvents();
		*angel = (1 * phi / 180) * parent->time() / 10;
		*r += (parent->time() / 100) * (parent->time() / 100);
		parent->checkDotList()->value("O")->setRadium(parent->time() / 100);
		//parent->checkDotList()->value("O")->setDotColor(QColor(parent->checkDotList()->value("O")->dotColor().red(), parent->checkDotList()->value("O")->dotColor().green(), parent->checkDotList()->value("O")->dotColor().blue(), alpha));
		//oparent->checkDotList()->value("O")->dotLine()->setDotLineColor(QColor(parent->checkDotList()->value("O")->dotLine()->dotLineColor().red(), parent->checkDotList()->value("O")->dotLine()->dotLineColor().green(), parent->checkDotList()->value("O")->dotLine()->dotLineColor().blue(), alpha));
		delete x;
		delete y;
		if (qint64(*angel * 180 / phi) % 90 < 10)
		{
			parent->checkDotList()->value("M")->setRadium(40.0);
			parent->checkDotList()->value("N")->setRadium(40.0);
			parent->checkDotList()->value("1")->setRadium(40.0);
			parent->checkDotList()->value("2")->setRadium(40.0);
			parent->checkDotList()->value("3")->setRadium(40.0);
			parent->checkDotList()->value("4")->setRadium(40.0);
		}
		else
		{
			parent->checkDotList()->value("M")->setRadium(30.0);
			parent->checkDotList()->value("N")->setRadium(30.0);
			parent->checkDotList()->value("1")->setRadium(30.0);
			parent->checkDotList()->value("2")->setRadium(30.0);
			parent->checkDotList()->value("3")->setRadium(30.0);
			parent->checkDotList()->value("4")->setRadium(30.0);
		}
		if (alpha <= 255)
		{
			alpha += 1;
		}
	}
	else
	{
		parent->repaint();
	}
}

MWidget*& TestDemo_Rotate_Class::Parent()
{
	return parent;
}