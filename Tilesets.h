#pragma once
#include "libraries/olcPixelGameEngine.h"

namespace AKI {

struct Tileset {

	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite>		sprTile;
	std::unique_ptr<olc::Decal>			decTile;

	Tileset() {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());
	}


};
}
