#include"TestDemo.h"

TestDemo_Rotate_Class::TestDemo_Rotate_Class(MOONIGHT_Qt* parent)
	: QObject(parent)
{
	QPixmap backImage("D:\\Painting\\00013.png");
	parent->Ui()->central->setBackImage(backImage);
	parent->Ui()->central->setShowBackImage(true);
	parent->Ui()->central->setShowBackBackImage(true);
	parent->Ui()->central->setBackCoverColor(QColor(0, 0, 0, 196));
	parent->repaint();
	parent->Ui()->central->checkDotList()->insert("M", new MCheckDot(parent->Ui()->central));
	parent->Ui()->central->checkDotList()->value("M")->show();
	this->parent = parent;
	angel = new qreal(0.0);
	r = new qreal(0.0);
}

TestDemo_Rotate_Class::~TestDemo_Rotate_Class()
{}

void TestDemo_Rotate(MOONIGHT_Qt* w)
{
	TestDemo_Rotate_Class* r = new TestDemo_Rotate_Class(w);
	w->Ui()->mainTime->start();
	w->Ui()->litTime->start();
	w->connect
	(
		w->Ui()->mainTime,
		SIGNAL(timeout()),
		r,
		SLOT(rotateCheckDot())
	);
}

void TestDemo_Rotate_Class::rotateCheckDot()
{
	qreal* x = new qreal(*r * qCos(*angel));
	qreal* y = new qreal(*r * qSin(*angel));
	parent->Ui()->central->checkDotList()->value("M")->dotLine()->setAngel(*angel * 180 / phi);
	QPoint newpoint = QPoint(parent->Ui()->central->oriSize().width()/2 + *x, parent->Ui()->central->oriSize().height()/2 + *y);
	parent->Ui()->central->checkDotList()->value("M")->setPoint(newpoint);
	parent->Ui()->central->checkDotList()->value("M")->setKey(Qt::Key_M, "M");
	parent->Ui()->central->checkDotList()->value("M")->setKeyVisuable(true);
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

MOONIGHT_Qt*& TestDemo_Rotate_Class::Parent()
{
	return parent;
}