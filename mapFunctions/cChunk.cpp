#include "cChunk.h"

///
/// This class cChunk constructor creates a whole new chunk gen each time it calls itself.
/// This should be taken out and put in a better spot.
cChunk::cChunk(olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p, uint64_t id, std::shared_ptr<MapUtilChunkGen> cg) {

    loadTypicalData(packSizeAtStart,atStartMapTL, atStartMapBR, p, id);
	ChunkGen = cg;
	vChunk = ChunkGen->GenerateChunk();
	//vChunk = MUCG.GenerateChunk();


}

cChunk::cChunk(olc::vi2d& packSizeAtStart,olc::vi2d& atStartMapTL,olc::vi2d& atStartMapBR, olc::PixelGameEngine* p, uint64_t id, std::vector<uint64_t> chunkToLoad) {
    loadTypicalData(packSizeAtStart,atStartMapTL, atStartMapBR, p, id);
    vChunk = chunkToLoad;
}

void cChunk::loadTypicalData(olc::vi2d &packSizeAtStart, olc::vi2d &atStartMapTL, olc::vi2d &atStartMapBR, olc::PixelGameEngine *p, uint64_t id) {
    PACK_SIZE = packSizeAtStart;
    mapTL = atStartMapTL;
    mapBR = atStartMapBR;
    pge = p;
    ChunkID = id;
    decryptIDtoYX();
    cTiles = std::make_unique<TileID::cTileID>(PACK_SIZE,pge);

}


//Takes in the z,y,x coordinates of a tile and returns the TileID
int cChunk::TileIDAtLocation(int zLayer, int yCol, int xRow) {
	//Is x in Y[even] or Y[odd]
	if (xRow < 8) { yCol = yCol * 2; };
	if (xRow > 7) { yCol = (yCol * 2) + 1; };

	//calculate the bitshifting needed to move x to LSB
	int bitshift = 56 - (xRow * 8);

	bitshiftedIDtmp = vChunk[vectorID(zLayer,yCol)] >> bitshift;
    bitshiftedIDtmp &= extractor;
    //if the above line creats an error in shifting bits. the below line was
    //what was there origninally. I think it means the same thing.
    //bitshiftedIDtmp = bitshiftedIDtmp &= extractor;
	return (int)bitshiftedIDtmp;
}

//returns a pointer to a tile that is at the location of z, vi2d(yx)
std::unique_ptr<Tile>& cChunk::TilePtrAtLocation(int zLayer, olc::vi2d yx) {
	//call TileIDAtLoc and return a pointer at that loc
    std::unique_ptr<Tile>& t = cTiles->vptrTiles[TileIDAtLocation(zLayer, yx.y, yx.x)];
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
            auto& t = cTiles->vptrTiles[TileIDAtLocation(zLayer, y, x)];
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
    if (newPos.x >= mapTL.x && newPos.x <= mapBR.x) {
        if (newPos.y >= mapTL.y && newPos.y <= mapBR.y) {
			return true;
		}
		else return false;
	}
	else return false;
}

//call chunk gen passing the current chunk and return it with edits
void cChunk::tileReplacement(TileID::TileIDList newTile, int x, int y, int z) {
	vChunk = ChunkGen->editchunkSingleTile(vChunk,x,y,z,newTile);
	//vChunk = MUCG.editchunkSingleTile(vChunk,x,y,z,newTile);
}

std::string cChunk::compileChunkToString(int i) {
    if (i < (int)vChunk.size()) {
        std::string s = std::to_string(vChunk[i]);
        return s;
    }
    else {return "NULLVAL";}
}























