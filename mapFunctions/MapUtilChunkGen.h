#pragma once
#include "MapUtilTileIDList.h"
#include "ChunkDataStruct.h"


class MapUtilChunkGen {
private:

	ChunkDataStruct newChunkStruct;

	//Creates stone from z[0] to z[10] then a dirt island.
	void CreateFlatWorld(olc::vi2d idxy) {
		for (int z = 0; z < 11; ++z) {
			//FillChunkZLayer(z, TileID::Stone);
			newChunkStruct.fillZLayerBlocks(z,TileID::Stone);
		}
		newChunkStruct.fillZLayerSlabs(11,TileID::Grass);
		newChunkStruct.fillXColSlabs(11,0,TileID::Water);
		newChunkStruct.fillXColSlabs(11,15,TileID::Water);
		newChunkStruct.fillYRowSlabs(11,0,TileID::Water);
		newChunkStruct.fillYRowSlabs(11,15,TileID::Water);
		newChunkStruct.fillSingleSlab(11,idxy.y+1,idxy.x+1, TileID::Dirt);

	}
	olc::vi2d decryptIDtoXY(u_int64_t ChunkID) {
		//shift bits right until just MSB 8 are left
		uint64_t bitshiftedIDtmp = ChunkID >> 32;
		olc::vi2d tmp;
		tmp.y = (int)bitshiftedIDtmp;
		//and with FF to remove all MSB8 and leave LSB
		bitshiftedIDtmp = 0x00000000FFFFFFFF;
		tmp.x = (int)(ChunkID &= bitshiftedIDtmp);
		return tmp;
	}


public:

	ChunkDataStruct& GenerateChunkStruct(uint64_t chunkid) {
		CreateFlatWorld(decryptIDtoXY(chunkid));
		return newChunkStruct;
	}


};




