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

##### 更新日志

###### 2023/12/29

1. 实现了计数器

2. 实现了偏差量计

3. 添加了统合元件

###### 2023/12/25

1. 重构了计时逻辑
2. 实现了暂停

###### 2023/12/20

1. 重构了判定逻辑

2. 缩窄了判定区间

3. 实现了判定动画 

###### 2023/12/15

1. 规避了Qt的阻塞式事件循环，实现了曲谱与时间的强相关

2. 修正了时间轴偏移

3. 实现了音符的绘制

---

##### 接下来的更新目标

1. 实现主界面

2. 添加以BPM为基础的制谱方法

---

##### 为开发者提供的项目介绍

---

采用Qt图形库。

采用C++20标准。

采用AVX2增强指令集。

---

本项目中的窗口/组件类：

```c++

```

```
本项目采用自适应设计方法，所有的设计只需要基于Size =（3200，1800）的原点在左上角的x轴正方向为向右、y轴正方向为向左的原始坐标系进行即可，程序会自动将设计好的界面匹配到任意尺寸的窗口上。
以下所述“逻辑坐标”即是指基于这个原始坐标系的坐标。
“视觉坐标”指的是在屏幕上显示的基于实际显示区大小的坐标。
```

---

注释正在补全中。

---

##### 为谱面编辑师提供的项目介绍

---

正在补全中。

---



$$
designed-by- MOONOTUS
$$
