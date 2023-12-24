#pragma once
#include"MCenter.h"

class MWidget;

class MFormerCaculator  : public QWidget
{
	Q_OBJECT
protected:
	//void paintEvent(QPaintEvent* event);//经过重写的绘制函数

private:
	MWidget* Parent;
	QPixmap* Image;
	QPixmap* Mask;
	qint64* Score;
	QString* ScoreText;
	QString* MusicName;
	qint64* Combo;
	QString* ComboText;
	qreal* Accuracy;
	QString* AccuracyText;
	qint32* Check;
	QPoint* MoonPoint;
	QPoint* VMoonPoint;
	qreal* MoonRadium;
	qreal* VMoonRadium;

public:
	MFormerCaculator(MWidget *parent);
	~MFormerCaculator();

	//void setImage();
	//void setMask();
	//void setScore();
	//void setMusicName();
	//void setCombo();
	//void setAccuracy();
	//void setCheck();
	//qreal vMoonPoint();
	//qreal vMoonRadiym();
	//MWidget*& MParent();
};
