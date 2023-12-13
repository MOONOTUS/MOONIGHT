#pragma once

#include"MCenter.h"

class MCheckDot;

class MWidget : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);//������д�Ļ��ƺ���

signals:

public slots:
	void timeAdd_ms();//��ʱ�ۣ���parent->litTime���ź�timeout()����

private:
	QWidget* Parent;//�洢�������ָ��
	QPixmap* backImage;//����ͼƬ
	QPixmap* backBackImage;//��䱳���հ׵�ģ������ͼƬ�������ñ���ͼƬʱ�Զ����ɣ�
	QColor* backCoverColor;//��������ɫ��RGBA��
	QColor* backColor;//����ɫ��RGBA��
	QSize* OriSize;//ԭʼ�ߴ磬����ֵ����������Ӧ��ʵ��
	QMap<QString, MCheckDot*>* CheckDotList;//�ж����QMap����������ͨ��Keyֵ��ȡ��Ӧ���ж��㣬һ�㽨������ж�����ж�����Keyֵ
	bool* ifShowBackImage;//�Ƿ���ʾ����ͼƬ
	bool* ifShowBackBackImage;//�Ƿ���ʾ�����ı���ͼƬ
	bool* ifShowLogo;//�Ƿ���ʾ��־
	qint64* time_ms;//��msΪ��λ�ļ�ʱ
	QPixmap* Logo;//MOONOIGHT�ı�־ͼƬ

public:
	MWidget(QWidget* parent = nullptr);
	~MWidget();

	void setBackImage(QString& path);//�趨����ͼƬ��ͬʱ���ɱ�����ģ������
	void setBackImage(QPixmap& image);//�趨����ͼƬ��ͬʱ���ɱ�����ģ������
	void setBackColor(QColor color);//�趨����ɫ
	void setBackColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨����ɫ
	void setBackCoverColor(QColor color);//�趨��������ɫ
	void setBackCoverColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//�趨��������ɫ
	void setShowBackImage(bool show);//�趨�Ƿ���ʾ����ͼƬ
	void setShowBackBackImage(bool show);//�趨�Ƿ���ʾ�����ı���ͼƬ
	void setShowLogo(bool show);//�趨�Ƿ���ʾ��־
	bool showBackImage();//����*ifShowBackImage
	bool showBackBackImage();//����*ifShowBackBackImage
	bool showLogo();//����*ifSHowLogo
	void setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist);//�趨�ж�������
	QMap<QString, MCheckDot*>*& checkDotList();//�����ж�������������
	QSize oriSize();//����*OriSize����������Ӧ��ʵ��
	QWidget*& MParent();//����Parent��������Դ
	void setTime(qint64 ms);//�趨��ǰʱ�䣬ͨ��ֻ�����׿�ʼʱ���ã���ʱ������
	qint64 time();//����time_ms
};
