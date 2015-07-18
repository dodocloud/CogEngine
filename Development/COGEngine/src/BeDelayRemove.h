#pragma once

#include "GBehavior.h"
#include "BeTranslateAnim.h"
#include "Enums.h"
#include "GMsg.h"

/**
* Behavior that removes object with delay
*/
class BeDelayRemove : public GBehavior{
private:
	int millis;
	int actual;

public:
	BeDelayRemove(int millis) : GBehavior(ElemType::MODEL){
		this->millis = millis;
		this->actual = 0;
	}

	virtual void Update(const uint64 delta, const uint64 absolute){
		actual += delta;

		if (actual > millis){
			owner->GetParent()->RemoveChild(owner,false,true);
		}
	}
};
