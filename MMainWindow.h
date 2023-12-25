#pragma once
#include"MCenter.h"

#include <QWidget>

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
