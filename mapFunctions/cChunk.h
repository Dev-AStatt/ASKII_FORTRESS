#pragma once
#include "MapUtilTileIDList.h"
#include "MapUtilChunkGen.h"
#include "ChunkDataStruct.h"

class cChunk {
private:
	///
	///  Chunk ID's are orgonized as such.
	/// 0x0000000200000001
	///   [  y   ][   x  ] of global chunk position.
	///
	uint64_t ChunkID;
	uint64_t extractor = 0xFF;
	uint64_t bitshiftedIDtmp;
	long chunkPositionY;
	long chunkPositionX;
	
//
//	Chunks are going to be made of two identifieers for each "Block"
//	There is the slab, which is what is walked on, and the fill that
//	is the infill of stuff that fills the space between slabs.
//
	ChunkDataStruct FullChunkIDs;
	std::vector<std::unique_ptr<Tile>> vptrTiles;
	std::shared_ptr<MapUtilChunkGen> ChunkGen;
	//olc::PixelGameEngine* pge;
	std::shared_ptr<TileID::TileManager> tileManager;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

//    olc::vi2d mapTL; //map area Top Left
//    olc::vi2d mapBR; //map area bottom right
	olc::vi2d vTileFinalPosition;


    //loads typical data that is needed no mater how class is created
	void loadTypicalData(uint64_t id, std::shared_ptr<MapUtilChunkGen> gen,
						 std::shared_ptr<AKI::GameConfig> gconf,
						 std::shared_ptr<AKI::GraphicsEngine> graph,
						 std::shared_ptr<TileID::TileManager> tm);
    //VectorID takes in the z and y coordinate that is understood
	//for a 3d object and translates that into the 1d Vector
	int vectorID(int z, int y) { return (z * 32 + y); };

	//void takes the chunk ID passed into the constructor
	//and translates that into the chunks global y,x position.
	void decryptIDtoYX();
	//takes input of new tile position and checks to see if it
	//is contained in the window. false if it lays outside map view.
	bool checkIfOnScreen(olc::vi2d& newPos);
public:
	//Return functions for fetching class data
	long getChunkPosX() {return chunkPositionX;};
	long getChunkPosY() {return chunkPositionY;};

    //Creating New Chunk, will call chunk generator for new
	cChunk(uint64_t id,std::shared_ptr<MapUtilChunkGen> gen,
		   std::shared_ptr<AKI::GameConfig> gconf, std::shared_ptr<AKI::GraphicsEngine> graph,
		   std::shared_ptr<TileID::TileManager> tm);
    //Will load passed in chunk by being given tileset

	cChunk(uint64_t id, std::vector<uint64_t> chunkToLoad, std::shared_ptr<MapUtilChunkGen> gen,
		   std::shared_ptr<AKI::GameConfig> gconf, std::shared_ptr<AKI::GraphicsEngine> graph,
		   std::shared_ptr<TileID::TileManager> tm);
	void DrawChunk(int zLayer, olc::vi2d& moveViewOffset);
	//Returns the pointer of the Slab at location z, olc(y,x)
	std::unique_ptr<Tile>& SlabPtrAtLocation(int zLayer, olc::vi2d yx);
	//Returns the pointer of the Infill at location z, olc(y,x)
	std::unique_ptr<Tile>& InfillPtrAtLocation(int zLayer, olc::vi2d yx);
	//takes input of tile and position and edits the chunk slab
	void SlabReplacement(TileID::TileIDList newTile, int x, int y, int z);
	//takes input of tile and position and edits the chunk Infill
	void InfillReplacement(TileID::TileIDList newTile, int x, int y, int z);
    std::string compileChunkToString(int i);
    //returns the int of MapUtilTileIDList enum for the tile at
    //location z,y,x
	int SlabIDAtLocation(int zLayer, int yCol, int xRow);
	int InfillIDAtLocation(int zLayer, int yCol, int xRow);

};

