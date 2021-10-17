#include "Ent.h"

Ent::Ent(olc::vi2d& PS, olc::PixelGameEngine* p) {
	constructEntBasics(PS,p);
	//These lines should be overwritten by inheriting classes
	decalSourcePos		= { 15,3 };
	entPositionXY		= {1,1};
	entStepZPosition	= 0;
	viewDistance		= 3;
	thirst				= 100;
	tint				= olc::WHITE;
}

void Ent::constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p) {
	PACK_SIZE = PS;
	pge = p;
	entHeadZPosition = entStepZPosition + 1;
	constructDecal();	//construct decal will add decals to Ents
	cTiles = std::make_unique<TileID::cTileID>(PACK_SIZE,pge);
	Destination = std::make_unique<Memory::EntDest>();
	UpdatePosInView();
	alive = true;
}

//used for update Position in view to check if number is pos
int notNegativeXY(int x) { if(x >=0) { return x; } else return 0; }

void Ent::UpdatePosInView() {
	positionsXYInView.clear();
	objectsInView.clear();
	for(int y = notNegativeXY(entPositionXY.y - viewDistance); y < entPositionXY.y + viewDistance; ++y) {
		for(int x = notNegativeXY(entPositionXY.x - viewDistance); x < entPositionXY.x + viewDistance; ++x) {
			positionsXYInView.emplace_back(olc::vi2d(x,y));
			//fill objects in view vector with -1 {empty/no item}

		}
	}
}

void Ent::constructDecal() {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());
	}


int Ent::entRand(int from, int to) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(from, to); // define the range
	return distr(gen);
}

void Ent::moveSelf(int x, int y) {
	//check if tile going to walk on is "walkable"
	if(watchYourStep(x,y)) {
		entPositionXY = entPositionXY + olc::vi2d(x,y);
		UpdatePosInView();
	}
}

bool Ent::watchYourStep(int x, int y) {
	//this function for index is wrong
	int index = (x+viewDistance) + ((y+viewDistance) * (viewDistance*2 + 1));
	auto& t = cTiles->vptrTiles[tilesInView[index]];
	if(t->isWalkable()) {
		return true;
	}
	return false;
}

void Ent::DrawSelf(int activeZLayer, olc::vi2d& viewOffset) {
	if(activeZLayer == entStepZPosition) {
		olc::vi2d entFinalPos = {entPositionXY.x + viewOffset.x,entPositionXY.y + viewOffset.y };
		//the ent pos gets a + 1x1 to adjust for the header bar to match up
		//with the chunkxyz's so 0x0 is the same 0x0
		pge->DrawPartialDecal((entFinalPos + olc::vi2d(1,1)) * PACK_SIZE,	//position to draw to
							  decTile.get(),
							  decalSourcePos*PACK_SIZE,
							  PACK_SIZE,
							  olc::vi2d(1, 1),								//scale
							  tint);
	}
}

void Ent::pathfinding(int currentTask) {
	if((int)vPriorities.size() <=0) {
		moveSelf(entRand(-1,1),entRand(-1,1));
	} else {
		//look if already has a destination with the same prioirity
		if(Destination->getPriority() == vPriorities[0]) {
			moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));
		}
		else {
			if(vPriorities[0] == Memory::water) {
				Destination->setNewDest(searchForTile(TileID::Water),entStepZPosition,Memory::water,TileID::Water);
				moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));
			}
			if(vPriorities[0] == Memory::food) {
				//add set dest to object
				moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));
			}
		}


	}
}

bool Ent::searchForFood() {
	for(int i = 0; i < (int)objectsInView.size(); ++i) {
		//if object is -1 then it is an empty space
		if(objectsInView[i] != -1) {

		}
	}
}

//will currently return 0,0 if no tile is found
olc::vi2d Ent::searchForTile(TileID::TileIDList tileLookingFor) {
	olc::vi2d closest = {0,0}, temp;
	for (int i = 0; i < (int)tilesInView.size(); ++i) {
		if(tilesInView[i] == tileLookingFor) {
			temp = positionsXYInView[i];
			if(closerToEnt(closest,temp)) {
				closest = temp;
			}
		}
	}
	return closest;
}

bool Ent::closerToEnt(olc::vi2d &oldXY, olc::vi2d &newXY) {
	olc::vi2d d = entPositionXY - oldXY;
	//get the distance to the old match
	int oldDist = std::abs(d.x) + std::abs(d.y);
	d = entPositionXY - newXY;
	int newDist = std::abs(d.x) + std::abs(d.y);

	if(newDist < oldDist) { return true; }
	return false;
}

void Ent::giftObjectsInView(std::vector<int> vGivenItems) {
	if((int)vGivenItems.size() == (viewDistance*12 + 1)) {
		objectsInView = vGivenItems;
	}
}
