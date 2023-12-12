# MOONIGHT

# 月夜圆舞

###### MOONOTUS|荷月语



你好，这里是MOONOTUSTUDIO，我是MOONOTUS|荷月语。

这个项目的名字叫做MOONIGHT|月夜圆舞，是一个略有一些些创新的音游。

有意思的是，我准备在不使用任何游戏引擎的前提下，通过纯粹的代码，借助一些第三方库，来实现这个项目。

你可能会感到疑惑，在现在这个时代，游戏引擎为我们提供了极大的便利，为什么还要吃力不讨好地通过手搓来实现一个游戏。

说的没错。

但是，

我也不知道。

可能这就是一种浪漫。

其实这个企划，最开始只是我偶然的天马行空，但当我尝试通过代码去实现某些功能的时候，却逐渐痴迷其中，于是，我决定做下去。

经过一番考虑，我决定将这个企划开源，我把全部的代码上传到Gitee，也许之后会同步到Github，希望对此感兴趣的人，偶然间看到这个项目的人，能够共同参与到这个企划中来，这是——属于所有人的浪漫。

实际上，开源还有其他的考量，其中很重要的一项就是避免我自己没法坚持下去，而导致她无法继续进行，如果有一天我真的敲不动了，希望有人，能代我继续，坚持下去。

---

###### 更新日志

1.    实现了准度判定；

2.    实现了模糊；

 3.    实现了分离窗口。

---

###### 接下来的更新目标

1.    实现音符绘制；

2.    优化模糊算法执行效率；

3.    实现启动动画；

4.    编写第一个测试关卡。    

---

###### 为开发者提供的项目介绍

---

采用Qt图形库。

采用C++20标准。

采用AVX2增强指令集。

---

本项目中的窗口/组件类：

```c++
class MOONIGHT_Qt : public QMainWindow;//主窗口
class MWidget : public QWidget;//经过重写的窗口类
class MCheckDot : public QPushButton;//判定点
class MCheckDotLine;//轨道线
class MNote;//音符
```

```
本项目采用自适应设计方法，所有的设计只需要基于Size =（1920，1080）的原点在左上角的x轴正方向为向右、y轴正方向为向左的原始坐标系进行即可，程序会自动将设计好的界面匹配到任意尺寸的窗口上。
以下所述“逻辑坐标”即是指基于这个原始坐标系的坐标。
“视觉坐标”指的是在屏幕上显示的基于实际显示区大小的坐标。
```

```c++
class MOONIGHT_Qt : public QMainWindow
{
    Q_OBJECT

public:
    MOONIGHT_Qt(QWidget *parent = nullptr);
    ~MOONIGHT_Qt();
    Ui::MOONIGHT_QtClass* Ui();

public slots:

private:
    Ui::MOONIGHT_QtClass ui;
};

//调用MOONIGHT_Qt的成员函数Ui()，返回其私有成员ui的指针，ui中有三个成员：

public:
    MWidget *central;
    QTimer* mainTime;
    QTimer*

//其中，central是主窗口的核心组件，其它组件全部分支于central的对象树下；
//mainTime是一个以10ms为周期的计时器，用于动效的实现；
//litTime是一个以1ms为周期的计时器，用于曲谱的计时。
```

```c++
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
    qint64* time_ms;//以ms为单位的计时

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
    bool showBackImage();//返回ifShowBackImage
    bool showBackBackImage();//返回ifShowBackBackImage
    void setCheckDotList(QMap<QString, MCheckDot*>*& checkdotlist);//设定判定点容器
    QMap<QString, MCheckDot*>*& checkDotList();//返回判定点容器的引用
    QSize oriSize();//返回OriSize，用于自适应的实现
    QWidget*& MParent();//返回Parent，用于溯源
    void setTime(qint64 ms);//设定当前时间，通常只在曲谱开始时调用，时间置零
    qint64 time();//返回time_ms
};
```

```c++
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
    void paintEvent(QPaintEvent* event);//重写的重绘函数
    void keyPressEvent(QKeyEvent* event);//重写的键盘按下事件函数
    void keyReleaseEvent(QKeyEvent* event);//重写的键盘释放事件函数

    void paintDot(QPainter* paint);//绘制判定点
    void paintDotLine(QPainter* paint);//绘制判定线
    void paintNote(QPainter* paint);//绘制音符

signals:
    void touched();//触发信号
    void released();//释放信号
    void misschecked();//掉落信号

public slots:
    void check();//判定槽
    void aftercheck();//hold音符专用的释放判定槽
    void misscheck();//掉落槽

private:
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
    MWidget* Parent;//存储parent指针，用于溯源
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
    void setSpeed(qreal speed_px);//设定音符的逻辑速度
    qreal speed();//返回*Speed
    void setLineRadium(qreal lineradium);//设定轨道线的逻辑长度
    qreal lineRadium();//返回*LineRadium

};
```

```c++
class MCheckDotLine
{

    Q_OBJECT

private:
    MCheckDot* Parent;//存储parent，用于溯源
    bool* Visuable;//轨道线是否可见
    qreal* Width;//轨道线的逻辑宽度
    qreal* Angel;//轨道线的角度
    QColor* DotLineColor;//轨道线的颜色（RGBA）
    qreal* VWidth;//轨道线的视觉宽度

public:
    MCheckDotLine(MCheckDot* parent = nullptr);
    ~MCheckDotLine();

    void setVisuable(bool visuable);//设定轨道线是否可见
    bool visuable();//返回*Visuable
    void setWidth(qreal width);//设定轨道线的逻辑宽度
    qreal width();//返回*Width
    void setAngel(qreal angle);//设定轨道线的角度
    qreal angle();//返回*Angle
    void setDotLineColor(QColor color);//设定轨道线的颜色
    void setDotLineColor(qint32 R, qint32 G, qint32 B, qint32 A = 255);//设定轨道线的颜色
    QColor dotLineColor();//返回*DotLineColor
    qreal vWidth();//返回*VWidth
    MCheckDot*& MParent();//返回Parent，用于溯源
};
```

```c++
class MNote
{
public:
#define click 0x01
#define catch 0x00
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
	qint32* Type;//音符的类型
	qint32* BeatKey;//beat音符专有的额外键
	QString* BeatKeyText;//beat音符专有的额外键文本
	qint64* Time;//音符的判定时间
	qint64* TimeLength;//hold音符专有的持续时长
	qint64* EndTime;//hold音符专业的判定介绍时间
	qint64* NextTime;//下一个音符的判定时间，用于音符判定和音符绘制的实现

public:
	MNote(MCheckDot* parent = nullptr);
	~MNote();

	void MNoteSet(bool visuable, qreal radium = -1, qreal width = -1, QColor color = Qt::transparent, qint32 type = -1, qint64 time = -1, qint64 nextTime = -1, qint32 beatKey = -1, QString beatKeyText = "", qint64 timeLength = 0);//设定音符的各项参数，默认参数表示不改变

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
	void setNextTime(qint64 time_ms);//设定下一个音符的判定时间，用于音符判定和音符绘制的实现
	qint64 nextTime();//返回*NextTime
	MCheckDot*& MParent();//返回Parent，用于溯源
};
```

---

注释正在补全中。

---

###### 为谱面编辑师提供的项目介绍

---

正在补全中。

---



$$
designed-by- MOONOTUS
$$
