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

protected:
	void paintEvent(QPaintEvent* event);//��д���ػ溯��
	void keyPressEvent(QKeyEvent* event);//��д�ļ��̰����¼�����
	void keyReleaseEvent(QKeyEvent* event);//��д�ļ����ͷ��¼�����

	void paintDot(QPainter* paint);//�����ж���
	void paintDotLine(QPainter* paint);//�����ж���
	void paintNote(QPainter* paint);//��������
	void paintClickNote(QPainter* paint);//����click����
	void paintCatchNote(QPainter* paint);//����catch����
	void paintBeatNote(QPainter* paint);//����beat����
	void paintHoldNote(QPainter* paint_);//����hold����

signals:
	void touched();//�����ź�
	void released();//�ͷ��ź�
	void misschecked();//�����ź�

public slots:
	void check();//�ж���
	void aftercheck();//hold����ר�õ��ͷ��ж���
	void misscheck();//�����

private:
	MCheckDotLine* DotLine;//���
	QMap<qint64, MNote*>* NoteList;//��������������ͨ��Keyֵ��ȡ��Ӧ��������һ�㽨������������ж�ʱ����Keyֵ
	qint64* NextTime;//��һ���������ж�ʱ�䣬����ʵ���������ж��ͻ���
	QMap<qint64, qint32>* NoteCheckList;//�ж������������������Keyֵһһ��Ӧ����ж����
	bool* Visuable;//�ж����Ƿ�ɼ�
	QPoint* Point;//�ж�����߼�����
	qreal* Radium;//�ж�����߼��뾶
	qreal* Width;//�ж���ԲȦ���߼����
	QColor* DotColor;//�ж������ɫ��RGBA��
	QColor* DotKeyColor;//�ж�������ɫ��RGBA��
	qint32* Key;//�ж���
	QString* KeyText;//����Ļ����ʾ���ж����ı�
	bool* KeyVisuable;//�ж����ı��Ƿ�ɼ�
	MWidget* Parent;//�洢parentָ�룬������Դ
	QPoint* VPoint;//�ж�����Ӿ�����
	qreal* VRadium;//�ж�����Ӿ��뾶
	qreal* VWidth;//�ж���ԲȦ���Ӿ����
	QSet<qint32>* KeyPressingList;//���ڱ����µİ���
	bool* HoldPressing;//�Ƿ���hold������������
	qint64* HoldPressed;//�������µ�hold����Keyֵ����û����Ϊ0
	qreal* Speed;//�������߼��ٶ�
	qreal* VSpeed;//�������Ӿ��ٶ�
	qreal* LineRadium;//����ߵ��߼�����
	qreal* VLineRadium;//����ߵ��Ӿ�����


public:
	MCheckDot(MWidget *parent = nullptr);
	~MCheckDot();

	void setDotLine(MCheckDotLine& dotline);//�趨�����
	MCheckDotLine*& dotLine();//���ع���ߵ�����
	void setVisuable(bool visuable);//�趨�ж����Ƿ�ɼ�
	bool visuable();//����*Visuable
	void setPoint(QPoint& point);//�趨�ж�����߼�����
	void setPoint(qreal x, qreal y);//�趨�ж�����߼�����
	QPoint point();//�����ж�����߼�����
	void setRadium(qreal r);//�趨�ж�����߼��뾶
	qreal radium();//����*Radium
	void setWidth(qreal width);//�趨�ж���ԲȦ���߼����
	qreal width();//����*Width
	void setDotColor(QColor color);//�趨�ж�����ɫ
	void setDotColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨�ж�����ɫ
	QColor dotColor();//����*DotColor
	void setDotKeyColor(QColor color);//�趨�ж�������ɫ
	void setDotKeyColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨�ж�������ɫ
	QColor dotKeyColor();//����*DotKeyColor
	void setKey(qint32 key, QString keytext);//�趨�ж���
	qint32 key();//����*Key
	QString keyText();//����*KeyText
	QMap<qint64, MNote*>*& noteList();//������������������
	void setNextTime(qint64 time_ms);//�趨��һ���������ж�ʱ��
	qint64 nextTime();//����*NextTime
	QMap<qint64, qint32>*& noteCheckList();//�����ж��������������
	MWidget*& MParent();//����Parent��������Դ
	void setKeyVisuable(bool visuable);//�趨�ж����ı��Ƿ�ɼ�
	bool keyVisuable();//����*KeyVisuable
	void setSpeed(qreal speed_px_ps);//�趨�������߼��ٶ�
	qreal speed();//����*Speed
	void setLineRadium(qreal lineradium);//�趨����ߵ��߼�����
	qreal lineRadium();//����*LineRadium

};
