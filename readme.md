#  用C/C++制作一个简单的俄罗斯方块小游戏

<!-- [toc] -->
- [用C/C++制作一个简单的俄罗斯方块小游戏](#用cc制作一个简单的俄罗斯方块小游戏)
	- [0 准备](#0-准备)
	- [1 游戏界面设计](#1-游戏界面设计)
		- [1.1 界面布局](#11-界面布局)
		- [1.2 用 EasyX 显示界面](#12-用-easyx-显示界面)
		- [1.3 音乐播放](#13-音乐播放)
	- [2 方块设计](#2-方块设计)
		- [2.1 方块显示](#21-方块显示)
		- [2.2 随机生成一个方块](#22-随机生成一个方块)
		- [2.3 方块记录](#23-方块记录)
	- [3 方块移动和旋转](#3-方块移动和旋转)
		- [3.1 方块的移动](#31-方块的移动)
		- [3.2 方块的旋转](#32-方块的旋转)
		- [3.3 方块的碰撞和消除](#33-方块的碰撞和消除)
			- [3.3.1 碰撞](#331-碰撞)
			- [3.3.2 消除](#332-消除)
			- [3.3.3 分数和下落速度](#333-分数和下落速度)
			- [3.3.4 game over](#334-game-over)
	- [4 制作 exe 文件](#4-制作-exe-文件)
	- [5 总结](#5-总结)

![在这里插入图片描述](https://img-blog.csdnimg.cn/8994a9e5476a4c2f8629cab160843176.png)
## 0 准备

- 开发环境：Windows
- 编程语言：C/C++
- 开发软件：Visual Studio 2022 (软件安装可参考：链接: [Visual Studio 2022 免费版最新版本下载安装教程](https://blog.csdn.net/u011895157/article/details/128611019)
- 图形插件：EasyX

EasyX 的安装非常简单，百度搜索以下即可，**但是在安装前一定要先安装 Visual Studio**。下面的章节给出如何使用它。

## 1 游戏界面设计

### 1.1 界面布局

首先，我们要选择一章图片作为游戏的背景，我们可以在图片网站上下载合适的背景图片。

其次，在背景图片上划分出，游戏区和显示区，一般游戏区在正中间，两边为显示区。游戏区用于控制方块的移动、消除和旋转等；显示区用于速度和分数的展示。下面是我设计的游戏界面：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2ffba2436cdb4adc83f574fddd19690a.png)

用画图工具打开图片，可以看到背景大小为800*600像素，同时在图片中间设置游戏区（虚线框，大小自定义），添加速度和分数的文本框。

### 1.2 用 EasyX 显示界面

此时，我相信你应该会建立 VS 工程了，并且安装了 EasyX。

建立一个文件夹 imp ，把1.1小节中的图片放在里面。imp 文件夹和 `main.cpp` 文件同一目录。
显示图形需要调用头文件 `graphics.h`。我们需要知道显示的图形的大小，这边是800*600，显示的位置为（0，0）

```c
#include <graphics.h>

// 绘图窗口初始化
	initgraph(imp_width, imp_heght);
	loadimage(&background, _T("img/background.png"));
	putimage(0, 0, &background);
```

显示如下：

![背景显示](https://img-blog.csdnimg.cn/b47e649ab3f14db7a8c730428c6ecf4b.png)

这是一个简单的显示案例，后续方块的显示也是用这种方式。

### 1.3 音乐播放

先用 酷狗 下载一首好听的音乐，然后将音乐放在和 `main.cpp` 同一目录下。

我这边用了两首音乐，每次打开都是随机播放

程序：

```c
#include "Windows.h"
#include <time.h>

#pragma comment (lib, "winmm.lib")

void Music::palyMusic()
{
	int chFlag;
	srand((unsigned)time(NULL));
	chFlag = rand() % 2;
	
	if (chFlag == 0)
	{
		//mciSendString("close 1.mp3", NULL, 0, NULL);
		mciSendString("open 2.mp3", NULL, 0, NULL);
		mciSendString("play 2.mp3 repeat", NULL, 0, NULL);
		mciSendString("setaudio 2.mp3 volume to 100", 0, 0, 0);
	}
	else
	{
		//mciSendString("close 2.mp3", NULL, 0, NULL);
		mciSendString("open 1.mp3", NULL, 0, NULL);
		mciSendString("play 1.mp3 repeat", NULL, 0, NULL);
		mciSendString("setaudio 1.mp3 volume to 100", 0, 0, 0);
	}
}
```

## 2 方块设计

### 2.1 方块显示

设计7种方块类型：

```c
const int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};
```

方块的表示如下图所示：

![方块显示](https://img-blog.csdnimg.cn/3a27b5eab42a49eb8da3e0c6f77c2a72.png)

上面两张图表示在游戏中方块是如何表示的，方块可以由界面的横纵坐标表示，我们可以将下落的初始位置作为横坐标，方块的左边界作为纵坐标。其实就是游戏区的左上角作为坐标。

那么显示的原理知道了，就是操作数组，方块的图形呢？

![小方块显示](https://img-blog.csdnimg.cn/ad58fbc3fa554cc29b0e4d4a38f9e89e.png)

小方块的显示可以根据这张图，从上图不难看出，小方块的大小为：20*20像素。如果我们要显示第一个小方块，我们可以加载这张图片然后从坐标（0，0）开始，显示长宽为20像素的图片。同意，如果要显示第三个绿色方块，就是从坐标（40，0）开始。

下面是实现的部分程序：

```c
//计算小方块位置
blockType = rand() % 7;
for (int i = 0; i < 4; i++)
{
	smallBlock[i][0] = blocks[blockType][i] / 2;
	smallBlock[i][1] = blocks[blockType][i] % 2 + 1;//离左边界一格显示，方便旋转
}

//小方块显示函数
void Graph::block()
{
	IMAGE imgTmp;
	loadimage(&imgTmp, _T("img/small.png"));
	SetWorkingImage(&imgTmp);
	//putimage(0, 0, &imgTmp);
	for (int i = 0; i < 7; i++) {
		this->imgs[i] = new IMAGE;
		getimage(this->imgs[i], i * blocks_size, 0, blocks_size, blocks_size);
	}
	SetWorkingImage();
}
```
![初始位置](https://img-blog.csdnimg.cn/f4cc7f9705514789adc0c4a0eac0a84f.png)

### 2.2 随机生成一个方块

随机生成方块的原理就是将记录正在下落方块的数组清空初始化

```c
void Graph::random()
{
	blockType = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		smallBlock[i][0] = blocks[blockType][i] / 2;
		smallBlock[i][1] = blocks[blockType][i] % 2 + 1;//离左边界一格显示，方便变形
	}
	colBasis = 0;
	rowBasis = 0;
}
```

### 2.3 方块记录

我们不仅需要对当前正在操作的方块进行记录，还需要对已经下落还未被消除的方块进行记录。可以将游戏区看作一个二维数组，开辟一个 29*14 的二维数组进行记录。

```c
	//背景图像大小
	const unsigned int imp_width = 800;
	const unsigned int imp_heght = 600;
	//小方块大小
	const unsigned int blocks_size = 20;

	//游戏区边界
	const unsigned int left_margin = 240;
	const unsigned int right_margin = 485;
	const unsigned int down_margin = 570;
	const unsigned int up_margin = 10;
	const int rows = 29;
	const int cols = 14;
	
	//记录方块的数组
	vector<vector<int>> allBlock;
```

这里有个小技巧，因为方块要显示不同的颜色，因此我们可以用二维数组allBlock的值当作颜色的值

当allBlock[i][j]的值为0时，表示该位置没有方块；
当allBlock[i][j]的值大于0时，表示该位置有方块，显示的颜色用allBlock[i][j]的之表示

```c
//已静止方块显示
	for (int i = rows-1; i > 3; --i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if(allBlock[i][j]!=0)
				putimage(left_margin + j * blocks_size, up_margin + i * blocks_size, imgs[allBlock[i][j]-1]);
		}
	}
```

## 3 方块移动和旋转

### 3.1 方块的移动

方块的移动就是一个核心：**方块的移动 = 对数组的操作**

方块的下落 = 行坐标+1
方块的左移 = 列坐标-1
方块的右移 = 列坐标+1

前提是需要判断是否出界或者移动的下一个位置是否有方块

程序如下：

```c
void Graph::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		if (smallBlock[i][1] <= 0 || allBlock[smallBlock[i][0]][smallBlock[i][1] - 1] >= 1)
			return;
	}
	for (int i = 0; i < 4; i++)
	{
		--smallBlock[i][1];
	}
	--colBasis;
}

void Graph::moveDown()
{
	for (int i = 0; i < 4; i++)
	{
		if (smallBlock[i][0] >= rows)
			return;
	}
	for (int i = 0; i < 4; i++)
	{
		++smallBlock[i][0];
	}
	++rowBasis;
}

void Graph::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		if (smallBlock[i][1] >= cols - 1 || allBlock[smallBlock[i][0]][smallBlock[i][1] + 1] >= 1)
			return;
	}
	for (int i = 0; i < 4; i++)
	{
		++smallBlock[i][1];
	}
	++colBasis;
}
```

当然移动的前提说需要用户按键输入的，所以需要有判断按键输入的函数和读取按键值的函数，我这边使用函数 `_kbhit()` 来判断是否有按键输入，用函数 `_getch()` 读取按键值

```c
//控制方块移动
	if (_kbhit() && graph.startFlag)//如果键盘有输入
	{
		graph.keyPlay();
	}
```
```c
void Graph::keyPlay()
{
	int ch = 0;
	ch = _getch();
	switch (ch)
	{
		//WASD键（小写）
		case 119: changeBlock();//上键
			break;
		case 97: moveLeft();//左键
			break;
		case 115: moveDown();//下键
			break;
		case 100: moveRight();//右键
			break; 
		//上下左右键
		case 72: changeBlock();//上键
			break;
		case 75: moveLeft();//左键
			break;
		case 80: moveDown();//下键
			break;
		case 77: moveRight();//右键
			break;
	}
}
```

### 3.2 方块的旋转

![方块旋转](https://img-blog.csdnimg.cn/a7f487daf3d943ba8ef5e6ac71856b47.png)

如上图所示，这样可以用几行代码实现了方块的旋转，但是仍然需要注意下面的几个问题：

- 以什么为中心旋转？
- 方块是不断下落的，行和列是一直在变化的
- 在边界处有部分方块是不能旋转的

针对第一个问题，如果想让方块的旋转看起来不那么别捏，以4*4方格的中心旋转是最合适的，即图中的2，3，4，5作为旋转的核心。

针对第二个问题，可以将方块的行列切换至初始位置，再进行上图的公式，然后再切回来，这边可以设置两个变量确定方块离初始位置的距离。

针对第三个问题，将方块的行列号暂存，进行变换，然后再进行检测是否有方块在边界外面，如果有，旋转这步算作废。

旋转的时候初始位置的确定也是非常关键的，因为在边界处有些旋转是做不了的

![初始位置](https://img-blog.csdnimg.cn/f4cc7f9705514789adc0c4a0eac0a84f.png)

程序实现：

```c
void Graph::changeBlock()
{
	int temp[4][2] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		//配合偏置，进行方块的旋转
		temp[i][0] = smallBlock[i][1] - colBasis;
		temp[i][1] = 3 - (smallBlock[i][0] - rowBasis);

		temp[i][0] += rowBasis;
		temp[i][1] += colBasis;

		//检查合法性
		if (temp[i][1] == 0 || temp[i][1] == cols - 1)
			return;
	}
	for (int i = 0; i < 4; i++)//若合法，实行
	{
		smallBlock[i][0] = temp[i][0];
		smallBlock[i][1] = temp[i][1];
	}
}
```

### 3.3 方块的碰撞和消除

方块的消除需要考虑下面几个问题

- 碰撞检测
- 一行的消除算法

#### 3.3.1 碰撞

碰撞检测很容易实现，由于左右移动我已经设置了边界检测，这边只需要对四个方块进行判断，也就是是说判断它们下面是否有方块就行。如果有，就返回 1

```c
int Graph::check()
{
	int row, col;

	for (int i = 0; i < 4; i++)//若合法，实行
	{
		row = smallBlock[i][0]+1;
		col = smallBlock[i][1];

		if (row >= this->rows || allBlock[row][col] >= 1)
		{
			if (rowBasis == 0)
				return 2;
			else
				return 1;
		}
	}
	return 0;
}
```
#### 3.3.2 消除

对一行的消除，采用一个二维数组对所有的位置进行记录，如果在（i，j）处有方块，则 `allBlock[i][j]=1`；在碰撞检测完毕之后，对整个数组进行遍历，对每一行移动的行数进行记录，尽量减少时间复杂度。

```c
int clearRowNum[30] = { 0 };
int num=0;
//unordered_map<int, int>map;
if (check()==1)
{
	for (int i = 0; i < 4; i++) 
	{
		int row = smallBlock[i][0];
		int col = smallBlock[i][1];
		allBlock[row][col] = blockType+1;
	}
	//消除一行
	for (int i = rows-1; i > 3; --i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (allBlock[i][j] == 0)
			{
				clearRowNum[i] = num;
				break;
			}
			else if (j == cols-1)//该行需要消除
			{
				++num;
				clearRowNum[i] = 0;
			}
		}
	}

	for (int i = rows - 2; i > 3; --i)
	{
		if (clearRowNum[i] != 0)
		{
			for (int j = 0; j < cols; ++j)
			{
				allBlock[i + clearRowNum[i]][j] = allBlock[i][j];
			}
		}
	}
}
```

#### 3.3.3 分数和下落速度

同时，在消除函数中可以添加分数计算，速度计算。大致的逻辑是每消除一行，分数变多；分数越高，下落速度越快；

```c
//设置速度，得分越多，速度越快
score += num * cols;

speed = 100+score/10;
```

#### 3.3.4 game over

当小方块处于初始位置时，它的下方有方块时就可以判断 game over了。

```c
if (row >= this->rows || allBlock[row][col] >= 1)
{
	if (rowBasis == 0)
		return 2;
	else
		return 1;
}
```

game over 之后，界面会一直显示game over，直到输入 回车键

```c
//游戏结束
	if (!graph.startFlag)
	{
		settextcolor(WHITE);
		settextstyle(40, 0, "黑体");
		setbkmode(TRANSPARENT);
		char s[10] = "Game Over";
		outtextxy(300, 280, s);

		if (_kbhit() && _getch() == 13)//如果键盘有输入
		{
			graph.init();
		}
	}
```

![game over](https://img-blog.csdnimg.cn/9847c0a1a4b94970b3d670f9f48c665f.png)

## 4 制作 exe 文件

如何用 Visual Studio打包项目程序可以参考：

[Visual Studio 怎么将项目程序打包成软件](https://blog.csdn.net/u011895157/article/details/129367184?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22129367184%22%2C%22source%22%3A%22u011895157%22%7D)
## 5 总结

最后我想说的是，对方块的移动和旋转，其根本就是在对数组进行操作。

至于后续的一些最高分数记录，下一个方块提示等功能，都是锦上添花的功能，感兴趣的小伙伴可以尝试添加一下。