#pragma once
#include "mapFunctions/MapUtilTileIDList.h"
#include "GameConfig.h"
#include "objectFunctions/objecthandler.h"
#include "TreeDataStructure.h"

class EntSight {
public:
	EntSight(int vd, std::shared_ptr<Tiles::TileManager> tm);

	//returns referance to the sight tree data structure
	std::unique_ptr<Node>& getSightTree() {return sightTree;}
	//will eat unique pointer and set ent sight data tree to it.
	void setSightTree(std::unique_ptr<Node>& s) {sightTree = std::move(s); updateInteractableCoords();}
	//return pair {if tile was found, loc of tile found} of closest tile matching
	std::pair<bool, AKI::I3d> GetSlabInTree(Tiles::IDList tileLookingFor);
	//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
	bool watchYourStep(const AKI::I3d nPos) const;

	std::vector<AKI::I3d> getInteactionCoords() const {return interactCoords;}
	//will return true if op1 is closer or equal to option 2 from pos
	bool isCloser(AKI::I3d& pos, AKI::I3d& op1, AKI::I3d& op2) const;

private:
	int viewDistance = 0;
	std::shared_ptr<Tiles::TileManager> tileManager;
	std::vector<std::shared_ptr<Object>> objectPtrsInView;
	std::vector<AKI::I3d> interactCoords;
	std::unique_ptr<Node> sightTree;

	//search tree is the recursive function that will call itself and add
	//tiles it finds into the passed in vector searchResults.
	void searchTreeChildren(std::unique_ptr<Node>& parent,
							std::vector<std::pair<bool,AKI::I3d>>& searchResults,
							Tiles::IDList tileLookingFor);
	void updateInteractableCoords();
};
