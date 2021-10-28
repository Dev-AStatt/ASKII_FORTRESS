#include "entitieshandler.h"

EntitiesHandler::EntitiesHandler(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
								 std::shared_ptr<Maps> chunkman, std::shared_ptr<ObjectHandler> obj) {
	gameConfig = gc;
	graphicsEngine = ge;
	chunkManager = chunkman;
	ObjHandler = obj;
	tileManager = std::make_shared<TileID::TileManager>	(gameConfig,graphicsEngine);

}

void EntitiesHandler::newEntity(olc::vi2d posXY, int posZ, std::string n) {
	aliveEnts.emplace_back(std::make_unique<EntHuman>(graphicsEngine,gameConfig,tileManager,posXY,posZ,n));
}

void EntitiesHandler::drawEntities(int activeZLayer, olc::vi2d& viewOffset) {
    for(int i = 0; i < (int)aliveEnts.size(); ++i) {
		if(olcWithinBounds(aliveEnts[i]->returnPos(),viewOffset)) {
            aliveEnts[i]->DrawSelf(activeZLayer, viewOffset);
        }
    }
}

bool EntitiesHandler::olcWithinBounds(AKI::I3d checkpos, olc::vi2d& viewOffset) {
	checkpos.x = checkpos.x + viewOffset.x;
	checkpos.y = checkpos.y + viewOffset.x;
//    mapBR = mapBR + viewOffset;
	if(gameConfig->getMapTL().x <= checkpos.x && checkpos.x <= gameConfig->getMapBR().x) {
		if(gameConfig->getMapTL().y <= checkpos.y && checkpos.y <= gameConfig->getMapBR().y) {
            return true;
        }
    }
    return false;
}

void EntitiesHandler::newGameEntities() {
	newEntity({5,5},11,"Dave");
	newEntity({10,10},11, "Igor");
}


void EntitiesHandler::updateEntities(int tick) {
	for(int i = 0; i < (int)aliveEnts.size(); ++i) {
		//give view of map
		aliveEnts[i]->giftOfSight(chunkManager->viewOfWorld(aliveEnts[i]->returnPos(),aliveEnts[i]->returnViewDistance()));
		//give view of Objects
		passItemPtrToEnt(i);

		//update Ent
		aliveEnts[i]->updateSelf(tick);

		//check if entity is still alive
		if(!aliveEnts[i]->alive) {
			//this is to delete unique pointer from vector after ent dies
			aliveEnts.erase(aliveEnts.begin() + i);
		}
     }
}

void EntitiesHandler::passItemPtrToEnt(int entIndex) {
	std::vector<std::shared_ptr<Object>> tmp;
	std::vector<olc::vi2d> vPos = aliveEnts[entIndex]->getPosInView();
	//tmp = ObjHandler->fillVectWithObjPtrs(vPos,aliveEnts[entIndex]->returnStepZ());
	tmp = ObjHandler->fillVectWithObjPtrs(vPos,aliveEnts[entIndex]->returnStepZ());
	aliveEnts[entIndex]->giftObjectsInView(tmp);

}





