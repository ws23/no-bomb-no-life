#include "Character.h"
#include<iostream>
Character::~Character()
{

}
Character::Character(Character &copy)
	:
	status(copy.status),
	appearance(copy.appearance),
	name(copy.name),
	ability(copy.ability)
{}
void Character::UseItem()
{
	if (item)
	{
		item->BeUsed(*this);
		item = nullptr;//shared_ptr(nullptr_t)
	}
}
void Character::setPower(int change)
{
	if (!change)
		return;
	ability.power = (ability.power + change) <= ability.powerLim ? (ability.power + change) : (ability.powerLim);
	if (ability.power <= 0)
		ability.power = 1;
}
 int Character::getPower()
{
	return ability.power;
}

void Character::setAmount(int change)
{
	if (!change)
		return;
	ability.amount = ((ability.amount + change) <= ability.amountLim )? (ability.amount + change ): (ability.amountLim);
 	if (ability.amount <= 0)
		ability.amount = 1;
}
int Character::getAmount()
{
	return ability.amount;
}

void Character::setSpeed(int change)
{
	if (!change)
		return;
	ability.speed =( (ability.speed + change) <= ability.speedLim) ?( ability.speed + change ): (ability.speedLim);
	if (ability.speed <= 0)
		ability.speed = 1;
}
 int Character::getSpeed()
{
	return ability.speed;
}

void Character::setItem(std::shared_ptr<Item>& _item)
{
	item = _item;
	if (item->getType() == PASSIVE)
		this->UseItem();

}
Character& Character::operator =(Character &rside)
{
	if (this == &rside)
		return *this;
	else
	{
		status = rside.status;
		appearance = rside.appearance;
		name = rside.name;
		ability = rside.ability;
	}
	return *this;
}