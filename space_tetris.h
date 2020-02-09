#pragma once
#include "cell.h"
Cell Cpublic;

static int point = 0;
class Tetris;
class Space
{
public:
	Cell board[25][12];
	Tetris* current;
	Cell getCell(int x, int y)
	{
		return board[x][y];
	}
	void Ini()
	{
		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 12; j++)
			{
				board[i][j].setXY(i, j);
				if (j == 0 || j == 11)
				{
					board[i][j].setColor(1);
				}
			}
	}
	void print()
	{
		COORD co;	co.X = 0; co.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
		for (int i = 0; i < 21; i++)
		{
			if (i == 2) {
				SetConsoleColor(11);
				cout << "       按”A“”D“键移动方块      ";
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				for (int j = 1; j < 11; j++)	board[i + 4][j].print();
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				cout << endl;
			}
			else if (i == 5) {
				SetConsoleColor(11);
				cout << "       按”S“键直接使方块下移     ";
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				for (int j = 1; j < 11; j++)	board[i + 4][j].print();
				SetConsoleColor(140); cout << "  "; SetConsoleColor(3);
				cout << "        ※当前得分:" << point;
				cout << endl;
			}
			else if (i == 8) {
				SetConsoleColor(11);
				cout << "      按”W“键使方块顺时针旋转    ";
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				for (int j = 1; j < 11; j++)	board[i + 4][j].print();
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				cout << endl;

			}
			else if (i == 10) {
				cout << "                                   ";
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				for (int j = 1; j < 11; j++)	board[i + 4][j].print();
				SetConsoleColor(140); cout << "  "; SetConsoleColor(3);
				cout << "        ※共消行数:" << "0"; SetConsoleColor(7);
				cout << endl;

			}
			else if (i == 20) {
				cout << "                                   ";
				SetConsoleColor(140); cout << "                        "; SetConsoleColor(7);
				cout << endl;

			}
			else {
				cout << "                                   ";
				SetConsoleColor(140); cout << "  "; SetConsoleColor(7);
				for (int j = 1; j < 11; j++)	board[i + 4][j].print();
				SetConsoleColor(140); cout << "  "; SetConsoleColor(0);
				cout << "                                ";
				cout << endl;
			}
		}
		cout << endl << endl << endl << endl << endl << endl;
	}
	bool LineReplace(int l);

	void ClearLine();
	void SetNextBlock();
	void move(char c);
	//protected:
	friend class Tetris;
	friend class Tetris_I;
};
Space sp;

