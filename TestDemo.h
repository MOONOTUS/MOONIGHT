#pragma once
#include"MPivot.h"

class TestDemo_Rotate_Class:public QObject
{
	Q_OBJECT

private:
	MOONIGHT_Qt* parent;

public slots:
	void rotateCheckDot();

public:
	TestDemo_Rotate_Class(MOONIGHT_Qt* parent = nullptr);
	~TestDemo_Rotate_Class();
	qreal* angel;
	qreal* r;

	MOONIGHT_Qt*& Parent();
};

void TestDemo_Rotate(MOONIGHT_Qt* w);