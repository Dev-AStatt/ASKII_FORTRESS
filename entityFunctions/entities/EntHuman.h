#pragma once
#include "Ent.h"

class EntHuman : public Ent {
public:
    EntHuman() {}
	EntHuman(std::shared_ptr<AKI::GraphicsEngine> ge,
			 std::shared_ptr<AKI::GameConfig> gc,
			 std::shared_ptr<Tiles::TileManager> tm,
			 olc::vi2d& posXY, int posZ, std::string n) {
		constructEntBasics(tm,ge,gc);
		decalSourcePos		= { 0,4 };

		position			= {posXY.x, posXY.y, posZ};
		viewDistance		= 5;
		thirst				= 100;
		thirstBurnRate		= 2;
		hunger				= 100;
		hungerBurnRate		= 1;
		tint				= olc::WHITE;
		sEntName			= n;
		sight = std::make_unique<EntSight>(viewDistance,tileManager);

    }

	virtual bool updateSelf(int tick) override {
		if (tick % 10 == 0 && alive) {
			assessPriorities();
			if(vPriorities.size()>0) {
				//run pathfinding algorithum and return if sucessful
				bool onAPath = pathfinding();
				if(!onAPath) {
					moveSelf(AKIRand(-1,1),AKIRand(-1,1));
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
			if(thirst < 80) {
				vPriorities.emplace_back(Memories::water);
			}
			if(hunger < 70) {
				vPriorities.emplace_back(Memories::food);
			}
		}
		else {
			if(hunger < 70) {
				vPriorities.emplace_back(Memories::food);
			}
			if(thirst < 70) {
				vPriorities.emplace_back(Memories::water);
			}
		}
	}
};
