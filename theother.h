#pragma once
#include <conio.h>
#include <thread>
#include "space_tetris.h"

int operator-(SYSTEMTIME a, SYSTEMTIME b)
{
	if (a.wSecond == b.wSecond)
		return a.wMilliseconds - b.wMilliseconds;
	else if (a.wSecond - b.wSecond == 1 || a.wSecond - b.wSecond == -59)
		return a.wMilliseconds - b.wMilliseconds + 1000;
	else
		return a.wMilliseconds - b.wMilliseconds + 2000;
}

void* Music()
{
	while (1)
	{
		PlaySound(TEXT("D:\\TEST\\test.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(100);
	}
}

void* Game()
{
	char c = NULL;
	sp.Ini();
	SYSTEMTIME temp_time, current_time;
	GetLocalTime(&temp_time);
	bool land_or_not = false;
	sp.SetNextBlock();
	while (true)
	{
		sp.print();
		if (sp.current->BlockLandTest())		//当前方块1落地时的处理
			land_or_not = true;
		while (true)
		{
			GetLocalTime(&current_time);
			if (current_time - temp_time >= 1000)		//如果获得的当前时间和之前的时间之差超过了设定的值则执行一次下落
			{
				temp_time = current_time;
				sp.move('s');
				break;
			}
			if (_kbhit())		//如果有按键被按下
			{
				c = _getch();
				if (c == 'w' || c == 's' || c == 'a' || c == 'd')	//只有按了指定的游戏控制键程序才继续
					break;
			}
			Sleep(20);			//延时以降低CPU利用率
		}
		sp.move(c);
		c = ' ';
		if (land_or_not)
		{
			sp.ClearLine();
			sp.SetNextBlock();

			sp.print(); //显示界面
			GetLocalTime(&temp_time);
			land_or_not = false;
		}
		if (sp.board[1][5].color !=0&& sp.board[1][6].color != 0) exit(0);
	}
	return 0;
}

class Control
{
public:

	void Start()
	{
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Music, &Music, 0, NULL);
		HANDLE hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Game, &Game, 0, NULL);
		WaitForSingleObject(hThread, INFINITE);
		WaitForSingleObject(hThread2, INFINITE);
		CloseHandle(hThread);
		CloseHandle(hThread2);
	}
};
