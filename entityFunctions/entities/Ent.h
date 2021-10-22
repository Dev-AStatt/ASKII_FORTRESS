#pragma once
#include <random>
#include "olcPixelGameEngine.h"
#include "mapFunctions/MapUtilTileIDList.h"
#include "entityFunctions/entities/EntDest.h"
#include "objectFunctions/objecthandler.h"

///
/// \brief The Ent class currently is not used for anything in this project
/// but is saved for later as this is how we can handle entities in the world.
///
class Ent {
private:
protected:

    std::string sEntName;
    olc::vi2d decalSourcePos;
    olc::vi2d entPositionXY;
	int entStepZPosition;
	int entHeadZPosition;
    int viewDistance;
	int thirst;
	int thirstBurnRate;
	int hunger;
	int hungerBurnRate;



    olc::Pixel tint;
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;

    //These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite>		sprTile;
	std::unique_ptr<olc::Decal>			decTile;
	std::unique_ptr<TileID::cTileID>	cTiles;
	std::unique_ptr<Memory::EntDest>	Destination;

	std::vector<int> vPriorities;

    //field of view
	std::vector<int>		tilesInView;
	//std::vector<int>		objectsInView;
	std::vector<olc::vi2d>	positionsXYInView;
	std::vector<std::shared_ptr<Object>> objectPtrsInView;



	//
	//Functions
	//
	//Basics that need to be loaded for every Ent and inheritors
	void constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p);
	void UpdatePosInView();
	//full sprite tile with art, and put into decTile to be used by drawing
	void constructDecal();
    //Randomizer function with default inputs
	int entRand(int from = 0, int to = 10);
	bool pathfinding();
	//return true if anything edable is in view
	bool searchForFood();
	olc::vi2d locationOfFood();
	int foodIDAt(olc::vi2d XY);
	//returns true if tile is in view
	bool searchForTile(TileID::TileIDList tileLookingFor);
	//returns the 2d coord of tile
	olc::vi2d locateTile(TileID::TileIDList tileLookingFor);
	//will compare old and new vi2d and retrun true if new is closer
	bool closerToEnt(olc::vi2d& old, olc::vi2d& newXY);

public:
	bool alive;
    Ent() {};
	Ent(olc::vi2d& PS, olc::PixelGameEngine* p, std::string n);

	std::string returnName()				{return "";}
	int returnStepZ()						{return entStepZPosition;}
	int returnViewDistance()				{return viewDistance;}
	int getViewDistance()					{return viewDistance;}
	std::vector<olc::vi2d> getPosInView()	{return positionsXYInView;}
	virtual olc::vi2d& returnPos()			{return entPositionXY;}
	virtual bool updateSelf(int tick)		{return true;};

	virtual void moveSelf(int x, int y);
	//just translates a moveself with vi2d to moveself
	virtual void moveSelfvi2d(olc::vi2d XY) {moveSelf(XY.x,XY.y);}
    //returns true if you can walk on tile in the x,y direction
	bool watchYourStep(int x, int y);
	virtual void DrawSelf(int activeZLayer, olc::vi2d& viewOffset);
	virtual void giftOfSight(std::vector<int> vSight) {tilesInView = vSight;}
	virtual void giftObjectsInView(std::vector<std::shared_ptr<Object>> vPSight) {objectPtrsInView = vPSight;}


	//looks at current needs and redefines priorities
	virtual void assessPriorities(){};


};







