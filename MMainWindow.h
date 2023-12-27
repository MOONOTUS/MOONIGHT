#pragma once
#include"MCenter.h"
#include"MCell.h"

class MMainWindow  : public QWidget
{
#define startstate 0x000

	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);

public slots:
	void timeAdd_ms();
	void UiAnimation();

private:
	static QSize* OriSize;
	qint32* State;
	QWidget* Parent;
	bool* Started;
	QTimer* UiTimeFlush;
	QTimer* UiFlushTime;
	QElapsedTimer* UiTime;
	qint64* time_ms;
	QMap<QString, MCell*>* CellList;

public:
	MMainWindow(QWidget *parent);
	~MMainWindow();

	void UiSetUp();

	void addCell(QString key, MCell* cell);
	QMap<QString, MCell*>*& cellList();
	qreal visualProportion();//视觉比例
	qreal visualProportionX();//视觉比例
	qreal visualProportionY();//视觉比例
};
