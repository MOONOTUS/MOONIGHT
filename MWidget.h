#pragma once

#include"MCenter.h"

class MCheckDot;

class MWidget : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);

signals:

public slots:
	void timeAdd_ms();

private:
	QWidget* Parent;
	QPixmap* backImage;
	QPixmap* backBackImage;
	QColor* backCoverColor;
	QColor* backColor;
	QSize* OriSize;
	QMap<QString, MCheckDot*>* CheckDotList;
	bool* ifShowBackImage;
	bool* ifShowBackBackImage;
	qint64* time_ms;

public:
	MWidget(QWidget* parent = nullptr);
	~MWidget();

	void setBackImage(QString& path);
	void setBackImage(QPixmap& image);
	void setBackColor(QColor color);
	void setBackColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	void setBackCoverColor(QColor color);
	void setBackCoverColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	void setShowBackImage(bool show);
	void setShowBackBackImage(bool show);
	bool showBackImage();
	bool showBackBackImage();
	void setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist);
	QMap<QString, MCheckDot*>*& checkDotList();
	QSize oriSize();
	QWidget*& MParent();
	void setTime(qint64 ms);
	qint64 time();
};
