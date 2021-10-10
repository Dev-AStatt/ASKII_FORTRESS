#pragma once
#include "Tiles.h"
#include "MapUtilChunkGen.h"
#include <vector>
#include <memory>


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
	

	std::vector<uint64_t> vChunk = std::vector<uint64_t>(511,0);
	std::vector<std::unique_ptr<Tile>> vptrTiles;


    MapUtilChunkGen MUCG;


	olc::vi2d PACK_SIZE;
    olc::vi2d mapTL; //map area Top Left
    olc::vi2d mapBR; //map area bottom right
	olc::vi2d vTileFinalPosition;
	olc::PixelGameEngine* pge;

    //loads typical data that is needed no mater how class is created
    void loadTypicalData(olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p, uint64_t id);

    void fillvptrTiles();
    //VectorID takes in the z and y coordinate that is understood
	//for a 3d object and translates that into the 1d Vector
	int vectorID(int z, int y) { return (z * 32 + y); };
	//returns the int of MapUtilTileIDList enum for the tile at
	//location z,y,x
	int TileIDAtLocation(int zLayer, int yCol, int xRow);
	//void takes the chunk ID passed into the constructor
	//and translates that into the chunks global y,x position.
	void decryptIDtoYX();
	//takes input of new tile position and checks to see if it
	//is contained in the window. false if it lays outside map view.
	bool checkIfOnScreen(olc::vi2d& newPos);
public:
    //Creating New Chunk, will call chunk generator for new
    cChunk(olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p, uint64_t id);
    //Will load passed in chunk by being given tileset
    cChunk(olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p, uint64_t id, std::vector<uint64_t> chunkToLoad);
	void DrawChunk(int zLayer, olc::vi2d& moveViewOffset);
	//Returns the pointer of the tile at location z, olc(y,x)
	std::unique_ptr<Tile>& TilePtrAtLocation(int zLayer, olc::vi2d yx);
    long returnChunkPosX() {return chunkPositionX;};
    long returnChunkPosY() {return chunkPositionY;};
    //takes input of tile and position and edits the chunk
    void tileReplacement(TileID::TileIDList newTile, int x, int y, int z);
    std::string compileChunkToString(int i);

};

