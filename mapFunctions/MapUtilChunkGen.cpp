#include "MapUtilChunkGen.h"


ChunkDataStruct MapUtilChunkGen::GenerateChunkStruct() {
	CreateFlatWorld();
	return newChunkStruct;
}


void MapUtilChunkGen::CreateFlatWorld() {
	for (int z = 0; z < 11; ++z) {
		//FillChunkZLayer(z, TileID::Stone);
		newChunkStruct.fillZLayerBlocks(z,TileID::Stone);
	}
	newChunkStruct.fillZLayerSlabs(11,TileID::Grass);
	newChunkStruct.fillXColSlabs(11,0,TileID::Water);
	newChunkStruct.fillXColSlabs(11,15,TileID::Water);
	newChunkStruct.fillYRowSlabs(11,0,TileID::Water);
	newChunkStruct.fillYRowSlabs(11,15,TileID::Water);

}


