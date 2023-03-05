#include "Graph.h"
#include <graphics.h>
#include <iostream>
#include <map>


void Graph::init()
{
	startFlag = true;

	random();
	//�ٶȺͷ���
	this->speed = 100;
	score = 0;

	// ��ͼ���ڳ�ʼ��
	initgraph(imp_width, imp_heght);
	loadimage(&background, _T("img/background.png"));
	putimage(0, 0, &background);

	this->block();//С�����ʼ��
	this->updateSpeed(speed);//�ٶ�0
	this->updateScore(score);//����0

	
	for (auto& row : allBlock) {
		for (auto& col : row) {
			col = 0;
		}
	}
	
}

void Graph::random()
{

	//�����˶�
	blockType = rand() % 7;
	//blockType = 5;

	//putimage(left_margin + 7 * blocks_size, down_margin, imgs[0]);
	/*for (int i = 0; i < 14; i++) {
		putimage(left_margin+ i * blocks_size, down_margin, imgs[1]);
	}*/
	for (int i = 0; i < 4; i++)
	{
		smallBlock[i][0] = blocks[blockType][i] / 2;
		smallBlock[i][1] = blocks[blockType][i] % 2 + 1;//��ʼ�к�+1
	}
	colBasis = 0;
	rowBasis = 0;
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

void Graph::updateSpeed(unsigned int speed)
{
	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	char s[5];
	sprintf_s(s, "%d", speed);
	outtextxy(25, 480, s);
}

void Graph::updateScore(unsigned int score)
{
	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);
	char s[5];
	sprintf_s(s, "%d", score);
	outtextxy(685, 480, s);
}

void Graph::updateScreen()
{
	cleardevice();
	BeginBatchDraw();//������Ļ��˸

	putimage(0, 0, &background);

	//�Ѿ�ֹ����
	for (int i = rows-1; i > 3; --i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if(allBlock[i][j]!=0)
				putimage(left_margin + j * blocks_size, up_margin + i * blocks_size, imgs[allBlock[i][j]-1]);
		}
	}

	//���䷽��
	for (int i = 0; i < 4; i++)
	{
		putimage(left_margin + smallBlock[i][1] * blocks_size, up_margin + smallBlock[i][0] * blocks_size, imgs[blockType]);
	}

	updateScore(score);
	updateSpeed(speed);
	
	EndBatchDraw();
}

void Graph::keyPlay()
{
	int a = 1;
	int ch = 0;
	//ExMessage messageBuf = getmessage(EX_KEY);
	/*keyFlag = !keyFlag;
	if (keyFlag)
		return;*/
	//printf("��Ϣ��%c ���� %d\n", messageBuf.ch, a++);
	ch = _getch();
	printf("��Ϣ��%d\n", ch);
	switch (ch)
	{
		case 119: changeBlock();//�ϼ�
			break;
		case 97: moveLeft();//���
			break;
		case 115: moveDown();//�¼�
			break;
		case 100: moveRight();//�Ҽ�
			break; 
	}
	
		//memset(&messageBuf, '\0', sizeof(messageBuf));
}


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

void Graph::changeBlock()
{
	int temp[4][2] = { 0 };
	//++dirFlag;	
	//if (dirFlag>3)
	//{
	//	dirFlag = 0;
	//}
	//switch (dirFlag)
	//{
	//case 0:
	//	/*for (int i = 0; i < 4; i++)
	//	{
	//		smallBlock[i][0] = blocks[blockType][i] / 2;
	//		smallBlock[i][1] = blocks[blockType][i] % 2;
	//	}
	//	break;*/
	//case 1:	
	//case 2:
	//case 3:
	//default;
	//for (int i = 0; i < 4; i++)//���鴦�ڱ߽粻�ɱ���
	//{
	//	if (smallBlock[i][1] == 0 || smallBlock[i][1] == cols)
	//		return;
	//}
	for (int i = 0; i < 4; i++)
	{
		//���ƫ�ã����з������ת
		temp[i][0] = smallBlock[i][1] - colBasis;
		temp[i][1] = 3 - (smallBlock[i][0] - rowBasis);

		temp[i][0] += rowBasis;
		temp[i][1] += colBasis;

		//���Ϸ���
		if (temp[i][1] < 0 || temp[i][1] >= cols || temp[i][0] < 0 || temp[i][0] >= rows)
			return;

		
	}
	for (int i = 0; i < 4; i++)//���Ϸ���ʵ��
	{
		smallBlock[i][0] = temp[i][0];
		smallBlock[i][1] = temp[i][1];
	}
	/*	break;
	}*/
}

int Graph::check()
{
	int row, col;

	for (int i = 0; i < 4; i++)//���Ϸ���ʵ��
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

void Graph::clearBlock()
{
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
		//����һ��
		for (int i = rows-1; i > 3; --i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (allBlock[i][j] == 0)
				{
					clearRowNum[i] = num;
					break;
				}
				else if (j == cols-1)//������Ҫ����
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
		//�����ٶȣ��÷�Խ�࣬�ٶ�Խ��
		score += num * cols;

		speed = 100+score/10;
		random();
	}
	else if (check()==2)//game over
	{
		startFlag = false;	
	}
}

