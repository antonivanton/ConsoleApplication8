#include "pch.h"
#include <iostream>
#include<conio.h>

using namespace std;


bool gameOver;
const int wind = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eGo { Stop = 0, LEFT, RIGHT, DOWN, UP };
eGo dir;

void Setup() {
	gameOver = false;
	dir = Stop;
	x = wind / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % wind;
	fruitY = rand() % height;
	score = 0;

}

void Draw() {
	system("cls");
	//verh
	for (int i = 0; i < wind + 1; i++)
		cout << "#";
	cout << endl;

	//boka
	for (int i = 0; i < height; i++) {

		for (int j = 0; j < wind; j++) {
			if (j == 0 || j == wind - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && fruitX)
				cout << "x";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if(!print)
				cout << " ";

			}

		}
		cout << endl;
		cout << "Score " << score << endl;

		//niz
	}
	for (int i = 0; i < wind + 1; i++)
		cout << "#";
	cout << endl;
}


void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case'a':
			dir = LEFT;
			break;
		case'd':
			dir = RIGHT;
			break;
		case'w':
			dir = UP;
			break;
		case's':
			dir = DOWN;
			break;
		case'x':
			gameOver = true;
			break;
		}
	}

}


void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//dvigenie
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
		//pole
		if (x > wind || x < 0 || y>height || y < 0)
			gameOver = true;

		for (int i = 0; i < nTail; i++) {
			if (tailX[i] == x && tailY[i] == y)
				gameOver = true;
		}

		//ochki
		if (x == fruitX && y == fruitY) {
			score += 1;
			fruitX = rand() % wind;
			fruitY = rand() % height;
			nTail++;


		}
	}
}

int main() {
	Setup();
	while (!gameOver); {
		Draw();
		Input();
		Logic();
	}
	return 0;
}