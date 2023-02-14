#pragma once
#include <easyx.h>
class Graph
{
public:
	void init();
	void block();
	void updateSpeed(int speed);
	void updateScore(int score);
	void updateScreen();
	void keyPlay();

	//�����ƶ�
	void moveLeft();
	void moveDown();
	void moveRight();

private:
	//����ͼ���С
	const unsigned int imp_width = 800;
	const unsigned int imp_heght = 600;
	//С�����С
	const unsigned int blocks_size = 35;
	//��Ϸ���߽�
	const unsigned int left_margin = 240;
	const unsigned int right_margin = left_margin + 7 * blocks_size;
	const unsigned int down_margin = 590 - blocks_size;
	const unsigned int up_margin = down_margin - blocks_size*15;

	const int blocks[7][4] = {
		1,3,5,7, // I
		0,2,3,5, // Z 1��
		1,2,3,4, // Z 2��
		1,2,3,5, // T
		0,2,4,5, // L
		1,3,4,5, // J
		0,1,2,3, // ��
	};
	unsigned int smallBlock[4][2];

	unsigned int blockType;

	unsigned int score;
	unsigned int speed;

	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom;

	IMAGE* imgs[7];
	IMAGE background;//����
};

