#include "cChunk.h"


cChunk::cChunk(uint64_t id, ChunkDataStruct& passedInChunk, std::shared_ptr<AKI::GameConfig> gconf,
			   std::shared_ptr<AKI::GraphicsEngine> graph, std::shared_ptr<Tiles::TileManager> tm) {

	FullChunkIDs = passedInChunk;
	ChunkID = id;
	gameConfig = gconf;
	graphicsEngine = graph;
	tileManager = tm;
	decryptIDtoYX();

}


//Takes in the z,y,x coordinates of a tile and returns the TileID
int cChunk::getSlabIDAt(int zLayer, int yRow, int xCol) {
	if(withinChunk(zLayer,yRow,xCol)) {
		return FullChunkIDs.getSlabIDAt(zLayer,yRow,xCol);
	}
	else return -1;
}

//Takes in the z,y,x coordinates of a tile and returns the TileID
int cChunk::getInfillIDAt(int zLayer, int yRow, int xCol) {
	if(withinChunk(zLayer,yRow,xCol)) {
		return FullChunkIDs.getInfillIDAt(zLayer,yRow,xCol);
	} else return -1;
}



void cChunk::decryptIDtoYX() {
	//shift bits right until just MSB 8 are left
	uint64_t bitshiftedIDtmp = ChunkID >> 32;
	chunkPositionY = (long)bitshiftedIDtmp;
	//and with FF to remove all MSB8 and leave LSB
	bitshiftedIDtmp = 0x00000000FFFFFFFF;
	chunkPositionX = (long)(ChunkID &= bitshiftedIDtmp);
}


void cChunk::DrawChunk(int zLayer, olc::vi2d& moveViewOffset) {
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			int idOfTile = getSlabIDAt(zLayer,y,x);		//get id of tile
			if(idOfTile == -1) {break;}
			//get final position based on chunk position and view offset
			vTileFinalPosition = {x + (int)(chunkPositionX * 16) + 1 + moveViewOffset.x,(y + (int)(chunkPositionY * 16) + 1) + moveViewOffset.y };
			tileManager->drawTile(vTileFinalPosition,idOfTile);
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
void cChunk::SlabReplacement(Tiles::IDList newTile, int x, int y, int z) {
	FullChunkIDs.fillSingleSlab(z,y,x,newTile);
}

void cChunk::InfillReplacement(Tiles::IDList newTile, int x, int y, int z) {
	FullChunkIDs.fillSingleInfill(z,y,x,newTile);
}

std::string cChunk::compileChunkToString(int i) {
    if (i < (int)FullChunkIDs.slabs.size()) {
        std::string s = std::to_string(FullChunkIDs.slabs[i]);
        return s;
    }
    else {return "NULLVAL";}
}























