#pragma once
#include "GameConfig.h"

namespace AKI {

// O--------------------------------------------------------O
// | Graphics Engine will move to hold all drawing rutines	|
// O--------------------------------------------------------O



class GraphicsEngine {
private:
	olc::PixelGameEngine* pge;
	std::shared_ptr<GameConfig> gameConfig;

public:
	GraphicsEngine() {}
	GraphicsEngine(std::shared_ptr<GameConfig> ge, olc::PixelGameEngine* p);
	//
	//position passed in for string is in tilespace and default white color
	//offset will default to {0,0}, if you need to nudge text outside of tile use offset
	//
	void drawString(int posX, int posY,std::string str,int offsetX = 0, int offsetY = 0, olc::Pixel col = olc::WHITE);
	void drawString(olc::vi2d pos,std::string str,olc::vi2d offset = {0,0}, olc::Pixel col = olc::WHITE);
	//
	//Draw tile will draw the tile at position decalPos on the tilesheet
	//at location in tilespace tilePos
	//
	void drawTile(olc::vi2d tilePos, olc::vi2d& decalPos, olc::Pixel col = olc::WHITE);
};


}
