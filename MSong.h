#pragma once
#include"MCenter.h"

class MCell;

class MSong
{
private:
	MCell* Parent;
	QString* Name;
	qint64* ID;
	QPixmap* Image;

public:
	MSong(MCell* parent = nullptr);
	~MSong();

	void setName(QString name);
	void setID(qint64 id);
	void setImage(QString path);
	void setImage(QPixmap image);

	MCell*& MParent();
	QString name();
	qint64 id();
	QPixmap image();
};