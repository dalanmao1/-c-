#include <iostream>
#include "Music.h"
#include "Graph.h"
#include <chrono>//计时器
#include <windows.h>

using namespace std;

const double MaxtimeDown = 1000;
const double MaxtimeRefresh = 200;
double timer();

int main()
{
	Music music;
	Graph graph;
	/*unsigned int timeDown = 10;
	unsigned int timeRefresh = 0.02;*/

	graph.init();
	//_sleep(1000);
	music.palyMusic();
	auto timeDown = timer();
	auto timeRefresh = timer();
	while (1)
	{
		
		if(_kbhit() && graph.startFlag)//如果键盘有输入
			graph.keyPlay();

		if ((timer()- timeDown) >= (MaxtimeDown-graph.speed) && graph.startFlag)
		{
			graph.moveDown();
			timeDown = timer();
		}

		if ((timer() - timeRefresh) >= MaxtimeRefresh)//屏幕刷新
		{
			graph.updateScreen();
			timeRefresh = timer();
		}	
		graph.clearBlock();

		if (!graph.startFlag)
		{
			settextcolor(WHITE);
			settextstyle(40, 0, "黑体");
			setbkmode(TRANSPARENT);
			char s[10] = "Game Over";
			outtextxy(300, 280, s);

			if (_kbhit() && _getch() == 32)//如果键盘有输入
			{
				graph.init();
			}
		}
	}
	return 0;
}

double timer() 
{
	static const auto start_time = std::chrono::steady_clock::now();

	const auto end_time = std::chrono::steady_clock::now();
	const auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	return elapsed_time;

	//return GetTickCount(); //计时器
}
