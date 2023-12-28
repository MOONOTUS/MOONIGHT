#pragma once
#include"MCenter.h"

class MCheckDot;

class MNote
{
public:
#define click 0x01
#define cat 0x00
#define hold 0x10
#define beat 0x11

private:
	static QColor* AutoNoteColor;
	static qint32* AutoNoteType;
	static QColor* AutoLineColor;
	static QColor* AutoKeyColor;

private:
	MCheckDot* Parent;//存储parent，用于溯源
	bool* Visuable;//音符是否可见
	qreal* Radium;//音符的逻辑半径
	qreal* VRadium;//音符的视觉半径
	qreal* Width;//音符边缘的宽度
	qreal* VWidth;//音符边缘的视觉宽度
	QColor* NoteColor;//音符的颜色
	QColor* LineColor;
	QColor* KeyColor;
	qint32* Type;//音符的类型
	qint32* BeatKey;//beat音符专有的额外键
	QString* BeatKeyText;//beat音符专有的额外键文本
	qint64* Time;//音符的判定时间
	qint64* TimeLength;//hold音符专有的持续时长
	qint64* EndTime;//hold音符专有的判定介绍时间
	qint64* VTime;//音符的视觉时间
	qint64* VTimeLength;//hold音符专有的视觉时长
	qint64* VEndTime;//hold音符专有的视觉结束时间
	qint64* NextTime;//下一个音符的判定时间，用于音符判定和音符绘制的实现
	qreal* Speed;//音符的独立逻辑速度，-1代表依照判定点指定的速度运动
	qreal* VSpeed;//音符的独立视觉速度，-1代表依照判定点指定的速度运动

public:
	MNote(MCheckDot* parent = nullptr);
	MNote(MNote* note);
	~MNote();

	inline void MNoteSet(bool visuable, qreal radium = -1, qreal width = -1, QColor color = Qt::transparent, qint32 type = -1, qint64 time = -1, qint64 nextTime = -1, qint32 beatKey = -1, QString beatKeyText = "", qint64 timeLength = 0, qreal speed  = -1);//设定音符的各项参数，默认参数表示不改变
	inline 
	inline void setVisuable(bool visuable);//设定音符是否可见
	inline bool visuable() const;//返回*Visuable
	inline void setRadium(qreal r);//设定音符的逻辑半径
	inline qreal radium() const;//返回*Radium
	inline qreal vRadium() const;//返回*VRadium
	inline void setWidth(qreal width);//设定音符边缘的逻辑宽度
	inline qreal width() const;//返回*Width
	inline qreal vWidth() const;//返回*VWidth
	inline void setNoteColor(QColor color);//设定音符颜色（RGBA）
	inline void setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定音符颜色（RGBA）
	inline QColor noteColor() const;//返回*NoteColor
	inline void setLineColor(QColor color);//设定音符颜色（RGBA）
	inline void setLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定音符颜色（RGBA）
	inline QColor lineColor() const;//返回*NoteColor
	inline void setKeyColor(QColor color);//设定音符颜色（RGBA）
	inline void setKeyColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定音符颜色（RGBA）
	inline QColor keyColor() const;//返回*KeyColor
	inline void setType(qint32 type);//设定音符类型
	inline qint32 type() const;//返回*Type
	inline void setBeatKey(qint32 key, QString keytext);//设定beat音符专有的额外键
	inline qint32 beatKey() const;//返回*BeatKey
	inline QString beatKeyText() const;//返回*BeatKeyText
	inline void setTime(qint64 time_ms);//设定音符的判定时间
	inline qint64 time() const;//返回*Time
	inline void setTimeLength(qint64 time_ms);//设定hold音符专有的判定时长
	inline qint64 timeLength() const;//返回*TimeLength
	inline qint64 endTime() const;//返回*EndTime
	inline void setVTime(qint64 time_ms);//设定音符的视觉时间
	inline qint64 vTime() const;//音符的视觉时间
	inline void setVTimeLength(qint64 time_ms);//设定hold音符专有的视觉时长
	inline qint64 vTimeLength() const;//hold音符专有的视觉时长
	inline qint64 vEndTime() const;//hold音符专有的视觉结束时间
	inline void setNextTime(qint64 time_ms);//设定下一个音符的判定时间，用于音符判定和音符绘制的实现
	inline qint64 nextTime() const;//返回*NextTime
	inline MCheckDot*& MParent();//返回Parent，用于溯源
	inline void setSpeed(qreal speed);//设定音符的独立逻辑速度
	inline qreal speed() const;//音符的独立逻辑速度
	inline qreal vSpeed() const;//音符的独立视觉速度
	inline static void setAutoNoteColor(QColor color);
	inline static void setAutoNoteColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	inline static QColor autoNoteColor();
	inline static void setAutoNoteType(qint32 type);
	inline static qint32 autoNoteType();
	inline static void setAutoLineColor(QColor color);
	inline static void setAutoLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	inline static QColor autoLineColor();
	inline static void setAutoKeyColor(QColor color);
	inline static void setAutoKeyColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);
	inline static QColor autoKeyColor();
};