#pragma once
#include "Ent.h"

class EntHuman : public Ent {
private:


public:
    EntHuman() {

    }
	EntHuman(olc::vi2d& PS, olc::PixelGameEngine* p, olc::vi2d& posXY, int posZ, std::string n) {
        constructEntBasics(PS,p);
		decalSourcePos		= { 0,4 };
		entPositionXY		= posXY;
		entStepZPosition	= posZ;
		viewDistance		= 3;
		thirst				= 70;
		hunger				= 100;
		tint				= olc::WHITE;
		sEntName			= n;
    }

	virtual bool updateSelf(int tick) override {
		if (tick % 10 == 0 && alive) {
			assessPriorities();
			if(vPriorities.size()>0) {
				pathfinding(vPriorities[0]);
			}
			thirst = thirst - 5;
			hunger = hunger - 2;
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
