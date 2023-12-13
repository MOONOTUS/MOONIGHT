#pragma once

#include"MCenter.h"

class MCheckDot;

class MWidget : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);//经过重写的绘制函数

signals:

public slots:
	void timeAdd_ms();//计时槽，与parent->litTime的信号timeout()连接

private:
	QWidget* Parent;//存储父对象的指针
	QPixmap* backImage;//背景图片
	QPixmap* backBackImage;//填充背景空白的模糊背景图片（在设置背景图片时自动生成）
	QColor* backCoverColor;//背景遮罩色（RGBA）
	QColor* backColor;//背景色（RGBA）
	QSize* OriSize;//原始尺寸，固有值，用于自适应的实现
	QMap<QString, MCheckDot*>* CheckDotList;//判定点的QMap容器，可以通过Key值获取对应的判定点，一般建议采用判定点的判定键做Key值
	bool* ifShowBackImage;//是否显示背景图片
	bool* ifShowBackBackImage;//是否显示背景的背景图片
	bool* ifShowLogo;//是否显示标志
	qint64* time_ms;//以ms为单位的计时
	QPixmap* Logo;//MOONOIGHT的标志图片

public:
	MWidget(QWidget* parent = nullptr);
	~MWidget();

	void setBackImage(QString& path);//设定背景图片，同时生成背景的模糊背景
	void setBackImage(QPixmap& image);//设定背景图片，同时生成背景的模糊背景
	void setBackColor(QColor color);//设定背景色
	void setBackColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定背景色
	void setBackCoverColor(QColor color);//设定背景遮罩色
	void setBackCoverColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定背景遮罩色
	void setShowBackImage(bool show);//设定是否显示背景图片
	void setShowBackBackImage(bool show);//设定是否显示背景的背景图片
	void setShowLogo(bool show);//设定是否显示标志
	bool showBackImage();//返回*ifShowBackImage
	bool showBackBackImage();//返回*ifShowBackBackImage
	bool showLogo();//返回*ifSHowLogo
	void setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist);//设定判定点容器
	QMap<QString, MCheckDot*>*& checkDotList();//返回判定点容器的引用
	QSize oriSize();//返回*OriSize，用于自适应的实现
	QWidget*& MParent();//返回Parent，用于溯源
	void setTime(qint64 ms);//设定当前时间，通常只在曲谱开始时调用，将时间置零
	qint64 time();//返回time_ms
};
