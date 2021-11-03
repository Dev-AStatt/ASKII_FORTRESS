#pragma once
#include <vector>
#include "entities/Ent.h"
#include "entities/EntHuman.h"
#include "mapFunctions/Maps.h"
#include "objectFunctions/objecthandler.h"
#include "mapFunctions/MapUtilTileIDList.h"
#include "Popup.h"
#include "entityFunctions/TreeDataStructure.h"

class EntitiesHandler
{
private:

	std::shared_ptr<Maps> chunkManager;
	std::shared_ptr<ObjectHandler> ObjHandler;
    std::vector<std::unique_ptr<Ent>> aliveEnts;
	std::shared_ptr<TileID::TileManager> tileManager;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;
	std::shared_ptr<AKI::Popup> popup;

    //functions
	bool olcWithinBounds(AKI::I3d checkpos, olc::vi2d& viewOffset);

	void addChildren(std::unique_ptr<Node>& n, AKI::I3d& parentPos);

public:
	EntitiesHandler(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
					std::shared_ptr<Maps> chunkman, std::shared_ptr<ObjectHandler> obj, std::shared_ptr<AKI::Popup> pop);

	void newEntity(olc::vi2d posXY, int posZ, std::string n);
    void newGameEntities();
	void drawEntities(int activeZLayer,olc::vi2d& viewOffset);
    void updateEntities(int tick);
	void passItemPtrToEnt(int entIndex);
	void updateSight(int entIndex);
};

