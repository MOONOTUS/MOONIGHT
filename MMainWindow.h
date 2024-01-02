#pragma once
#include"MCenter.h"

class MCell;

class MMainWindow  : public QWidget
{
#define startstate 0x000
#define chapterstate 0x001
#define songliststate 0x002

	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

public slots:
	void timeAdd_ms();
	void UiAnimation();
	void statechange_start_to_chapter();
	void statechange_chapter_to_songlist(QString chapterkey);

private:
	static QSize* OriSize;
	static qint32* StateNowSetUp;
	static qint64* ChapterSum;
	qint32* State;
	QWidget* Parent;
	bool* Started;
	QTimer* UiTimeFlush;
	QTimer* UiFlushTime;
	QElapsedTimer* UiTime;
	qint64* time_ms;
	QMap<QString, MCell*>* CellList;
	QMap<QString, MCell*>* ChapterList;
	QMap<qint64, QString>* ChapterNumList;
	QMap<QString, QPixmap*>* MaskList;
	QString* Chapter;
	qint64* CenterChapter;

public:
	MMainWindow(QWidget *parent);
	~MMainWindow();

	void UiSetUp();
	static void nowSetUp(qint32 nowsetup);

	void addCell(QString key, MCell* cell, qint32 linkstate = *MMainWindow::StateNowSetUp);
	void addChapter(QString key, QString chaptername, QPixmap chaptercover);
	QMap<QString, MCell*>*& cellList();
	qreal visualProportion() const;//视觉比例
	qreal visualProportionX() const;//视觉比例
	qreal visualProportionY() const;//视觉比例
	QTimer*& uiFlushTime() ;
	QWidget*& MParent();
};
