#include "CGAME.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include "GUI.h"
#pragma comment(lib, "winmm.lib")

void CGAME::input(char cmd)
{

	switch (cmd)
	{
	case 'w':
	{
		//gameBoard[pep.mY][pep.mX] = '.';
		pep.Up(GAME_HEIGHT);
		pep.isDead = pep.isDead || pepRunInto();
		pep.isWin = pep.isWin || (pep.mY == 0);
		PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (pep.isDead)
		{
			PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		return;
	}
	case 's':
	{
		//gameBoard[pep.mY][pep.mX] = '.';
		pep.Down(GAME_HEIGHT);
		pep.isDead = pep.isDead || pepRunInto();
		pep.isWin = pep.isWin || (pep.mY == 0);
		PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (pep.isDead)
		{
			PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		return;
	}
	case 'a':
	{
		//gameBoard[pep.mY][pep.mX] = '.';
		pep.Left(GAME_HEIGHT);
		pep.isDead = pep.isDead || pepRunInto();
		pep.isWin = pep.isWin || (pep.mY == 0);
		PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (pep.isDead)
		{
			PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		return;
	}
	case 'd':
	{
		//gameBoard[pep.mY][pep.mX] = '.';
		pep.Right(GAME_WIDTH);
		pep.isDead = pep.isDead || pepRunInto();
		pep.isWin = pep.isWin || (pep.mY == 0);
		PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (pep.isDead)
		{
			PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		return;
	}
	default:
		break;
	}
}

bool CGAME::pepRunInto()
{
	for (int i = 0; i < CarTruck_yLine.size(); i++)
	{
		if (pep.mY == CarTruck_yLine[i])
		{
			for (int i = 0; i < carVct.size(); i++)
			{
				if(havePep(carVct[i].getX(),carVct[i].getY()))  {return true;};
			}
			for (int i = 0; i < truckVct.size(); i++)
			{
				if (havePep(truckVct[i].getX(), truckVct[i].getY())) { return true; };
			}

		}
	}

	for (int i = 0; i < animal_yLine.size(); i++)
	{
		if (pep.mY == animal_yLine[i])
		{
			for (int i = 0; i < dinoVct.size(); i++)
			{
				if (havePep(dinoVct[i].getX(), dinoVct[i].getY())) { return true; };
			}
			for (int i = 0; i < eleVct.size(); i++)
			{
				if (havePep(eleVct[i].getX(), eleVct[i].getY())) { return true; };
			}

		}
	}

	return false;
}


void CGAME::drawBorder()
{
	SetConsoleTextAttribute(Consolehandle, 15); // White
	short height = 3;
	short with = 3;

	//Upper bound 
	gotoxy(with-1, height - 1);
	for (int i = 0; i < GAME_WIDTH + 2; i++)
	{
		std::cout << char(219);
	}
	//Side bound
	for (int i = 0; i < GAME_HEIGHT + 1; i++)
	{
		for (int a = 0; a < CarTruck_yLine.size(); a++)
		{
			if (i == CarTruck_yLine[a])
			{
				//Chuyen do xanh
				if (carIsStop == true)
				{
					SetConsoleTextAttribute(Consolehandle, 12); // Red
				}
				else
				{
					SetConsoleTextAttribute(Consolehandle, 10); // Green
				}
			}
		}
		gotoxy(with-1, 3 + i);
		std::cout << char(219);
		gotoxy(with-1 + GAME_WIDTH + 1, 3 + i);
		std::cout << char(219);
		SetConsoleTextAttribute(Consolehandle, 15); // White
	}
	//Lower Bound
	gotoxy(with-1, height + GAME_HEIGHT + 1);
	for (int i = 0; i < GAME_WIDTH + 2; i++)
	{
		std::cout << char(219);
	}
}

void CGAME::draw()
{
	SetConsoleTextAttribute(Consolehandle, 15); // White
	system("cls");
	this->drawBorder();
	short height = 3;
	short with = 3;
	gotoxy(with + pep.mX, height + pep.mY);
	std::cout << "^";


	for (int i = 0; i < carVct.size(); i++)
	{
		gotoxy(with + carVct[i].getX(), height + carVct[i].getY());
		std::cout << CCAR::symb;
	}

	for (int i = 0; i < eleVct.size(); i++)
	{
		gotoxy(with + eleVct[i].getX(), height + eleVct[i].getY());
		std::cout << CELEPHANT::symb;
	}

	for (int i = 0; i < truckVct.size(); i++)
	{
		gotoxy(with + truckVct[i].getX(), height + truckVct[i].getY());
		std::cout << CTRUCK::symb;
	}

	for (int i = 0; i < dinoVct.size(); i++)
	{
		gotoxy(with + dinoVct[i].getX(), height + dinoVct[i].getY());
		std::cout << CDINOSAUR::symb;
	}
	
}

void CGAME::dinoUpdate(bool green)
{
	if (!green) { return; }
	int vctSize = dinoVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		/*if (true)
		{
			gameBoard[dinoVct[i].mY][dinoVct[i].mX] = '.';
		}*/
		dinoVct[i].Move(GAME_WIDTH, CDINOSAUR::spds);
		pep.isDead = pep.isDead || havePep(dinoVct[i].mX, dinoVct[i].mY);
		pep.isWin = pep.isWin || (pep.mY == 0);
	}
}


void CGAME::truckUpdate(bool green)
{
	if (!green) 
	{ 
		return; 
	}
	int vctSize = truckVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		/*if (true)
		{
			gameBoard[truckVct[i].mY][truckVct[i].mX] = '.';
		}*/
		truckVct[i].Move(GAME_WIDTH, CTRUCK::spds);
		pep.isDead = pep.isDead || havePep(truckVct[i].mX,truckVct[i].mY);
		pep.isWin = pep.isWin || (pep.mY == 0);

	}
}
void CGAME::carUpdate(bool green)
{
	if (!green) 
	{
		return; 
	}
	int vctSize = carVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		/*if (true)
		{
			gameBoard[carVct[i].mY][carVct[i].mX] = '.';
		}*/
		carVct[i].Move(GAME_WIDTH, CCAR::spds);
		pep.isDead = pep.isDead || havePep(carVct[i].mX, carVct[i].mY);
		pep.isWin = pep.isWin || (pep.mY == 0);

	}
}


void CGAME::eleUpdate(bool green)
{
	if (!green) { return; }
	int vctSize = eleVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		//if (true)
		//{
		//	gameBoard[eleVct[i].mY][eleVct[i].mX] = '.';
		//}
		eleVct[i].Move(GAME_WIDTH, CELEPHANT::spds);
		pep.isDead = pep.isDead || havePep(eleVct[i].mX, eleVct[i].mY);
		pep.isWin = pep.isWin || (pep.mY == 0);
	}
}

