#pragma once
#include"MCenter.h"

class MCheckDot;

class MNote
{
public:
#define click 0x01
#define catch 0x00
#define hold 0x10
#define beat 0x11

private:
	MCheckDot* Parent;//�洢parent��������Դ
	bool* Visuable;//�����Ƿ�ɼ�
	qreal* Radium;//�������߼��뾶
	qreal* VRadium;//�������Ӿ��뾶
	qreal* Width;//������Ե�Ŀ��
	qreal* VWidth;//������Ե���Ӿ����
	QColor* NoteColor;//��������ɫ
	qint32* Type;//����������
	qint32* BeatKey;//beat����ר�еĶ����
	QString* BeatKeyText;//beat����ר�еĶ�����ı�
	qint64* Time;//�������ж�ʱ��
	qint64* TimeLength;//hold����ר�еĳ���ʱ��
	qint64* EndTime;//hold����רҵ���ж�����ʱ��
	qint64* NextTime;//��һ���������ж�ʱ�䣬���������ж����������Ƶ�ʵ��

public:
	MNote(MCheckDot* parent = nullptr);
	~MNote();

	void MNoteSet(bool visuable, qreal radium = -1, qreal width = -1, QColor color = Qt::transparent, qint32 type = -1, qint64 time = -1, qint64 nextTime = -1, qint32 beatKey = -1, QString beatKeyText = "", qint64 timeLength = 0);//�趨�����ĸ��������Ĭ�ϲ�����ʾ���ı�

	void setVisuable(bool visuable);//�趨�����Ƿ�ɼ�
	bool visuable();//����*Visuable
	void setRadium(qreal r);//�趨�������߼��뾶
	qreal radium();//����*Radium
	qreal vRadium();//����*VRadium
	void setWidth(qreal width);//�趨������Ե���߼����
	qreal width();//����*Width
	qreal vWidth();//����*VWidth
	void setNoteColor(QColor color);//�趨������ɫ��RGBA��
	void setNoteColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨������ɫ��RGBA��
	QColor noteColor();//����*NoteColor
	void setType(qint32 type);//�趨��������
	qint32 type();//����*Type
	void setBeatKey(qint32 key, QString keytext);//�趨beat����ר�еĶ����
	qint32 beatKey();//����*BeatKey
	QString beatKeyText();//����*BeatKeyText
	void setTime(qint64 time_ms);//�趨�������ж�ʱ��
	qint64 time();//����*Time
	void setTimeLength(qint64 time_ms);//�趨hold����ר�е��ж�ʱ��
	qint64 timeLength();//����*TimeLength
	qint64 endTime();//����*EndTime
	void setNextTime(qint64 time_ms);//�趨��һ���������ж�ʱ�䣬���������ж����������Ƶ�ʵ��
	qint64 nextTime();//����*NextTime
	MCheckDot*& MParent();//����Parent��������Դ
};