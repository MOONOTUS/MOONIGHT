#pragma once

#include"MCenter.h"
#include"MCheckDotLine.h"
#include"MNote.h"

class MWidget;

class MCheckDot  : public QPushButton
{
	Q_OBJECT

public:
#define strictperfect 0x1111
#define preperfect 0x1011
#define lagperfect 0x0011
#define pregood 0x1010
#define laggood 0x0010
#define prebad 0x1001
#define lagbad 0x0001
#define miss 0x0000
#define ANIMATIONTHINESS 1.5

protected:
	void paintEvent(QPaintEvent* event);//重写的重绘函数
	//void keyPressEvent(QKeyEvent* event);//重写的键盘按下事件函数
	//void keyReleaseEvent(QKeyEvent* event);//重写的键盘释放事件函数

	void paintDot(QPainter* paint);//绘制判定点
	void paintDotLine(QPainter* paint);//绘制判定线
	void paintNote(QPainter* paint);//绘制音符
	void paintClickNote(QPainter* paint);//绘制click音符
	void paintCatNote(QPainter* paint);//绘制cat音符
	void paintBeatNote(QPainter* paint);//绘制beat音符
	void paintHoldNote(QPainter* paint_);//绘制hold音符
	void paintCheckAnimation(QPainter* paint);

signals:
	void touched();//触发信号
	void released();//释放信号
	void misschecked();//掉落信号

public slots:
	void check();//判定槽
	void aftercheck();//hold音符专用的释放判定槽
	void misscheck();//掉落槽
	void press(QKeyEvent* event);
	void release(QKeyEvent* event);

private:
	MWidget* Parent;//存储parent指针，用于溯源
	MCheckDotLine* DotLine;//轨道
	QMap<qint64, MNote*>* NoteList;//音符容器，可以通过Key值获取对应的音符，一般建议采用音符的判定时间做Key值
	qint64* NextTime;//下一个音符的判定时间，用于实现音符的判定和绘制
	QMap<qint64, qint32>* NoteCheckList;//判定结果容器，与音符的Key值一一对应存放判定结果
	bool* Visuable;//判定点是否可见
	QPoint* Point;//判定点的逻辑坐标
	qreal* Radium;//判定点的逻辑半径
	qreal* Width;//判定点圆圈的逻辑宽度
	QColor* DotColor;//判定点的颜色（RGBA）
	QColor* DotKeyColor;//判定键的颜色（RGBA）
	qint32* Key;//判定键
	QString* KeyText;//在屏幕上显示的判定键文本
	bool* KeyVisuable;//判定键文本是否可见
	QPoint* VPoint;//判定点的视觉坐标
	qreal* VRadium;//判定点的视觉半径
	qreal* VWidth;//判定点圆圈的视觉宽度
	QSet<qint32>* KeyPressingList;//正在被按下的按键
	bool* HoldPressing;//是否有hold音符正被按下
	qint64* HoldPressed;//正被按下的hold音符Key值，若没有则为0
	qreal* Speed;//音符的逻辑速度
	qreal* VSpeed;//音符的视觉速度
	qreal* LineRadium;//轨道线的逻辑长度
	qreal* VLineRadium;//轨道线的视觉长度
	QMap<qint64, qint32>* NoteCheckAnimationList;//打击特效列表
	qreal* Digonal;//打击误差

public:
	MCheckDot(MWidget *parent = nullptr);
	~MCheckDot();

	void setDotLine(MCheckDotLine& dotline);//设定轨道线
	MCheckDotLine*& dotLine();//返回轨道线的引用
	void setVisuable(bool visuable);//设定判定点是否可见
	bool visuable();//返回*Visuable
	void setPoint(QPoint& point);//设定判定点的逻辑坐标
	void setPoint(qreal x, qreal y);//设定判定点的逻辑坐标
	QPoint point();//返回判定点的逻辑坐标
	void setRadium(qreal r);//设定判定点的逻辑半径
	qreal radium();//返回*Radium
	void setWidth(qreal width);//设定判定点圆圈的逻辑宽度
	qreal width();//返回*Width
	void setDotColor(QColor color);//设定判定点颜色
	void setDotColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定判定点颜色
	QColor dotColor();//返回*DotColor
	void setDotKeyColor(QColor color);//设定判定键的颜色
	void setDotKeyColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定判定键的颜色
	QColor dotKeyColor();//返回*DotKeyColor
	void setKey(qint32 key, QString keytext);//设定判定键
	qint32 key();//返回*Key
	QString keyText();//返回*KeyText
	QMap<qint64, MNote*>*& noteList();//返回音符容器的引用
	void setNextTime(qint64 time_ms);//设定下一个音符的判定时间
	qint64 nextTime();//返回*NextTime
	QMap<qint64, qint32>*& noteCheckList();//返回判定结果容器的引用
	MWidget*& MParent();//返回Parent，用于溯源
	void setKeyVisuable(bool visuable);//设定判定键文本是否可见
	bool keyVisuable();//返回*KeyVisuable
	void setSpeed(qreal speed_px_ps);//设定音符的逻辑速度
	qreal speed();//返回音符逻辑速度
	void setLineRadium(qreal lineradium);//设定轨道线的逻辑长度
	qreal lineRadium();//返回轨道线逻辑长度
	void addNote(qint64 time = 0, qint64 nexttime = 0, qint32 type = click, qint64 timelength = 0, qint32 beatkey = Qt::Key_Escape, QString beatkeytext = "");//快捷添加新Note
	void addNote(QColor notecolor = Qt::transparent, qint64 time = 0, qint64 nexttime = 0, qint32 type = click, qint64 timelength = 0, qint32 beatkey = Qt::Key_Escape, QString beatkeytext = "");//快捷添加新Note
	void addNote(QColor notecolor = Qt::transparent, QColor LineColor = Qt::transparent, qint64 time = 0, qint64 nexttime = 0, qint32 type = click, qint64 timelength = 0, qint32 beatkey = Qt::Key_Escape, QString beatkeytext = "");//快捷添加新Note

};
