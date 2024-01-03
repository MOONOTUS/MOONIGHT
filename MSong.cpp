#include"MPivot.h"

MSong::MSong(MCell* parent)
{
	Parent = parent;
	Name = new QString("Unknown");
	ID = new qint64(-1);
	Image = nullptr;
}

MSong::~MSong()
{};

void MSong::setName(QString name)
{
	delete Name;
	Name = new QString(name);
}

void MSong::setID(qint64 id)
{
	delete ID;
	ID = new qint64(id);
}

void MSong::setImage(QString path)
{
	if (Image != nullptr)
	{
		delete Image;
	}
	Image = new QPixmap(path);
}

void MSong::setImage(QPixmap image)
{
	if (Image != nullptr)
	{
		delete Image;
	}
	Image = new QPixmap(image);
}

MCell*& MSong::MParent()
{
	return Parent;
}

QString MSong::name()
{
	return *Name;
}

qint64 MSong::id()
{
	return *ID;
}

QPixmap MSong::image()
{
	if (Image != nullptr)
	{
		return *Image;
	}
	else
	{
		return QPixmap();
	}
}