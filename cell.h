#pragma once

#include <Windows.h>
#include <windows.h>
#include <iostream>

using namespace std;

BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}

class Cell
{
public:
	Cell() { }
	Cell(int xx, int yy, int c = 0) {  }
	void setXY(int i, int j)
	{
		x = i; y = j;
	}
	void setColor(int a)
	{
		color = a;
	}
	bool validity()//若操作合法，返回1，否则返回0
	{
		if (x == 24 || y == 0 || y == 11) return false;//是否出范围检测；
		if (color != 0)return false;		//格子validity检测；
		return true;//若均通过，则该操作合法；
	}
	void print()
	{
		SetConsoleColor(color);
		cout << "■";
		SetConsoleColor(0);
	}
	bool Left()
	{
		x--;
		return true;
	}
	bool Right()
	{
		x++;
		return true;
	}
	bool Drop()
	{
		y++;
		return true;
	}
	//private:
	int x = 0;
	int y = 0;
public:
	int color = 0;
	friend class Tetris;
	friend class Space;
	friend class Tetris_I;
};
