#pragma once
#include <cstdint> // include this header for uint64_t
#include <vector>

//	may god help you, AS Oct 29th 2021

struct ChunkDataStruct {
	std::vector<uint64_t> slabs = std::vector<uint64_t>(511,0);
	std::vector<uint64_t> infill = std::vector<uint64_t>(511,0);

	/*
	 * Ok, so data is structured in an odd way but it helps to reduce the memory load of the chunk.
	 * What happens is there is a vector that holds 64 bit compilations of ID's 0xFF
	 *
	 * The chunk is 16 * 33, or think of it as 16 <z> * (2 <y>), so there are 2 Y's for every
	 * row of Y's.
	 * If Y is even it holds the row number and if
	 *
	 *
	 * Z[0] starts at the bottom of the world and [X,Y] is in the top left corner.
	 *
	 *
	 *	Y1.0 for x0 -> x7, and Y1.5 for x8-x15
	 *		x------------------------>
	 *		y1.0		y1.5
	 *		|			|
	 *		V			V
	 *
	 *	ANY USE OF THE WORD BLOCK
	 *	stands for the infill and slab as one unit. normally used for filling both
	 *	at the same time.
	 */


	//will return the intager id of tile at the location specified
	int slabIDAt(int z, int y, int x) {
		//calculate the bitshifting needed to move x to LSB
		int bitshift = 56 - (x * 8);

		bitshiftedIDtmp = slabs[vectorID(z,y,x)] >> bitshift;
		bitshiftedIDtmp &= extractor;
		//if the above line creats an error in shifting bits. the below line was
		//what was there origninally. I think it means the same thing.
		//bitshiftedIDtmp = bitshiftedIDtmp &= extractor;
		return (int)bitshiftedIDtmp;
	}
	//will return the intager id of tile at the location specified
	int infillIDAt(int z, int y, int x) {
		//calculate the bitshifting needed to move x to LSB
		int bitshift = 56 - (x * 8);

		bitshiftedIDtmp = infill[vectorID(z,y,x)] >> bitshift;
		bitshiftedIDtmp &= extractor;
		//if the above line creats an error in shifting bits. the below line was
		//what was there origninally. I think it means the same thing.
		//bitshiftedIDtmp = bitshiftedIDtmp &= extractor;
		return (int)bitshiftedIDtmp;
	}


	//BLOCK stands for both the slab and infill of one unit x,y,z.
	//these will each call the same fill single OR,
	//fill single OR handles filling single tiles will inputs t/f of if
	//infill and/or slabs should be filled with tileID
	void fillSingleBlock(int z, int y, int x, int tileID) { fillSingleOR(z,y,x,tileID,true,true); }
	void fillSingleSlab(int z, int y, int x, int tileID)  {	fillSingleOR(z,y,x,tileID,true,false);}
	void fillSingleinfill(int z, int y, int x, int tileID){	fillSingleOR(z,y,x,tileID,false,true);}

	/*
	*	Function to fill a row of X tiles in a y row with a single tile type.
	*	for both slabs and infill.
	*	z is the z layer of chunk,
	*	yRowToFill is the litteral Y value of the column [0-15].
	*	function will do both y0 and y1 for the whole 128 bit row.
	* 	Ex: yRowToFill = 1. will fill y[2] and y[3].
	*/
	void fillYRowBlocks(int z, int yRowToFill, int tileID) {
		yRowToFill = yRowToFill * 2;
		//Convert int to 64 bit unsigned to be used for bitwise opperations.
		unitTileId = tileID;

		int vID; //this will be used in the loop alot so decalring it before.

		//Run for both Y holding one row. [y0] = x0 -> x7, [y1] for x8-x15
		for (int y = yRowToFill; y <= yRowToFill + 1; ++y) {
			//get vector position to modify, or really the vector of the yRow to modify
			vID = z * 32 + y;

			//Because we are changing the whole row we can start with 0.
			slabs[vID]	= 0x0;
			infill[vID] = 0x0;

			//For each x in a row of Y1.0
			for (int x = 0; x < 8; ++x) {
				//start at the leftmost bit x0
				bitshift = 56 - (x * 8);
				//Bitshift the tile number to position of tile in mem so we can OR
				bitshiftedIDtmp = unitTileId << bitshift;
				//OR bits of tile ID into correct tile position.
				slabs[vID]	|= bitshiftedIDtmp;
				infill[vID] |= bitshiftedIDtmp;
			}
		}
	}

	/*
	*	Function to fill a column of X with a single Tile on a single z plane.
	*	for both slabs and infill.
	*	z is the z layer of chunk,
	*/
	void fillXColumn(int z, int xColToFill, int tileID) {
		for (int y = 0; y < 16; ++y) {
			fillSingleBlock(z, y, xColToFill, tileID);
		}
	}
	//this will take in a z layer and fill the entier layer with
	//a single tile passed in.
	void fillZLayer(int z, int tileID) {
		for (int y = 0; y < 16; ++y) {
			fillYRowBlocks(z,y,tileID);
		}
	}


private:
	//these are declared here cuz they are used alot in the functions
	int bitshift = 0;
	uint64_t unitTileId = 0;
	uint64_t extractor = 0xFF;
	uint64_t bitshiftedIDtmp;

	//VectorID takes in the z and y coordinate and returns the ID location
	//of the slab or infill vector that x resides in.
	int vectorID(int z, int y, int x) {
		//this checks to see if x is in the even or odd y value pair, Y1.0 or Y1.5
		if (x < 8) { y = y * 2; };
		if (x > 7) { y = (y * 2) + 1; };

		return (z * 32 + y);
	}


	void fillSingleOR(int z, int y, int x, int tileID, bool fillSlab, bool fillInfill) {
		//Convert int to 64 bit unsigned to be used for bitwise opperations.
		unitTileId = tileID;

		bitshift = 56 - (x * 8);
		//bitshiftedIDtmp is used to hold the bitshifted value
		//Bitshift the tile number to position of tile in mem so we can OR
		bitshiftedIDtmp = unitTileId << bitshift;


		//get vector position to modify, or really the vector of the yRow to modify
		int vectID = vectorID(z,y,x);

		//Clear the single tile before writing to it.
		for (int n = bitshift; n < 4 + bitshift; ++n) {

			// if slab is to be filled, for each 4 bits in tile ID clear each bit
			if(fillSlab)	{ slabs[vectID]		&= ~(1ULL << n); }
			// if infill is to be filled, for each 4 bits in tile ID clear each bit
			if(fillInfill)	{ infill[vectID]	&= ~(1ULL << n); }
		}
		//OR bits of tile ID into correct tile position.
		if(fillSlab)	{ slabs[vectID]	|= bitshiftedIDtmp; }
		if(fillInfill)	{ infill[vectID]|= bitshiftedIDtmp; }
	}

};
