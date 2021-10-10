#pragma once
#include "olcPixelGameEngine.h"

class Tile {
private:
	
public:
	Tile() {};
    Tile(olc::vi2d& PS, olc::PixelGameEngine* p) {

		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = { 15,3 };
		tint = olc::WHITE;
	}
	std::string returnName() {
        return "";
	}

	virtual void DrawSelf(const olc::vi2d& pos) {
		pge->DrawPartialDecal(pos * PACK_SIZE, decTile.get(), decalSourcePos*PACK_SIZE, PACK_SIZE, olc::vi2d(1, 1), tint);
	}
protected:
	std::string sTileName;
	olc::vi2d decalSourcePos;
	olc::Pixel tint;
	olc::vi2d PACK_SIZE;
	olc::PixelGameEngine* pge;
	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite> sprTile;
	std::unique_ptr<olc::Decal> decTile;
	bool mineable = false;

	void constructDecal() {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());
	}

};

class TileStone : public Tile {
public:
	TileStone(olc::vi2d& PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = { 3,8 };
		sTileName = "Stone";
		tint = olc::GREY;
		mineable = true;
	}

};

class TileAir : public Tile {
public:
	TileAir(olc::vi2d& PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		sTileName = "Air";
		tint = olc::BLACK;
	}

};

class TileWater : public Tile {
public:
	TileWater(olc::vi2d& PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = { 14,7 };
		sTileName = "Water";
		tint = olc::BLUE;
	}

};

class TileGrass : public Tile {
public:
	TileGrass(olc::vi2d& PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = { 12,15 };
		sTileName = "Grass";
		tint = olc::GREEN;
		mineable = true;
	}

};

class TileDirt : public Tile {
public:
	TileDirt(olc::vi2d& PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = { 5,8 };
		sTileName = "Stone";
		tint = olc::GREY;
		mineable = true;
	}

};
