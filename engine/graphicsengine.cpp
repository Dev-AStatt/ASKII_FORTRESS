#include "graphicsengine.h"

namespace AKI {

GraphicsEngine::GraphicsEngine(std::shared_ptr<GameConfig> ge, olc::PixelGameEngine* p) {
	gameConfig = ge;
	pge = p;
}

void GraphicsEngine::updateTick(uint32_t t) {

	tick = t;

	for(int i = 0; i < (int)debugStrings.size(); ++i) {
		drawString({50,16 + i},debugStrings[i]);
	}
}

void GraphicsEngine::drawString(int posX, int posY,std::string str,int offsetX, int offsetY, olc::Pixel col) {
	pge->DrawStringDecal(olc::vi2d(posX,posY) * gameConfig->getPackSize() + olc::vi2d(offsetX,offsetY), str, col);
}

void GraphicsEngine::drawString(olc::vi2d pos,std::string str, olc::Pixel col,olc::vi2d offset) {
	pge->DrawStringDecal(pos * gameConfig->getPackSize() + offset, str, col);
}

void GraphicsEngine::drawTile(olc::vi2d tilePos, olc::vi2d decalPos, olc::Pixel col) const {
	if(!isTileInMapView(tilePos)) {return;}
	pge->DrawPartialDecal(tilePos * gameConfig->getPackSize(),
						  gameConfig->decTile.get(),
						  decalPos*gameConfig->getPackSize(),
						  gameConfig->getPackSize(),
						  olc::vi2d(1, 1),
						  col);
}

void GraphicsEngine::addDebugString(std::string str) {
	if(debugStrings.size() > 6) {
		debugStrings.clear();
	}

	debugStrings.emplace_back(str);
}

bool GraphicsEngine::isTileInMapView(olc::vi2d &tilePos) const {
	if(gameConfig->getMapTL() < tilePos && gameConfig->getMapBR() > tilePos) {
		return true;
	}
	return false;
}

}

