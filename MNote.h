﻿#pragma once
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
	MCheckDot* Parent;//存储parent，用于溯源
	bool* Visuable;//音符是否可见
	qreal* Radium;//音符的逻辑半径
	qreal* VRadium;//音符的视觉半径
	qreal* Width;//音符边缘的宽度
	qreal* VWidth;//音符边缘的视觉宽度
	QColor* NoteColor;//音符的颜色
	QColor* LineColor;
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

	void MNoteSet(bool visuable, qreal radium = -1, qreal width = -1, QColor color = Qt::transparent, qint32 type = -1, qint64 time = -1, qint64 nextTime = -1, qint32 beatKey = -1, QString beatKeyText = "", qint64 timeLength = 0, qreal speed  = -1);//设定音符的各项参数，默认参数表示不改变

	void setVisuable(bool visuable);//设定音符是否可见
	bool visuable();//返回*Visuable
	void setRadium(qreal r);//设定音符的逻辑半径
	qreal radium();//返回*Radium
	qreal vRadium();//返回*VRadium
	void setWidth(qreal width);//设定音符边缘的逻辑宽度
	qreal width();//返回*Width
	qreal vWidth();//返回*VWidth
	void setNoteColor(QColor color);//设定音符颜色（RGBA）
	void setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定音符颜色（RGBA）
	QColor noteColor();//返回*NoteColor
	void setLineColor(QColor color);//设定音符颜色（RGBA）
	void setLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定音符颜色（RGBA）
	QColor lineColor();//返回*NoteColor
	void setType(qint32 type);//设定音符类型
	qint32 type();//返回*Type
	void setBeatKey(qint32 key, QString keytext);//设定beat音符专有的额外键
	qint32 beatKey();//返回*BeatKey
	QString beatKeyText();//返回*BeatKeyText
	void setTime(qint64 time_ms);//设定音符的判定时间
	qint64 time();//返回*Time
	void setTimeLength(qint64 time_ms);//设定hold音符专有的判定时长
	qint64 timeLength();//返回*TimeLength
	qint64 endTime();//返回*EndTime
	void setVTime(qint64 time_ms);//设定音符的视觉时间
	qint64 vTime();//音符的视觉时间
	void setVTimeLength(qint64 time_ms);//设定hold音符专有的视觉时长
	qint64 vTimeLength();//hold音符专有的视觉时长
	qint64 vEndTime();//hold音符专有的视觉结束时间
	void setNextTime(qint64 time_ms);//设定下一个音符的判定时间，用于音符判定和音符绘制的实现
	qint64 nextTime();//返回*NextTime
	MCheckDot*& MParent();//返回Parent，用于溯源
	void setSpeed(qreal speed);//设定音符的独立逻辑速度
	qreal speed();//音符的独立逻辑速度
	qreal vSpeed();//音符的独立视觉速度
};