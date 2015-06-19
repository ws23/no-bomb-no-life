/*
File: Character.h Character.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include<string>
#include<memory>
#include"Item.h"
#include<windows.h>
enum STATUS{ DEAD, ALIVE, NEAR_DEATH };

struct Ability
{
	int power;     //waterball power
	int powerLim;  //limit of power
	int amount;	//waterball amount
	int amountLim; //limit of amount
	int speed;     //character speed
	int speedLim;  //limit of speed
};

class Character
{
public:
	Character(){}
	Character(std::string _appearance, std::string _name, Ability _ability) :status(ALIVE), appearance(_appearance), name(_name), ability(_ability){}
	Character(Character &);
	~Character();

	void UseItem();

	//set/get function
	void setStatus(STATUS _status){ status = _status; }
	STATUS getStatus(){ return status; }

	void setItem(std::shared_ptr<Item>& _item);

	//change 為增加或減少的量，非直接指定能力直
	void setPower(int change);
	int getPower();

	void setAmount(int change);
	int getAmount();

	void setSpeed(int change);
	int getSpeed();

	int getPowerLim(){ return ability.powerLim; }
	int getAmountLim(){ return ability.amountLim; }
	int getSpeedLim(){ return ability.speedLim; }

	std::string getAppearance(){ return appearance; }
	std::string getName(){ return name; }
	bool checkItem(){ return item ? true : false; }
	std::string getItemName()
	{
		if (item)return item->getName();
		else return NULL;
	}
	Character& operator =(Character& rside);

private:
	STATUS status;//DEAD, ALIVE, NEAR_DEATH 三種狀態
	std::string appearance;
	std::string name;
	Ability ability;
	std::shared_ptr<Item> item;

};

