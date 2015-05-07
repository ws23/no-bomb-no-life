#include"BombGame.h"
#include"controlCon.h"
#include<iostream>

BombGame::BombGame()
{
	SetConsoleSize(100, 30);
}

BombGame::~BombGame()
{
}
void BombGame::setMenu(std::unique_ptr<Menu>& _menu)
{
	menu = std::move(_menu);
}
int BombGame::DisplayMenu()
{
	if (menu)
		return (menu->DisplayList());
	else std::cout << "Loading Menu failed!" << std::endl;
}
int BombGame::OptionDetail(int opt)
{
	switch (opt)
	{
	case 1:return menu->DisplayPvPMenu(); 
	case 2:return menu->DisplayPvCMenu();
	case 3:return menu->DisplayConfig();
	case 4:return menu->DisplayStaff();
	}
}
