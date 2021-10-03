#pragma once
#include "olcPixelGameEngine.h"
#include "cChunk.h"


//
//This is a class that is designed to hold pointers to each chunk in the map.
//Should be built to include all edits to maps as well.
//Handles drawing of the map too for now. but may be needed to move to game engine.
//
class Maps {
private:
	std::vector<std::unique_ptr<cChunk>> vptrActiveChunks;
	
	olc::vi2d PACK_SIZE;
    olc::vi2d mapTL;
    olc::vi2d mapBR;
	olc::PixelGameEngine* pge;

    //This is fixed Do not change
    int chunkSize = 16;
	


	void mapCreateStartingChunks();
public:
	Maps() {};
	bool mapLoaded = false;
	int activeZLayer;
	olc::vi2d moveViewOffset = { 0,0 };
	

	void changeZLayer(int i);
    Maps(olc::vi2d& packSizeAtStart, olc::vi2d& atStartMapTL, olc::vi2d& atStartMapBR, olc::PixelGameEngine* p);
	void DrawActiveChunks();
	void changeMapViewOffset(olc::vi2d i);
	void resetMapViewOffset() { moveViewOffset = { 0,0 }; };
    void flipTileOnMap(olc::vi2d& insplocXY);


};

