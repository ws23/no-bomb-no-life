/*
File: Item.h Item.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include<string>
#define PASSIVE 0
#define ACTIVE 1
class Character;

class Item
{
public:
	Item(){}
	Item(std::string _name) :name(_name){}
	Item(std::string _name, std::string _appearance, int _power, int _amount, int _speed) :name(_name), appearance(_appearance), power(_power), amount(_amount), speed(_speed){};
	virtual ~Item()=0;

	virtual void BeUsed(Character&) = 0;

	//get function
	std::string getName(){ return name; }
	std::string getAppearance(){ return appearance; }
	virtual int getType() = 0;
	//以下數值為變動的量，非直接指定值
	int getPower(){ return power; } 
	int getAmount(){ return amount; }
	int getSpeed(){ return speed; }

private:
	const std::string name;
	const std::string appearance;
	//以下數值為變動的量，非直接指定值
	int power;
	int amount;
	int speed;
};


