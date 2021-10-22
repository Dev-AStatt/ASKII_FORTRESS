#pragma once
#include "mapFunctions/TileFunctions/Tiles.h"
#include "mapFunctions/TileFunctions/TileSlope.h"
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

    class cTileID;
};

class TileID::cTileID {
private:
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;
public:
    cTileID();
    cTileID(olc::vi2d PS, olc::PixelGameEngine* p) {
        PACK_SIZE = PS;
        pge = p;
        fillvptrTiles();
    }
    std::vector<std::unique_ptr<Tile>> vptrTiles;

    void fillvptrTiles() {
        //This creates the tile pointers that can be drawn. Clean this up later, this espessially need to be in MapUtilTileIDList
        vptrTiles.emplace_back(std::make_unique<TileAir>(PACK_SIZE, pge));
        vptrTiles.emplace_back(std::make_unique<TileWater>(PACK_SIZE, pge));
        vptrTiles.emplace_back(std::make_unique<TileGrass>(PACK_SIZE, pge));
        vptrTiles.emplace_back(std::make_unique<TileDirt>(PACK_SIZE, pge));
        vptrTiles.emplace_back(std::make_unique<TileStone>(PACK_SIZE, pge));
		vptrTiles.emplace_back(std::make_unique<TileSlopeNorth>(PACK_SIZE, pge));
		vptrTiles.emplace_back(std::make_unique<TileSlopeSouth>(PACK_SIZE, pge));
    }
};
