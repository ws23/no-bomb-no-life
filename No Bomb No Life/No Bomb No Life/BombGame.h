/*
File: BombGame.h BombGame.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include<memory>
#include"Menu.h"
#include"Character.h"
#include"Map.h"
#include"WaterBall.h"
#include"passiveItem.h"

class BombGame
{
public:
	BombGame();
	~BombGame();

	void startMenu();//選單流程，選取角色、地圖
	void startGame();
	void showResult();
	void gameTimeCounter();
	
private:
	std::unique_ptr<Menu> menu;
	std::shared_ptr<Character> player1;
	std::shared_ptr<Character> player2;
	std::shared_ptr<Map> map;
	std::shared_ptr<WaterBall> allBall;
	std::vector<std::shared_ptr<Item>> itemList;
	std::string time_str;
	int itemTable[20][18];
	void produceItem();
};

