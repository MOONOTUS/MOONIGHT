#pragma once
#include"MPivot.h"

class TestDemo_Rotate_Class:public QObject
{
	Q_OBJECT

private:
	MWidget* parent;

public slots:
	void rotateCheckDot();

public:
	TestDemo_Rotate_Class(MWidget* parent = nullptr);
	~TestDemo_Rotate_Class();
	qreal* angel;
	qreal* r;

	MWidget*& Parent();
};

void TestDemo_Rotate(MOONIGHT_Qt* w);