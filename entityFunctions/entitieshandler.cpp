#include "entitieshandler.h"

EntitiesHandler::EntitiesHandler(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
								 std::shared_ptr<Maps> chunkman, std::shared_ptr<ObjectHandler> obj, std::shared_ptr<AKI::Popup> pop) {
	gameConfig = gc;
	graphicsEngine = ge;
	chunkManager = chunkman;
	ObjHandler = obj;
	popup = pop;
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
		updateSight(i);

		//give view of Objects
		passItemPtrToEnt(i);

		//update Ent
		aliveEnts[i]->updateSelf(tick);

		//check if entity is still alive
		if(!aliveEnts[i]->alive) {
			std::string s = " Has Died";
			s = aliveEnts[i]->returnName() + s;
			popup->PopupMessage(s);
			//this is to delete unique pointer from vector after ent dies
			aliveEnts.erase(aliveEnts.begin() + i);
		}
     }
}

void EntitiesHandler::passItemPtrToEnt(int entIndex) {
	std::vector<std::shared_ptr<Object>> tmp;
	std::vector<AKI::I3d> vPos = aliveEnts[entIndex]->getCordsInView();
	//tmp = ObjHandler->fillVectWithObjPtrs(vPos,aliveEnts[entIndex]->returnStepZ());
	tmp = ObjHandler->fillVectWithObjPtrs(vPos);
	aliveEnts[entIndex]->giftObjectsInView(tmp);

}


 void EntitiesHandler::updateSight(int entIndex) {
	//first we need to get the fist parent node for the Data structure,
	//we need the position, slab, and infill int's.

	//get the ent starting position
	AKI::I3d entStartingPos = aliveEnts[entIndex]->returnPos();

	std::shared_ptr<Node> source;
	source = std::make_shared<Node>(chunkManager->getBlockFromWorldPos(entStartingPos),entStartingPos);


	for(int y = entStartingPos.y - 1; y <= entStartingPos.y + 1; ++y) {
		for(int x = entStartingPos.x - 1; x <= entStartingPos.x + 1; ++x) {
			AKI::I3d newPos = {x,y,entStartingPos.z};
			source->newChild(chunkManager->getBlockFromWorldPos(newPos),newPos);
		}
	}
	aliveEnts[entIndex]->setSightNodeSource(source);
}















