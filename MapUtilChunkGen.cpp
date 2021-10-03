#include "MapUtilChunkGen.h"
//
//Generates a new chunk and returns hard copy. 
//
std::vector<uint64_t> MapUtilChunkGen::GenerateChunk() {

	CreateFlatWorld();

	return newChunk;
}

//
//Takes the input of a already created chunk and will fill the single tile with a new tile
//
std::vector<uint64_t> MapUtilChunkGen::editchunkSingleTile(std::vector<uint64_t> activeChunk, int x, int y, int z, TileID::TileIDList newTile) {
    newChunk = activeChunk;

    FillSingleTile(z,y,x,newTile);

    return newChunk;
}





//
// FillChunkZLayer will take a Z layer value and a tile id and
// fill that layer with all tiles of that ID
//
void MapUtilChunkGen::FillChunkZLayer(int zLayerToFill, int tileID) {

	for (int yCol = 0; yCol < 16; ++yCol) {
		FillChunkXRow(zLayerToFill, yCol, tileID);
	}

}
//
//Function takes Z, y, x coordinate and changes tile at single location.
//
void MapUtilChunkGen::FillSingleTile(int zLayer, int yCol, int xRow, int tileID) {
	if (xRow < 8) { yCol = yCol * 2; };
	if (xRow > 7) { yCol = (yCol * 2) + 1; };

	//Convert int to 64 bit unsigned to be used for bitwise opperations.
	unitTileId = tileID;

	bitshift = 56 - (xRow * 8);
	//bitshiftedIDtmp is used to hold the bitshifted value
	//Bitshift the tile number to position of tile in mem so we can OR
	bitshiftedIDtmp = unitTileId << bitshift;

	//Clear the single tile before writing to it. 
	for (int n = bitshift; n < 4 + bitshift; ++n) {
		//for each 4 bits in tile ID clear each bit
		newChunk[vectorID(zLayer,yCol)] &= ~(1ULL << n);
	}

	//OR bits of tile ID into correct tile position. 
	newChunk[vectorID(zLayer, yCol)] |= bitshiftedIDtmp;
}



//
//Function to fill an X row with a single tile type. 
//zLayerToFill is the z layer of chunk, yColToFil is the litteral Y value of the column [0-15].
//function will do both y0 and y1 for the whole 128 bit row. 
// 	   Ex: yColToFill = 1. will fill y[2] and y[3].
//
void MapUtilChunkGen::FillChunkXRow(int zLayer, int yColToFill, int tileIDToFill) {

	yColToFill = yColToFill * 2;
	//Convert int to 64 bit unsigned to be used for bitwise opperations.
	unitTileId = tileIDToFill;
	
	//Run for both Y holding one row. [y0] = x0 -> x7, [y1] for x8-x15
	for (int y = yColToFill; y < yColToFill + 2; ++y) {
		//Because we are changing the whole row we can start with 0. 
		newChunk[vectorID(zLayer, y)] = 0x0;
		//For each x in a row of Y1.0
		for (int x = 0; x < 8; ++x) {
			//start at the leftmost bit x0 
			bitshift = 56 - (x * 8);
			//Bitshift the tile number to position of tile in mem so we can OR
			bitshiftedIDtmp = unitTileId << bitshift;
			//OR bits of tile ID into correct tile position. 
			newChunk[vectorID(zLayer, y)] |= bitshiftedIDtmp;
		}
	}

}

void MapUtilChunkGen::FillChunkYCol(int zLayer, int xRowToFill, int tileIDToFill) {
	for (int y = 0; y < 16; ++y) {
		FillSingleTile(zLayer, y, xRowToFill, tileIDToFill);
	}
}


void MapUtilChunkGen::CreateFlatWorld() {
	for (int z = 0; z < 11; ++z) {
		FillChunkZLayer(z, TileID::Stone);
	}
	FillChunkZLayer(11, TileID::Grass);
	FillChunkXRow(11, 0, TileID::Water);
	FillChunkXRow(11, 15, TileID::Water);
	FillChunkYCol(11,0, TileID::Water);
	FillChunkYCol(11,15,TileID::Water);
	
}
