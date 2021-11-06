#pragma once
#include <random>
#include "mapFunctions/MapUtilTileIDList.h"
#include "entityFunctions/EntDest.h"
#include "objectFunctions/objecthandler.h"
#include "entityFunctions/EntSight.h"
#include "entityFunctions/TreeDataStructure.h"

///
/// \brief The Ent class currently is not used for anything in this project
/// but is saved for later as this is how we can handle entities in the world.
///
class Ent {
public:
	bool alive;
    Ent() {};
	Ent(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
		std::shared_ptr<Tiles::TileManager> tm, std::string n);

	std::string returnName() const 				{return sEntName;}
	int returnStepZ() const 					{return entZPosition;}
	int returnViewDistance() const				{return viewDistance;}
	int getViewDistance() const					{return viewDistance;}
	const AKI::I3d& returnPos()	const 			{return position;}
	virtual bool updateSelf(int tick)			{if(tick>0) {return true;} return true;};

	std::unique_ptr<Node>& getNodeSource()	{return sight->getSightTree();}
	void setSightNodeSource(std::unique_ptr<Node>& s) {sight->setSightTree(s);}

	void moveSelf(int x, int y, int z = 0);
	void moveSelfvi2d(olc::vi2d XY) {moveSelf(XY.x,XY.y);}
	void moveSelfI3d(AKI::I3d XYZ)	{moveSelf(XYZ.x,XYZ.y,XYZ.z);}

	void DrawSelf(int activeZLayer, olc::vi2d& viewOffset) const;
	//void giftObjectsInView(std::vector<std::shared_ptr<Object>> vPSight) {objectPtrsInView = vPSight;}
	//looks at current needs and redefines priorities
	virtual void assessPriorities(){};

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

	std::shared_ptr<Tiles::TileManager>tileManager;
	std::unique_ptr<Memories::EntDest>	Destination;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;
	std::unique_ptr<EntSight> sight;
	std::vector<int> vPriorities;
	std::shared_ptr<Memories::EntMemory> entMemory;

	// O----------------------------------------------------O
	// | Private Functions							        |
	// O----------------------------------------------------O

	//Basics that need to be loaded for every Ent and inheritors
	void constructEntBasics(std::shared_ptr<Tiles::TileManager> tm,
							std::shared_ptr<AKI::GraphicsEngine> ge,
							std::shared_ptr<AKI::GameConfig> gc);
	//Randomizer function with default inputs
	int AKIRand(int from, int to) const;

	bool pathfinding();
	//return true if anything edable is in view
	bool searchForFood();
	olc::vi2d locationOfFood();
	int foodIDAt(olc::vi2d XY);

	//used for update Position in view to check if number is pos
	int notNegativeXY(int x) { if(x >=0) { return x; } else return 0; }
	void drink() {thirst = 100;}
	void eat()	 {hunger = 100;}

};







