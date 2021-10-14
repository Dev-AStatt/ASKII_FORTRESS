#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "entities/Ent.h"
#include "entities/EntHuman.h"
#include "mapFunctions/Maps.h"

class EntitiesHandler
{
private:
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;
    Maps* map;

    std::vector<std::unique_ptr<Ent>> aliveEnts;


    //functions
    bool olcWithinBounds(olc::vi2d checkpos, olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);



public:
    EntitiesHandler(olc::vi2d PS, Maps* m, olc::PixelGameEngine* p);
    void newEntity(olc::vi2d posXY, int posZ);
    void newGameEntities();
    void drawEntities(int activeZLayer,olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);

    void updateEntities(int tick);
};


//olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p
