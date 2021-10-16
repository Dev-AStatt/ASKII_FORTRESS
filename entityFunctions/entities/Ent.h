#pragma once
#include <random>
#include "olcPixelGameEngine.h"
#include "mapFunctions/Tiles.h"
#include "mapFunctions/MapUtilTileIDList.h"


///
/// \brief The Ent class currently is not used for anything in this project
/// but is saved for later as this is how we can handle entities in the world.
///
class Ent {
private:
protected:
	enum priorities {
		food,
		water,
		social,
		recreation,
		reproduction
	};

    std::string sEntName;
    olc::vi2d decalSourcePos;
    olc::vi2d entPositionXY;
	int entStepZPosition;
	int entHeadZPosition;
    int viewDistance;
	int thirst;
	int hunger;

    olc::Pixel tint;
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;

    //These are pointers to sprites and Decals
    std::unique_ptr<olc::Sprite> sprTile;
    std::unique_ptr<olc::Decal> decTile;
    std::unique_ptr<TileID::cTileID> cTiles;

	std::vector<int> vPriorities;

    //field of view
    std::vector<int> fieldOfView;
	//
	//Functions
	//
	//Basics that need to be loaded for every Ent and inheritors
	void constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p);
	//full sprite tile with art, and put into decTile to be used by drawing
	void constructDecal();
    //Randomizer function with default inputs
	int entRand(int from = 0, int to = 10);
	void pathfinding(int currentTask);

public:
    Ent() {};
	Ent(olc::vi2d& PS, olc::PixelGameEngine* p);

	bool alive;

	std::string returnName() {return "";}
	int returnStepZ() {return entStepZPosition;}
	int returnViewDistance() {return viewDistance;}
	virtual void moveSelf(int x, int y);
    //returns true if you can walk on tile in the x,y direction
	bool watchYourStep(int x, int y);
	virtual void DrawSelf(int activeZLayer, olc::vi2d& viewOffset);
	virtual olc::vi2d& returnPos() {return entPositionXY;}
	virtual bool updateSelf(int tick){return true;};
	virtual void giftOfSight(std::vector<int> vSight) {fieldOfView = vSight;}
	//looks at current needs and redefines priorities
	virtual void assessPriorities(){};


};
