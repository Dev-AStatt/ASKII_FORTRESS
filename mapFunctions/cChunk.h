#pragma once
#include "MapUtilTileIDList.h"
#include "ChunkDataStruct.h"

class cChunk {
private:
	///
	///  Chunk ID's are orgonized as such.
	/// 0x0000000200000001
	///   [  y   ][   x  ] of global chunk position.
	///
	uint64_t ChunkID;
	long chunkPositionY;
	long chunkPositionX;
	
//
//	Chunks are going to be made of two identifieers for each "Block"
//	There is the slab, which is what is walked on, and the fill that
//	is the infill of stuff that fills the space between slabs.
//
	ChunkDataStruct FullChunkIDs;
	std::vector<std::unique_ptr<Tile>> vptrTiles;

	std::shared_ptr<TileID::TileManager> tileManager;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

	olc::vi2d vTileFinalPosition;

	//void takes the chunk ID passed into the constructor
	//and translates that into the chunks global y,x position.
	void decryptIDtoYX();
	//takes input of new tile position and checks to see if it
	//is contained in the window. false if it lays outside map view.
	bool checkIfOnScreen(olc::vi2d& newPos);
public:
    //Creating New Chunk, will call chunk generator for new
	cChunk(uint64_t id, ChunkDataStruct &passedInChunk, std::shared_ptr<AKI::GameConfig> gconf,
		   std::shared_ptr<AKI::GraphicsEngine> graph, std::shared_ptr<TileID::TileManager> tm);


	~cChunk() {}

	//Return functions for fetching class data
	long getChunkPosX() {return chunkPositionX;};
	long getChunkPosY() {return chunkPositionY;};
	//returns the int of MapUtilTileIDList enum for the tile at
	//location z,y,x
	int getSlabIDAt(  AKI::I3d pos) {return getSlabIDAt(  pos.z,pos.y,pos.x);}
	int getInfillIDAt(AKI::I3d pos) {return getInfillIDAt(pos.z,pos.y,pos.x);}
	AKI::Block getBlockIDAt(AKI::I3d pos) {
		return {getSlabIDAt(pos.z,pos.y,pos.x),getInfillIDAt(pos.z,pos.y,pos.x)};
	}
	int getSlabIDAt(int zLayer, int yRow, int xCol);
	int getInfillIDAt(int zLayer, int yRow, int xCol);

	void DrawChunk(int zLayer, olc::vi2d& moveViewOffset);

	//takes input of tile and position and edits the chunk slab
	void SlabReplacement(TileID::TileIDList newTile, int x, int y, int z);
	//takes input of tile and position and edits the chunk Infill
	void InfillReplacement(TileID::TileIDList newTile, int x, int y, int z);
    std::string compileChunkToString(int i);



	//function will check to make sure input values are within the
	//real values that can be used.
	bool withinChunk(AKI::I3d pos) {return withinChunk(pos.z,pos.y,pos.z);}
	bool withinChunk(int z, int y = 0, int x = 0) {
		if(z < 0 || z > 15) { return false; }
		if(y < 0 || y > 15) { return false; }
		if(x < 0 || x > 15) { return false; }
		return true;
	}

};

