#pragma once
#include "mapFunctions/TileFunctions/Tiles.h"
#include "mapFunctions/TileFunctions/TileSlope.h"
#include "engine/graphicsengine.h"
namespace TileID {
	enum TileIDList {
		Air,
		Water,
		Grass,
		Dirt,
		Stone,
		SlopeNorth,
		SlopeSouth,
	};
	enum TileIDSlope {
		North,
		South,
		East,
		West,
	};

	class TileManager;
};

class TileID::TileManager {
private:
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;
public:
	TileManager();
	TileManager(std::shared_ptr<AKI::GameConfig> gc,std::shared_ptr<AKI::GraphicsEngine> ge) {
		graphicsEngine = ge;
		gameConfig = gc;
        fillvptrTiles();
    }
	TileManager(olc::vi2d PS, olc::PixelGameEngine* p) {
		PACK_SIZE = PS;
		pge = p;

		fillvptrTiles();
	}
    std::vector<std::unique_ptr<Tile>> vptrTiles;

    void fillvptrTiles() {
        //This creates the tile pointers that can be drawn. Clean this up later, this espessially need to be in MapUtilTileIDList
		vptrTiles.emplace_back(std::make_unique<TileAir>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileWater>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileGrass>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileDirt>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileStone>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileSlopeNorth>(graphicsEngine));
		vptrTiles.emplace_back(std::make_unique<TileSlopeSouth>(graphicsEngine));
    }
};
