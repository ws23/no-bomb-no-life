#include"Menu.h"
#include"controlCon.h"//for set console

#include<iostream>
#include<windows.h>
#include<string>
#include<conio.h>
#include<vector>
#include<cstdlib>

bool Menu::TimeSwitch(true);

Menu::Menu()
{
	//角色資訊設定
	const std::vector<std::string> name{ "咩咩", "小撫子", "忍野忍", "小紅", "已知圖騰" };
	const std::vector<std::string>  appearance{ "◎", "㊣", "忍", "⊕", "∴" };
	size_t NumOfCharacter(name.size());

	int power[]{1, 2, 2, 4, 2};
	int powerLim[]{10, 8, 8, 6, 10};
	int amount[]{2, 1, 2, 1, 1};
	int amountLim[]{9, 8, 9, 8, 7};
	int speed[]{1, 4, 2, 1, 1};
	int speedLim[]{7, 6, 8, 9, 8};
	std::vector<Ability> ability;

	//Character List
	for (size_t i = 0; i < NumOfCharacter; i++)
		ability.push_back(Ability{ power[i], powerLim[i], amount[i], amountLim[i], speed[i], speedLim[i] });


	for (size_t i = 0; i < NumOfCharacter; i++)
		CharacterList.push_back(std::make_shared<Character>(appearance[i], name[i], ability[i]));

	//Map list
	for (int i = 1; i <= NUM_OF_MAP; i++)
		mapList.push_back(std::make_shared<Map>("map" + std::to_string(i)));
}
int Menu::DisplayList()
{
	SetConsoleSize(100, 30);
	using std::cout;
	using std::endl;

	const std::vector<std::string> menuList{ ("Player Vs Player"), ("Player Vs Computer"), ("Help"), ("Staff"), ("Exit") };
	const char *point("⊙");


	int fr = 0;//flag to row
	int fc = 0;//flag to column
	int chk;//gets the keyboard value
	size_t numOfList(menuList.size());
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));
	setCursorVisible(false, hConsole);


loop:
	FillConsole();
	//TimeSwitch = false;
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
						return PVP_OPTION;
					else if (fr == 1)
						return PVC_OPTION;
					else if (fr == 2)
						return HELP_OPTION;
					else if (fr == 3)
						return STAFF_OPTION;
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
		case UP:  //up
			fr--;
			if (fr < 0)
				fr = numOfList - 1;
			break;
		case DOWN:  //down
			fr++;
			if (fr > static_cast<int>(numOfList)-1)
				fr = 0;
			break;
		case ESC:  //Esc
			fc--;
			break;
		case ENTER:  //enter
			fc++;
			break;
		}

	}
}

