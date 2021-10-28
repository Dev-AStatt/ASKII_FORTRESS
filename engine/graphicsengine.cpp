#include "graphicsengine.h"

namespace AKI {

GraphicsEngine::GraphicsEngine(std::shared_ptr<GameConfig> ge, olc::PixelGameEngine* p) {
	gameConfig = ge;
	pge = p;
}

void GraphicsEngine::drawString(int posX, int posY,std::string str,int offsetX, int offsetY, olc::Pixel col) {
	pge->DrawStringDecal(olc::vi2d(posX,posY) * gameConfig->getPackSize() + olc::vi2d(offsetX,offsetY), str, col);
}

void GraphicsEngine::drawString(olc::vi2d pos,std::string str,olc::vi2d offset, olc::Pixel col) {
	pge->DrawStringDecal(pos * gameConfig->getPackSize() + offset, str, col);
}

void GraphicsEngine::drawTile(olc::vi2d tilePos, olc::vi2d& decalPos, olc::Pixel col) {
	pge->DrawPartialDecal(tilePos * gameConfig->getPackSize(),
						  gameConfig->decTile.get(),
						  decalPos*gameConfig->getPackSize(),
						  gameConfig->getPackSize(),
						  olc::vi2d(1, 1),
						  col);
}

}

