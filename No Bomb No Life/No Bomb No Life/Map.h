/*
File: Map.h  Map.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include<windows.h>
#include<string>
#define MAP_WIDTH 20
#define MAP_HEIGHT 18

enum ELE_STATUS{
	NORMAL,NON_ELIMINATION, ELIMINATION//normal為可行走的路
};
struct MapElement
{
	int id;//編號0為可行走的路 1的為不可消除之障礙物 其餘都為可消除之障礙物
	COORD pos;
	ELE_STATUS elimination;
	unsigned short colorIndex;

};
class Map

{
public:
	Map();
	Map(Map &map);
	Map(std::string FileName);
	~Map();
	std::string getName(){ return name; }
	
	int getEleColor(int x, int y){ return element[x][y].colorIndex; }
	int getEleId(int x, int y){ return element[x][y].id; }
	ELE_STATUS getEleStatus(int x, int y){ return element[x][y].elimination; }
	void setEleStatusToNormal(int x,int y);


	void displayElement(int,int);
	void displayMap();
	Map& operator =(Map& rside);

private:
	HANDLE hConsole;
	std::string name;
	int normalColor;
	MapElement **element;
	
	
};

