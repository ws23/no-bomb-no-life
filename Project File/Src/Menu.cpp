#include"Menu.h"
#include"controlCon.h"//for set console

#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
#include<cstdlib>

bool Menu::TimeSwitch(true);

int Menu::DisplayList()
{
	using std::cout;
	using std::endl;

	const std::vector<std::string> menuList{ ("Player Vs Player"), ("Player Vs Computer"), ("Config"), ("Staff"), ("Exit") };
	const char *point("⊙");


	int fr = 0;//flag to row
	int fc = 0;//flag to column
	int chk;//gets the keyboard value
	size_t numOfList(menuList.size());
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));


loop:
	FillConsole();

	MakeTitleGraph(TimeSwitch);
	if (TimeSwitch)TimeSwitch = false;

	while (true)
	{
		gotoXY(0, 5);
		for (size_t index = 0; index < numOfList; index++)
		{
			if (fr == index)
			{
				cout << "   " << point << '\t';
				strDraw(menuList[index], 252, hConsole);//white backgroung,red txt
				cout << " \n\n\n" << endl;
			}
			else
				cout << '\t' << menuList[index] << "\n\n\n" << endl;

			if (fc != 0)
			{
				FillConsole();
				if (fc == 1)//每一個項目裡的內容
				{
					if (fr == 0)
						return 1;
					else if (fr == 1)
						return 2;
					else if (fr == 2)
						return 3;
					else if (fr == 3)
						return 4;
					else if (fr == 4)
						exit(EXIT_SUCCESS);
				}
				else if (fc == -1)
				{
					cout << "\t\t\tPress Esc again to quit the game !" << endl;
					if ((chk = _getch()) == 0x1b)//Esc
						exit(EXIT_SUCCESS);
					else
					{
						fc = 0;
						goto loop;
					}
					fc = 0;
					system("pause");
					goto loop;
				}


			}
		}

		switch (chk = _getch())
		{
		case 0x48:  //up
			fr--;
			if (fr < 0)
				fr = numOfList - 1;
			break;
		case 0x50:  //down
			fr++;
			if (fr > static_cast<int>(numOfList)-1)
				fr = 0;
			break;
		case 0x1b:  //Esc
			fc--;
			break;
		case 0xD:  //enter
			fc++;
			break;
		}

	}
}

int Menu::DisplayPvPMenu()
{
	char chk;
	std::cout << "PVP" << std::endl;
	if (chk = _getch() == 0x1b)
		return 0;
	else std::cout << "go" << std::endl;
	return 1;
}

int  Menu::DisplayPvCMenu()
{
	char chk;
	std::cout << "PVC" << std::endl;
	if (chk = _getch() == 0x1b)
		return 0;
	else std::cout << "go" << std::endl;
	return 1;
}
int  Menu::DisplayConfig()
{
	char chk;
	std::cout << "Config" << std::endl;
	if (chk = _getch() == 0x1b)
		return 0;
	else std::cout << "go" << std::endl;
	return 1;
}
int  Menu::DisplayStaff()
{
	char chk;
	std::cout << "Staff" << std::endl;
	if (chk = _getch() == 0x1b)
		return 0;
	else std::cout << "go" << std::endl;
	return 1;
}

void Menu::strDraw(std::string str, int colorIndex, HANDLE hConsole /*= GetStdHandle(STD_OUTPUT_HANDLE)*/)
{
	SetConsoleTextAttribute(hConsole, colorIndex);
	std::cout << str;
	SetConsoleTextAttribute(hConsole, 7);//back to the default color

}

void Menu::MakeTitleGraph(bool &TimeSwitch)
{
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));
	int ColorIndex, pos_x, pos_y;
	int delay(20);//延遲時間
	std::string chOut;

	/*
	7:灰字黑底
	8:深灰字黑底
	9:藍字黑底
	12:紅字黑底
	120:深灰字灰底
	*/

	/*'N'O*/
