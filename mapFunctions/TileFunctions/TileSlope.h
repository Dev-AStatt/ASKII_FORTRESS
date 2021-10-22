#pragma once
#include "mapFunctions/TileFunctions/Tiles.h"

class TileSlope : public Tile {
protected:
	//this is duplicated in MapUtilTileIDList.h
	enum SlopeD {
		North,
		South,
		East,
		West,
	};
	SlopeD sDirection;

public:
	int getTileSlope() {return sDirection;}
	bool slopeDirectionIs(int s) {if(s == sDirection){return true;} else {return false; }}

	//stuff that each slope must construct
	void basicSlopeConstructor(olc::vi2d& PS, olc::PixelGameEngine* p,
							   olc::vi2d source, std::string name,
							   SlopeD s, olc::Pixel c = olc::GREY,bool mine = true) {
		PACK_SIZE = PS;
		pge = p;
		constructDecal();
		decalSourcePos = source;
		sTileName = name;
		tint = c;
		mineable = mine;
		sDirection = s;
	}
};


class TileSlopeNorth : public TileSlope {
public:
	TileSlopeNorth(olc::vi2d& PS, olc::PixelGameEngine* p) {
		basicSlopeConstructor(PS,p,{14,1},"Slope North", SlopeD::North);
	}
};

class TileSlopeSouth : public TileSlope {
public:
	TileSlopeSouth(olc::vi2d& PS, olc::PixelGameEngine* p) {
		basicSlopeConstructor(PS,p,{15,1},"Slope South",SlopeD::South);
	}
};

class TileSlopeEast : public TileSlope {
public:
	TileSlopeEast(olc::vi2d& PS, olc::PixelGameEngine* p) {
		basicSlopeConstructor(PS,p,{0,1},"Slope East",SlopeD::East);
		}
};

class TileSlopeWest : public TileSlope {
public:
	TileSlopeWest(olc::vi2d& PS, olc::PixelGameEngine* p) {
		basicSlopeConstructor(PS,p,{1,1},"Slope West",SlopeD::West);

	}
};

