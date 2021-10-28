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
	void basicSlopeConstructor(std::shared_ptr<AKI::GraphicsEngine> ge,
							   olc::vi2d source, std::string name,
							   SlopeD s, olc::Pixel c = olc::GREY,bool mine = true) {

		graphicsEngine = ge;
		decalSourcePos	= source;
		sTileName		= name;
		tint			= c;
		mineable		= mine;
		sDirection		= s;
		constructDecal();
	}
};


class TileSlopeNorth : public TileSlope {
public:
	TileSlopeNorth(std::shared_ptr<AKI::GraphicsEngine> ge) {
		basicSlopeConstructor(ge,{14,1},"Slope North", SlopeD::North);
	}
};

class TileSlopeSouth : public TileSlope {
public:
	TileSlopeSouth(std::shared_ptr<AKI::GraphicsEngine> ge) {
		basicSlopeConstructor(ge,{15,1},"Slope South",SlopeD::South);
	}
};

class TileSlopeEast : public TileSlope {
public:
	TileSlopeEast(std::shared_ptr<AKI::GraphicsEngine> ge) {
		basicSlopeConstructor(ge,{0,1},"Slope East",SlopeD::East);
		}
};

class TileSlopeWest : public TileSlope {
public:
	TileSlopeWest(std::shared_ptr<AKI::GraphicsEngine> ge) {
		basicSlopeConstructor(ge,{1,1},"Slope West",SlopeD::West);

	}
};

