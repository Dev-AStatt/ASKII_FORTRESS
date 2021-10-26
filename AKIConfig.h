#pragma once
#include "libraries/olcPixelGameEngine.h"

namespace AKI {

struct GameConfig {
	int			PSIZEint	= 16;
	olc::vi2d	PACK_SIZE	={16,16};
	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite>		sprTile;
	std::unique_ptr<olc::Decal>			decTile;

	GameConfig() {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());
	}


};
}
