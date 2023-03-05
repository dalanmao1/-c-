#pragma once
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <list>

using namespace std;
class Graph
{

public: 

	Graph() :allBlock(rows, vector<int>(cols, 0)) {};

	void init();
	void block();
	void updateSpeed(unsigned int speed);
	void updateScore(unsigned int score);
	void updateScreen();
	void keyPlay();
	bool keyFlag = false;
	//������ɷ���
	void random();
	//�����ƶ�
	void moveLeft();
	void moveDown();
	void moveRight();
	void changeBlock();
	//��ײ���
	int check();
	//��������
	void clearBlock();
	//�����ٶ�
	unsigned int speed ;

	bool startFlag = true;

private:
	//����ͼ���С
	const unsigned int imp_width = 800;
	const unsigned int imp_heght = 600;
	//С�����С
	const unsigned int blocks_size = 20;

	//��Ϸ���߽�
	const unsigned int left_margin = 240;
	const unsigned int right_margin = 485;
	const unsigned int down_margin = 570;
	const unsigned int up_margin = 10;
	const int rows = 29;
	const int cols = 14;
	
	//��¼���������
	vector<vector<int>> allBlock;

	//�����ƫ�ã����ڷ�����ת
	unsigned int rowBasis = 0;
	unsigned int colBasis = 0;


	const int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1��
		3,5,4,6, // Z 2��
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // ��
	};
	//��¼�ĸ����������
	int smallBlock[4][2];

	unsigned int blockType;
	//����
	unsigned int score;


	//�������ڰ��ָ������
	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom;

	IMAGE* imgs[7];
	IMAGE background;//����

	//���鷽���־λ
	unsigned int dirFlag = 0;
	
	
};

