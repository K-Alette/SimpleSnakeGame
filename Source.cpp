//Snake game using C++
/********** FLASH WARNING ***********/
// This game will blip/flash every second or so as it refreshes the screen
// anyone who is photosensitive to flashing lights use caution

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

//define global variables
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//Set up game board
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}

//Draw game board
void Draw()
{
	system("cls"); //system("clear"); = linux
	for (int i = 0; i < width+2; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "|";
			if (i == y && j == x)
				cout << "O"; //head of snake
			else if (i == fruity && j == fruitx)
				cout << "F"; //fruit
			else
			{	bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o"; //snake tail
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "|";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "-";
	cout << endl;

	cout << "Score: " << score << endl;
}

//Definte user input for direction
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		}
	}
}

//game logic for player movement and scoring
void Logic()
{
	//make tail follow movement of piece in front of it
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}

	//direction output
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		Sleep(80);
		y--;
		break;
	case DOWN:
		Sleep(80);
		y++;
		break;
	default:
		break;
	}

	//allow user to pass through walls and come back out on other side
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	//if user head collides with tail, game over
	for (int i = 0; i < nTail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
			gameOver = true;
	}

	//user scores when colliding with fruit
	if (x == fruitx && y == fruity)
	{
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		nTail++;
	}
}

/* MAIN */
int main()
{
	Setup();

	//game loop continues until game over
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10); //slow down game (higher values = more bliping issue with output)
	}
}