#include "MWidget.h"
#include"MCheckDot.h"

MWidget::MWidget(QWidget* parent)
	: QWidget(parent)
{
	Parent = parent;//����parent
	CheckDotList = new QMap<QString, MCheckDot*>;//���õĳ�ʼ��
	this->OriSize = new QSize(1920, 1080);//�趨Size=��1920��1080����ԭʼ����ϵ
	ifShowBackImage = new bool(false);//��ʼ����ʾ����ͼƬΪ��
	ifShowBackBackImage = new bool(false);//��ʼ����ʾ�����ı���Ϊ��
	ifShowLogo = new bool(true);//��ʼ����ʾ��־Ϊ��
	backColor = new  QColor(245, 245, 245);//��ʼ������ɫΪ��245��245��245��255�������Ұ�ɫ
	Logo = new QPixmap("D:\\Painting\\MOONIGHT_Beta_Little.png");//��ȡLogoͼƬ���Ժ��Ϊ���·��
	backCoverColor = new QColor(255, 255, 255, 0);//��ʼ����������ɫΪȫ͸����ɫ��������ʾ����
	time_ms = new qint64(0);//ʱ������
}

MWidget::~MWidget()
{}

void MWidget::paintEvent(QPaintEvent* event)
{
	qDebug() << "MOONOTUSYSTEM::_Data::_*time_ms_::" << *time_ms;
	QPainter* paint = new QPainter(this);
	paint->setRenderHint(QPainter::Antialiasing);
	paint->setRenderHint(QPainter::TextAntialiasing);
	if (*ifShowBackBackImage)//�����ı����Ļ���
	{
		paint->drawPixmap(QRect(0, 0, this->width(), this->height()), *backBackImage);
		if (!(backCoverColor->alpha() == 0))
		{
			paint->fillRect(QRect(0, 0, this->width(), this->height()), QColor(backCoverColor->red(), backCoverColor->green(), backCoverColor->blue(), backCoverColor->alpha() / 2));//���ǽ����˲�͸���ȵ�����ɫ
		}
	}
	else//����ɫ�Ļ���
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backColor);
	}
	if (*ifShowBackImage)//����ͼƬ�Ļ���
	{
		paint->drawPixmap(QRect(0, (this->height() - this->width() * 9 / 16) / 2, this->width(), this->width() * 9 / 16), *backImage);
	}
	if (*ifShowLogo)//��־�Ļ���
	{
		paint->drawPixmap(QRect(0, (this->height() - this->width() * 9 / 16) / 2, this->width(), this->width() * 9 / 16), *Logo);
	}
	if (!(backCoverColor->alpha() == 0))//�������ֲ�Ļ���
	{
		paint->fillRect(QRect(0, 0, this->width(), this->height()), *backCoverColor);
	}

	event->accept();
}

void MWidget::setBackImage(QPixmap& image)
{
	backImage = new QPixmap(image);
	if (backImage->width() / backImage->height() > 16 / 9)//����Ӧģ�飬�Զ��Ժ��ʵķ�����ͼƬ�ü�Ϊ16��9�ı���
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(), backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);//���ɱ���ͼƬ��ģ������
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));//�洢�����ı���ͼƬ
}

void MWidget::setBackImage(QString& path)
{
	backImage = new QPixmap(path);
	if (backImage->width() / backImage->height() > 16 / 9)//����Ӧģ�飬�Զ��Ժ��ʵķ�����ͼƬ�ü�Ϊ16��9�ı���
	{
		backImage = new QPixmap(backImage->copy((backImage->width() - backImage->height() * 16 / 9) / 2, 0, backImage->height() * 16 / 9, backImage->height()));
	}
	else if (backImage->width() / backImage->height() < 16 / 9)
	{
		backImage = new QPixmap(backImage->copy(0, (backImage->height() - backImage->width() * 9 / 16) / 2, backImage->width(),backImage->width() * 9 / 16));
	}
	QImage backBack = backImage->toImage();
	GaussiamBlur(36, 2000, backBack);//���ɱ���ͼƬ��ģ������
	backBackImage = new QPixmap(QPixmap::fromImage(backBack));//�洢�����ı���ͼƬ
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