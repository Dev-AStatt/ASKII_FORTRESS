#pragma once
#include "MapUtilTileIDList.h"
#include "ChunkDataStruct.h"
#include "cChunk.h"


class MapUtilChunkGen {
private:

	//the two of these are needed to give to cChunk
	std::shared_ptr<AKI::GraphicsEngine>	graphicsEngine;
	std::shared_ptr<AKI::GameConfig>		gameConfig;
	std::shared_ptr<Tiles::TileManager>	tileManager;

	ChunkDataStruct newChunkStruct;
	std::vector<std::shared_ptr<cChunk>> vptrActiveChunks;

	//Creates stone from z[0] to z[10] then a dirt island.
	void CreateDebugWorld() {
		for (int z = 0; z < 11; ++z) {
			//FillChunkZLayer(z, TileID::Stone);
			newChunkStruct.fillZLayerBlocks(z,Tiles::Stone);
		}

		newChunkStruct.fillXColBlocks(11,0,Tiles::Dirt);
		newChunkStruct.fillXColBlocks(11,1,Tiles::Dirt);
		newChunkStruct.fillXColSlabs(12,0,Tiles::Grass);
		newChunkStruct.fillXColSlabs(12,1,Tiles::Grass);
		newChunkStruct.fillXColBlocks(11,2,Tiles::SlopeSouth);
		for(int i = 3; i <= 12; ++i) {
			newChunkStruct.fillXColSlabs(11,i,Tiles::Grass);
		}
		newChunkStruct.fillXColBlocks(11,13,Tiles::SlopeNorth);
		newChunkStruct.fillXColBlocks(11,14,Tiles::Dirt);
		newChunkStruct.fillXColBlocks(11,15,Tiles::Dirt);
		newChunkStruct.fillXColSlabs(12,14,Tiles::Grass);
		newChunkStruct.fillXColSlabs(12,15,Tiles::Grass);

		newChunkStruct.fillSingleSlab(12,2,15, Tiles::Water);
		newChunkStruct.fillSingleSlab(12,3,15, Tiles::Water);
		newChunkStruct.fillSingleSlab(12,2,0, Tiles::Water);
		newChunkStruct.fillSingleSlab(12,3,0, Tiles::Water);


		newChunkStruct.fillSingleSlab(11,2,8, Tiles::Water);
		//newChunkStruct.fillSingleSlab(11,3,14, TileID::Water);

		//newChunkStruct.fillSingleSlab(11,idxy.y+1,idxy.x+1, TileID::Water);

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

	uint64_t olcTo64Hex (olc::vi2d olcvi2d) {
		uint64_t bitshiftedIDtmp = (uint64_t)olcvi2d.y;
		uint64_t olcTo64Hex = bitshiftedIDtmp << 32;
		olcTo64Hex = olcTo64Hex + olcvi2d.x;
		return olcTo64Hex;
	}

public:
	MapUtilChunkGen(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc, std::shared_ptr<Tiles::TileManager> tm) {
		graphicsEngine = ge;
		gameConfig = gc;
		tileManager = tm;

	}
	//returns a referance to the chunk created here. to be
	ChunkDataStruct& GenerateChunkStruct() {
		CreateDebugWorld();
		return newChunkStruct;
	}

	std::vector<std::shared_ptr<cChunk>>& makeWorld(int worldsize) {
		//
		//Chunks in x---->
		//          y
		//          |
		//          V

		for (int x = 0; x < worldsize; ++x) {
			for (int y = 0; y < worldsize; ++y) {
				//compress the xy world position to a uint64 to be used as a chunk ID/chunk location
				uint64_t locationHex = olcTo64Hex({x,y});
				vptrActiveChunks.emplace_back(std::make_shared<cChunk>(locationHex,GenerateChunkStruct(),
																	   gameConfig,graphicsEngine,tileManager));
			}
		}
		return vptrActiveChunks;
	}


};




