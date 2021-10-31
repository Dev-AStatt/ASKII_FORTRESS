#pragma once
#include "engine/graphicsengine.h"

class Tile {
private:
	
public:
	Tile() {};
	Tile(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		decalSourcePos = { 15,3 };
		tint = olc::WHITE;
	}
	std::string returnName()	{ return "";}
	bool isWalkable()			{ return walkable;}
	bool isSolid()				{ return solid; }
	virtual void DrawSelf(const olc::vi2d& pos) {
		graphicsEngine->drawTile(pos,decalSourcePos,tint);
	}

protected:
	std::string sTileName;
	olc::vi2d decalSourcePos;
	olc::Pixel tint;

	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite> sprTile;
	std::unique_ptr<olc::Decal> decTile;
	bool mineable = false;
    bool walkable = true;
	bool solid = true;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

	void constructDecal() {
		//move this crap to TileIDList
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());
	}
	void constructBasics(std::shared_ptr<AKI::GraphicsEngine> ge) {
		graphicsEngine = ge;

		constructDecal();
	}
};

class TileStone : public Tile {
public:
	TileStone(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		decalSourcePos = { 3,8 };
		sTileName = "Stone";
		tint = olc::GREY;
		mineable = true;
	}
};

class TileAir : public Tile {
public:
	TileAir(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		sTileName = "Air";
		tint = olc::BLACK;
        walkable = false;
		solid = false;
	}
};

class TileWater : public Tile {
public:
	TileWater(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		decalSourcePos = { 14,7 };
		sTileName = "Water";
		tint = olc::BLUE;
        walkable = false;
		solid = false;
	}
};

class TileGrass : public Tile {
public:
	TileGrass(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		decalSourcePos = { 12,15 };
		sTileName = "Grass";
		tint = olc::GREEN;
		mineable = true;
	}
};

class TileDirt : public Tile {
public:
	TileDirt(std::shared_ptr<AKI::GraphicsEngine> ge) {
		constructBasics(ge);
		decalSourcePos = { 5,8 };
		sTileName = "Stone";
		tint = olc::GREY;
		mineable = true;
	}
};

