#include "Maps.h"


Maps::Maps(olc::vi2d& packSizeAtStart, olc::vi2d& atStartMapTL, olc::vi2d& atStartMapBR, olc::PixelGameEngine* p) {
    PACK_SIZE = packSizeAtStart;
	pge = p;
	ChunkGen = std::make_shared<MapUtilChunkGen>();
    mapTL = atStartMapTL;
    mapBR = atStartMapBR;


}

void Maps::newMap(int atStartWorldSize) {
    currentWorldSize = atStartWorldSize;
    mapCreateStartingChunks(atStartWorldSize);
    activeZLayer = 11;
}

void Maps::continueMap(int chunkNum, int worldSize, std::vector<uint64_t> newChunk) {
    if (chunkNum < worldSize*worldSize) {
        olc::vi2d newChunkLocation;
        newChunkLocation = {chunkNum % worldSize, chunkNum/worldSize};
        uint64_t locationHex = olcTo64Hex(newChunkLocation);
        //
        //Right here call cChunk and make new chunk with id and vect
        //
		vptrActiveChunks.emplace_back(std::make_unique<cChunk>(PACK_SIZE, mapTL,mapBR, pge, locationHex, newChunk,ChunkGen));

        if(chunkNum == (worldSize*worldSize) -1) {
            currentWorldSize = worldSize;
            mapLoaded = true;
            activeZLayer = 11;
        }
    }
}


//Creates the first 3x3 chunk area
void Maps::mapCreateStartingChunks(int worldsize) {
    //
    //Chunks in x---->
    //          y
    //          |
    //          V

    for (int x = 0; x < worldsize; ++x) {
        for (int y = 0; y < worldsize; ++y) {
            //new chunk location {x,y}
            makeNewChunk({x,y});
        }
    }
	mapLoaded = true;
}

//creates a new chunk at passed location {x,y}
void Maps::makeNewChunk(olc::vi2d newChunkLocation) {
    // get the hex value for cChunk for an id
    uint64_t locationHex = olcTo64Hex(newChunkLocation);
	vptrActiveChunks.emplace_back(std::make_unique<cChunk>(PACK_SIZE, mapTL,mapBR, pge, locationHex,ChunkGen));
}

uint64_t Maps::olcTo64Hex (olc::vi2d olcvi2d) {
    uint64_t bitshiftedIDtmp = (uint64_t)olcvi2d.y;
    uint64_t olcTo64Hex = bitshiftedIDtmp << 32;
    olcTo64Hex = olcTo64Hex + olcvi2d.x;
    return olcTo64Hex;
}

void Maps::DrawActiveChunks() {
	 
    for (size_t c = 0; c < vptrActiveChunks.size(); ++c) {
	
		vptrActiveChunks[c]->DrawChunk(activeZLayer, moveViewOffset);

	}
}

void Maps::changeZLayer(int i) {
	if (mapLoaded) {

        if (0 <= activeZLayer + i && activeZLayer + i < 15) {
			activeZLayer = activeZLayer + i;
		}
	}
}
//takes an input of a vi2d and adjust the moveViewOffset by that ammount
void Maps::changeMapViewOffset(olc::vi2d i) {
	if ((moveViewOffset.x + i.x) <= 0 && (moveViewOffset.y + i.y) <= 0) {
		moveViewOffset = moveViewOffset + i;
	}
}

//Function will take in the XY of inspector on the map
//and adjust for the map offset (view) and then look for
//what chunk is at that location. for that chunk. then
//it will flip the tile that the curser was pointing at.
void Maps::flipTileOnMap(olc::vi2d& insplocXY) {
    //this produces the relative chunk the insp is pointing at in x,y
    int chunkX = ((-1)*moveViewOffset.x + insplocXY.x) / chunkSize;
    int chunkY = ((-1)*moveViewOffset.y + insplocXY.y) / chunkSize;
    int tileX = ((-1)*moveViewOffset.x + insplocXY.x) % chunkSize;
    int tileY = ((-1)*moveViewOffset.y + insplocXY.y) % chunkSize;

    int chunkToPoint = 0;
    if(mapLoaded) {
        //sort through list of active chunks looking for a match
        for (size_t c = 0; c < vptrActiveChunks.size(); c++) {
			if (chunkX == vptrActiveChunks[c]->getChunkPosX() &&chunkY == vptrActiveChunks[c]->getChunkPosY() ) {
                chunkToPoint = c;
            }
        }
        vptrActiveChunks[chunkToPoint]->tileReplacement(TileID::Water,tileX,tileY,activeZLayer);
    }
}


std::vector<int> Maps::viewOfWorld(olc::vi2d& posXY, int posZ,int viewDistance) {
    std::vector<int> vSight;
    //std::vector<olc::vi2d> chunksInView;
    olc::vi2d chunkIDLoc;
    int chunkIndex;

    int yStart = posXY.y - viewDistance;
    int yEnd = posXY.y + viewDistance;
    int XStart = posXY.x - viewDistance;
    int XEnd = posXY.x + viewDistance;

    for(int y = yStart; y <= yEnd; ++y) {
        for(int x = XStart; x <= XEnd; ++x) {
            chunkIDLoc = worldPosToChunkXY({x,y});
            chunkIndex = returnVIndexOfChunk(chunkIDLoc);
            if(chunkIndex >= 0) {
				int temp = vptrActiveChunks[chunkIndex]->SlabIDAtLocation(posZ,y,x);
                vSight.emplace_back(temp);
            }

        }
    }
    return vSight;
}


olc::vi2d Maps::worldPosToChunkXY(olc::vi2d worldPos) {
    olc::vi2d chunkXY = {worldPos.x / chunkSize,worldPos.y / chunkSize};
    return chunkXY;
}

int Maps::returnVIndexOfChunk(olc::vi2d XY) {
    int r = XY.x + (XY.y*currentWorldSize);
    if(r >= 0 && r <= (int)vptrActiveChunks.size()) {
        return r;
    }
    else return -1;
}

bool Maps::vi2dInVector(std::vector<olc::vi2d> vect, olc::vi2d check) {

    for(int i = 0; i < (int)vect.size(); ++i) {
        if (check == vect[i]) {
            return true;
        }
    }

    return false;
}















