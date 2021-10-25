#pragma once
#include "libraries/olcPixelGameEngine.h"
#include "mapFunctions/cChunk.h"
#include "mapFunctions/MapUtilChunkGen.h"
#include "TileFunctions/Tiles.h"
#include "MapUtil_I3d.h"



//
//This is a class that is designed to hold pointers to each chunk in the map.
//Should be built to include all edits to maps as well.
//Handles drawing of the map too for now. but may be needed to move to game engine.
//
class Maps {
private:

	
	olc::vi2d PACK_SIZE;
    olc::vi2d mapTL;
    olc::vi2d mapBR;
	olc::PixelGameEngine* pge;
	std::shared_ptr<MapUtilChunkGen> ChunkGen;

    //This is fixed Do not change
    int chunkSize = 16;
    int currentWorldSize;
	


    void mapCreateStartingChunks(int worldsize);
    void makeNewChunk(olc::vi2d newChunkLocation);
    //used for the creation of a new chunk.
    uint64_t olcTo64Hex (olc::vi2d olcvi2d);
    //takes a xy position in the world and returns
    //the chunk x and chunk y in an olc::vi2d
    olc::vi2d worldPosToChunkXY(olc::vi2d worldPos);

    //takes in the id xy of a chunk and returns position in vptrActiveChunks
    int returnVIndexOfChunk(olc::vi2d XY);
    bool vi2dInVector(std::vector<olc::vi2d> vect, olc::vi2d check);
public:
	//
	//Convert this to shared pointers and create get functions to protect chunks
	//
    std::vector<std::unique_ptr<cChunk>> vptrActiveChunks;
	bool mapLoaded = false;
	int activeZLayer;
	olc::vi2d moveViewOffset = { 0,0 };
	//
	//All of these should be protected
	//


	Maps() {};
	void changeZLayer(int i);
    //   Size of Texture pack,       Top left x,y of map,    Bottom Right of map,      pixel game engine
    Maps(olc::vi2d& packSizeAtStart, olc::vi2d& atStartMapTL, olc::vi2d& atStartMapBR, olc::PixelGameEngine* p);
	void DrawActiveChunks();
	void changeMapViewOffset(olc::vi2d i);
	void resetMapViewOffset() { moveViewOffset = { 0,0 }; };
	//this is just a debug function currently to interact with maps for saving
    void flipTileOnMap(olc::vi2d& insplocXY);
    void newMap(int atStartWorldSize);
    void continueMap(int chunkNum,int worldSize, std::vector<uint64_t> newChunk);

	std::vector<int> viewOfWorld(AKI::I3d pos,int viewDistance);
};

