#pragma once
#include "MapUtilTileIDList.h"
#include <vector>
#include <cstdint> // include this header for uint64_t

///
/// Chunk Orgonization. Vector <z> Vector <Y> = 0xFF for X
/// Y is a 31 entery vector as it holds Y1.0 for x0 -> x7, and Y1.5 for x8-x15 
/// Y even numbers hold comumn numbers and odd are second set of x's for evens
/// 


class MapUtilChunkGen {


private:
	//new chunk that is 16x33 of 0's
	std::vector<uint64_t> newChunk = std::vector<uint64_t>(511, 0);
	//Temporary or Maluable Values
	uint64_t unitTileId = 0;
	int bitshift = 0;
	//bitshiftedIDtmp is used to hold the bitshifted value
	uint64_t bitshiftedIDtmp = 0;


	int vectorID(int z, int y) { return (z * 32 + y); };
public:
	//
	//Generates a new chunk and returns hard copy. 
	//
	std::vector<uint64_t> GenerateChunk();

    //
    //Takes the input of a already created chunk and will fill the single tile with a new tile
    //
    std::vector<uint64_t> editchunkSingleTile(std::vector<uint64_t> activeChunk, int x, int y, int z, TileID::TileIDList newTile);

	//
	// FillChunkZLayer will take a Z layer value and a tile id and
	// fill that layer with all tiles of that ID
	//
	void FillChunkZLayer(int zLayerToFill, int tileID);
	//
	//Function takes Z, y, x coordinate and changes tile at single location.
	//
	void FillSingleTile(int zLayer, int yCol, int xRow, int tileID);
	//
	//Function to fill an X row with a single tile type. 
	//zLayerToFill is the z layer of chunk, yColToFil is the litteral Y value of the column [0-15].
	//function will do both y0 and y1 for the whole 128 bit row. 
	// 	   Ex: yColToFill = 1. will fill y[2] and y[3].
	//
	void FillChunkXRow(int zLayer, int yColToFill, int tileIDToFill);

	//More Inifficient version of Fill Chunk XRow. Same thing for Y
	void FillChunkYCol(int zLayer, int xRowToFill, int tileIDToFill);

	//Creates stone from z[0] to z[10] then a dirt island.
	void CreateFlatWorld();


};
