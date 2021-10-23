#include "objecthandler.h"

ObjectHandler::ObjectHandler(olc::vi2d PS,olc::vi2d atStartTL,olc::vi2d atStartBR, olc::PixelGameEngine* p) {
	PACK_SIZE = PS;
	pge = p;
	mapTL = atStartTL;
	mapBR = atStartBR;
	constructDecal();
	jumpstart();

}

void ObjectHandler::createMeat(olc::vi2d posXY, int posZ)  {
	vObjects.emplace_back(std::make_shared<ObjectMeat>(posXY.x,posXY.y, posZ));
}

void ObjectHandler::drawSingleObject(olc::vi2d posXY, olc::vi2d decalSourcePos, olc::vi2d &viewOffset, int bc)  {
	olc::vi2d objFinalPos = {posXY.x + viewOffset.x,posXY.y + viewOffset.y };
	pge->DrawPartialDecal((objFinalPos + olc::vi2d(1,1)) * PACK_SIZE,		// object final position after view offset adjustment
						  decTile.get(),									// get decal
						  decalSourcePos*PACK_SIZE,							// position x,y of tile on decal
						  PACK_SIZE,										// size of tile
						  olc::vi2d(1, 1),									// scale of decal
						  colorExchanger(bc));								// color
}

void ObjectHandler::drawObjects(int activeZLayer, olc::vi2d &viewOffset)  {
	for(int i = 0; i < (int)vObjects.size(); ++i) {
		if(visable({vObjects[i]->getXPos(),vObjects[i]->getYPos(),vObjects[i]->getZPos()},activeZLayer,viewOffset)) {
			drawSingleObject({vObjects[i]->getXPos(),vObjects[i]->getYPos()},	// object x,y
							 {vObjects[i]->getDecX(),vObjects[i]->getDecY()},	// decal  x,y
							 viewOffset,										// map view offset {x,y}
							 vObjects[i]->getBColor());							// color
		}
	}
}

bool ObjectHandler::visable(AKI::I3d pos, int activeZLayer,olc::vi2d viewOffset) {
	if(pos.z == activeZLayer) {
		if (pos.x >= mapTL.x - viewOffset.x && pos.x <= mapBR.x - viewOffset.x) {
			if (pos.y >= mapTL.y - viewOffset.y && pos.y <= mapBR.y - viewOffset.y) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

int ObjectHandler::ItemIDAtPosition(AKI::I3d pos) {
	for(int i = 0; i < (int)vObjects.size(); ++i) {
		if(vObjects[i]->getXPos() == pos.x && vObjects[i]->getYPos() == pos.y && vObjects[i]->getZPos() == pos.z) {
			return vObjects[i]->getID();
		}
	}


	return -1;
}



std::vector<std::shared_ptr<Object>> ObjectHandler::fillVectWithObjPtrs(std::vector<olc::vi2d> &vectPosXY, int z) {
	std::vector<std::shared_ptr<Object>> tmp;
	for(int i = 0; i < (int)vectPosXY.size(); ++i) {
		//if(ItemIDAtPosition(vectPosXY[i],z) != -1) {
		if(ItemIDAtPosition({vectPosXY[i].x,vectPosXY[i].y,z}) != -1) {
			std::shared_ptr<Object> check = getObjPtrAt({vectPosXY[i].x,vectPosXY[i].y,z});
			if(check != nullptr) {
				tmp.emplace_back(check);
			}
		}
	}
	return tmp;
}

std::shared_ptr<Object> ObjectHandler::getObjPtrAt(AKI::I3d pos) {
	if(isObjPtrAt(pos)) {
		for(int i = 0; i < (int)vObjects.size(); ++i) {
			if(vObjects[i]->getXPos() == pos.x && vObjects[i]->getYPos() == pos.y && vObjects[i]->getZPos() == pos.z) {
				return vObjects[i];
			}
		}
	}
	return nullptr;
}

bool ObjectHandler::isObjPtrAt(AKI::I3d pos) {
	for(int i = 0; i < (int)vObjects.size(); ++i) {
		if(vObjects[i]->getXPos() == pos.x && vObjects[i]->getYPos() == pos.y && vObjects[i]->getZPos() == pos.z) {
			return true;
		}
	}
	return false;
}



