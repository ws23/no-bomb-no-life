/*
File: PassiveItem.h PassiveItem.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once
#include "Item.h"

//被動道具
class passiveItem :public Item
{
public:
	passiveItem(std::string _name, std::string _appearance, int _powerSetting, int _amountSetting, int _speedSetting) :Item(_name, _appearance, _powerSetting, _amountSetting, _speedSetting){};
	~passiveItem(){}

	void BeUsed(Character&);
	int getType(){ return PASSIVE; }
};