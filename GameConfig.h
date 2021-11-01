#pragma once
#include "libraries/olcPixelGameEngine.h"

namespace AKI {

class GameConfig {
private:
	int iTexture_Size = 16;
	int chunkSize = 16;
	int screenTileHeight;
	int screenTileWidth;
	olc::vi2d texture_Size = {16,16};

	olc::vi2d mapOutline;
	olc::vi2d mapAreaTopLeft;
	olc::vi2d mapAreaBottomRight;
	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite>		sprTile;


public:
	GameConfig() {}
	GameConfig(olc::PixelGameEngine* p) {
		sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
		decTile = std::make_unique<olc::Decal>(sprTile.get());

		mapOutline.x		=	(p->ScreenWidth() / 4) - 1;
		mapOutline.y		=	(p->ScreenHeight() - (iTexture_Size * 32));
		mapAreaTopLeft		=	{1,1};
		mapAreaBottomRight	=	{chunkSize * 3, chunkSize * 2};

		screenTileHeight	=	(int)p->ScreenHeight() / iTexture_Size;
		screenTileWidth		=	(int)p->ScreenWidth() / iTexture_Size;
	}

	std::unique_ptr<olc::Decal>	 decTile;
	int		  getPackSizeInt()	{return iTexture_Size;}
	int		  getChunkSize()	{return chunkSize;}
	int		  getScreenTileH()	{return screenTileHeight;}
	int		  getScreenTileW()	{return screenTileWidth;}
	olc::vi2d getMapTL()		{return mapAreaTopLeft;}
	olc::vi2d getMapBR()		{return mapAreaBottomRight;}
	olc::vi2d getPackSize()		{return texture_Size;}
	olc::vi2d getMapOutline()	{return mapOutline;}



	void setPackSize(olc::vi2d& ps) {texture_Size = ps;}


};

struct I3d {
	int x;
	int y;
	int z;

	I3d(int nX, int nY, int nZ) {x = nX; y = nY; z = nZ;}
	I3d() : x(0), y(0), z(0) {}
	I3d I3d_XOffset(int i) {return I3d((this->x + i),this->y,this->z);}
	I3d I3d_YOffset(int i) {return I3d(this->x,(this->y + i),this->z);}
	I3d I3d_ZOffset(int i) {return I3d(this->x,this->y,(this->z + i));}

	I3d  operator +  (const I3d& rhs) const { return I3d(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
	I3d  operator -  (const I3d& rhs) const { return I3d(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
	I3d& operator += (const I3d& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
	I3d& operator -= (const I3d& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
	bool operator == (const I3d& rhs) const {return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);}
	bool operator != (const I3d& rhs) const {return (this->x != rhs.x && this->y != rhs.y && this->z != rhs.z);}

};

//struct is the block [infill + slab] tile ID's. This needs to be passed around often enough
struct Block {
	int slab;
	int infill;

	Block(int s, int i) {slab = s; infill = i;}
	Block() : slab(0), infill(0) {}
};

}


