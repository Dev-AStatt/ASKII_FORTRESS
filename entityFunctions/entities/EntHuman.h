#pragma once
#include "Ent.h"

class EntHuman : public Ent {
private:


public:
    EntHuman() {}
	EntHuman(olc::vi2d& PS, olc::PixelGameEngine* p, olc::vi2d& posXY, int posZ, std::string n) {
		constructEntBasics(PS,p);

		decalSourcePos		= { 0,4 };
		entPositionXY		= posXY;
		entStepZPosition	= posZ;
		viewDistance		= 3;
		thirst				= 100;
		thirstBurnRate		= 2;
		hunger				= 100;
		hungerBurnRate		= 1;
		tint				= olc::WHITE;
		sEntName			= n;
		UpdatePosInView();
    }

	virtual bool updateSelf(int tick) override {
		if (tick % 10 == 0 && alive) {
			assessPriorities();
			if(vPriorities.size()>0) {
				//run pathfinding algorithum and return if sucessful
				bool onAPath = pathfinding();
				if(!onAPath) {
					moveSelf(entRand(-1,1),entRand(-1,1));
				}
			}
			thirst = thirst - thirstBurnRate;
			hunger = hunger - hungerBurnRate;
        }
		if (thirst <=0) {
			alive = false;
		}
		if(alive) {
			return true;
		}
		else {return false;}
    }

	virtual void assessPriorities() override {
		vPriorities.clear();
		if(thirst < hunger) {
			if(thirst < 70) {
				vPriorities.emplace_back(Memory::water);
			}
			if(hunger < 70) {
				vPriorities.emplace_back(Memory::food);
			}
		}
		else {
			if(hunger < 70) {
				vPriorities.emplace_back(Memory::food);
			}
			if(thirst < 70) {
				vPriorities.emplace_back(Memory::water);
			}
		}
	}
};