#pragma region N

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 38, pos_y = 5);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	chOut = "■";
	for (pos_x = 38, pos_y = 4; pos_y > 0; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 40, --pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 8;
	for (pos_x = 40, pos_y = 5; pos_y > 1; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 42, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	gotoXY(pos_x = 42, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◣";
	gotoXY(pos_x = 44, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	gotoXY(pos_x = 44, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◣";
	ColorIndex = 120;
	gotoXY(pos_x = 46, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	ColorIndex =8;
	gotoXY(pos_x = 46, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 7;
	for (pos_x = 46, pos_y = 3; pos_y > 0; pos_y--)
	{
		gotoXY(pos_x = 46, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 48, pos_y = 1);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex =8;
	for (pos_x = 48, pos_y = 5; pos_y > 1; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

#pragma endregion First N

	/*N'O'*/
#pragma region O

	chOut = "◥";
	ColorIndex = 7;
	gotoXY(pos_x = 54, pos_y = 5);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 54, pos_y = 4; pos_y > 0; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 56, pos_y = 1; pos_x <= 60; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 8;
	for (pos_x = 56, pos_y = 5; pos_y > 1; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 58, pos_y = 2; pos_x <= 62; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 2; pos_y <= 5; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 5; pos_x >= 58; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	pos_x = 58;
	pos_y = 4;
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 60;
	pos_y = 4;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 58;
	pos_y = 3;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion First O

	/*'B'OMB by Jheng, Bo An*/
#pragma region B

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 38, pos_y = 12);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_y--; pos_y >= 7; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_x <= 42; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);



	ColorIndex = 9;
	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 40; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_y <= 12; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y -= 3; pos_x <= 42; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 40, pos_y += 2; pos_x <= 42; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 44, pos_y = 9; pos_y <= 11; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◤";
	gotoXY(pos_x = 44, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion First B

	/*B'O'MB by Jheng, Bo An*/
#pragma region O

	chOut = "◥";
	ColorIndex = 7;
	gotoXY(pos_x = 50, pos_y = 12);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 50, pos_y = 11; pos_y > 7; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 50, pos_y = 8; pos_x <= 56; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 9;
	for (pos_x = 52, pos_y = 12; pos_y > 8; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 52, pos_y = 9; pos_x <= 58; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 58, pos_y = 9; pos_y <= 12; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 58, pos_y = 12; pos_x >= 54; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	pos_x = 54;
	pos_y = 11;
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 56;
	pos_y = 11;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 54;
	pos_y = 10;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion Second O

	/*BO'M'B by Jheng, Bo An*/
#pragma region M


	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 64, pos_y = 12);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_y--; pos_y >= 7; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_x <= 72; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);



	ColorIndex = 9;
	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 66; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_y <= 12; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	chOut = "■";
	for (pos_x += 2, pos_y -= 4; pos_y <= 10; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◥";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	ColorIndex = 9;
	chOut = "■";
	for (pos_x += 2, pos_y -= 2; pos_y <= 11; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	chOut = "■";
	for (pos_x += 2, pos_y -= 3; pos_y <= 11; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◥";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	ColorIndex = 9;
	chOut = "■";
	for (pos_x += 2, pos_y -= 4; pos_y <= 12; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}



#pragma endregion First M

	/*BOM'B' by Jheng, Bo An*/
#pragma region B

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 80, pos_y = 12);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_y--; pos_y >= 7; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_x <= 84; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);



	ColorIndex = 9;
	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 82; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_y <= 12; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y -= 3; pos_x <= 84; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 82, pos_y += 2; pos_x <= 84; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 86, pos_y = 9; pos_y <= 11; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◤";
	gotoXY(pos_x = 86, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion Second B

	/*'N'O by Jheng, Bo An*/
#pragma region N

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 38, pos_y = 19);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	chOut = "■";
	for (pos_x = 38, pos_y = 18; pos_y > 14; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 40, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 8;
	for (pos_x = 40, pos_y = 19; pos_y > 15; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 42, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	gotoXY(pos_x = 42, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◣";
	gotoXY(pos_x = 44, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	gotoXY(pos_x = 44, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◣";
	ColorIndex = 120;
	gotoXY(pos_x = 46, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	ColorIndex = 8;
	gotoXY(pos_x = 46, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 7;
	for (pos_x = 46, pos_y = 17; pos_y > 14; pos_y--)
	{
		gotoXY(pos_x = 46, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 48, pos_y = 15);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 8;
	for (pos_x = 48, pos_y = 19; pos_y > 15; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

#pragma endregion Second N

	/*N'O' by Jheng, Bo An*/
#pragma region O

	chOut = "◥";
	ColorIndex = 7;
	gotoXY(pos_x = 54, pos_y = 19);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 54, pos_y = 18; pos_y > 14; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 56, pos_y = 15; pos_x <= 60; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 8;
	for (pos_x = 56, pos_y = 19; pos_y > 15; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 58, pos_y = 16; pos_x <= 62; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 16; pos_y <= 19; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 19; pos_x >= 58; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	pos_x = 58;
	pos_y = 19;
	gotoXY(pos_x, --pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 60;
	pos_y = 19;
	chOut = "◣";
	gotoXY(pos_x, --pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 58;
	pos_y = 17;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion Third O

	/*'L'IFE by Jheng, Bo An*/
#pragma region L

	ColorIndex = 7;

	chOut = "◥";
	gotoXY(pos_x = 38, pos_y = 27);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 38, pos_y--; pos_y >= 22; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 40, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	ColorIndex = 12;
	chOut = "■";
	for (pos_x, pos_y++; pos_y <= 27; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y--; pos_x <= 44; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}


	ColorIndex = 7;

	chOut = "◣";
	gotoXY(pos_x -= 2, --pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	gotoXY(pos_x -= 2, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion First L

	/*L'I'FE by Jheng, Bo An*/
#pragma region I

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 50, pos_y = 23);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x, pos_y--; pos_x <= 54; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	ColorIndex = 12;

	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 52; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";

	for (pos_x += 4, pos_y++; pos_y <= 27; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";

	for (pos_x += 2, pos_y--; pos_x >= 52; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}


	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	gotoXY(pos_x, --pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	chOut = "◣";
	gotoXY(pos_x += 2, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◣";
	gotoXY(pos_x += 4, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


#pragma endregion First I

	/*LI'F'E by Jheng, Bo An*/
#pragma region F

	ColorIndex = 7;

	chOut = "◥";
	gotoXY(pos_x = 62, pos_y = 27);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";

	for (pos_y--; pos_y >= 22; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_x <= 66; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	ColorIndex = 12;
	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 64; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_y <= 27; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y -= 3; pos_x <= 68; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

#pragma endregion First F

	/*LIF'E' by Jheng, Bo An*/
#pragma region E

	ColorIndex = 7;

	chOut = "◥";
	gotoXY(pos_x = 74, pos_y = 27);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";

	for (pos_y--; pos_y >= 22; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_x <= 78; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);


	ColorIndex = 12;
	chOut = "■";
	for (pos_x, pos_y++; pos_x >= 76; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y++; pos_y <= 27; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x += 2, pos_y -= 3; pos_x <= 80; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 76, pos_y += 2; pos_x <= 80; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}
#pragma endregion First E


}

