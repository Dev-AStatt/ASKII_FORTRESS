#pragma once
#include "MapUtilTileIDList.h"
#include "ChunkDataStruct.h"


class MapUtilChunkGen {
private:

	ChunkDataStruct newChunkStruct;

	//Creates stone from z[0] to z[10] then a dirt island.
	void CreateFlatWorld();


public:

	//
	//Generates a new chunk and returns hard copy.
	//
	ChunkDataStruct GenerateChunkStruct();


};
