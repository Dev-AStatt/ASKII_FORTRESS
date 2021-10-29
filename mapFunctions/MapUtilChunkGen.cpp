#include "MapUtilChunkGen.h"


ChunkDataStruct MapUtilChunkGen::GenerateChunkStruct() {
	CreateFlatWorld();
	return newChunkStruct;
}


void MapUtilChunkGen::CreateFlatWorld() {
	for (int z = 0; z < 11; ++z) {
		//FillChunkZLayer(z, TileID::Stone);
		newChunkStruct.fillZLayer(z,TileID::Stone);
	}
	newChunkStruct.fillZLayer(11,TileID::Grass);
	newChunkStruct.fillXColumn(11,0,TileID::Water);
	newChunkStruct.fillXColumn(11,15,TileID::Water);
	newChunkStruct.fillYRowBlocks(11,0,TileID::Water);
	newChunkStruct.fillYRowBlocks(11,15,TileID::Water);

}


