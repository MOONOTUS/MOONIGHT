#pragma once
#include"MPivot.h"

class InfinityHeaven_Class :public QObject
{
	Q_OBJECT

private:
	MWidget* parent;

public slots:
	void InfinityHeaven();

public:
	InfinityHeaven_Class(MWidget* parent = nullptr);
	~InfinityHeaven_Class();

	MWidget*& Parent();
};

void TestDemo_InfinityHeaven(MOONIGHT_Qt * w);
