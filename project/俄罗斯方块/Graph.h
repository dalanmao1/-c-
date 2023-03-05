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
	//随机生成方块
	void random();
	//方块移动
	void moveLeft();
	void moveDown();
	void moveRight();
	void changeBlock();
	//碰撞检测
	int check();
	//方块消除
	void clearBlock();
	//下落速度
	unsigned int speed ;

	bool startFlag = true;

private:
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

	//下落的偏置，用于方块旋转
	unsigned int rowBasis = 0;
	unsigned int colBasis = 0;


	const int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};
	//记录四个方块的坐标
	int smallBlock[4][2];

	unsigned int blockType;
	//分数
	unsigned int score;


	//方块所在八字格的区域
	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom;

	IMAGE* imgs[7];
	IMAGE background;//背景

	//方块方向标志位
	unsigned int dirFlag = 0;
	
	
};

