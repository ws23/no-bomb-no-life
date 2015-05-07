/*
File: Menu.h Menu.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include<string>
#include<windows.h>

class Menu
{
public:
	Menu(){}
	~Menu(){}
	int DisplayList();
	int DisplayPvPMenu();
	int DisplayPvCMenu();
	int DisplayConfig();
	int DisplayStaff();

private:
	static bool TimeSwitch;
	void strDraw(std::string str, int colorIndex, HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE));
	void MakeTitleGraph(bool& TimeSwitch);

};

