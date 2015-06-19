#include"BombGame.h"
#include"controlCon.h"
#include"passiveItem.h"
#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<cstdio>
#include<thread>
#include<chrono>
#include<time.h>
#include<cstdlib>
#define FOR_SPEED(x) ((10 - (x)) * 10 + 80 )
BombGame::BombGame() :menu(new Menu), player1(new Character), player2(new Character), map(new Map), time_str("300"), allBall(new WaterBall)
{


}


BombGame::~BombGame()
{
}
void BombGame::startMenu()
{
	int opt(0);

	while (!opt)//0就繼續顯示主選單
	{
		if (menu)
			opt = menu->DisplayList();
		else
		{
			std::cout << "Loading Menu failed!" << std::endl;
			break;
		}
	label:
		switch (opt)
		{
		case 1:opt = menu->DisplayPvPMenu(player1, player2); break;//return 1
		case 2:opt = menu->DisplayPvCMenu(); break;//return 2
		case 3:opt = menu->DisplayHelp(); break;//return 0
		case 4:opt = menu->DisplayStaff(); break;//return 0
		}
		Sleep(100);

		if (opt == PVP_OPTION)
		{
			if (menu->selectMap(map))
				return;
			opt = 1;
			goto label;
			
		}
		else if (opt == PVC_OPTION)
		{
			//not finish
		}
	}



}
void BombGame::startGame()
{
	FillConsole();
	srand(time(NULL));
	produceItem();

	inline void timeThreadF(BombGame&);
	inline void draw(std::string, int);

	gotoXY(40, 14);
	draw("Loading...", 15);

	//charactersetting
	COORD player1_pos;
	COORD player2_pos;

	do
	{
		player1_pos.X = rand() % 20;
		player1_pos.Y = rand() % 18;
	} while (map->getEleStatus(player1_pos.X, player1_pos.Y) != NORMAL);

	do
	{
		player2_pos.X = rand() % 20;
		player2_pos.Y = rand() % 18;

	} while (map->getEleStatus(player2_pos.X, player2_pos.Y) != NORMAL);

	int p1_color(map->getEleColor(player1_pos.X, player1_pos.Y) * 16 + 12);
	int p2_color(map->getEleColor(player2_pos.X, player2_pos.Y) * 16 + 9);
	int delay1(FOR_SPEED(player1->getSpeed())), delay2(FOR_SPEED(player2->getSpeed()));
	int key_flag1, key_flag2;

	//for the player control
	inline void player1Ctrl(COORD* pos, int* delay, int *flag, COORD* ball, bool *cont);
	inline void player2Ctrl(COORD* pos, int* delay, int *flag, COORD* ball, bool *cont);

	//for time LCD 
	inline void dash(bool *LCD, int lcd, int size);
	inline void ver(bool *LCD, int lcd1, int lcd2, int size);
	bool LCD[10][7] = {
			{ 1, 1, 1, 0, 1, 1, 1 },
			{ 0, 0, 1, 0, 0, 1, 0 },
			{ 1, 0, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 1, 0, 1, 1 },
			{ 0, 1, 1, 1, 0, 1, 0 },
			{ 1, 1, 0, 1, 0, 1, 1 },
			{ 1, 1, 0, 1, 1, 1, 1 },
			{ 1, 0, 1, 0, 0, 1, 0 },
			{ 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 0, 1, 1 }
	};
	int lcd_size(3);
	int length(time_str.size());

	FillConsole();
	map->displayMap();
	allBall->setMap(map);

	std::string old_time_str("300");
	bool cont(true), first(true);
	COORD old_pos1(player1_pos), old_pos2(player2_pos);
	COORD ball1{ -1, -1 }, ball2{ -1, -1 };
	int ballColor(map->getEleColor(player1_pos.X, player1_pos.Y) * 16 + 9);
	int waterColor(map->getEleColor(player1_pos.X, player1_pos.Y) * 16 + 11);
	bool itemCheck[MAP_WIDTH][MAP_HEIGHT] = {};
	std::string tempTime("000");
	//thread
	std::thread timeThread(timeThreadF, std::ref(*this));
	std::thread p1Thread(player1Ctrl, &player1_pos, &delay1, &key_flag1, &ball1, &cont);
	std::thread p2Thread(player2Ctrl, &player2_pos, &delay2, &key_flag2, &ball2, &cont);

	while (time_str != "000"&&player1->getStatus() != DEAD&&player2->getStatus() != DEAD)
	{
		int i;

#pragma region display

		if ((old_pos1.X != player1_pos.X) || (old_pos1.Y != player1_pos.Y) || first)
		{
			if (first)
				player1_pos = old_pos1;
			if ((map->getEleStatus(player1_pos.X, player1_pos.Y) == NORMAL&&allBall->getTable({ player1_pos.X, player1_pos.Y }).time <= 0))
			{

				gotoXY(player1_pos.X * 2, player1_pos.Y);
				draw(player1->getAppearance(), p1_color);
				switch (key_flag1)
				{
				case 0:if (allBall->getTable({ player1_pos.X, player1_pos.Y + 1 }).time < 0)map->displayElement(player1_pos.X, player1_pos.Y + 1); break;
				case 1:if (allBall->getTable({ player1_pos.X, player1_pos.Y - 1 }).time < 0)map->displayElement(player1_pos.X, player1_pos.Y - 1); break;
				case 2:if (allBall->getTable({ player1_pos.X - 1, player1_pos.Y }).time < 0)map->displayElement(player1_pos.X - 1, player1_pos.Y); break;
				case 3:if (allBall->getTable({ player1_pos.X + 1, player1_pos.Y }).time < 0)map->displayElement(player1_pos.X + 1, player1_pos.Y); break;
				}
				if ((player2_pos.X == old_pos1.X) && (player2_pos.Y == old_pos1.Y))
				{
					if (allBall->getTable(player2_pos).time <= 0)
					{
						gotoXY(player2_pos.X * 2, player2_pos.Y);
						draw(player2->getAppearance(), p2_color);
					}
				}
				old_pos1.X = player1_pos.X;
				old_pos1.Y = player1_pos.Y;

			}
			else
			{
				player1_pos.X = old_pos1.X;
				player1_pos.Y = old_pos1.Y;
			}


		}

		if ((old_pos2.X != player2_pos.X) || (old_pos2.Y != player2_pos.Y) || first)
		{
			if (first)
				player2_pos = old_pos2;
			if ((map->getEleStatus(player2_pos.X, player2_pos.Y) == NORMAL&&allBall->getTable({ player2_pos.X, player2_pos.Y }).time <= 0))
			{
				gotoXY(player2_pos.X * 2, player2_pos.Y);
				draw(player2->getAppearance(), p2_color);

				switch (key_flag2)
				{
				case 0:if (allBall->getTable({ player2_pos.X, player2_pos.Y + 1 }).time < 0)map->displayElement(player2_pos.X, player2_pos.Y + 1); break;
				case 1:if (allBall->getTable({ player2_pos.X, player2_pos.Y - 1 }).time < 0)map->displayElement(player2_pos.X, player2_pos.Y - 1); break;
				case 2:if (allBall->getTable({ player2_pos.X - 1, player2_pos.Y }).time < 0)map->displayElement(player2_pos.X - 1, player2_pos.Y); break;
				case 3:if (allBall->getTable({ player2_pos.X + 1, player2_pos.Y }).time < 0)map->displayElement(player2_pos.X + 1, player2_pos.Y); break;
				}

				if ((player1_pos.X == old_pos2.X) && (player1_pos.Y == old_pos2.Y))
				{
					if (allBall->getTable(player1_pos).time <= 0)
					{
						gotoXY(player1_pos.X * 2, player1_pos.Y);
						draw(player1->getAppearance(), p1_color);
					}
				}
				old_pos2.X = player2_pos.X;
				old_pos2.Y = player2_pos.Y;

			}
			else
			{
				player2_pos.X = old_pos2.X;
				player2_pos.Y = old_pos2.Y;
			}

		}
		if (itemCheck[player1_pos.X][player1_pos.Y])
		{
			player1->setItem(itemList[itemTable[player1_pos.X][player1_pos.Y]]);
			itemCheck[player1_pos.X][player1_pos.Y] = false;
			itemTable[player1_pos.X][player1_pos.Y] = -1;
		}
		if (itemCheck[player2_pos.X][player2_pos.Y])
		{
			player2->setItem(itemList[itemTable[player2_pos.X][player2_pos.Y]]);
			itemCheck[player2_pos.X][player2_pos.Y] = false;
			itemTable[player2_pos.X][player2_pos.Y] = -1;
		}
		first = false;

#pragma endregion element and player display

#pragma region time

		/*
		-  0
		| | 1 2
		-  3
		| | 4 5
		-  6

		display LCD
		*/

		COORD pos{ 33, 20 };

		if (time_str != old_time_str)
		{

			old_time_str = time_str;

			//LCD
			gotoXY(pos.X, pos.Y);
			for (i = 0; i < length; i++)
			{
				if (i == 1)
					printf("     ");
				else if (i)
					printf("  ");
				dash(LCD[time_str[i] - '0'], 0, lcd_size);
			}


			gotoXY(pos.X, ++pos.Y);
			int j;

			for (j = 0; j < lcd_size; j++)
			{
				for (i = 0; i < length; i++)
				{
					if (i == 1)
						printf("     ");
					else if (i)
						printf("  ");
					ver(LCD[time_str[i] - '0'], 1, 2, lcd_size);
				}
				gotoXY(pos.X, ++pos.Y);
			}

			for (i = 0; i < length; i++)
			{
				if (i == 1)
					printf("     ");
				else if (i)
					printf("  ");
				dash(LCD[time_str[i] - '0'], 3, lcd_size);
			}

			gotoXY(pos.X, ++pos.Y);

			for (j = 0; j < lcd_size; j++)
			{
				for (i = 0; i < length; i++)
				{
					if (i == 1)
						printf("     ");
					else if (i)
						printf("  ");
					ver(LCD[time_str[i] - '0'], 4, 5, lcd_size);
				}
				gotoXY(pos.X, ++pos.Y);
			}

			for (i = 0; i < length; i++)
			{
				if (i == 1)
					printf("     ");
				else if (i)
					printf("  ");
				dash(LCD[time_str[i] - '0'], 6, lcd_size);
			}

			/*  水球 道具 */


			for (int i = 0; i < MAP_WIDTH; i++)
				for (int j = 0; j < MAP_HEIGHT; j++)
					if (allBall->getTable({ i, j }).time == WATERING)
					{
				if (itemTable[i][j] != -1 && !itemCheck[i][j])
				{
					gotoXY(i * 2, j);
					draw(itemList[itemTable[i][j]]->getAppearance(), map->getEleColor(i, j) * 16);
					itemCheck[i][j] = true;
				}
				else
				{
					map->displayElement(i, j);
					itemCheck[i][j] = false;
					itemTable[i][j] = -1;
				}
					}
			allBall->allTimeSubOne();
			allBall->freshTable();


#pragma region UI

			std::string p1Ability_BAR[] =
			{
				"P1:",
				"",
				"速度:",
				"",
				"水球:",
				"",
				"水柱:"

			};

			short p1AbilityBar_x(42), p1AbilityBar_y(1);

			gotoXY(p1AbilityBar_x, p1AbilityBar_y++);
			draw(p1Ability_BAR[0], 12);
			for (int i = 1; i < 7; i++)
			{
				gotoXY(p1AbilityBar_x, p1AbilityBar_y++);
				std::cout << p1Ability_BAR[i];
				std::cout << '\n';
			}



			std::string p2Ability_BAR[] =
			{
				"P2:",
				"",
				"速度:",
				"",
				"水球:",
				"",
				"水柱:"

			};

			short p2AbilityBar_x(42), p2AbilityBar_y(10);

			gotoXY(p2AbilityBar_x, p2AbilityBar_y++);
			draw(p2Ability_BAR[0], 11);

			for (int i = 1; i < 7; i++)
			{
				gotoXY(p2AbilityBar_x, p2AbilityBar_y++);
				std::cout << p2Ability_BAR[i];
				std::cout << '\n';
			}

			gotoXY(p1AbilityBar_x + 7, 1);
			draw(player1->getName(), 12);
			gotoXY(p1AbilityBar_x + 7, 3);
			for (int i = player1->getSpeed(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";
			gotoXY(p1AbilityBar_x + 7, 5);
			for (int i = player1->getAmount(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";
			gotoXY(p1AbilityBar_x + 7, 7);
			for (int i = player1->getPower(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";

			gotoXY(p2AbilityBar_x + 7, 10);
			draw(player2->getName(), 11);
			gotoXY(p2AbilityBar_x + 7, 12);
			for (int i = player2->getSpeed(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";
			gotoXY(p2AbilityBar_x + 7, 14);
			for (int i = player2->getAmount(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";
			gotoXY(p2AbilityBar_x + 7, 16);
			for (int i = player2->getPower(); i; i--)
				draw("▅ ", 9);
			std::cout << +"         ";




#pragma endregion UI
		}
#pragma endregion depend on time 

#pragma region ball
		//add ball 
		if (ball1.X != -1)
		{
			if (allBall->getNumOfBallById(1) < player1->getAmount() && allBall->getTable(ball1).time == NO_BOMB)
			{
				allBall->addBall(ball1, 1, player1->getPower());
				gotoXY(ball1.X * 2, ball1.Y);
				draw("●", ballColor);
			}
			ball1 = { -1, -1 };
		}
		if (ball2.X != -1)
		{
			if (allBall->getNumOfBallById(2) < player2->getAmount() && allBall->getTable(ball2).time == NO_BOMB)
			{
				allBall->addBall(ball2, 2, player2->getPower());
				gotoXY(ball2.X * 2, ball2.Y);
				draw("●", ballColor);
			}
			ball2 = { -1, -1 };
		}


		for (int i = 0; i < MAP_WIDTH; i++)
			for (int j = 0; j < MAP_HEIGHT; j++)
			{
			gotoXY(i * 2, j);
			if (allBall->getTable({ i, j }).time == WATERING)
			{
				draw("■", waterColor);
				if (player1_pos.X == i&&player1_pos.Y == j&&player2_pos.X == i&&player2_pos.Y == j)
				{
					player1->setStatus(DEAD);
					player2->setStatus(DEAD);

				}
				else if (player1_pos.X == i&&player1_pos.Y == j)
				{
					player1->setStatus(DEAD);

				}
				else if (player2_pos.X == i&&player2_pos.Y == j)
				{
					player2->setStatus(DEAD);

				}
			}
			}



#pragma endregion ball display and check winner
	}
	time_str = "000";
	cont = false;
	p1Thread.join();
	p2Thread.join();
	timeThread.join();

}
void BombGame::gameTimeCounter()
{

	int minute(2), sec(59);

	while ((sec >= 0 || minute >= 0) && time_str != "000")
	{
		std::string sec_str(sec < 10 ? '0' + std::to_string(sec) : std::to_string(sec));
		time_str = (std::to_string(minute) + sec_str);

		if (!sec&&!minute)
			break;
		sec = sec ? (sec - 1) : (minute-- ? 59 : 0);

		std::chrono::duration<int, std::milli> per(999);
		std::this_thread::sleep_for(per);
		//Sleep(995);
	}

}
void BombGame::showResult()
{
	int result;
	if (player1->getStatus() == player2->getStatus())
		result = 0;
	else if (player1->getStatus() == DEAD)
		result = 2;
	else if (player2->getStatus() == DEAD)
		result = 1;
	menu->DisplayResult(result);
}

void BombGame::produceItem()
{
	//載入道具
	std::vector<std::string>passiveItemName{ "Skate", "Bomb", "PowerDrink", "PowerStar", "SpeedGhost", "PoisonMushroom", "PoisonPill", "Snails" };
	std::vector<std::string> passiveTtemAppearance{ "︿", "B", "◆", "★", "︽", "∩", "〣", "﹀" };

	size_t NumOfPassiveItem(passiveItemName.size());

	int PassiveItemEffectOfPower[]{0, 0, 1, 10, 0, -2, 0, 0};
	int PassiveItemEffectOfBomb[]{0, 1, 0, 0, 0, 0, -2, 0};
	int PassiveItemEffectOfSpeed[]{1, 0, 0, 0, 10, 0, 0, -2};

	for (size_t i = 0; i < NumOfPassiveItem; i++)
	{
		itemList.push_back(std::make_shared<passiveItem>(passiveItemName[i], passiveTtemAppearance[i], PassiveItemEffectOfPower[i], PassiveItemEffectOfBomb[i], PassiveItemEffectOfSpeed[i]));
	}


	//Table
	int numOfItem(itemList.size());
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
		int type;
		type = -1;
		if (map->getEleStatus(i, j) == ELIMINATION)
		{
			if (!(rand() % 4))
				type = rand() % 3;
			else if (!(rand() % 3))
				type = rand() % numOfItem;
		}
		itemTable[i][j] = type;
		}

}
//inline function
void timeThreadF(BombGame& game)
{
	game.gameTimeCounter();
}
void draw(std::string str, int colorIndex)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorIndex);
	std::cout << str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//back to the default color
}
void dash(bool *LCD, int lcd, int size)
{

	int i;

	putchar(' ');
	if (LCD[lcd])
		for (i = 0; i < size; i++)
			putchar('-');
	else
		for (i = 0; i < size; i++)
			putchar(' ');

	putchar(' ');

}
void ver(bool *LCD, int lcd1, int lcd2, int size)
{

	int i;

	if (LCD[lcd1])
		putchar('|');
	else putchar(' ');

	for (i = 0; i < size; i++)
		putchar(' ');

	if (LCD[lcd2])
		putchar('|');
	else putchar(' ');
}
void player1Ctrl(COORD* pos, int* delay, int* flag, COORD* ball, bool *cont)
{
	while (*cont)
	{
		if (GetAsyncKeyState(P1_ENTER))
		{
			ball->X = pos->X;
			ball->Y = pos->Y;
		}
		else if (GetAsyncKeyState(P1_UP))
		{
			if (((*pos).Y - 1) >= 0)
			{
				(*pos).Y--;
			}
			else continue;
			*flag = 0;
		}
		else if (GetAsyncKeyState(P1_DOWN))
		{

			if (((*pos).Y + 1) < MAP_HEIGHT)
			{
				(*pos).Y++;
			}
			else continue;
			*flag = 1;
		}
		else if (GetAsyncKeyState(P1_RIGHT))
		{

			if (((*pos).X + 1) < MAP_WIDTH)
			{
				(*pos).X++;
			}
			else continue;
			*flag = 2;

		}
		else if (GetAsyncKeyState(P1_LEFT))
		{

			if (((*pos).X - 1) >= 0)
			{
				(*pos).X--;
			}
			else continue;
			*flag = 3;
		}

		std::chrono::duration<int, std::milli> per(*delay);
		std::this_thread::sleep_for(per);
	}

}
void player2Ctrl(COORD* pos, int* delay, int *flag, COORD* ball, bool *cont)
{
	while (*cont)
	{
		if (GetAsyncKeyState(P2_ENTER))
		{
			ball->X = pos->X;
			ball->Y = pos->Y;
		}
		else if (GetAsyncKeyState(P2_UP))
		{
			if (((*pos).Y - 1) >= 0)
			{
				(*pos).Y--;
			}
			else continue;
			*flag = 0;
		}
		else if (GetAsyncKeyState(P2_DOWN))
		{
			if (((*pos).Y + 1) < MAP_HEIGHT)
			{
				(*pos).Y++;
			}
			else continue;
			*flag = 1;
		}
		else if (GetAsyncKeyState(P2_RIGHT))
		{

			if (((*pos).X + 1) < MAP_WIDTH)
			{
				(*pos).X++;
			}
			else continue;
			*flag = 2;
		}
		else if (GetAsyncKeyState(P2_LEFT))
		{

			if (((*pos).X - 1) >= 0)
			{
				(*pos).X--;
			}
			else continue;
			*flag = 3;
		}

		std::chrono::duration<int, std::milli> per(*delay);
		std::this_thread::sleep_for(per);
	}

}
