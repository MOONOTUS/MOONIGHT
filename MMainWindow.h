#pragma once
#include"MCenter.h"

class MMainWindow  : public QWidget
{
	Q_OBJECT

public:
	MMainWindow(QWidget *parent);
	~MMainWindow();

private:
	bool* Started;
	QTimer* UiTime;


};
