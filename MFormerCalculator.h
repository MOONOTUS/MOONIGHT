#pragma once
#include"MCenter.h"

class MWidget;

class MFormerCalculator  : public QWidget //计数器类
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event);//经过重写的绘制函数

private:
	MWidget* Parent;//存储parent，用于溯源
	QPixmap* Image;//计数器背景
	qint64* Score;//分数
	QString* ScoreText;//显示的分数文本
	QString* MusicName;//曲谱名
	qint64* Combo;//连击数
	QString* ComboText;//显示的连击数文本
	qreal* Accuracy;//准度
	QString* AccuracyText;//显示的准度文本
	qint32* Check;//判定类型
	QString* CheckText;//显示的判定文本
	QPoint* MoonPoint;//偏差指示器的逻辑位置
	QPoint* VMoonPoint;//偏差指示器的视觉位置
	qreal* MoonRadium;//偏差指示器的逻辑半径
	qreal* VMoonRadium;//偏差指示器的视觉半径
	bool* Show;//计数器的可见性
	qreal* Deviation;//偏差
	QString* Type;//偏差类型

public:
	MFormerCalculator(MWidget *parent);
	~MFormerCalculator();

	void setImage(QString path);//设定计数器背景
	void setImage(QPixmap image);//设定计数器背景
	void setScore(qint64 score);//设定分数
	void setMusicName(QString name);//设定曲谱名
	void setCombo(qint64 combo);//设定连击数
	void setAccuracy(qreal accuracy);//设定准度
	void setCheck(qint32 check);//设定判定
	void setCheckText(QString checktext);//设定判定文本
	QPoint vMoonPoint() const;//偏差指示器的视觉位置
	qreal vMoonRadium() const;//偏差指示器的视觉半径
	void setShow(bool show);//设定计数器可见性
	bool ifShow() const;//计数器可见性
	void setDeviation(qreal deviation);//设定偏差
	qreal deviation() const;//偏差
	void setType(QString type);//设定偏差类型
	QString type() const;//偏差类型
	constexpr MWidget*& MParent();//返回Parent，用于溯源
};
