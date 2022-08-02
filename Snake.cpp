#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameState = true,gameover = false;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score,speed,mode = 100, m = 1;
int tailX[100], tailY[100]; //coordinate
int nTail;		// specify the lenght of the tail
char choice;
enum eDirection { STOP = 0, LEFT, RIGHT,DOWN,UP};
eDirection dir;

void gamemode();
void startGame();
void menu();

void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)				//wall
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)								//wall
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)	//the position of fruit
				cout << "F";
			else
			{
				bool print = false;						// create the tail
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";							
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "\n score: " << score << endl;
	cout << "Level: " << m <<" "<< gameover << endl;
}

void Input()					//using WASD to control the snake
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0]; // previous x-coordinate of the tail of the segment
	int prevY = tailY[0]; // previous y-coordinate of the tail of the segment
	int tempX, tempY;
	tailX[0] = x;		//follow the head 
	tailY[0] = y;		//follow the head 

	for (int i = 1; i < nTail; i++)
	{
		tempX = tailX[i]; //remember the current position of the tail
		tempY = tailY[i]; //remember the current position of the tail
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}

	switch (dir)
	{
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
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameover = true;
		system("cls");
		cout << "Score: " << score << " " << gameState <<" " << gameover << endl;
		cout << "enter any key to back to the menu ";
		cin >> choice;
		if (choice != ' ')
		{
			system("cls");
			gameover = false;
			menu();
		}
	}

	/*
	Invincible mode

	if(x >= width)
		x = 0;
	else if(x < 0)
		x = width -1;
	if(y >= height)
		x = 0;
	else if(y < 0)
		x = height -1;
	*/

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			gameover = true;
		}

	if (x == fruitX && y == fruitY) // get the score and the tail will be longer
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

	
}

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void menu()
{
	
	cout << "\n\n\n\n\t  Snake Game";
	bool starMenu = true;
	int Set[] = { 12,7,7 }; // default colors
	int counter = 1;
	char key;
	while(starMenu)
	{
		gotoxy(10, 5);			//position
		color(Set[0]);
		cout << "1. Start";

		gotoxy(10, 6);			//position
		color(Set[1]);
		cout << "2. Setting";

		gotoxy(10, 7);			//position
		color(Set[2]);
		cout << "3. Exit";

		key = _getch();

		if ((key == 'w'||key ==72) && (counter >= 2 && counter <= 3)) // 72 = UP
		{
			counter--;

		}
		if ((key == 's' || key == 80) && (counter >= 1 && counter <= 2)) // 80 = DOWN
		{
			counter++;
		}

		if (key == '\r') // carriage return = enter key
		{
			switch (counter)
			{
			case 1:
				startGame();
				break;
			case 2:
				system("cls");
				gamemode();
				break;
			case 3:
				exit(0);
				break;
			}

		}
		Set[0] = 7; //default white color;
		Set[1] = 7;
		Set[2] = 7;
		if (counter == 1)
		{
			Set[0] = 12;	//12 is color red
		}
		if (counter == 2)
		{
			Set[1] = 12;	
		}
		if (counter == 3)
		{
			Set[2] = 12;	
		}
	}
}

void gamemode()
{
	cout << "Game Mode: (Now) " << m << endl;
	cout << "Mode 1: Easy " << endl;
	cout << "Mode 2: Normal " << endl;
	cout << "Mode 3: Hard " << endl;
	cout << "Select a game mode(1~3): ";
	cin >> m;
	switch (m)
	{
	case 1:
		mode = 100;
		break;
	case 2:
		mode = 50;
		break;
	case 3:
		mode = 1;
		break;
	}
	system("cls");
	menu();
}

void startGame()
{
	setup();
	while (gameState != gameover)
	{
		Draw();
		Input();
		Logic();
		Sleep(mode);
	}

	if (gameState == gameover)
	{
		gameover = false;
		nTail = 0;
		return startGame();
	}

}


int main()
{
	menu();
	return 0;
}