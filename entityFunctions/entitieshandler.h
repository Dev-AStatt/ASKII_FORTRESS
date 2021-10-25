#pragma once
#include <vector>
#include "libraries/olcPixelGameEngine.h"
#include "entities/Ent.h"
#include "entities/EntHuman.h"
#include "mapFunctions/Maps.h"
#include "objectFunctions/objecthandler.h"
#include "mapFunctions/MapUtil_I3d.h"

class EntitiesHandler
{
private:
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;
    Maps* map;
	std::shared_ptr<ObjectHandler> ObjHandler;
    std::vector<std::unique_ptr<Ent>> aliveEnts;

    //functions
	bool olcWithinBounds(AKI::I3d checkpos, olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);

public:
	EntitiesHandler(olc::vi2d PS, Maps* m, std::shared_ptr<ObjectHandler> obj, olc::PixelGameEngine* p);

	void newEntity(olc::vi2d posXY, int posZ, std::string n);
    void newGameEntities();
    void drawEntities(int activeZLayer,olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);
    void updateEntities(int tick);
	void passItemPtrToEnt(int entIndex);
};


//olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p
