#pragma once
#include "GameConfig.h"

namespace AKI {

// O--------------------------------------------------------O
// | Graphics Engine will move to hold all drawing rutines	|
// O--------------------------------------------------------O



class GraphicsEngine {
private:
	uint32_t tick = 0;
	olc::PixelGameEngine* pge;
	std::shared_ptr<GameConfig> gameConfig;

	int debugCount = 0;
	std::vector<std::string> debugStrings;

public:
	GraphicsEngine() {}
	GraphicsEngine(std::shared_ptr<GameConfig> ge, olc::PixelGameEngine* p);
	void updateTick(uint32_t t);
	//
	//position passed in for string is in tilespace and default white color
	//offset will default to {0,0}, if you need to nudge text outside of tile use offset
	//
	void drawString(int posX, int posY,std::string str,int offsetX = 0, int offsetY = 0, olc::Pixel col = olc::WHITE);
	void drawString(olc::vi2d pos,std::string str,olc::Pixel col = olc::WHITE,olc::vi2d offset = {0,0});
	//
	//Draw tile will draw the tile at position decalPos on the tilesheet
	//at location in tilespace tilePos
	//
	void drawTile(olc::vi2d tilePos, olc::vi2d& decalPos, olc::Pixel col = olc::WHITE);

	void addDebugString(std::string str);
};


}
