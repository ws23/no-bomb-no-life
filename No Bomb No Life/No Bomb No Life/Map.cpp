#include "Map.h"
#include<fstream>
#include<iostream>
#include"controlCon.h"


Map::Map() :hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
	element = new MapElement *[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; i++)
		element[i] = new MapElement[MAP_HEIGHT];
}
Map::Map(Map &map) :hConsole(map.hConsole), name(map.name), normalColor(map.normalColor)
{
	element = new MapElement *[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; i++)
		element[i] = new MapElement[MAP_HEIGHT];

	for (int x = 0; x < MAP_WIDTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			element[x][y] = map.element[x][y];

}
Map::Map(std::string FileName) :hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
	std::fstream MapFile(FileName, std::ios::in);

	int numOfType;

	if (MapFile.good())
	{
		element = new MapElement *[MAP_WIDTH];
		for (int i = 0; i < MAP_WIDTH; i++)
			element[i] = new MapElement[MAP_HEIGHT];

		MapFile >> name;
		MapFile >> numOfType;

		int *colorIndex = new int[numOfType];

		for (int i = 0; i < numOfType; i++)
			MapFile >> colorIndex[i];

		for (int y = 0; y < MAP_HEIGHT; y++)
			for (int x = 0; x < MAP_WIDTH; x++)
				MapFile >> element[x][y].id;

		for (int x = 0; x < MAP_WIDTH; x++)
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
			element[x][y].pos.X = x ;
			element[x][y].pos.Y = y;
			element[x][y].colorIndex = colorIndex[element[x][y].id];
			switch (element[x][y].id)
			{
			case 0:element[x][y].elimination = NORMAL; break;
			case 1:element[x][y].elimination = NON_ELIMINATION; break;
			default:element[x][y].elimination = ELIMINATION; break;
			}
			}

		normalColor = colorIndex[0];

		MapFile.close();
		delete[] colorIndex;
	}


}
Map::~Map()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		delete[] element[i];

	delete[] element;
}
Map& Map::operator =(Map& rside)
{
	if (this == &rside)
		return *this;
	else{
		hConsole = rside.hConsole;
		name = rside.name;
		for (int x = 0; x < MAP_WIDTH; x++)
			for (int y = 0; y < MAP_HEIGHT; y++)
				element[x][y] = rside.element[x][y];
	}
	return *this;
}
void Map::displayMap()
{
	if (!name.empty())
		for (int x = 0; x < MAP_WIDTH; x++)
			for (int y = 0; y < MAP_HEIGHT; y++)
				displayElement(x,y);

}
void Map::displayElement(int x,int y)
{
	gotoXY(element[x][y].pos.X*2, element[x][y].pos.Y);
	SetConsoleTextAttribute(hConsole, element[x][y].colorIndex);
	std::cout << "¡½";
	SetConsoleTextAttribute(hConsole, 7);//back to the default color
}
void Map::setEleStatusToNormal(int x, int y)
{
	element[x][y].elimination = NORMAL;
	element[x][y].colorIndex = normalColor;
	element[x][y].id = 0;
}
