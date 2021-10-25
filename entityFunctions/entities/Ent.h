#pragma once
#include <random>
#include "libraries/olcPixelGameEngine.h"
#include "mapFunctions/MapUtil_I3d.h"
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

	int entZPosition;
	AKI::I3d position;

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
	std::unique_ptr<Memories::EntDest>	Destination;

	std::vector<int> vPriorities;

    //field of view
	std::vector<int>		tilesInView;
	std::vector<AKI::I3d>	I3dCoordinatesInView;
	std::vector<AKI::I3d>	I3dInteractCoords;

	std::vector<olc::vi2d>	positionsXYInView;
	std::vector<std::shared_ptr<Object>> objectPtrsInView;



	// O----------------------------------------------------O
	// | Private Functions							        |
	// O----------------------------------------------------O

	//Basics that need to be loaded for every Ent and inheritors
	void constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p);
	//Randomizer function with default inputs
	int AKIRand(int from, int to);
	//full sprite tile with art, and put into decTile to be used by drawing
	void constructDecal();

	//will construct a AKI::I3D of what is in view
	void UpdateCoordinatesInView();
	//Create vector of tiles that Ent Can interact with
	void updateInteractableCoords();
	//int entRand(int from = 0, int to = 10);
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
	//returns true if you can walk on tile in the x,y direction
	bool watchYourStep(AKI::I3d nPos);

public:
	bool alive;
    Ent() {};
	Ent(olc::vi2d& PS, olc::PixelGameEngine* p, std::string n);

	std::string returnName()				{return "";}
	int returnStepZ()						{return entZPosition;}
	int returnViewDistance()				{return viewDistance;}
	int getViewDistance()					{return viewDistance;}
	std::vector<olc::vi2d> getPosInView()	{return positionsXYInView;}
	AKI::I3d& returnPos()					{return position;}
	virtual bool updateSelf(int tick)		{return true;};


	virtual void moveSelf(int x, int y, int z = 0);
	//just translates a moveself with vi2d to moveself
	void moveSelfvi2d(olc::vi2d XY) {moveSelf(XY.x,XY.y);}
	void moveSelfI3d(AKI::I3d XYZ)	{moveSelf(XYZ.x,XYZ.y,XYZ.z);}

	virtual void DrawSelf(int activeZLayer, olc::vi2d& viewOffset);
	virtual void giftOfSight(std::vector<int> vSight) {tilesInView = vSight;}
	virtual void giftObjectsInView(std::vector<std::shared_ptr<Object>> vPSight) {objectPtrsInView = vPSight;}


	//looks at current needs and redefines priorities
	virtual void assessPriorities(){};


};







