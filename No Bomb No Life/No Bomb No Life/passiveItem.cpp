#include "passiveItem.h"
#include "Character.h"

void passiveItem::BeUsed(Character& target)
{
	target.setPower(this->getPower());
	target.setAmount(this->getAmount());
	target.setSpeed(this->getSpeed());
}
