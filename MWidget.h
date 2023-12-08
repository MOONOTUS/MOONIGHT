#pragma once

#include"MCenter.h"

class MWidget : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);

private:
	QPixmap* backImage;
	QPixmap* backBackImage;
	QColor* backCoverColor;
	QColor* backColor;
	QSize* OriSize;
	bool* ifShowBackImage;
	bool* ifShowBackBackImage;

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
	QSize oriSize();
};
