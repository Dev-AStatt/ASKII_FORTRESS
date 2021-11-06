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
	std::vector<AKI::I3d> vPos;;// = aliveEnts[entIndex]->getCordsInView();
	//tmp = ObjHandler->fillVectWithObjPtrs(vPos,aliveEnts[entIndex]->returnStepZ());
	tmp = ObjHandler->fillVectWithObjPtrs(vPos);
	aliveEnts[entIndex]->giftObjectsInView(tmp);

}


 void EntitiesHandler::updateSight(int entIndex) {
	//first we need to get the fist parent node for the Data structure,
	//we need the position, slab, and infill int's.

	//get the ent starting position
	AKI::I3d entStartingPos = aliveEnts[entIndex]->returnPos();

	std::unique_ptr<Node> source;
	source = std::make_unique<Node>(chunkManager->getBlockFromWorldPos(entStartingPos),entStartingPos);
	std::vector<AKI::I3d> alreadyIndexedLocs;
	alreadyIndexedLocs.emplace_back(source->location);

	//call recursive funcation to fill children to specified debth by view distance
	addChildren(source,alreadyIndexedLocs,1,aliveEnts[entIndex]->getViewDistance());

	aliveEnts[entIndex]->setSightNodeSource(source);
}

 void EntitiesHandler::addChildren(std::unique_ptr<Node>& n, std::vector<AKI::I3d>& alreadyIndexed, int currentDebth, int maxDebth) {
	 if(currentDebth > maxDebth) {return;}
	 if(n->block.infill != TileID::Air) {return;}

	 //
	 //direction shows the {+1, -1} direction that the map is going
	 //
	int searchYStart = n->location.y - 1;
	int searchYEnd	 = n->location.y + 1;
	int searchXStart = n->location.x - 1;
	int searchXEnd	 = n->location.x + 1;
	//make sure this doesnt go off the map
	if(searchYStart < 0) {searchYStart = 0;}
	if(searchYEnd   < 0) {searchYEnd   = 0;}
	if(searchXStart < 0) {searchXStart = 0;}
	if(searchXEnd   < 0) {searchXEnd   = 0;}

	AKI::I3d newPos;
	//
	//loop for sourounding tiles and add children for tiles not in alreadyIndexed vector
	//
	for(int y = searchYStart; y <= searchYEnd; ++y) {
		for(int x = searchXStart; x <= searchXEnd; ++x) {
			if(n->location == AKI::I3d(x,y,n->location.z)) {break;}		//make sure we dont try and add the parent pos
			newPos = AKI::I3d(x,y,n->location.z);
			AKI::Block newBlock = chunkManager->getBlockFromWorldPos(newPos);
			if(newBlock.infill != TileID::Air) {						//if the infill of a tile is not air, we want to look above it
				newPos = newPos.I3d_ZOffset(1);
			}
			//if new pos is not included in vector alreadyIndexed		  cool lamda function!
			if(std::none_of(alreadyIndexed.cbegin(),alreadyIndexed.cend(),[newPos](AKI::I3d i){return i == newPos;})) {
				n->newChild(newBlock,{x,y,n->location.z});
				alreadyIndexed.emplace_back(newPos);
			}
		 }
	 }
	//
	//recursivly call self to get children
	//
	for(int i = 0; i < (int)n->getNumChildren(); ++i) {
		addChildren(n->getChild(i), alreadyIndexed,++currentDebth,maxDebth);
	}
 }





 /*
  *		-----------------
  *		| x	| x	| x	| x	| x	| x	|
  *		| x	| x	| x	| x	| x	| x	|
  *		| x	| x | 	| x	| x	| x	|
  *		| x	| x	| x	| x	| x	| x	|
  *		| x	| x	| x	| x	| x	| x	|
  */










