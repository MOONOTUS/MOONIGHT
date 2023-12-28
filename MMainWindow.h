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

	inline void UiSetUp();

	inline void addCell(QString key, MCell* cell);
	inline QMap<QString, MCell*>*& cellList();
	inline qreal visualProportion() const;//视觉比例
	inline qreal visualProportionX() const;//视觉比例
	inline qreal visualProportionY() const;//视觉比例
};