int Menu::DisplayPvPMenu(std::shared_ptr<Character>& player1, std::shared_ptr<Character>& player2)
{
	SetConsoleSize(100, 30);
	FillConsole();
	using std::cout;
	using std::endl;
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));
	size_t NumOfCharacter(CharacterList.size());
	short pos_x(50 - NumOfCharacter * 3);//x軸偏中
	short pos_y(13);//y軸偏中
	char *point1("↓");
	char *point2("↑");
	int fc1(0);//player1
	int fc2(0);//player2
	const std::string P1_BAR[]
	{
		" .----------------. .----------------. ",
			"| .--------------. | .--------------. |",
			"| |   ______     | | |     __       | |",
			"| |  |_   __ \\   | | |    /  |      | |",
			"| |    | |__) |  | | |    `| |      | |",
			"| |    |  ___/   | | |     | |      | |",
			"| |   _| |_      | | |    _| |_     | |",
			"| |  |_____|     | | |   |_____|    | |",
			"| |              | | |              | |",
			"| '--------------' | '--------------' |",
			" '----------------' '----------------' "
	};
	const std::string P2_BAR[]
	{
		" .----------------.  .----------------. ",
			"| .--------------. || .--------------. |",
			"| |   ______     | || |    _____     | |",
			"| |  |_   __ \\   | || |   / ___ `.   | |",
			"| |    | |__) |  | || |  |_/___) |   | |",
			"| |    |  ___/   | || |   .'____.'   | |",
			"| |   _| |_      | || |  / /____     | |",
			"| |  |_____|     | || |  |_______|   | |",
			"| |              | || |              | |",
			"| '--------------' || '--------------' |",
			" '----------------'  '----------------' "
	};

	COORD chDisplay1{ 41, 2 }, chDisplay2{ 2, 18 };
	bool flag1(true), flag2(true), flag3(false), flag4(false);

	//display P1 BAR
	gotoXY(0, 0);
	for (int i = 0; i < 11; i++)
	{
		strDraw(P1_BAR[i], 12, hConsole);//紅色
		cout << '\n';
	}
	//display P2 BAR
	for (int i = 0, y = 16; i < 11; i++, y++)
	{
		gotoXY(60, y);
		strDraw(P2_BAR[i], 11, hConsole);//青色
		cout << '\n';
	}

	//display character appearance
	gotoXY(pos_x, pos_y);
	for (size_t index = 0; index < NumOfCharacter; index++)
		cout << CharacterList[index]->getAppearance() << "      ";

	while (true)
	{


		//player1
		gotoXY(pos_x, pos_y - 2);
		for (size_t index = 0; index < NumOfCharacter; index++)
		{
			if (fc1 == index)
			{
				strDraw(point1, 12, hConsole);
				cout << "        ";
			}
			else
				cout << "        ";
		}

		//player2
		gotoXY(pos_x, pos_y + 2);
		for (size_t index = 0; index < NumOfCharacter; index++)
		{
			if (fc2 == index)
			{
				strDraw(point2, 11, hConsole);
				cout << "        ";
			}
			else
				cout << "        ";
		}

		//15 :亮白色 9:藍色 8:灰色
		//display character detail1
		std::string space{ "             " };
		gotoXY(chDisplay1.X, chDisplay1.Y);
		strDraw("角色名稱: " + CharacterList[fc1]->getName() + space, 15, hConsole);

		gotoXY(chDisplay1.X, chDisplay1.Y + 2);
		strDraw("速度: ", 15, hConsole);
		for (int i = CharacterList[fc1]->getSpeed(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc1]->getSpeedLim() - CharacterList[fc1]->getSpeed(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		gotoXY(chDisplay1.X, chDisplay1.Y + 4);
		strDraw("水球: ", 15, hConsole);
		for (int i = CharacterList[fc1]->getAmount(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc1]->getAmountLim() - CharacterList[fc1]->getAmount(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		gotoXY(chDisplay1.X, chDisplay1.Y + 6);
		strDraw("水柱: ", 15, hConsole);
		for (int i = CharacterList[fc1]->getPower(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc1]->getPowerLim() - CharacterList[fc1]->getPower(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		//display character detail2
		gotoXY(chDisplay2.X, chDisplay2.Y);
		strDraw("角色名稱: " + CharacterList[fc2]->getName() + space, 15, hConsole);


		gotoXY(chDisplay2.X, chDisplay2.Y + 2);
		cout << "速度: ";
		for (int i = CharacterList[fc2]->getSpeed(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc2]->getSpeedLim() - CharacterList[fc2]->getSpeed(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		gotoXY(chDisplay2.X, chDisplay2.Y + 4);
		strDraw("水球: ", 15, hConsole);
		for (int i = CharacterList[fc2]->getAmount(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc2]->getAmountLim() - CharacterList[fc2]->getAmount(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		gotoXY(chDisplay2.X, chDisplay2.Y + 6);
		strDraw("水柱: ", 15, hConsole);
		for (int i = CharacterList[fc2]->getPower(); i; i--)
			strDraw("▅ ", 9, hConsole);
		for (int i = CharacterList[fc2]->getPowerLim() - CharacterList[fc2]->getPower(); i; i--)
			strDraw("▅ ", 8, hConsole);
		cout << space;

		//接收指令
		Sleep(50);

	wait:
		bool flag(false);
		//player1
		if (flag1)
		{
			if (GetAsyncKeyState(P1_LEFT))
			{
				flag = true;
				fc1--;
				if (fc1 < 0)
					fc1 = NumOfCharacter - 1;

			}
			else if (GetAsyncKeyState(P1_RIGHT))
			{
				flag = true;
				fc1++;
				if (fc1 == NumOfCharacter)
					fc1 = 0;
			}
			else if (GetAsyncKeyState(P1_ENTER))//'>'
			{
				*player1 = *CharacterList[fc1];
				flag = true;
				flag1 = false;
				flag3 = true;
			}
		}
		else if (GetAsyncKeyState(P1_CANCEL))//'?'
		{
			flag = true;
			flag1 = true;
			flag3 = true;
		}
		//player2
		if (flag2)
		{
			if (GetAsyncKeyState(P2_LEFT))
			{
				flag = true;
				fc2--;
				if (fc2 < 0)
					fc2 = NumOfCharacter - 1;
			}
			else if (GetAsyncKeyState(P2_RIGHT))
			{
				flag = true;
				fc2++;
				if (fc2 == NumOfCharacter)
					fc2 = 0;
			}
			else if (GetAsyncKeyState(P2_ENTER))//'Z'
			{
				*player2 = *CharacterList[fc2];
				flag = true;
				flag2 = false;
				flag4 = true;
			}
		}
		else if (GetAsyncKeyState(P2_CANCEL))//'X'
		{
			flag = true;
			flag2 = true;
			flag4 = true;
		}

		//display "已鎖定"
		if (flag4)
		{
			if (!flag2)
			{
				gotoXY(chDisplay2.X + 40, chDisplay2.Y);
				strDraw("已鎖定!", 11, hConsole);
			}
			else
			{
				gotoXY(chDisplay2.X + 40, chDisplay2.Y);
				cout << space;
			}
			flag4 = false;
		}
		if (flag3)
		{
			if (!flag1)
			{
				gotoXY(chDisplay1.X + 40, chDisplay1.Y);
				strDraw("已鎖定!", 12, hConsole);
			}
			else
			{
				gotoXY(chDisplay1.X + 40, chDisplay1.Y);
				cout << space;
			}
			flag3 = false;
		}

		if (!flag)
		{
			char temp;
			if (temp = _getch() == ESC)
				return 0;
			goto wait;
		}
		else if (!flag1&&!flag2)
		{
			gotoXY(2, pos_y);
			strDraw("Press Enter", 14, hConsole);
			gotoXY(88, pos_y);
			strDraw("Press Enter", 14, hConsole);
			char temp;
			while (true)
			{
				temp = _getch();
				if (temp == ENTER)
					return PVP_OPTION;
				else if (temp == '/' || temp == '?')
				{
					flag1 = true;
					flag3 = true;

					gotoXY(2, pos_y);
					cout << "           ";
					gotoXY(88, pos_y);
					cout << "           ";
					goto wait;
				}
				else if (temp == 'X' || temp == 'x')
				{
					flag2 = true;
					flag4 = true;

					gotoXY(2, pos_y);
					cout << "           ";
					gotoXY(88, pos_y);
					cout << "           ";
					goto wait;
				}
			}
		}
		else {

			gotoXY(2, pos_y);
			cout << "           ";
			gotoXY(88, pos_y);
			cout << "           ";
			Sleep(150);
		}
	}


}


int  Menu::DisplayPvCMenu()
{
	SetConsoleSize(100, 30);
	char chk;
	std::cout << "Coming sooooooooooon~~" << std::endl;
	if (chk = _getch())
		return 0;
}
int  Menu::DisplayHelp()//by Jheng, Bo An
{
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));

	const std::string Help_BAR[]
	{
		" _    _      _",
			"| |  | |    | |",
			"| |__| | ___| |_ __",
			"|  __  |/ _ \\ | '_ \\",
			"| |  | |  __/ | |_) |",
			"|_|  |_|\\___|_| .__/ ",
			"              | |    ",
			"              |_|   ",
	};

	for (int i = 0; i <= 7; i++)
	{
		strDraw(Help_BAR[i], 14, hConsole);//黃色
		std::cout << '\n';
	}

	std::cout << "\n";
	std::cout << "遊戲時間三分鐘，時間之內將另一個玩家炸死即勝利\n\n";

	std::cout << "確認鍵: <Enter>\n";
	std::cout << "返回建: <ESC>\n\n";

	std::cout << "player one:\n";
	std::cout << "角色控制鍵: 上<↑>，下<↓>，左<←>，右<→>\n";
	std::cout << "選擇(放置水球)鍵: <'>'>\n";
	std::cout << "取消鍵: <'?'>\n\n";

	std::cout << "player two:\n";
	std::cout << "角色控制鍵: 上<Y>，下<H>，左<G>，右<J>\n";
	std::cout << "選擇(放置水球)鍵: <Z>\n";
	std::cout << "取消鍵: <X>\n"<<std::endl;

	strDraw("注意: 一個障礙物是無法抵抗多顆水球的攻擊\n      水柱將會摧毀障礙物後繼續前進!", 12);

	std::string Item_BAR[]
	{
		"道具說明:",
			"",
			"Skate(︿):速度增加一格",
			"",
			"Bomb(B):水球增加一格",
			"",
			"PowerDrink(◆):水柱增加一格",
			"",
			"PowerStar(★):水柱滿格",
			"",
			"SpeedGhost(︽):速度滿格",
			"",
			"PoisonMushroom(∩):水柱減少兩格",
			"",
			"PoisonPill(〣):水球減少兩格",
			"",
			"Snails(﹀):速度減少兩格",
	};

	short ItemBar_x(50), ItemBar_y(9);

	for (int i = 0; i <= 16; i++)
	{
		gotoXY(ItemBar_x, ItemBar_y++);
		std::cout << Item_BAR[i];
		//std::cout << '\n';
	}


	char chk;
	while (true)
		if (chk = _getch() == 0x1b)
			return 0;
}
int  Menu::DisplayStaff()//by Jheng, Bo An
{
	HANDLE hConsole(GetStdHandle(STD_OUTPUT_HANDLE));

	const std::string Staff_BAR[]
	{
		"   _____ _         __  __ ",
			"  / ____| |       / _|/ _|",
			" | (___ | |_ __ _| |_| |_ ",
			"  \\___ \\| __/ _` |  _|  _|",
			"  ____) | || (_| | | | |  ",
			" |_____/ \\__\\__,_|_| |_|  ",
	};
	gotoXY(0, 0);
	for (int i = 0; i <= 5; i++)
	{
		strDraw(Staff_BAR[i], 13, hConsole);//紫色
		std::cout << '\n';
	}
	std::cout << "\n";

	const std::string Producer_BAR[]
	{
		"                      _                     ",
			"                     | |                    ",
			"  _ __  _ __ ___   __| |_   _  ___ ___ _ __ ",
			" | '_ \\| '__/ _ \\ / _` | | | |/ __/ _ \\ '__|   .",
			" | |_) | | | (_) | (_| | |_| | (_|  __/ |   ",
			" | .__/|_|  \\___/ \\__,_|\\__,_|\\___\\___|_|      .",
			" | |",
			" |_|",

	};

	for (int i = 0; i <= 7; i++)
	{
		strDraw(Producer_BAR[i], 12, hConsole);//紅色
		std::cout << '\n';
	}

	std::cout << "\n";


	const std::string Assistant_BAR[]
	{
		"	           _     _              _",
			"     /\\           (_)   | |            | |",
			"    /  \\   ___ ___ _ ___| |_ __ _ _ __ | |_  ",
			"   / /\\ \\ / __/ __| / __| __/ _` | '_ \\| __|  .",
			"  / ____ \\\\__ \\__ \\ \\__ \\ || (_| | | | | |_   ",
			" /_/    \\_\\___/___/_|___/\\__\\__,_|_| |_|\\__|  .",
	};

	for (int i = 0; i <= 5; i++)
	{
		strDraw(Assistant_BAR[i], 11, hConsole);//青色
		std::cout << '\n';
	}

	std::cout << "\n";

	gotoXY(50, 11);
	std::cout << "Hung, Chun Chung.(NaiveRed)";
	gotoXY(50, 20);
	std::cout << "Jheng, Bo An.";

	char chk;

	while (true)
		if (chk = _getch() == 0x1b)
			return 0;
}
void Menu::DisplayResult(int opt)
{
	FillConsole();
	const std::string Draw_BAR[] =
	{
		"    ____  ____  ___ _       __ ",
		"   / __ \\/ __ \\/   | |     / / ",
		"  / / / / /_/ / /| | | /| / /  ",
		" / /_/ / _, _/ ___ | |/ |/ /   ",
		"/_____/_/ |_/_/  |_|__/|__/    ",
	};

	const	std::string P1_BAR[] =
	{
		".-------.    ,---. ",
		"\\  _(`)_ \\  /_   | ",
		"| (_ o._)|    ,_ | ",
		"|  (_,_) /,-./  )| ",
		"|   '-.-' \\  '_ '`)",
		"|   |      > (_)  )",
		"|   |     (  .  .-'",
		"/   )      `-'`-'| ",
		"`---'        '---' ",
	};
	std::string P2_BAR[] =
	{
		".-------.   .`````-.  ",
		"\\  _(`)_ \\ /   ,-.  \\ ",
		"| (_ o._)|(___/  |   |",
		"|  (_,_) /      .'  / ",
		"|   '-.-'   _.-'_.-'  ",
		"|   |     _/_  .'     ",
		"|   |    ( ' )(__..--.",
		"/   )   (_{;}_)      |",
		"`---'    (_,_)-------'",
	};
	const std::string Win_BAR[] =
	{
		" __          _______ _   _ ",
		" \\ \\        / /_   _| \\ | |",
		"  \\ \\  /\\  / /  | | |  \\| |",
		"   \\ \\/  \\/ /   | | | . ` |",
		"    \\  /\\  /   _| |_| |\\  |",
		"     \\/  \\/   |_____|_| \\_|",
	};

	char chk;
	short WinBar_x(30), WinBar_y(16);
	short drawBar_x(30), drawBar_y(12);
	short P2Bar_x(33), P2Bar_y(6);
	short P1Bar_x(35), P1Bar_y(6);

	switch (opt)
	{
	case 0:
		for (int i = 0; i <= 4; i++)
		{
			gotoXY(drawBar_x, drawBar_y++);
			strDraw(Draw_BAR[i], 14);
			std::cout << '\n';
		}
		while (true)
			if (chk = _getch() == ENTER)
				return;
	case 1:

		for (int i = 0; i <= 8; i++)
		{
			gotoXY(P1Bar_x, P1Bar_y++);
			strDraw(P1_BAR[i], 14);
			std::cout << '\n';
		}


		for (int i = 0; i <= 5; i++)
		{
			gotoXY(WinBar_x, WinBar_y++);
			strDraw(Win_BAR[i], 14);
			std::cout << '\n';
		}
		std::cout << "\n";

		while (true)
			if (chk = _getch() == ENTER)
				return;
	case 2:


		for (int i = 0; i <= 8; i++)
		{
			gotoXY(P2Bar_x, P2Bar_y++);
			strDraw(P2_BAR[i], 14);
			std::cout << '\n';
		}



		for (int i = 0; i <= 5; i++)
		{
			gotoXY(WinBar_x, WinBar_y++);
			strDraw(Win_BAR[i], 14);
			std::cout << '\n';
		}
		std::cout << "\n";
		while (true)
			if (chk = _getch() == ENTER)
				return;
	}
}
bool Menu::selectMap(std::shared_ptr<Map>& map)
{
	SetConsoleSize(90, 30);
	FillConsole();

	size_t NumOfMap(mapList.size());
	int fc(0);
	char chk;

	const std::string MAP_BAR[] = {
		" ____    ____            _            _______  ",
		"|_   \\  /   _|          / \\          |_   __ \\  ",
		"  |   \\/   |           / _ \\           | |__) | ",
		"  | |\\  /| |          / ___ \\          |  ___/  ",
		" _| |_\\/_| |_       _/ /   \\ \\_       _| |_     ",
		"|_____||_____|     |____| |____|     |_____|    ",
	};


	short mapBar_x(20), mapBar_y(19);
	for (int i = 0; i <= 5; i++)
	{
		gotoXY(mapBar_x, mapBar_y++);
		strDraw(MAP_BAR[i], 15);
		std::cout << '\n';
	}

	while (true)
	{

		mapList[fc]->displayMap();
		gotoXY(63, 5);
		strDraw("▲", 15);
		gotoXY(61, 7);
		strDraw(mapList[fc]->getName(), 249);
		std::cout << "\t\t\t";
		gotoXY(63, 9);
		strDraw("▼", 15);

	loop:
		chk = _getch();
		if (chk == UP)
		{
			fc++;
			gotoXY(63, 5);
			strDraw("▲", 252);
			Sleep(50);
			if (fc >= NumOfMap)
				fc = 0;
		}
		else if (chk == DOWN)
		{
			fc--;
			gotoXY(63, 9);
			strDraw("▼", 252);
			Sleep(50);
			if (fc < 0)
				fc = NumOfMap - 1;
		}
		else if (chk == ENTER)
		{
			map = mapList[fc];
			return true;
		}
		else if (chk == ESC)
		{
			return false;
		}
		else goto loop;
	}
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
	int delay(15);//延遲時間
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
	ColorIndex = 8;
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
	ColorIndex = 8;
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

