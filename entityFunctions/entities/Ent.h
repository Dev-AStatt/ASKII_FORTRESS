#pragma once
#include <random>
#include "mapFunctions/MapUtilTileIDList.h"
#include "entityFunctions/entities/EntDest.h"
#include "objectFunctions/objecthandler.h"
#include "EntSight.h"
#include "TreeDataStructure.h"

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

	std::shared_ptr<TileID::TileManager>tileManager;
	std::unique_ptr<Memories::EntDest>	Destination;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;

	std::unique_ptr<EntSight> sight;
	std::vector<int> vPriorities;


	std::vector<AKI::I3d>	I3dInteractCoords;


	std::vector<std::shared_ptr<Object>> objectPtrsInView;



	// O----------------------------------------------------O
	// | Private Functions							        |
	// O----------------------------------------------------O

	//Basics that need to be loaded for every Ent and inheritors
	void constructEntBasics(std::shared_ptr<TileID::TileManager> tm,
							std::shared_ptr<AKI::GraphicsEngine> ge,
							std::shared_ptr<AKI::GameConfig> gc);
	//Randomizer function with default inputs
	int AKIRand(int from, int to);
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

	//used for update Position in view to check if number is pos
	int notNegativeXY(int x) { if(x >=0) { return x; } else return 0; }


public:
	bool alive;
    Ent() {};
	Ent(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
		std::shared_ptr<TileID::TileManager> tm, std::string n);

	std::string returnName()				{return sEntName;}
	int returnStepZ()						{return entZPosition;}
	int returnViewDistance()				{return viewDistance;}
	int getViewDistance()					{return viewDistance;}
	//std::vector<olc::vi2d> getPosInView()	{return positionsXYInView;}
	AKI::I3d& returnPos()					{return position;}
	virtual bool updateSelf(int tick)		{if(tick>0) {return true;} return true;};
	std::vector<AKI::I3d>& getCordsInView() {return sight->getCordsInView();}
	std::shared_ptr<Node>& getNodeSource()	{return sight->sightTree;}
	void setSightNodeSource(std::shared_ptr<Node> s) {sight->sightTree = s;}

	virtual void moveSelf(int x, int y, int z = 0);
	//just translates a moveself with vi2d to moveself
	void moveSelfvi2d(olc::vi2d XY) {moveSelf(XY.x,XY.y);}
	void moveSelfI3d(AKI::I3d XYZ)	{moveSelf(XYZ.x,XYZ.y,XYZ.z);}

	virtual void DrawSelf(int activeZLayer, olc::vi2d& viewOffset);
	virtual void giftObjectsInView(std::vector<std::shared_ptr<Object>> vPSight) {objectPtrsInView = vPSight;}


	//looks at current needs and redefines priorities
	virtual void assessPriorities(){};


};







