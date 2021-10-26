#pragma once
#include "libraries/olcPixelGameEngine.h"

namespace AKI {

class GameConfig {
private:
	int iTexture_Size = 16;
	int chunkSize = 16;
	olc::vi2d texture_Size = {16,16};

	olc::vi2d mapOutline;
	olc::vi2d mapAreaTopLeft;
	olc::vi2d mapAreaBottomRight;
	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite>		sprTile;


public:
	GameConfig() {}
	GameConfig(uint32_t screenWidth, uint32_t screenHeight) {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());

		mapOutline.x		=	(screenWidth / 4) - 1;
		mapOutline.y		=	(screenHeight - (iTexture_Size * 32));
		mapAreaTopLeft		=	{1,1};
		mapAreaBottomRight	=	{chunkSize * 3, chunkSize * 2};
	}

	std::unique_ptr<olc::Decal>	 decTile;
	int		  getPackSizeInt()	{return iTexture_Size;}
	int		  getChunkSize()	{return chunkSize;}
	olc::vi2d getMapTL()		{return mapAreaTopLeft;}
	olc::vi2d getMapBR()		{return mapAreaBottomRight;}
	olc::vi2d getPackSize()		{return texture_Size;}


	void setPackSize(olc::vi2d& ps) {texture_Size = ps;}


};

}
