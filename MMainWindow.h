#pragma once
#include"MCenter.h"

class MCell;

class MMainWindow  : public QWidget
{
#define startstate 0x000

	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);

public slots:
	void timeAdd_ms();
	void UiAnimation();
	void Test();

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
	qreal visualProportion() const;//视觉比例
	qreal visualProportionX() const;//视觉比例
	qreal visualProportionY() const;//视觉比例
	QTimer*& uiFlushTime() ;
	QWidget*& MParent();
};
