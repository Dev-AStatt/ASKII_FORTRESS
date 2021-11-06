#pragma once
#include "engine/graphicsengine.h"

namespace Tiles {
	enum IDList {
		Air,
		Water,
		Grass,
		Dirt,
		Stone,
		SlopeNorth,
		SlopeSouth,
		SlopeEast,
		SlopeWest
	};
	enum IDSlopeList {
		North,
		South,
		East,
		West,
	};
	enum class TileType {
		normal,
		slope
	};

//	class TileManager;


class Tile {
public:
	Tile() {}
	Tile(TileType typ, std::string sName, olc::vi2d sourcePos, olc::Pixel t = olc::WHITE,bool walk = true, bool mine = true, bool sol = true) {
		type = typ;
		sTileName = sName;
		decalSourcePos = sourcePos;
		tint = t;
		mineable = mine;
		solid = sol;
		walkable = walk;

	}
	olc::vi2d getDecalPos()	const {return decalSourcePos;}
	std::string returnName() const	{ return "";}
	bool isWalkable() const			{ return walkable;}
	bool isSolid()	const			{ return solid; }
	olc::Pixel getTint() const		{ return tint;}
private:
	TileType type;
	std::string sTileName;
	olc::vi2d decalSourcePos;
	olc::Pixel tint;
	bool mineable = false;
	bool walkable = true;
	bool solid = true;

};


class TileManager {

public:
	std::vector<std::unique_ptr<Tile>> vptrTiles;
	TileManager();
	TileManager(std::shared_ptr<AKI::GameConfig> gc,std::shared_ptr<AKI::GraphicsEngine> ge) {
		graphicsEngine = ge;
		gameConfig = gc;
        fillvptrTiles();
    }

	void drawTile(const olc::vi2d& pos, int id) const {
		graphicsEngine->drawTile(pos,vptrTiles[id]->getDecalPos(),vptrTiles[id]->getTint());
	}


private:
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

	void fillvptrTiles() {
		//This creates the tile pointers that can be drawn. Clean this up later, this espessially need to be in MapUtilTileIDList

		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::normal,"Air",			olc::vi2d(0,0),olc::GREY,	false,false,false));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::normal,"Water",			olc::vi2d(14,7),olc::BLUE,	false,false,false));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::normal,"Grass",			olc::vi2d(12,15),olc::GREEN,true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::normal,"Dirt",			olc::vi2d(5,8),olc::GREY,	true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::normal,"Stone",			olc::vi2d(3,8),olc::GREY,	true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::slope,"Slope North",	olc::vi2d(14,1),olc::GREY	,true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::slope,"Slope South",	olc::vi2d(15,1),olc::GREY	,true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::slope,"Slope East",		olc::vi2d(0,1),olc::GREY,	true,true,true));
		vptrTiles.emplace_back(std::make_unique<Tile>(TileType::slope,"Slope West",		olc::vi2d(1,1),olc::GREY,	true,true,true));
	}

};



};
