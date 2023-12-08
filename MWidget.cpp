#include "MWidget.h"

MWidget::MWidget(QWidget* parent)
	: QWidget(parent)
{
	this->OriSize = new QSize(1920, 1080);
	ifShowBackImage = new bool(false);
	ifShowBackBackImage = new bool(false);
	backColor = new  QColor(245, 245, 245);
	backCoverColor = new QColor(255, 255, 255, 0);
}

MWidget::~MWidget()
{}

void MWidget::paintEvent(QPaintEvent* event)
{
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);
	if (*ifShowBackBackImage)
	{
		paint->drawPixmap(QRect(0, 0, this->width(), this->height()), *backBackImage);
		paint->fillRect(QRect(0, 0, this->width(), this->height()), QColor(backCoverColor->red(), backCoverColor->green(), backCoverColor->blue(), backCoverColor->alpha() / 2));
	}
	if (*ifShowBackImage)
	{
		paint->drawPixmap(QRect(0, (this->height() - this->width() * 9 / 16) / 2, this->width(), this->width() * 9 / 16), *backImage);
	}
	else
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backColor);
	}
	if (!(backCoverColor->alpha() == 0))
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backCoverColor);
	}

	event->accept();
}

void MWidget::setBackImage(QPixmap& image)
{
	backImage = new QPixmap(image);
	if (backImage->width() / backImage->height() > 16 / 9)
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(), backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));
}

void MWidget::setBackImage(QString& path)
{
	backImage = new QPixmap(path);
	if (backImage->width() / backImage->height() > 16 / 9)
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(),backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));
}

void MWidget::setBackColor(QColor color)
{
	backColor = new QColor(color);
}

void MWidget::setBackColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	backColor = new QColor(R, G, B, A);
}

void MWidget::setBackCoverColor(QColor color)
{
	backCoverColor = new QColor(color);
}

void MWidget::setBackCoverColor(qint32 R, qint32 G, qint32 B, qint32 A)
{
	backCoverColor = new QColor(R, G, B, A);
}

void MWidget::setShowBackImage(bool show)
{
	ifShowBackImage = new bool(show);
}

void MWidget::setShowBackBackImage(bool show)
{
	ifShowBackBackImage = new bool(show);
}

bool MWidget::showBackImage()
{
	return *ifShowBackImage;
}

bool MWidget::showBackBackImage()
{
	return *ifShowBackBackImage;
}

QSize MWidget::oriSize()
{
	return *OriSize;
}