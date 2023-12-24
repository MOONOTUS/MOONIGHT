#pragma once
#include"MCenter.h"

class MWidget;

class MFormerCalculator  : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event);//经过重写的绘制函数

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
	QString* CheckText;
	QPoint* MoonPoint;
	QPoint* VMoonPoint;
	qreal* MoonRadium;
	qreal* VMoonRadium;
	bool* Show;
	qreal* Deviation;

public:
	MFormerCalculator(MWidget *parent);
	~MFormerCalculator();

	void setImage(QString path);
	void setMask(QString path);
	void setImage(QPixmap image);
	void setMask(QPixmap image);
	void setScore(qint64 score);
	void setMusicName(QString name);
	void setCombo(qint64 combo);
	void setAccuracy(qreal accuracy);
	void setCheck(qint32 check);
	QPoint vMoonPoint();
	qreal vMoonRadium();
	MWidget*& MParent();
	void setShow(bool show);
	bool ifShow();
	void setDeviation(qreal deviation);
	qreal deviation();
};
