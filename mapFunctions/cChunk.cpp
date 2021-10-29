#include "cChunk.h"


cChunk::cChunk(uint64_t id, std::shared_ptr<MapUtilChunkGen> gen,
			   std::shared_ptr<AKI::GameConfig> gconf, std::shared_ptr<AKI::GraphicsEngine> graph,std::shared_ptr<TileID::TileManager> tm) {

	loadTypicalData(id,gen,gconf,graph,tm);
	FullChunkIDs = ChunkGen->GenerateChunkStruct();

}

cChunk::cChunk(uint64_t id, std::vector<uint64_t> chunkToLoad, std::shared_ptr<MapUtilChunkGen> gen,
			   std::shared_ptr<AKI::GameConfig> gconf, std::shared_ptr<AKI::GraphicsEngine> graph,
			   std::shared_ptr<TileID::TileManager> tm) {
	loadTypicalData(id,gen,gconf,graph,tm);
    FullChunkIDs.slabs = chunkToLoad;
}

//Stuff that needs to be loaded if a new chunk or a loaded chunk is made
void cChunk::loadTypicalData(uint64_t id, std::shared_ptr<MapUtilChunkGen> cg,
							 std::shared_ptr<AKI::GameConfig> gc,
							 std::shared_ptr<AKI::GraphicsEngine> ge,
							 std::shared_ptr<TileID::TileManager> tm) {
	ChunkID = id;
	gameConfig = gc;
	graphicsEngine = ge;
	tileManager = tm;
	ChunkGen = cg;
	decryptIDtoYX();
}


//Takes in the z,y,x coordinates of a tile and returns the TileID
int cChunk::SlabIDAtLocation(int zLayer, int yRow, int xCol) {
	return FullChunkIDs.getSlabIDAt(zLayer,yRow,xCol);
}

//Takes in the z,y,x coordinates of a tile and returns the TileID
int cChunk::InfillIDAtLocation(int zLayer, int yRow, int xCol) {
	return FullChunkIDs.getInfillIDAt(zLayer,yRow,xCol);
}

//returns a pointer to a tile that is at the location of z, vi2d(yx)
std::unique_ptr<Tile>& cChunk::SlabPtrAtLocation(int zLayer, olc::vi2d yx) {
	//call TileIDAtLoc and return a pointer at that loc
	std::unique_ptr<Tile>& t = tileManager->vptrTiles[SlabIDAtLocation(zLayer, yx.y, yx.x)];
	return t;

}

//returns a pointer to a tile that is at the location of z, vi2d(yx)
std::unique_ptr<Tile>& cChunk::InfillPtrAtLocation(int zLayer, olc::vi2d yx) {
	//call TileIDAtLoc and return a pointer at that loc
	std::unique_ptr<Tile>& t = tileManager->vptrTiles[InfillIDAtLocation(zLayer, yx.y, yx.x)];
	return t;

}

void cChunk::decryptIDtoYX() {
	//shift bits right until just MSB 8 are left
	bitshiftedIDtmp = ChunkID >> 32;
	chunkPositionY = (long)bitshiftedIDtmp;
	//and with FF to remove all MSB8 and leave LSB
	bitshiftedIDtmp = 0x00000000FFFFFFFF;
	chunkPositionX = (long)(ChunkID &= bitshiftedIDtmp);
}


void cChunk::DrawChunk(int zLayer, olc::vi2d& moveViewOffset) {
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			auto& t = tileManager->vptrTiles[SlabIDAtLocation(zLayer, y, x)];
			if (t) {							//the + 1 on the X, Y is to add space for the header
				vTileFinalPosition = {x + (int)(chunkPositionX * 16) + 1 + moveViewOffset.x,(y + (int)(chunkPositionY * 16) + 1) + moveViewOffset.y };
				//make sure adjusted position is on screen
				if (checkIfOnScreen(vTileFinalPosition)) {
					t->DrawSelf(vTileFinalPosition);
				}
			}
		}
	}
}

bool cChunk::checkIfOnScreen(olc::vi2d& newPos) {
    //if position to draw is greater than the top left map corner x
    //and smaller than the bottom rght corner x
	if (newPos.x >= gameConfig->getMapTL().x && newPos.x <= gameConfig->getMapBR().x) {
		if (newPos.y >= gameConfig->getMapTL().y && newPos.y <= gameConfig->getMapBR().y) {
			return true;
		}
		else return false;
	}
	else return false;
}

//call chunk gen passing the current chunk and return it with edits
void cChunk::SlabReplacement(TileID::TileIDList newTile, int x, int y, int z) {
	FullChunkIDs.fillSingleSlab(z,y,x,newTile);
	//FullChunkIDs.slabs = ChunkGen->editchunkSingleTile(FullChunkIDs.slabs,x,y,z,newTile);
}

void cChunk::InfillReplacement(TileID::TileIDList newTile, int x, int y, int z) {
	FullChunkIDs.fillSingleInfill(z,y,x,newTile);
	//FullChunkIDs.infill = ChunkGen->editchunkSingleTile(FullChunkIDs.slabs,x,y,z,newTile);
}

std::string cChunk::compileChunkToString(int i) {
    if (i < (int)FullChunkIDs.slabs.size()) {
        std::string s = std::to_string(FullChunkIDs.slabs[i]);
        return s;
    }
    else {return "NULLVAL";}
}























