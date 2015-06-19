/*
File: Menu.h Menu.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed),some parts by Jheng, Bo An
Email: jason841201@gmail.com
*/
#pragma once
#include<string>
#include<windows.h>
#include<vector>
#include"Character.h"
#include"Map.h"
#include<memory>
#define PVP_OPTION 1
#define PVC_OPTION 2
#define HELP_OPTION 3
#define STAFF_OPTION 4
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4B
#define RIGHT 0x4D
#define ESC 0x1b
#define ENTER 0xD
#define P1_UP VK_UP
#define P1_DOWN VK_DOWN
#define P1_LEFT VK_LEFT
#define P1_RIGHT VK_RIGHT
#define P1_ENTER VK_OEM_PERIOD
#define P1_USE VK_OEM_2
#define P1_CANCEL P1_USE 
#define P2_UP 'Y'
#define P2_DOWN 'H'
#define P2_LEFT 'G'
#define P2_RIGHT 'J'
#define P2_ENTER 'Z'
#define P2_USE 'X'
#define P2_CANCEL P2_USE
#define NUM_OF_MAP 14

class Menu
{
public:
	Menu();
	~Menu(){}
	int DisplayList();//顯示主選單，回傳選擇1. PVP/2. PVC/3. Config/4. Staff

	int DisplayPvPMenu(std::shared_ptr<Character>&, std::shared_ptr<Character>&);//載入player1,player2
	int DisplayPvCMenu();
	int DisplayHelp();
	int DisplayStaff();
	void DisplayResult(int opt);
	bool selectMap(std::shared_ptr<Map>&);


private:
	static bool TimeSwitch;//選單圖案是否延遲 true=延遲 ,false=不延遲
	std::vector<std::shared_ptr<Map>> mapList;
	std::vector<std::shared_ptr<Character>> CharacterList;
	void strDraw(std::string str, int colorIndex, HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE));//輸出所設定的顏色字串
	void MakeTitleGraph(bool& TimeSwitch);//顯示選單圖案
	
};

