#pragma once
#include "olcPixelGameEngine.h"
#include "mapFunctions/cChunk.h"
//#include "memory"


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

    //This is fixed Do not change
    int chunkSize = 16;
	


    void mapCreateStartingChunks(int worldsize);
    void makeNewChunk(olc::vi2d newChunkLocation);
    //used for the creation of a new chunk.
    uint64_t olcTo64Hex (olc::vi2d olcvi2d);
public:

    std::vector<std::unique_ptr<cChunk>> vptrActiveChunks;

	Maps() {};
	bool mapLoaded = false;
	int activeZLayer;
	olc::vi2d moveViewOffset = { 0,0 };
	

	void changeZLayer(int i);
    //   Size of Texture pack,       Top left x,y of map,    Bottom Right of map,      pixel game engine
    Maps(olc::vi2d& packSizeAtStart, olc::vi2d& atStartMapTL, olc::vi2d& atStartMapBR, olc::PixelGameEngine* p);
	void DrawActiveChunks();
	void changeMapViewOffset(olc::vi2d i);
	void resetMapViewOffset() { moveViewOffset = { 0,0 }; };
    void flipTileOnMap(olc::vi2d& insplocXY);
    void newMap(int atStartWorldSize);
    void continueMap(int chunkNum,int worldSize, std::vector<uint64_t> newChunk);

};

