#include "Ent.h"

Ent::Ent(olc::vi2d& PS, olc::PixelGameEngine* p) {
	constructEntBasics(PS,p);
	//These lines should be overwritten by inheriting classes
	decalSourcePos = { 15,3 };
	entPositionXY = {1,1};
	entStepZPosition = 0;
	viewDistance = 3;
	thirst = 100;
	tint = olc::WHITE;
}

void Ent::constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p) {
	PACK_SIZE = PS;
	pge = p;
	entHeadZPosition = entStepZPosition + 1;
	alive = true;

	constructDecal();	//construct decal will add decals to Ents
	cTiles = std::make_unique<TileID::cTileID>(PACK_SIZE,pge);
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

	if(watchYourStep(x,y)) {
		entPositionXY = entPositionXY + olc::vi2d(x,y);
	}
}

bool Ent::watchYourStep(int x, int y) {

	//this function for index is wrong
	int index = (x+viewDistance) + ((y+viewDistance) * (viewDistance*2 + 1));
	auto& t = cTiles->vptrTiles[fieldOfView[index]];
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
		pge->DrawPartialDecal((entFinalPos + olc::vi2d(1,1)) * PACK_SIZE, decTile.get(), decalSourcePos*PACK_SIZE, PACK_SIZE, olc::vi2d(1, 1), tint);
	}
}

void Ent::pathfinding(int currentTask) {
	moveSelf(entRand(-1,1),entRand(-1,1));
}

