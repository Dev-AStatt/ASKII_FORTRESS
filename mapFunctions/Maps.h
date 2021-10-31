#pragma once
#include "engine/graphicsengine.h"
#include "mapFunctions/cChunk.h"
#include "mapFunctions/MapUtilChunkGen.h"

//
//This is a class that is designed to hold pointers to each chunk in the map.
//Should be built to include all edits to maps as well.
//Handles drawing of the map too for now. but may be needed to move to game engine.
//
class Maps {
private:

	std::shared_ptr<MapUtilChunkGen> ChunkGen;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<TileID::TileManager> tileManager;

    int currentWorldSize;

    void mapCreateStartingChunks(int worldsize);

    //takes a xy position in the world and returns
    //the chunk x and chunk y in an olc::vi2d
    olc::vi2d worldPosToChunkXY(olc::vi2d worldPos);

    //takes in the id xy of a chunk and returns position in vptrActiveChunks
    int returnVIndexOfChunk(olc::vi2d XY);
    bool vi2dInVector(std::vector<olc::vi2d> vect, olc::vi2d check);
public:
	//
	// create get functions to protect chunks
	//
	std::vector<std::shared_ptr<cChunk>> vptrActiveChunks;
	bool mapLoaded = false;
	int activeZLayer;
	olc::vi2d moveViewOffset = { 0,0 };
	//
	//All of these should be protected
	//
	Maps() {};
	int getWorldSize() {return currentWorldSize;}
	void changeZLayer(int i);
    //   Size of Texture pack,       Top left x,y of map,    Bottom Right of map,      pixel game engine
	Maps(std::shared_ptr<AKI::GraphicsEngine> ge,std::shared_ptr<AKI::GameConfig> gc);
	void DrawActiveChunks();
	void changeMapViewOffset(olc::vi2d i);
	void resetMapViewOffset() { moveViewOffset = { 0,0 }; };
	//this is just a debug function currently to interact with maps for saving
    void flipTileOnMap(olc::vi2d& insplocXY);
    void newMap(int atStartWorldSize);
    void continueMap(int chunkNum,int worldSize, std::vector<uint64_t> newChunk);


	std::vector<int> getSlabsInView(AKI::I3d pos,int viewDistance) {return getInViewBool(pos,viewDistance,true,false);}
	std::vector<int> getInfillInView(AKI::I3d pos,int viewDistance){return getInViewBool(pos,viewDistance,false,true);}

private:
	std::vector<int> getInViewBool(AKI::I3d pos, int viewDistance, bool bSlabs, bool bInfill);
};

