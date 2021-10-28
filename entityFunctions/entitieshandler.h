#pragma once
#include <vector>
#include "entities/Ent.h"
#include "entities/EntHuman.h"
#include "mapFunctions/Maps.h"
#include "objectFunctions/objecthandler.h"
#include "mapFunctions/MapUtil_I3d.h"
#include "mapFunctions/MapUtilTileIDList.h"

class EntitiesHandler
{
private:

    Maps* map;
	std::shared_ptr<ObjectHandler> ObjHandler;
    std::vector<std::unique_ptr<Ent>> aliveEnts;
	std::shared_ptr<TileID::TileManager> tileManager;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

    //functions
	bool olcWithinBounds(AKI::I3d checkpos, olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);

public:
	EntitiesHandler(Maps* m, std::shared_ptr<ObjectHandler> obj,
					std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc);

	void newEntity(olc::vi2d posXY, int posZ, std::string n);
    void newGameEntities();
    void drawEntities(int activeZLayer,olc::vi2d& mapTL, olc::vi2d& mapBR, olc::vi2d& viewOffset);
    void updateEntities(int tick);
	void passItemPtrToEnt(int entIndex);
};

