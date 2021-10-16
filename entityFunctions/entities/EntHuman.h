#pragma once
#include "Ent.h"

class EntHuman : public Ent {
private:


public:
    EntHuman() {

    }
    EntHuman(olc::vi2d& PS, olc::PixelGameEngine* p, olc::vi2d& posXY, int posZ) {
        constructEntBasics(PS,p);
        decalSourcePos = { 0,4 };
        entPositionXY = posXY;
		entStepZPosition = posZ;
        viewDistance = 2;
		thirst = 100;
		hunger = 100;

        tint = olc::WHITE;
    }

	virtual bool updateSelf(int tick) override {
		if (tick % 10 == 0 && alive) {
			if(vPriorities.size()>0) {
				pathfinding(vPriorities[0]);
			}
            moveSelf(entRand(-1,1),entRand(-1,1));
			thirst = thirst - 1;
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
		if(thirst < hunger && thirst < 70) {
			vPriorities.emplace_back(water);
			vPriorities.emplace_back(food);
		}
	}
};
