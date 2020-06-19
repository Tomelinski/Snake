/*
Author: Tom Zielinski
Date: 3/23/2020
Program: Snake
Program Description:
*/

#include "iostream"
#include "windows.h"	// For colours, Beep(), and Sleep()
#include "conio.h"		// For using the arrow keys
#include "Random.cpp"
#include "Console.cpp"
#include "fstream"
#include "vector"
#include "Users.cpp"
#include "algorithm"


using namespace std;

//ascii char for snake and boarder
const char wall = 219;
const char snake = 207;
const char fruit = 208;
const int winner = 120;

//map size
const int height = 20;
const int width = 40;

//variable
bool gameOver;
bool exitGame;
int snakeX, snakeY;
int fruitX, fruitY;
int tailX[winner], tailY[winner];
int tail;
int score;
int prevScore;
int UserChoise;
int deathChoise;
string username;
string save = "HighScore.save";
vector<Users> player;

enum eDirection { STOP = 0, UP, DOWN, RIGHT, LEFT };
eDirection dir;


void setup() {

	UserChoise = 1;
	deathChoise = 1;
	gameOver = false;
	exitGame = false;
	dir = STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	fruitX = Random::Next(width - 2) + 1;
	fruitY = Random::Next(height - 2) + 1;
	tail = 0;
	prevScore = score;
	score = 0;
	

}

void draw() {
	Console::Clear();
	string board = "";

	cout << "Score: " << score;

	cout << "\n\n";

	for (int i = 0; i <= height; i++)
	{
		for (int f = 0; f <= width; f++)
		{
			if (f == 0 || f == width || i == 0 || i == height) {
				board += wall;
			}
			else {

				if (f == snakeX && i == snakeY)
				{
					board += snake;
				}
				else if (f == fruitX && i == fruitY)
				{
					board += fruit;
				}
				else
				{
					bool print = false;
					
					for (int j = 0; j < tail; j++)
					{
						
						if (tailX[j] == f && tailY[j] == i)
						{
							board += snake;
							print = true;
						}
					}
					
					if (!print)
					{
						board += " ";
					}
				}

			}



		}

		board += "\n";
	}

	cout << board;
}

void input() {

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
			//gameOver = true;
			exitGame = true;
			break;
		}
	}

}

void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;

	for (int i = 1; i < tail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	case RIGHT:
		snakeX++;
		break;
	case LEFT:
		snakeX--;
		break;
	default:
		break;
	}

	if (snakeX <= 0 || snakeX >= width || snakeY <= 0 || snakeY >= height)
	{
		gameOver = true;
	}
	for (int i = 0; i < tail; i++)
	{
		if (snakeX == tailX[i] && snakeY == tailY[i])
		{
			gameOver = true;
		}

	}
	if(snakeX == fruitX &&  snakeY == fruitY)
	{
		score += 10;
		bool fruitSnake = false;
		do
		{
			
			fruitX = Random::Next(width - 2) + 1;
			fruitY = Random::Next(height - 2) + 1;
			for (int i = 0; i < tail; i++)
			{
				fruitSnake = false;
				if (fruitX == tailX[i] && fruitY == tailY[i])
				{
					fruitX = Random::Next(width - 2) + 1;
					fruitY = Random::Next(height - 2) + 1;
					fruitSnake = true;
					break;
				}
			}

		} while (fruitSnake);
		tail++;
	}

}

void sort() {

}

void saveGame() {
	char uInput;
	
	do
	{
		Console::Clear();
		Console::Write(R"(
   _____              __  __   ______      ____   __      __  ______   _____  
  / ____|     /\     |  \/  | |  ____|    / __ \  \ \    / / |  ____| |  __ \ 
 | |  __     /  \    | \  / | | |__      | |  | |  \ \  / /  | |__    | |__) |
 | | |_ |   / /\ \   | |\/| | |  __|     | |  | |   \ \/ /   |  __|   |  _  / 
 | |__| |  / ____ \  | |  | | | |____    | |__| |    \  /    | |____  | | \ \ 
  \_____| /_/    \_\ |_|  |_| |______|    \____/      \/     |______| |_|  \_\)", Colour::Green);

	
		cout << "\n your Score: " << score;
		cout << "\nWould you like to save?";
		if (deathChoise == 1)
		{
			Console::Write("[Yes] ", Colour::DarkGreen);
			Console::Write("[No]", Colour::White);
		}
		else if (deathChoise == 2)
		{
			Console::Write("[Yes] ", Colour::White);
			Console::Write("[No]", Colour::DarkGreen);
		}

		uInput = _getch();

		if (uInput == 'a')
		{
			if (deathChoise == 1)
			{
				deathChoise = 2;
			}
			else
			{
				deathChoise--;
			}
		}
		else if (uInput == 'd')
		{
			if (deathChoise == 2)
			{
				deathChoise = 1;
			}
			else
			{
				deathChoise++;
			}
		}
	} while (uInput != (char)13);

	char uName[4];

	if (deathChoise == 1)
	{
		
		cout << "\nEnter Username: ";

		cin.getline(uName, 4);
		
		username = uName;

		player.insert(player.end(), Users(username, score));

		if (score > player[10].score)
		{
			ofstream outputFile;

			sort(player.begin(), player.end(), Users::SortScore);
			outputFile.open(save, ios::out);
			outputFile << player[0].name << " " << player[0].score << "\n";
			outputFile.close();
			
			outputFile.open(save, ios::app);
			for (int i = 1; i <= 9; i++)
			{
				outputFile << player[i].name << " " << player[i].score << "\n";

			}
			outputFile.close();
		}

	}


}

