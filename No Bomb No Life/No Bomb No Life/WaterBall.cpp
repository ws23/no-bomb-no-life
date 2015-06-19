#include "WaterBall.h"
#include"controlCon.h"

WaterBall::WaterBall() :time(4)
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			ballTable[i][j] = Ball{ 0, 0, NO_BOMB };
}

WaterBall::~WaterBall()
{
}
void WaterBall::freshTable()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			if (ballTable[i][j].time == BOMBING)
		freshRule({ i, j }, ballTable[i][j].range);
			
}
void WaterBall::freshRule(COORD pos, int range)
{
	ballTable[pos.X][pos.Y].time = WATERING;
	//向右
	for (int r = 1; r <= ballTable[pos.X][pos.Y].range; r++)
	{
		if (pos.X + r < MAP_WIDTH)
		{
			ELE_STATUS temp(map->getEleStatus(pos.X + r, pos.Y));
			if (temp == NORMAL)
			{
				if (ballTable[pos.X + r][pos.Y].time >= BOMBING)
					freshRule({ pos.X + r, pos.Y }, ballTable[pos.X + r][pos.Y].range);
				ballTable[pos.X + r][pos.Y].time = WATERING;
			}
			else if (temp == ELIMINATION)
			{
				map->setEleStatusToNormal(pos.X + r, pos.Y);
				ballTable[pos.X + r][pos.Y].time = WATERING;
				break;
			}
			else if (temp == NON_ELIMINATION)
				break;
		}
	}
	//向左
	for (int r = 1; r <= ballTable[pos.X][pos.Y].range; r++)
	{
		if (pos.X - r >= 0)
		{
			ELE_STATUS temp(map->getEleStatus(pos.X - r, pos.Y));
			if (temp == NORMAL)
			{
				if (ballTable[pos.X - r][pos.Y].time >= BOMBING)
					freshRule({ pos.X - r, pos.Y }, ballTable[pos.X - r][pos.Y].range);
				ballTable[pos.X - r][pos.Y].time = WATERING;
			}
			else if (temp == ELIMINATION)
			{
				map->setEleStatusToNormal(pos.X - r, pos.Y);
				ballTable[pos.X - r][pos.Y].time = WATERING;
				break;
			}
			else if (temp == NON_ELIMINATION)
				break;
		}
	}
	//向上
	for (int r = 1; r <= ballTable[pos.X][pos.Y].range; r++)
	{
		if (pos.Y - r >= 0)
		{
			ELE_STATUS temp(map->getEleStatus(pos.X, pos.Y - r));
			if (temp == NORMAL)
			{
				if (ballTable[pos.X][pos.Y - r].time >= BOMBING)
					freshRule({ pos.X, pos.Y - r }, ballTable[pos.X][pos.Y - r].range);
				ballTable[pos.X][pos.Y - r].time = WATERING;
			}
			else if (temp == ELIMINATION)
			{
				map->setEleStatusToNormal(pos.X, pos.Y - r);
				ballTable[pos.X][pos.Y - r].time = WATERING;
				break;
			}
			else if (temp == NON_ELIMINATION)
				break;
		}
	}
	//向下
	for (int r = 1; r <= ballTable[pos.X][pos.Y].range; r++)
	{
		if (pos.Y + r < MAP_HEIGHT)
		{
			ELE_STATUS temp(map->getEleStatus(pos.X, pos.Y + r));
			if (temp == NORMAL)
			{
				if (ballTable[pos.X][pos.Y + r].time >= BOMBING)
					freshRule({ pos.X, pos.Y + r }, ballTable[pos.X][pos.Y + r].range);
				ballTable[pos.X][pos.Y + r].time = WATERING;
			}
			else if (temp == ELIMINATION)
			{
				map->setEleStatusToNormal(pos.X, pos.Y + r);
				ballTable[pos.X][pos.Y + r].time = WATERING;
				break;
			}
			else if (temp == NON_ELIMINATION)
				break;
		}
	}

}

void WaterBall::addBall(COORD pos, int id, int range)
{
	if (map == NULL)
		return;
	ballTable[pos.X][pos.Y] = Ball{ id, range, time };
}
void WaterBall::allTimeSubOne()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
		if (ballTable[i][j].time >= 0)
			ballTable[i][j].time--;
		else if (ballTable[i][j].time == WATERING)
			ballTable[i][j].time = NO_BOMB;
		}
}
int WaterBall::getNumOfBallById(int id)
{
	int count(0);
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			if (ballTable[i][j].id == id&&ballTable[i][j].time > 0)
				count++;

	return count;


}
