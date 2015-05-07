/*
File: BombGame.h BombGame.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include"Menu.h"
#include<memory>

class BombGame
{
public:
	BombGame();
	~BombGame();

	void setMenu(std::unique_ptr<Menu>&);
	int DisplayMenu();
	int OptionDetail(int opt);
	
	
private:
	std::unique_ptr<Menu> menu;

};