void HighScore() {

	ifstream inputFile;
	Console::Clear();
	Console::Write(R"(
  _    _   _____    _____   _    _    _____    _____    ____    _____    ______ 
 | |  | | |_   _|  / ____| | |  | |  / ____|  / ____|  / __ \  |  __ \  |  ____|
 | |__| |   | |   | |  __  | |__| | | (___   | |      | |  | | | |__) | | |__   
 |  __  |   | |   | | |_ | |  __  |  \___ \  | |      | |  | | |  _  /  |  __|  
 | |  | |  _| |_  | |__| | | |  | |  ____) | | |____  | |__| | | | \ \  | |____ 
 |_|  |_| |_____|  \_____| |_|  |_| |_____/   \_____|  \____/  |_|  \_\ |______|)", Colour::DarkBlue);
	cout << "\n";

	inputFile.open(save);
	string fileUserName;
	int fileScore;
	//if file does not exist
	if (inputFile.fail())
	{
	  Console::WriteError("Could not open " + save);
	}
	else
	{
		cout << "   Username     |     Score\n";
		for (int i = 1; i <= 10; i++)
		{
			inputFile >> fileUserName >> fileScore;
			if (i < 10)
				cout << i << ".    " << fileUserName << "       |      " << fileScore << "\n";
			else
				cout << i << ".   " << fileUserName << "       |      " << fileScore << "\n";

		}

	}
	inputFile.close();



	cout << "\nPress any key to Exit";
	_getch();
}

void Dashboard() {
	char uInput;
	do
	{
		Console::Clear();
		Console::Write(R"(
  _____   _   _              _  __  ______     ______              __  __   ______ 
 / ____| | \ | |     /\     | |/ / |  ____|   /  ____|     /\     |  \/  | |  ____|
| (___   |  \| |    /  \    | ' /  | |__      | |  __     /  \    | \  / | | |__   
 \___ \  | . ` |   / /\ \   |  <   |  __|     | | |_ |   / /\ \   | |\/| | |  __|  
 ____) | | |\  |  / ____ \  | . \  | |____    | |__| |  / ____ \  | |  | | | |____ 
|_____/  |_| \_| /_/    \_\ |_|\_\ |______|   \______| /_/    \_\ |_|  |_| |______|)", Colour::Green);

		cout << "\n";
		cout << snake << " is your snake\n";
		cout << wall << " is a wall\n";
		cout << fruit << " is a fruit\n";
		cout << "Use W-A-S-D to move\n";
		cout << "Press x to exit\n";
		cout << "\nYour Score: " << prevScore;
		cout << "\n\n";
	
		if (UserChoise == 1)
		{
			Console::WriteLine("Play Snake", Colour::DarkGreen);
			Console::WriteLine("High Score", Colour::White);
			Console::WriteLine("Exit", Colour::White);
		}
		else if (UserChoise == 2)
		{
			Console::WriteLine("Play Snake", Colour::White);
			Console::WriteLine("High Score", Colour::DarkGreen);
			Console::WriteLine("Exit", Colour::White);
		}
		else if (UserChoise == 3)
		{
			Console::WriteLine("Play Snake", Colour::White);
			Console::WriteLine("High Score", Colour::White);
			Console::WriteLine("Exit", Colour::DarkGreen);
		}

		uInput = _getch();

		if (uInput == 'w')
		{
			if (UserChoise == 1)
			{
				UserChoise = 3;
			}
			else
			{
				UserChoise--;
			}
		}
		else if (uInput == 's')
		{
			if (UserChoise == 3)
			{
				UserChoise = 1;
			}
			else
			{
				UserChoise++;
			}
		}
		else if(uInput == 'x')
		{
			//gameOver = true;
			exitGame = true;
			UserChoise = 3;

			break;
		}

		if (uInput == (char)13 && UserChoise == 3)
		{
			//gameOver = true;
			exitGame = true;
			break;
		}

	} while (uInput != (char)13);
}

// Program execution begins and ends here.
int main()
{
	system("title Snake - Tom Zielinski");
	
	ifstream inputFile;
	inputFile.open(save);
	string fileUserName;
	int fileScore;
	//if file does not exist
	if (inputFile.fail())
	{
		Console::WriteError("Could not open " + save);
	}
	else
	{
		//inputFile >> fileUserName >> fileScore;
		//player.insert(player.begin(), Users(fileUserName, fileScore));
		for (int i = 0; i <= 10; i++)
		{
			inputFile >> fileUserName >> fileScore;
			player.insert(player.end(), Users(fileUserName, fileScore));

		}
	}
	inputFile.close();

	do {
		Random::Seed();

		setup();
		Dashboard();

		if (UserChoise == 1)
		{

			do {

				draw();
				input();
				logic();


				Sleep(50);
			} while (gameOver == false && exitGame == false);
			
			if (gameOver == true && exitGame == false)
			{
				saveGame();
			}
			
		}
		else if (UserChoise == 2)
		{
			HighScore();
		}

	} while (UserChoise != 3);



}
