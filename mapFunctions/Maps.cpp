#include "Maps.h"


Maps::Maps(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc) {
	graphicsEngine = ge;
	gameConfig = gc;
	//create the two functions maps needs
	tileManager = std::make_shared<TileID::TileManager>	(gameConfig,graphicsEngine);
	ChunkGen	= std::make_shared<MapUtilChunkGen>		(graphicsEngine,gameConfig,tileManager);
}

void Maps::newMap(int atStartWorldSize) {
    currentWorldSize = atStartWorldSize;
    mapCreateStartingChunks(atStartWorldSize);
    activeZLayer = 11;
}

void Maps::continueMap(int chunkNum, int worldSize, std::vector<uint64_t> newChunk) {
	//If you ever wonder why this isnt working its because the chunk creation is
	//commented out becasue we havnt changed the save load from when we changed
	//how the chunks are layed in memory

}

//
//Creates the first 3x3 chunk area
void Maps::mapCreateStartingChunks(int worldsize) {
	vptrActiveChunks = ChunkGen->makeWorld(worldsize);
	mapLoaded = true;
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

	int chunkX = ((-1)*moveViewOffset.x + insplocXY.x) / gameConfig->getChunkSize();
	int chunkY = ((-1)*moveViewOffset.y + insplocXY.y) / gameConfig->getChunkSize();
	int tileX = ((-1)*moveViewOffset.x + insplocXY.x) % gameConfig->getChunkSize();
	int tileY = ((-1)*moveViewOffset.y + insplocXY.y) % gameConfig->getChunkSize();

    int chunkToPoint = 0;
    if(mapLoaded) {
        //sort through list of active chunks looking for a match
        for (size_t c = 0; c < vptrActiveChunks.size(); c++) {
			if (chunkX == vptrActiveChunks[c]->getChunkPosX() &&chunkY == vptrActiveChunks[c]->getChunkPosY() ) {
                chunkToPoint = c;
            }
        }
		vptrActiveChunks[chunkToPoint]->SlabReplacement(TileID::Water,tileX,tileY,activeZLayer);
    }
}


std::vector<int> Maps::viewOfWorldSlabs(AKI::I3d pos,int viewDistance) {
    std::vector<int> vSight;
    //std::vector<olc::vi2d> chunksInView;
    olc::vi2d chunkIDLoc;
    int chunkIndex;

	int yStart = pos.y - viewDistance;
	int yEnd   = pos.y + viewDistance;
	int XStart = pos.x - viewDistance;
	int XEnd   = pos.x + viewDistance;

    for(int y = yStart; y <= yEnd; ++y) {
        for(int x = XStart; x <= XEnd; ++x) {
            chunkIDLoc = worldPosToChunkXY({x,y});
            chunkIndex = returnVIndexOfChunk(chunkIDLoc);
            if(chunkIndex >= 0) {
				int temp = vptrActiveChunks[chunkIndex]->getSlabIDAt(pos.z,y,x);
                vSight.emplace_back(temp);
            }

        }
    }
    return vSight;
}


std::vector<int> Maps::viewOfWorldInfill(AKI::I3d pos,int viewDistance) {
	std::vector<int> vSight;
	//std::vector<olc::vi2d> chunksInView;
	olc::vi2d chunkIDLoc;
	int chunkIndex;

	int yStart = pos.y - viewDistance;
	int yEnd   = pos.y + viewDistance;
	int XStart = pos.x - viewDistance;
	int XEnd   = pos.x + viewDistance;

	for(int y = yStart; y <= yEnd; ++y) {
		for(int x = XStart; x <= XEnd; ++x) {
			chunkIDLoc = worldPosToChunkXY({x,y});
			chunkIndex = returnVIndexOfChunk(chunkIDLoc);
			if(chunkIndex >= 0) {
//RIGHT HERE SOMETHING IS WRONG. IF Y>15 it returns the wrong value
				int correctedX = x % 16;
				int correctedY = y % 16;
				int temp = vptrActiveChunks[chunkIndex]->getInfillIDAt(pos.z,correctedY,correctedX);
				vSight.emplace_back(temp);
			}

		}
	}
	return vSight;
}

olc::vi2d Maps::worldPosToChunkXY(olc::vi2d worldPos) {
	olc::vi2d chunkXY = {worldPos.x / gameConfig->getChunkSize(),worldPos.y / gameConfig->getChunkSize()};
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















