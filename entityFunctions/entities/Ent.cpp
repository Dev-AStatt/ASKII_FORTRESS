#include "Ent.h"

Ent::Ent(olc::vi2d& PS, olc::PixelGameEngine* p, std::string n) {
	constructEntBasics(PS,p);
	//These lines should be overwritten by inheriting classes
	decalSourcePos		= { 15,3 };
	entPositionXY		= {1,1};
	entStepZPosition	= 0;
	viewDistance		= 3;
	thirst				= 100;
	tint				= olc::WHITE;
	sEntName			= n;
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

bool Ent::pathfinding() {
	if((int)vPriorities.size() <= 0) { return false;}

	//look if already has a destination with the same prioirity
	if(Destination->getPriority() == vPriorities[0]) {
		if(Destination->arivedAtDest(entPositionXY,entHeadZPosition)) {
			std::cout << sEntName << " Has Arived At Destination" << '\n';
		} else {
			//std::cout << sEntName << " Is Following A Destination" << '\n';
			moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));
		}
		return true;
	}
	if(vPriorities[0] == Memory::water) {
		//search for tile returns if tile is even in view
		if(!searchForTile(TileID::Water)) { return false;}
		std::cout << sEntName << " Has Found Water" << '\n';
		//set destination to new tile found
		Destination->setNewDest(locateTile(TileID::Water),entStepZPosition,Memory::water,TileID::Water);
		//move tward tile
		moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));
		return true;
	}
	if(vPriorities[0] == Memory::food) {
		//check to see if there is anything edable in view
		if(!searchForFood()) { return false;}
		std::cout << sEntName << " Has Found Food" << '\n';
		//get location of food
		olc::vi2d tmp = locationOfFood();
		Destination->setNewDest(tmp,entStepZPosition,Memory::food,foodIDAt(tmp));	//set destindation of food
		moveSelfvi2d(Destination->directionToDest(entPositionXY,entStepZPosition));	//Go to food
		return true;
	}
	return false;
}

int Ent::foodIDAt(olc::vi2d XY) {
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->getXPos() == XY.x &&objectPtrsInView[i]->getYPos() == XY.y) {
			return objectPtrsInView[i]->getID();
		}
	}
	return -1;
}

bool Ent::searchForFood() {
	if((int)objectPtrsInView.size() > 0) {
		for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
			if(objectPtrsInView[i]->isEdable()) {
				return true;
			}
		}
	}
	return false;
}

olc::vi2d Ent::locationOfFood() {
	olc::vi2d closest, tmp;
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->isEdable()) {
			closest = {objectPtrsInView[i]->getXPos(),objectPtrsInView[i]->getYPos()};
		}
	}
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->isEdable()) {
			tmp = {objectPtrsInView[i]->getXPos(),objectPtrsInView[i]->getYPos()};
			if(closerToEnt(closest,tmp)) {
				closest = tmp;
			}
		}
	}
	std::cout << sEntName << " Found Food At: " << "{" << std::to_string(closest.x)<< ", " << std::to_string(closest.y) << "}" << '\n';
	return closest;
}

bool Ent::searchForTile(TileID::TileIDList tileLookingFor) {
	for (int i = 0; i < (int)tilesInView.size(); ++i) {
		if(tilesInView[i] == tileLookingFor) {
			return true;
		}
	}
	return false;
}


//will currently return 0,0 if no tile is found
olc::vi2d Ent::locateTile(TileID::TileIDList tileLookingFor) {
	olc::vi2d closest = {-200,-200}, temp;
	for (int i = 0; i < (int)tilesInView.size(); ++i) {
		if(tilesInView[i] == tileLookingFor) {
			temp = positionsXYInView[i];
			if(closerToEnt(closest,temp)) {
				closest = temp;
			}
		}
	}
	std::cout << sEntName << " Found Tile At: " << "{" << std::to_string(closest.x)<< ", " << std::to_string(closest.y) << "}" << '\n';
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

//void Ent::giftObjectsInView(std::vector<int> vGivenItems) {
//	if((int)vGivenItems.size() == (viewDistance*12 + 1)) {
//		objectsInView = vGivenItems;
//	}
//}
