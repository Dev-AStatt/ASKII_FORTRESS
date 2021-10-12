#pragma once
#include "Ent.h"

class EntHuman : public Ent {
public:
    EntHuman() {

    }
    EntHuman(olc::vi2d& PS, olc::PixelGameEngine* p, olc::vi2d& posXY, int posZ) {
        constructEntBasics(PS,p);
        decalSourcePos = { 0,4 };
        entPositionXY = posXY;
        entPositionZ = posZ;
        tint = olc::WHITE;
    }

    virtual void updateSelf(int tick) override {
        if (tick % 10 == 0) {
            moveSelf(entRand(-1,1),entRand(-1,1));
        }
    }


};
