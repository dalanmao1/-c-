#include "Graph.h"
#include <easyx.h>
#include <iostream>

void Graph::init()
{
	//方块运动
	left = left_margin;
	right = left_margin + 2 * blocks_size;
	top = up_margin;
	bottom = up_margin + 4 * blocks_size;
	//速度和分数
	speed = 0;
	score = 0;

	// 绘图窗口初始化
	initgraph(imp_width, imp_heght);
	loadimage(&background, _T("img/background.png"));
	putimage(0, 0, &background);

	this->block();//小方块初始化
	this->updateSpeed(speed);//速度0
	this->updateScore(score);//分数0

}

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

void Graph::updateSpeed(int speed)
{
	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	setbkmode(TRANSPARENT);
	char s[5];
	sprintf_s(s, "%d", speed);
	outtextxy(685, 480, s);
}

void Graph::updateScore(int score)
{
	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	setbkmode(TRANSPARENT);
	char s[5];
	sprintf_s(s, "%d", score);
	outtextxy(25, 480, s);
}

void Graph::updateScreen()
{
	cleardevice();
	//BeginBatchDraw();

	putimage(0, 0, &background);
	blockType = rand() % 7;
	
	/*putimage(left_margin + 7 * blocks_size, down_margin, imgs[0]);
	for (int i = 0; i < 16; i++) {
		putimage(left_margin, down_margin- i * blocks_size, imgs[1]);
	}*/
	for (int i = 0; i < 4; i++)
	{
		smallBlock[i][0] = blocks[blockType][i] / 2;
		smallBlock[i][1] = blocks[blockType][i] % 2;
	}

	for (int i = 0; i < 4; i++)
	{
		putimage(left + smallBlock[i][1] * blocks_size, top + smallBlock[i][0] * blocks_size, imgs[blockType]);
	}

	updateScore(score);
	updateSpeed(speed);
	//EndBatchDraw();
}

void Graph::keyPlay()
{
	ExMessage messageBuf;

	getmessage(&messageBuf, EX_KEY);
	//printf("消息：%c \n", messageBuf.ch);
	switch (messageBuf.ch)
	{
		case 'A': moveLeft();
			break;
		case 'D': moveRight();
			break;
		case 'S': moveDown();
			break;

	}
}

void Graph::moveLeft()
{

}

void Graph::moveDown()
{
	top += blocks_size;
}

void Graph::moveRight()
{
}

