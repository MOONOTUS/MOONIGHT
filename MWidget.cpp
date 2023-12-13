#include "MWidget.h"
#include"MCheckDot.h"

MWidget::MWidget(QWidget* parent)
	: QWidget(parent)
{
	Parent = parent;//储存parent
	CheckDotList = new QMap<QString, MCheckDot*>;//无用的初始化
	this->OriSize = new QSize(1920, 1080);//设定Size=（1920，1080）的原始坐标系
	ifShowBackImage = new bool(false);//初始化显示背景图片为假
	ifShowBackBackImage = new bool(false);//初始化显示背景的背景为假
	ifShowLogo = new bool(true);//初始化显示标志为真
	backColor = new  QColor(245, 245, 245);//初始化背景色为（245，245，245，255）的亮灰白色
	Logo = new QPixmap("D:\\Painting\\MOONIGHT_Beta_Little.png");//读取Logo图片，稍后改为相对路径
	backCoverColor = new QColor(255, 255, 255, 0);//初始化背景遮罩色为全透明白色，即不显示遮罩
	time_ms = new qint64(0);//时间置零
}

MWidget::~MWidget()
{}

void MWidget::paintEvent(QPaintEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Data::_*time_ms_::" << *time_ms;
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);
	if (*ifShowBackBackImage)//背景的背景的绘制
	{
		paint->drawPixmap(QRect(0, 0, this->width(), this->height()), *backBackImage);
		if (!(backCoverColor->alpha() == 0))
		{
			paint->fillRect(QRect(0, 0, this->width(), this->height()), QColor(backCoverColor->red(), backCoverColor->green(), backCoverColor->blue(), backCoverColor->alpha() / 2));//覆盖降低了不透明度的遮罩色
		}
	}
	else//背景色的绘制
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backColor);
	}
	if (*ifShowBackImage)//背景图片的绘制
	{
		paint->drawPixmap(QRect(0, (this->height() - this->width() * 9 / 16) / 2, this->width(), this->width() * 9 / 16), *backImage);
	}
	if (*ifShowLogo)//标志的绘制
	{
		paint->drawPixmap(QRect(0, (this->height() - this->width() * 9 / 16) / 2, this->width(), this->width() * 9 / 16), *Logo);
	}
	if (!(backCoverColor->alpha() == 0))//背景遮罩层的绘制
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backCoverColor);
	}

	event->accept();
}

void MWidget::setBackImage(QPixmap& image)
{
	backImage = new QPixmap(image);
	if (backImage->width() / backImage->height() > 16 / 9)//自适应模块，自动以合适的方案将图片裁剪为16：9的比例
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(), backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);//生成背景图片的模糊拷贝
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));//存储背景的背景图片
}

void MWidget::setBackImage(QString& path)
{
	backImage = new QPixmap(path);
	if (backImage->width() / backImage->height() > 16 / 9)//自适应模块，自动以合适的方案将图片裁剪为16：9的比例
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(),backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);//生成背景图片的模糊拷贝
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));//存储背景的背景图片
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

void MWidget::setShowLogo(bool show)
{
	ifShowLogo = new bool(show);
}

bool MWidget::showBackImage()
{
	return *ifShowBackImage;
}

bool MWidget::showBackBackImage()
{
	return *ifShowBackBackImage;
}

bool MWidget::showLogo()
{
	return *ifShowLogo;
}

void MWidget::setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist)
{
	CheckDotList = checkdotlist;
}

QMap<QString, MCheckDot*>*& MWidget::checkDotList()
{
	return CheckDotList;
}

QSize MWidget::oriSize()
{
	return *OriSize;
}

QWidget*& MWidget::MParent()
{
	return Parent;
}

void MWidget::setTime(qint64 ms)
{
	time_ms = new qint64(ms);
}

qint64 MWidget::time()
{
	return *time_ms;
}

void MWidget::timeAdd_ms()
{
	time_ms = new qint64((*time_ms) + 1);
}