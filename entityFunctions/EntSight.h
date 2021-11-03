#pragma once
#include "mapFunctions/MapUtilTileIDList.h"
#include "GameConfig.h"
#include "objectFunctions/objecthandler.h"
#include "TreeDataStructure.h"


class EntSight {
private:
	int viewDistance = 0;
	std::shared_ptr<TileID::TileManager> tileManager;

	std::vector<std::shared_ptr<Object>> objectPtrsInView;

	std::unique_ptr<Node> sightTree;

	//return val {bool if tile was found, tile loc if found else 0,0,0} pass in referance to node to search children
	std::pair<bool, AKI::I3d> searchTreeChildren(std::unique_ptr<Node>& parent, TileID::TileIDList tileLookingFor);
public:


	EntSight(int vd, std::shared_ptr<TileID::TileManager> tm);

	std::unique_ptr<Node>& getSightTree() {return sightTree;}
	//will eat unique pointer and set ent sight data tree to it.
	void setSightTree(std::unique_ptr<Node>& s) {sightTree = std::move(s);}

	//we are going to try and overrite this function
	bool isSlabInView(TileID::TileIDList tileLookingFor);

	//return pair {if tile was found, loc of tile found}
	std::pair<bool, AKI::I3d> searchTree(TileID::TileIDList tileLookingFor);

	//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
	bool watchYourStep(AKI::I3d nPos);

};
