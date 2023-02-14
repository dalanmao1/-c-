#include <iostream>
#include "Music.h"
#include "Graph.h"

using namespace std;

int main()
{
	Music music;
	Graph graph;

	graph.init();

	_sleep(2 * 1000);
	music.palyMusic();
	
	while (1)
	{
		graph.updateScreen();
		graph.keyPlay();
		_sleep(1 * 1000);
		//break;
	}
	return 0;
}