CGAME::CGAME(HANDLE &Consolehandler) :
	gameBoard(nullptr), carVct(0), truckVct(0), pep(GAME_WIDTH, GAME_HEIGHT - 1),dinoVct(0),eleVct(0), carIsStop(false),
	Consolehandle(Consolehandler)
{
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	//ConsoleColumns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//ConsoleRows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	//Crate game board
	/*gameBoard = new char* [GAME_HEIGHT];
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		gameBoard[i] = new char[GAME_WIDTH];
		for (int a = 0; a < GAME_WIDTH; a++)
		{
			gameBoard[i][a] = '.';
		}
	}*/

	for (int theHeight = 0; GAME_HEIGHT - theHeight > 1; )
	{
		//Line of car
		theHeight += 2;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		CarTruck_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CCAR::dist)
		{
			if (a + CCAR::size < GAME_WIDTH)
			{
				for (int b = 0; b < CCAR::size && (b + CCAR::size) < GAME_WIDTH; b++)
				{
					carVct.push_back(CCAR(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of truck
		theHeight += 1;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		CarTruck_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CTRUCK::dist)
		{
			if (a + CTRUCK::size < GAME_WIDTH)
			{
				for (int b = 0; b < CTRUCK::size && (b + CTRUCK::size) < GAME_WIDTH; b++)
				{
					truckVct.push_back(CTRUCK(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of ele
		theHeight += 2;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		animal_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CELEPHANT::dist)
		{
			if (a + CELEPHANT::size < GAME_WIDTH)
			{
				for (int b = 0; b < CELEPHANT::size && (b + CELEPHANT::size) < GAME_WIDTH; b++)
				{
					eleVct.push_back(CELEPHANT(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of dino
		theHeight += 1;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		animal_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CDINOSAUR::dist)
		{
			if (a + CDINOSAUR::size < GAME_WIDTH)
			{
				for (int b = 0; b < CDINOSAUR::size && (b + CDINOSAUR::size) < GAME_WIDTH; b++)
				{
					dinoVct.push_back(CDINOSAUR(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}
	}
}

// model save function
void CGAME::save()
{
	std::ofstream saveFile("saveFile.txt");
	saveFile << GAME_HEIGHT << " " << GAME_WIDTH << std::endl;
	saveFile << pep.mX << " " << pep.mY << std::endl;

	saveFile << "CCAR" << std::endl;
	for (int i = 0; i < carVct.size(); i++)
	{
		saveFile << carVct[i].getX() << " " << carVct[i].getY() << std::endl;
	}
}

// final save function
void CGAME::saveGame(std::string fileName)
{
	std::ofstream file(fileName);
	
	/*if (file.fail())
	{
		std::cout << "Cannot open file at " << fileName << std::endl;
		return;
	}*/
	std::cout << "Saving..." << std::endl; Sleep(1);
	// Sleep(1) for UX

	file << GAME_HEIGHT << " " << GAME_WIDTH << std::endl;
	file << pep.mX << " " << pep.mY << std::endl;

	file << "CCAR" << std::endl; // #
	for (int i = 0; i < carVct.size(); i++)
	{
		file <<  carVct[i].getX() << " " << carVct[i].getY() << std::endl;
	}

	file<< "CTRUCK " << std::endl; // **
	for (int i = 0; i < truckVct.size(); i++){
		file << truckVct[i].getX() << " " << truckVct[i].getY() << std::endl;
	}

	file<< "CDINOSAUR "<< std::endl; // >>>>
	for (int i = 0; i < dinoVct.size(); i++) {
		file << dinoVct[i].getX() << " " << dinoVct[i].getY() << std::endl;	
	}
	
	file << "CELEPHANT " << std::endl; // 000
	for (int i = 0; i < eleVct.size(); i++) {
		file << eleVct[i].getX() << " " << eleVct[i].getY() << std::endl;	
	}

	std::cout << "Save Succeessfully!" << std::endl;
	file.close();
}

void CGAME::loadGame(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << std::endl;
		return;
	}

	/*for (int y = 0; y < GAME_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_WIDTH; x++)
		{
			gameBoard[y][x] = '.';
		}
	}*/
	

	int hight, width;
	file >> hight >> width;
	//std::cout << hight << " " << width << std::endl;
	file >> pep.mX >> pep.mY;
	//std::cout << pep.mX << " " << pep.mY << std::endl;

	std::string car;
	file >> car; // junk car
	for (int i = 0; i < carVct.size(); i++)
	{
		file >> carVct[i].mX >> carVct[i].mY;
	}

	std::string truck;
	file >> truck; // junk truck
	for (int i = 0; i < truckVct.size(); i++) {
	file >> truckVct[i].mX >> truckVct[i].mY;
	}

	std::string dinosaur;
	file >> dinosaur; // junk dinosaur
	for (int i = 0; i < dinoVct.size(); i++) {
		file >> dinoVct[i].mX >> dinoVct[i].mY;
	}

	std::string elepants;
	file >> elepants; // junk elepants
	for (int i = 0; i < eleVct.size(); i++) {
	file >> eleVct[i].mX >> eleVct[i].mY;
	}

	file.close();
	std::cout << "Load successfull" << std::endl;
}


/*
* //Line of car
		theHeight += 2;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		CarTruck_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CCAR::dist)
		{
			if (a + CCAR::size < GAME_WIDTH)
			{
				for (int b = 0; b < CCAR::size && (b + CCAR::size) < GAME_WIDTH; b++)
				{
					carVct.push_back(CCAR(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of truck
		theHeight += 1;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		CarTruck_yLine.push_back(GAME_HEIGHT - theHeight);
		for (int a = 0; a < GAME_WIDTH; a += CTRUCK::dist)
		{
			if (a + CTRUCK::size < GAME_WIDTH)
			{
				for (int b = 0; b < CTRUCK::size && (b + CTRUCK::size) < GAME_WIDTH; b++)
				{
					truckVct.push_back(CTRUCK(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of ele
		theHeight += 2;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		for (int a = 0; a < GAME_WIDTH; a += CELEPHANT::dist)
		{
			if (a + CELEPHANT::size < GAME_WIDTH)
			{
				for (int b = 0; b < CELEPHANT::size && (b + CELEPHANT::size) < GAME_WIDTH; b++)
				{
					eleVct.push_back(CELEPHANT(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}

		//Line of dino
		theHeight += 1;
		if (GAME_HEIGHT - theHeight <= 0) { break; }
		for (int a = 0; a < GAME_WIDTH; a += CDINOSAUR::dist)
		{
			if (a + CDINOSAUR::size < GAME_WIDTH)
			{
				for (int b = 0; b < CDINOSAUR::size && (b + CDINOSAUR::size) < GAME_WIDTH; b++)
				{
					dinoVct.push_back(CDINOSAUR(a + b, GAME_HEIGHT - theHeight));
				}
			}
		}
*/

/*system("cls");

	//init people character
	gameBoard[pep.mY][pep.mX] = '^';

	//init car character
	int vctSize = carVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		gameBoard[carVct[i].mY][carVct[i].mX] = CCAR::symb;
	}

	//init truck character
	vctSize = truckVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		gameBoard[truckVct[i].mY][truckVct[i].mX] = CTRUCK::symb;
	}

	//init dino character
	vctSize = dinoVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		gameBoard[dinoVct[i].mY][dinoVct[i].mX] = CDINOSAUR::symb;
	}

	//init ele character
	vctSize = eleVct.size();
	for (int i = 0; i < vctSize; i++)
	{
		gameBoard[eleVct[i].mY][eleVct[i].mX] = CELEPHANT::symb;
	}
	int height = 3;

	gotoxy(15, height);
	std::cout << char(219);
	for (int x = 0; x < GAME_WIDTH; x++) { std::cout << char(219); }
	std::cout << char(219) << std::endl;

	for (int y = 0; y < GAME_HEIGHT; y++)
	{
		height++;
		bool isCarTruckLine = false;
		SetConsoleTextAttribute(Consolehandle, 15); // White
		gotoxy(15, height);

		for (int i = 0; i < CarTruck_yLine.size(); i++)
		{
			if (CarTruck_yLine[i] == y)
			{
				//Chuyen do xanh
				if (carIsStop == true)
				{
					SetConsoleTextAttribute(Consolehandle, 12); // Red
				}
				else
				{
					SetConsoleTextAttribute(Consolehandle, 10); // Green
				}

				std::cout << char(219);

				SetConsoleTextAttribute(Consolehandle, 15); // White

				for (int x = 0; x < GAME_WIDTH; x++)
				{
					std::cout << char(gameBoard[y][x]);
				}

				if (carIsStop == true)
				{
					SetConsoleTextAttribute(Consolehandle, 12); // Red
				}
				else
				{
					SetConsoleTextAttribute(Consolehandle, 10); // Green
				}

				std::cout << char(219) << std::endl;

				SetConsoleTextAttribute(Consolehandle, 15); // White
				isCarTruckLine = true;
				break;
			}
		}

		if (isCarTruckLine == false)
		{
			std::cout << char(219);
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				std::cout << char(gameBoard[y][x]);
			}
			std::cout << char(219) << std::endl;
		}
	}

	gotoxy(15, height+1);
	std::cout << char(219);
	for (int x = 0; x < GAME_WIDTH; x++) { std::cout << char(219); }
	std::cout << char(219) << std::endl;
}
*/