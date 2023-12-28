#pragma once

#include"MCenter.h"

class MCheckDot;
class MFormerCalculator;

class MWidget : public QWidget
{
#define FULLSCORE 1000000

	Q_OBJECT

protected:
	void paintEvent(QPaintEvent* event);//经过重写的绘制函数
	void keyPressEvent(QKeyEvent* event);//重写的键盘按下事件函数
	void keyReleaseEvent(QKeyEvent* event);//重写的键盘释放事件函数
	void mouseDoubleClickEvent(QMouseEvent* event);
	void closeEvent(QCloseEvent* event);


signals:
	void keyPressDown(QKeyEvent* event);
	void keyReleaseUp(QKeyEvent* event);

public slots:
	void timeAdd_ms();//计时槽，与parent->litTime的信号timeout()连接

private:
	static QSize* OriSize;//原始尺寸，固有值，用于自适应的实现
	QWidget* Parent;//存储父对象的指针
	QPixmap* backImage;//背景图片
	QPixmap* backBackImage;//填充背景空白的模糊背景图片（在设置背景图片时自动生成）
	QColor* backCoverColor;//背景遮罩色（RGBA）
	QColor* backColor;//背景色（RGBA）
	QMap<QString, MCheckDot*>* CheckDotList;//判定点的QMap容器，可以通过Key值获取对应的判定点，一般建议采用判定点的判定键做Key值
	bool* ifShowBackImage;//是否显示背景图片
	bool* ifShowBackBackImage;//是否显示背景的背景图片
	bool* ifShowLogo;//是否显示标志
	qint64* time_ms;//实际时间
	qint64* fixtime_ms;//修正时长，用于暂停
	QPixmap* Logo;//MOONOIGHT的标志图片
	QTimer* MainTime;//以10ms为周期的计时器，用于谱面设计
	QTimer* LitTime;//以1ms为周期的计时器，用于曲谱计时
	QTimer* FlushTime;//以5ms为周期的计时器，用于画面刷新
	QElapsedTimer* DisTime;//间隔计时器，用于曲谱计时
	QElapsedTimer* FixTime;//修正计时器，用于暂停的实现
	QSet<qint32>* KeyPressingList;//按键列表
	qint64* GapDelay;//空白延迟
	qint64* FixDelay;//修正延迟
	qint64* Delay;//总延迟
	QString* MusicPath;//乐曲路径
	QString* MusicName;//曲谱名称
	QAudioOutput* PlayerBase;//音频输出
	QMediaPlayer* Player;//音频解码
	bool* MusicPlayed;//乐曲启动状态
	QVector<qint32>* CheckList;//判定列表
	qint64* Combo;//连击数
	MFormerCalculator* Calculator;//计数器
	qint64* NoteCheckedSum;//已判定音符总数
	qint64* NoteSum;//音符总数
	qint64* Score;//分数
	qint64* EachScore;//每个音符的strictperf分数
	qreal* Accuracy;//准度
	bool* Pausing;//暂停状态

public:
	MWidget(QWidget* parent = nullptr);
	~MWidget();

	inline void setBackImage(QString& path);//设定背景图片，同时生成背景的模糊背景
	inline void setBackImage(QPixmap& image);//设定背景图片，同时生成背景的模糊背景
	inline void setBackColor(QColor color);//设定背景色
	inline void setBackColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定背景色
	inline void setBackCoverColor(QColor color);//设定背景遮罩色
	inline void setBackCoverColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定背景遮罩色
	inline void setShowBackImage(bool show);//设定是否显示背景图片
	inline void setShowBackBackImage(bool show);//设定是否显示背景的背景图片
	inline void setShowLogo(bool show);//设定是否显示标志
	inline bool showBackImage();//背景图片的可见性
	inline bool showBackBackImage();//背景的背景的可见性
	inline bool showLogo();//标志可见性
	inline void setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist);//设定判定点容器
	inline QMap<QString, MCheckDot*>*& checkDotList();//返回判定点容器的引用
	inline QSize oriSize() const;//返回*OriSize，用于自适应的实现
	inline void setTime(qint64 ms);//设定当前时间，通常只在曲谱开始时调用，将时间置零
	inline qint64 time() const;//返回经修正的当前时间
	inline qint64 fixtime() const;//返回修正时长
	inline QElapsedTimer*& disTime();//间隔计时器
	inline QSet<qint32>*& keyPressingList();//按键列表
	inline void setGapDelay(qint64 delay);//设定空白延迟
	inline void setFixDelay(qint64 delay);//设定修正延迟
	inline qint64 delay() const;//总延迟
	inline qint64 fixDelay() const;//修正延迟
	inline qint64 gapDelay() const;//空白延迟
	inline void setMusicPath(QString path);//设定音乐路径
	inline QString musicPath() const;//音乐路径
	inline void setMusicName(QString name);//设定曲谱名称
	inline QString musicName() const;//曲谱名称
	inline void playMusic(bool nodelay = false);//播放音乐
	inline void addCheck(qint32 check, qint64 time, qint64 timems);//添加判定结果
	inline QVector<qint32>*& checkList();//判定列表
	inline qreal visualProportion() const;//视觉比例
	inline qreal visualProportionX() const;//视觉比例
	inline qreal visualProportionY() const;//视觉比例
	inline void addToTitle(QString addtitle);//向窗口标题追加文本
	inline qint64 combo() const;//连击数
	inline void setFormerCalculator(MFormerCalculator* formercalculator);//设定计数器
	inline MFormerCalculator*& formerCalculator();//计数器
	inline qint64 score() const;//分数
	inline qint64 eachscore() const;//每个音符的striperfect分数
	inline qreal accuracy() const;//准度
	inline void pause();//暂停
	inline void continues();//继续
	inline bool pausing() const;//暂停状态
	inline QTimer*& mainTime();//10ms计时器
	inline QTimer*& litTime();//1ms计时器
	inline void setover();//曲谱设定结束标志
	inline QWidget*& MParent();//返回Parent，用于溯源
};
