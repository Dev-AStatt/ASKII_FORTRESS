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
	vObjects.emplace_back(std::make_unique<ObjectMeat>(posXY.x,posXY.y, posZ));
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
		if(visable({vObjects[i]->getXPos(),vObjects[i]->getYPos()},vObjects[i]->getZPos(),activeZLayer,viewOffset)) {
			drawSingleObject({vObjects[i]->getXPos(),vObjects[i]->getYPos()},	// object x,y
							 {vObjects[i]->getDecX(),vObjects[i]->getDecY()},	// decal  x,y
							 viewOffset,										// map view offset {x,y}
							 vObjects[i]->getBColor());							// color
		}
	}
}

bool ObjectHandler::visable(olc::vi2d posXY,int posZ, int activeZLayer,olc::vi2d viewOffset) {
	if(posZ == activeZLayer) {
		if (posXY.x >= mapTL.x - viewOffset.x && posXY.x <= mapBR.x - viewOffset.x) {
			if (posXY.y >= mapTL.y - viewOffset.y && posXY.y <= mapBR.y - viewOffset.y) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}