class Tetris
{
public:
	Cell* A, * B, * C, * D; int form = 1;
public:
	Tetris(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd, Space& s) {
		A = &s.board[xa][ya];
		B = &s.board[xb][yb];
		C = &s.board[xc][yc];
		D = &s.board[xd][yd];
		A->x = xa; A->y = ya; B->x = xb; B->y = yb;
		C->x = xc; C->y = yc; D->x = xd; D->y = yd;
	}
	bool validate(Cell a = Cpublic, Cell b = Cpublic, Cell c = Cpublic, Cell d = Cpublic)
	{
		if (a.color != 0 || b.color != 0 || c.color != 0 || d.color != 0)
		{
			//			if(a.Left)
			return false;
		}

		return true;//若均通过，则该操作合法；
	}
	virtual void Transform() = 0;
	enum
	{
		LEFT, RIGHT, DOWN
	};
	bool innerlogic(Cell A, Cell B, Cell C, Cell D, int mode)
	{
		if (LEFT)
		{

			return true;
		}
		return false;
	}
	virtual bool empty_or_not_left() = 0;
	virtual bool empty_or_not_right() = 0;
	//virtual bool empty_or_not_drop() = 0;
	void Drop()
	{
	//	if (empty_or_not_drop()) return;
		if (BlockLandTest()) return;
		int temp;
		temp = A->color;
		A->color = 0;
		B->color = 0;
		C->color = 0;
		D->color = 0;
		A = &sp.board[(A->x) + 1][A->y];
		B = &sp.board[(B->x) + 1][B->y];
		C = &sp.board[(C->x) + 1][C->y];
		D = &sp.board[(D->x) + 1][D->y];
		setColor(temp);

	}
	void Right()
	{
		if (A->y == 10 || B->y == 10 || C->y == 10 || D->y == 10) return;
		if (empty_or_not_right())
			return;
		int temp;
		temp = A->color;
		A->color = 0;
		B->color = 0;
		C->color = 0;
		D->color = 0;
		A = &sp.board[A->x][(A->y) + 1];
		B = &sp.board[B->x][(B->y) + 1];
		C = &sp.board[C->x][(C->y) + 1];
		D = &sp.board[D->x][(D->y) + 1];
		setColor(temp);
	}
	void Left()
	{
		if (A->y == 1 || B->y == 1 || C->y == 1 || D->y == 1) return;
		if (empty_or_not_left())
			return;
		int temp;
		temp = A->color;
		A->color = 0;
		B->color = 0;
		C->color = 0;
		D->color = 0;
		A = &sp.board[A->x][(A->y) - 1];
		B = &sp.board[B->x][(B->y) - 1];
		C = &sp.board[C->x][(C->y) - 1];
		D = &sp.board[D->x][(D->y) - 1];
		setColor(temp);
	}
	void setColor(int a)
	{
		A->setColor(a);
		B->setColor(a);
		C->setColor(a);
		D->setColor(a);
	}
	virtual bool BlockLandTest() = 0;
	friend class Space;
};
class Tetris_I :public Tetris //Done
{
public:
	/*bool empty_or_not_drop()
	{
		if (form == 1)
		{
			if (sp.board[(D->x) + 1][D->y].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(A->x) + 1][A->y].color|| sp.board[(B->x) + 1][B->y].color|| sp.board[(C->x) + 1][C->y].color|| sp.board[(D->x) + 1][D->y].color)
				return true;
			return false;
		}
	}*/
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[C->x][(C->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(A->x)][(A->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[C->x][(C->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) + 1].color)
				return true;
			return false;
		}
	}
	void Transform()
	{
		int temp;
		if (A->x == B->x) { //此时form=2，是横条
			//else {
			if (!validate(sp.board[(A->x) - 1][(A->y) + 1], sp.board[(C->x) + 1][(C->y) - 1], sp.board[(D->x) + 2][(D->y) - 2]))
				return;
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) - 1][(A->y) + 1];
			B = &sp.board[(B->x)][(B->y)];
			C = &sp.board[(C->x) + 1][(C->y) - 1];
			D = &sp.board[(D->x) + 2][(D->y) - 2];
			setColor(temp);
			form = 1;
			//}
		}
		else {
			if (!validate(sp.board[(A->x) + 1][(A->y) - 1], sp.board[(C->x) - 1][(C->y) + 1], sp.board[(D->x) - 2][(D->y) + 2]))
				return;
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) + 1][(A->y) - 1];
			B = &sp.board[(B->x)][(B->y)];
			C = &sp.board[(C->x) - 1][(C->y) + 1];
			D = &sp.board[(D->x) - 2][(D->y) + 2];
			setColor(temp);
			form = 2;
		}
	}
	Tetris_I(int xa = 0, int ya = 5, int xb = 1, int yb = 5, int xc = 2, int yc = 5, int xd = 3, int yd = 5, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(2);
	};
	bool BlockLandTest()
	{
		if (form == 1)
		{
			if (sp.getCell((D->x) + 1, D->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==2;
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((B->x) + 1, B->y).validity()
				&& sp.getCell((C->x) + 1, C->y).validity() && sp.getCell((D->x) + 1, D->y).validity()) {
				return false;
			}
			return true;
		}
	}

	friend class Space;
};
class Tetris_O :public Tetris
{
public:
	void Transform() {}
	Tetris_O(int xa = 2, int ya = 5, int xb = 3, int yb = 5, int xc = 2, int yc = 6, int xd = 3, int yd = 6, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(3);
	};
	bool empty_or_not_left()
	{
		if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color)
			return true;
		return false;
	}
	bool empty_or_not_right()
	{
		if (sp.board[(C->x)][(C->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
			return true;
		return false;
	}
	bool BlockLandTest() //对于O型来说，不执行旋转，则判断是否落地始终取决于下方的两个方块
	{
		if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((B->x) + 1, B->y).validity()) {
			return false;
		}
		return true;
	}
	friend class Space;
};
class Tetris_T :public Tetris
{
public:
	void Transform()
	{
		int temp;
		if (form == 1) { //此时form=2，是横条
			if (!validate(sp.board[(B->x) + 1][(B->y) + 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) + 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) - 1][(A->y) + 1];
			D = &sp.board[(D->x) - 1][(D->y) - 1];
			setColor(temp);
			form = 2;
			//}
		}
		else if (form == 2) { //此时form=2，是横条
			if (!validate(sp.board[(B->x) + 1][(B->y) - 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) + 1][(B->y) - 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) + 1][(A->y) + 1];
			D = &sp.board[(D->x) - 1][(D->y) + 1];
			setColor(temp);
			form = 3;
			//}
		}
		else if (form == 3) { //此时form=2，是横条
			if (!validate(sp.board[(B->x) - 1][(B->y) - 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) - 1][(B->y) - 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) + 1][(A->y) - 1];
			D = &sp.board[(D->x) + 1][(D->y) + 1];
			setColor(temp);
			form = 4;
			//}
		}
		else if (form == 4)
		{
			if (!validate(sp.board[(B->x) - 1][(B->y) + 1]))
				return;

			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) - 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) - 1][(A->y) - 1];
			D = &sp.board[(D->x) + 1][(D->y) - 1];
			setColor(temp);
			form = 1;
		}
		else {}
	}
	Tetris_T(int xa = 2, int ya = 5, int xb = 1, int yb = 6, int xc = 2, int yc = 6, int xd = 3, int yd = 6, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(4);
	};
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else if(form==2) {
			if (sp.board[(D->x)][(D->y) -1].color || sp.board[A->x][(A->y) - 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(C->x)][(C->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(B->x)][(B->y) - 1].color || sp.board[A->x][(A->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(C->x)][(C->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 2) {
			if (sp.board[(B->x)][(B->y) + 1].color || sp.board[A->x][(A->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) + 1].color || sp.board[A->x][(A->y) + 1].color)
				return true;
			return false;
		}
	}
	bool BlockLandTest()
	{
		if (form == 1) {
			if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((A->x) + 1, A->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 2) {
			if (sp.getCell((C->x) + 1, C->y).validity() && sp.getCell((D->x) + 1, D->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 3) {
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==4
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((B->x) + 1, B->y).validity()
				&& sp.getCell((D->x) + 1, D->y).validity()) {
				return false;
			}
			return true;
		}
	}


	friend class Space;
};////
class Tetris_L :public Tetris
{
public:
	void Transform()
	{

		int temp;
		if (form == 1) { //此时form=2，是横条

			if (!validate(sp.board[(A->x) + 2][(A->y) + 2], sp.board[(D->x) + 1][(D->y) - 1]) || A->y > 9)
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) + 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) + 2][(A->y) + 2];
			D = &sp.board[(D->x) + 1][(D->y) - 1];
			setColor(temp);
			form = 2;
			//}
		}
		else if (form == 2) { //此时form=2，是横条
			if (!validate(sp.board[(A->x) + 2][(A->y) - 2], sp.board[(D->x) - 1][(D->y) - 1]))
				return;
			else {
				temp = A->color;
				A->color = 0;
				B->color = 0;
				C->color = 0;
				D->color = 0;
				B = &sp.board[(B->x) + 1][(B->y) - 1];
				C = &sp.board[(C->x)][(C->y)];
				A = &sp.board[(A->x) + 2][(A->y) - 2];
				D = &sp.board[(D->x) - 1][(D->y) - 1];
				setColor(temp);
				form = 3;
			}
		}
		else if (form == 3) { //此时form=2，是横条
			if (A->y < 2 || !validate(sp.board[(A->x) - 2][(A->y) - 2], sp.board[(D->x) - 1][(D->y) + 1]))
				return;
			else {
				temp = A->color;
				A->color = 0;
				B->color = 0;
				C->color = 0;
				D->color = 0;
				B = &sp.board[(B->x) - 1][(B->y) - 1];
				C = &sp.board[(C->x)][(C->y)];
				A = &sp.board[(A->x) - 2][(A->y) - 2];
				D = &sp.board[(D->x) - 1][(D->y) + 1];
				setColor(temp);
				form = 4;
			}
		}
		else if (form == 4)
		{
			if (!validate(sp.board[(D->x) + 1][(D->y) + 1], sp.board[(A->x) - 2][(A->y) + 2]))
				return;

			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) - 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) - 2][(A->y) + 2];
			D = &sp.board[(D->x) + 1][(D->y) + 1];
			setColor(temp);
			form = 1;
		}
		else {}
	}
	Tetris_L(int xa = 1, int ya = 5, int xb = 2, int yb = 5, int xc = 3, int yc = 5, int xd = 3, int yd = 6, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(5);
	};
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[C->x][(C->y) - 1].color)
				return true;
			return false;
		}
		else if (form == 2) {
			if (sp.board[(C->x)][(C->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) - 1].color || sp.board[A->x][(A->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 2) {
			if (sp.board[(D->x)][(D->y) + 1].color || sp.board[A->x][(A->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[C->x][(C->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) +1].color || sp.board[C->x][(C->y) + 1].color)
				return true;
			return false;
		}
	}
	bool BlockLandTest()
	{
		if (form == 1) {
			if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((C->x) + 1, C->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 2) {
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 3) {
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==4
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((C->x) + 1, C->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
	}

	friend class Space;
};
class Tetris_S :public Tetris
{
public:
	void Transform()
	{
		if (!validate(sp.board[(A->x) + 2][(A->y) - 1]))
			return;

		int temp;
		if (form == 1) { //此时form=2，是横条
							//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) + 2][(A->y) - 1];
			B = &sp.board[(B->x) + 1][(B->y)];
			C = &sp.board[(C->x)][(C->y) - 1];
			D = &sp.board[(D->x) - 1][(D->y)];
			setColor(temp);
			form = 2;
			//}
		}
		else if (form == 2) {
			if (!validate(sp.board[(A->x) - 2][(A->y) + 1], sp.board[(D->x) + 1][(D->y)]))
				return;
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) - 2][(A->y) + 1];
			B = &sp.board[(B->x) - 1][(B->y)];
			C = &sp.board[(C->x)][(C->y) + 1];
			D = &sp.board[(D->x) + 1][(D->y)];
			setColor(temp);
			form = 1;
		}
		else {}
	}
	Tetris_S(int xa = 1, int ya = 5, int xb = 2, int yb = 5, int xc = 2, int yc = 6, int xd = 3, int yd = 6, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(6);
	};
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[A->x][(A->y) - 1].color || sp.board[C->x][(C->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) + 1].color ||  sp.board[C->x][(C->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(B->x)][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
	}
	bool BlockLandTest()
	{
		if (form == 1) {
			if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==2
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
	}

	friend class Space;
};
class Tetris_Z :public Tetris
{
public:
	void Transform()
	{
		int temp;
		if (form == 1) { //此时form=2，是横条
			if (!validate(sp.board[(A->x) + 2][(A->y) + 1], sp.board[(B->x) + 1][(B->y)]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) + 2][(A->y) + 1];
			B = &sp.board[(B->x) + 1][(B->y)];
			C = &sp.board[(C->x)][(C->y) + 1];
			D = &sp.board[(D->x) - 1][(D->y)];
			setColor(temp);
			form = 2;
			//}
		}
		else if (form == 2) {
			if (!validate(sp.board[(A->x) - 2][(A->y) - 1], sp.board[(D->x) + 1][(D->y)]))
				return;

			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			A = &sp.board[(A->x) - 2][(A->y) - 1];
			B = &sp.board[(B->x) - 1][(B->y)];
			C = &sp.board[(C->x)][(C->y) - 1];
			D = &sp.board[(D->x) + 1][(D->y)];
			setColor(temp);
			form = 1;
		}
		else {}
	}
	Tetris_Z(int xa = 1, int ya = 6, int xb = 2, int yb = 6, int xc = 2, int yc = 5, int xd = 3, int yd = 5, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(7);
	};
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[C->x][(C->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(B->x)][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) +1].color || sp.board[B->x][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[A->x][(A->y) + 1].color || sp.board[C->x][(C->y) + 1].color)
				return true;
			return false;
		}
	}
	bool BlockLandTest()
	{
		if (form == 1) {
			if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==2
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
	}

	friend class Space;
};
class Tetris_J :public Tetris
{
public:
	void Transform()
	{
		int temp;
		if (form == 1) { //此时form=2，是横条
			if (A->y > 9 || !validate(sp.board[(A->x) + 2][(A->y) + 2], sp.board[(B->x) + 1][(B->y) + 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) + 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) + 2][(A->y) + 2];
			D = &sp.board[(D->x) - 1][(D->y) + 1];
			setColor(temp);
			form = 2;
			//}
		}
		else if (form == 2) { //此时form=2，是横条
			if (A->y < 2 || !validate(sp.board[(A->x) + 2][(A->y) - 2], sp.board[(B->x) + 1][(B->y) - 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) + 1][(B->y) - 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) + 2][(A->y) - 2];
			D = &sp.board[(D->x) + 1][(D->y) + 1];
			setColor(temp);
			form = 3;
			//}
		}
		else if (form == 3) { //此时form=2，是横条
			if (A->y < 2 || !validate(sp.board[(A->x) - 2][(A->y) - 2], sp.board[(B->x) - 1][(B->y) - 1]))
				return;
			//else {
			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) - 1][(B->y) - 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) - 2][(A->y) - 2];
			D = &sp.board[(D->x) + 1][(D->y) - 1];
			setColor(temp);
			form = 4;
			//}
		}
		else if (form == 4)
		{
			if (A->y > 9 || !validate(sp.board[(A->x) - 2][(A->y) + 2], sp.board[(B->x) - 1][(B->y) + 1]))
				return;

			temp = A->color;
			A->color = 0;
			B->color = 0;
			C->color = 0;
			D->color = 0;
			B = &sp.board[(B->x) - 1][(B->y) + 1];
			C = &sp.board[(C->x)][(C->y)];
			A = &sp.board[(A->x) - 2][(A->y) + 2];
			D = &sp.board[(D->x) - 1][(D->y) - 1];
			setColor(temp);
			form = 1;
		}
		else {}
	}	
	Tetris_J(int xa = 1, int ya = 6, int xb = 2, int yb = 6, int xc = 3, int yc = 6, int xd = 3, int yd = 5, Space& sp = sp)
		:Tetris(xa, ya, xb, yb, xc, yc, xd, yd, sp)
	{
		setColor(14);
	};
	bool empty_or_not_left()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[D->x][(D->y) - 1].color)
				return true;
			return false;
		}
		else if (form == 2) {
			if (sp.board[(D->x)][(D->y) - 1].color || sp.board[C->x][(C->y) - 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(A->x)][(A->y) - 1].color || sp.board[B->x][(B->y) - 1].color || sp.board[C->x][(C->y) - 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) - 1].color || sp.board[A->x][(A->y) - 1].color)
				return true;
			return false;
		}
	}
	bool empty_or_not_right()
	{
		if (form == 1)
		{
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[C->x][(C->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 2) {
			if (sp.board[(D->x)][(D->y) + 1].color || sp.board[A->x][(A->y) + 1].color)
				return true;
			return false;
		}
		else if (form == 3) {
			if (sp.board[(A->x)][(A->y) + 1].color || sp.board[B->x][(B->y) + 1].color || sp.board[D->x][(D->y) + 1].color)
				return true;
			return false;
		}
		else {
			if (sp.board[(D->x)][(D->y) + 1].color || sp.board[C->x][(C->y) + 1].color)
				return true;
			return false;
		}
	}
	bool BlockLandTest()
	{
		if (form == 1) {
			if (sp.getCell((D->x) + 1, D->y).validity() && sp.getCell((C->x) + 1, C->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 2) {
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((C->x) + 1, C->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
		else if (form == 3) {
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()) {
				return false;
			}
			return true;
		}
		else //form==4
		{
			if (sp.getCell((A->x) + 1, A->y).validity() && sp.getCell((D->x) + 1, D->y).validity()
				&& sp.getCell((B->x) + 1, B->y).validity()) {
				return false;
			}
			return true;
		}
	}

	friend class Space;
};


bool Space::LineReplace(int l)
{
	int flag = 1; //初始状态为全满
	{
		for (int i = 1; i < 11; i++)
		{
			if (board[l][i].color == 0) {
				flag = 0; //有一个黑色格子就不是全满
			}
		}
		if (flag == 1)
		{
			for (int i = l - 1; i > 3; i--)
			{
				for (int j = 0; j < 12; j++)
				{
					board[i + 1][j].color = board[i][j].color;
					point++;
				}
			}
			return true;
		}
	}
	return false;
}
void Space::ClearLine()
{
	for (int i = 4; i < 24; i++)
		LineReplace(i);
}
void Space::move(char c)
{
	if (c == 'w') current->Transform();
	else if (c == 's') current->Drop();
	else if (c == 'a') current->Left();
	else if (c == 'd') current->Right();
	else {}
}
void Space::SetNextBlock()
{
	SYSTEMTIME current_time;
	GetLocalTime(&current_time);			//获取当前时间
											//CurrentBlock1 = NextBlock1;
	srand(current_time.wMilliseconds);		//用当前时间的毫秒数设置产生随机数的种子
	if (rand() % 7 == 0) current = new Tetris_T();
	else if (rand() % 7 == 1) current = new Tetris_L();
	else if (rand() % 7 == 2) current = new Tetris_O();
	else if (rand() % 7 == 3) current = new Tetris_I();
	else if (rand() % 7 == 4) current = new Tetris_S();
	else if (rand() % 7 == 5) current = new Tetris_J();
	else current = new Tetris_Z();
}


