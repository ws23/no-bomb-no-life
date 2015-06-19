/*
File: WaterBall.h WaterBall.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include"Map.h"
#include<memory>
#define BOMBING 0
#define WATERING -2
#define NO_BOMB -1
 

struct Ball
{
	int id;
	int range;
	int time;
};
class WaterBall
{
public:
	WaterBall();
	void setMap(std::shared_ptr<Map>& _map){ map = _map; }
	void addBall(COORD,  int id,int range);
	
	void allTimeSubOne();
	void freshTable();
	void freshRule(COORD, int range);
	
	Ball getTable(COORD pos){ return ballTable[pos.X][pos.Y]; }
	int getNumOfBallById(int id);


	~WaterBall();
private:
	int time;//引爆的時間
	std::shared_ptr<Map> map;
    Ball ballTable[MAP_WIDTH][MAP_HEIGHT];
};

