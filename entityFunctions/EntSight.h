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
	//search tree is the recursive function that will call itself and add
	//tiles it finds into the passed in vector searchResults.
	void searchTreeChildren(std::unique_ptr<Node>& parent,
							std::vector<std::pair<bool,AKI::I3d>>& searchResults,
							TileID::TileIDList tileLookingFor);
public:
	EntSight(int vd, std::shared_ptr<TileID::TileManager> tm);

	std::unique_ptr<Node>& getSightTree() {return sightTree;}
	//will eat unique pointer and set ent sight data tree to it.
	void setSightTree(std::unique_ptr<Node>& s) {sightTree = std::move(s);}

	//return pair {if tile was found, loc of tile found} of closest tile matching
	std::pair<bool, AKI::I3d> GetSlabInTree(TileID::TileIDList tileLookingFor);

	//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
	bool watchYourStep(const AKI::I3d nPos);

};
