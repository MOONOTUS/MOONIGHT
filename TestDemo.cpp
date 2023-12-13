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
	parent->checkDotList()->value("M")->show();
	parent->checkDotList()->value("M")->setKey(Qt::Key_M, "M"); 
	parent->checkDotList()->value("M")->setKeyVisuable(true);
	this->parent = parent;
	angel = new qreal(0.0);
	r = new qreal(0.0);
}

TestDemo_Rotate_Class::~TestDemo_Rotate_Class()
{}

void TestDemo_Rotate(MOONIGHT_Qt* w)
{
	TestDemo_Rotate_Class* r = new TestDemo_Rotate_Class(w->Ui()->central);
	w->Ui()->central->setTime(0);
	w->Ui()->mainTime->start();
	w->Ui()->litTime->start();
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
	qreal* x = new qreal(*r * qCos(*angel));
	qreal* y = new qreal(*r * qSin(*angel));
	parent->checkDotList()->value("M")->dotLine()->setAngel(*angel * 180 / phi);
	QPoint newpoint = QPoint(parent->oriSize().width()/2 + *x, parent->oriSize().height()/2 + *y);
	parent->checkDotList()->value("M")->setPoint(newpoint);
	parent->repaint();
	QCoreApplication::processEvents();
	*angel += 2 * phi / 180;
	*r += 0.5;
	delete x;
	delete y;
	if (*angel >= 2*phi)
	{
		*angel = 0;
	}
}

MWidget*& TestDemo_Rotate_Class::Parent()
{
	return parent;
}