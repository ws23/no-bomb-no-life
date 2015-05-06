#include"Menu.h"
#include"controlCon.h"//for set console

#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
#include<cstdlib>

void strDraw(std::string str, int colorIndex, HANDLE hConsole /*= GetStdHandle(STD_OUTPUT_HANDLE)*/)
{
	SetConsoleTextAttribute(hConsole, colorIndex);
	std::cout << str;
	SetConsoleTextAttribute(hConsole, 7);//back to the default color

}
void DisplayList()
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
	bool graph_time_flag(true);

loop:
	FillConsole();

	MakeTitleGraph(graph_time_flag);
	if (graph_time_flag)graph_time_flag = false;

	while (true)
	{
		gotoXY(0, 5);
		for (size_t index = 0; index < numOfList; index++)
		{
			if (fr == index)
			{
				cout << "   " << point << '\t';
				strDraw(menuList[index], 252, hConsole);//white backgroung,red txt
				cout << " \n" << endl;
			}
			else
				cout << '\t' << menuList[index] << '\n' << endl;

			if (fc != 0)
			{
				FillConsole();
				if (fc == 1)//每一個項目裡的內容
				{
					if (fr == 0)
						cout << "\t\t\t\t" << menuList[0] << endl;
					else if (fr == 1)
						cout << "\t\t\t\t" << menuList[1] << endl;
					else if (fr == 2)
						cout << "\t\t\t\t" << menuList[2] << endl;
					else if (fr == 3)
						cout << "\t\t\t\t" << menuList[3] << endl;
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
				}
				fc = 0;
				system("pause");
				goto loop;

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
void MakeTitleGraph(bool &TimeSwitch)
{
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));
	int ColorIndex, pos_x, pos_y;
	int delay(50);//延遲時間
	std::string chOut;

	/*
	7:灰字黑底
	9:藍字黑底
	121:藍字灰底
	*/

	/*1st N*/
#pragma region N

	ColorIndex = 7;
	chOut = "◥";
	gotoXY(pos_x = 38, pos_y = 4);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 38, pos_y = 3; pos_y >= 0; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 40, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 9;
	for (pos_x = 40, pos_y = 4; pos_y; pos_y--)
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
	ColorIndex = 121;
	gotoXY(pos_x = 46, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "◥";
	ColorIndex = 9;
	gotoXY(pos_x = 46, ++pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 7;
	for (pos_x = 46, pos_y = 2; pos_y >= 0; pos_y--)
	{
		gotoXY(pos_x = 46, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "◣";
	gotoXY(pos_x = 48, pos_y = 0);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	ColorIndex = 9;
	for (pos_x = 48, pos_y = 4; pos_y; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

#pragma endregion First N

	/*1st O*/
#pragma region O

	chOut = "◥";
	ColorIndex = 7;
	gotoXY(pos_x = 54, pos_y = 4);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	chOut = "■";
	for (pos_x = 54, pos_y = 3; pos_y >= 0; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	chOut = "■";
	for (pos_x = 56, pos_y = 0; pos_x <= 60; pos_x += 2)
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
	for (pos_x = 56, pos_y = 4; pos_y; pos_y--)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 58, pos_y = 1; pos_x <= 62; pos_x += 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 1; pos_y <= 4; pos_y++)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	for (pos_x = 62, pos_y = 4; pos_x >= 58; pos_x -= 2)
	{
		gotoXY(pos_x, pos_y);
		strDraw(chOut, ColorIndex, hConsole);
		if (TimeSwitch)Sleep(delay);
	}

	ColorIndex = 7;
	pos_x = 58;
	pos_y = 3;
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 60;
	pos_y = 3;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

	pos_x = 58;
	pos_y = 2;
	chOut = "◣";
	gotoXY(pos_x, pos_y);
	strDraw(chOut, ColorIndex, hConsole);
	if (TimeSwitch)Sleep(delay);

#pragma endregion First O

}