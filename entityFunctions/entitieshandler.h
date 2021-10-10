#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "entities/Ent.h"

class EntitiesHandler
{
private:
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;

    std::vector<std::unique_ptr<Ent>> aliveEnts;

public:
    EntitiesHandler(olc::vi2d PACK_SIZE, olc::PixelGameEngine* p);
    void newEntity();
    void drawEntities(int activeZLayer,olc::vi2d& mapTL, olc::vi2d& mapBR);
};


//olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p
