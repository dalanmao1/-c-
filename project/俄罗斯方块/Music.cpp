#include "Music.h"
#include "Windows.h"
#include <time.h>

#pragma comment (lib, "winmm.lib")

void Music::palyMusic()
{
	int chFlag;
	//char szModeBuffer[1024];
	/*mciSendString("open 1.mp3", NULL, 0, NULL);
	mciSendString("play 1.mp3", NULL, 0, NULL);*/
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
	//Sleep(9000);//สิฬý
	//mciSendString(TEXT("close 1.mp3"), NULL, 0, NULL);
	/*mciSendString("status 1.mp3 mode", szModeBuffer, 1024, NULL);
	printf("%s\n", szModeBuffer);
	Sleep(5);*/
}
