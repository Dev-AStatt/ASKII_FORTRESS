#include "entitieshandler.h"

EntitiesHandler::EntitiesHandler(olc::vi2d PS, Maps* m, olc::PixelGameEngine* p) {
    PACK_SIZE = PS;
    pge = p;
    map = m;
}

void EntitiesHandler::newEntity(olc::vi2d posXY, int posZ) {
    aliveEnts.emplace_back(std::make_unique<EntHuman>(PACK_SIZE,pge,posXY,posZ));
}

void EntitiesHandler::drawEntities(int activeZLayer, olc::vi2d &mapTL, olc::vi2d &mapBR, olc::vi2d& viewOffset) {
    for(int i = 0; i < (int)aliveEnts.size(); ++i) {
        if(olcWithinBounds(aliveEnts[i]->returnPos(),mapTL,mapBR,viewOffset)) {
            aliveEnts[i]->DrawSelf(activeZLayer, viewOffset);
        }
    }
}

bool EntitiesHandler::olcWithinBounds(olc::vi2d checkpos, olc::vi2d &mapTL, olc::vi2d &mapBR, olc::vi2d& viewOffset) {
    checkpos = checkpos + viewOffset;
//    mapBR = mapBR + viewOffset;
    if(mapTL.x <= checkpos.x && checkpos.x <= mapBR.x) {
        if(mapTL.y <= checkpos.y && checkpos.y <= mapBR.y) {
            return true;
        }
    }
    return false;
}

void EntitiesHandler::newGameEntities() {
    newEntity({5,5},11);
    newEntity({10,10},11);
}


void EntitiesHandler::updateEntities(int tick) {
     for(int i = 0; i < (int)aliveEnts.size(); ++i) {
         //map
         aliveEnts[i]->updateSelf(tick);
     }
}
