#include "EntSight.h"

EntSight::EntSight(int vd, std::shared_ptr<TileID::TileManager> tm) {
	   tileManager = tm;
	   if(vd > 0 && vd < 100) {
		   viewDistance = vd;
	   }else {
		   std::cout << "Why did someone pass a broken view distance" << '\n';
	   }
}

std::pair<bool, AKI::I3d> EntSight::searchTree(TileID::TileIDList tileLookingFor) {
	//search by layer
	if(sightTree->block.slab == tileLookingFor) {return std::make_pair(true,sightTree->location);}

	std::vector<std::unique_ptr<TreeSearchResult>> searchResults;

	searchTreeChildren(sightTree,searchResults,tileLookingFor);

	if(searchResults.size() == 1) {
		return std::make_pair(searchResults[0]->useable,searchResults[0]->location); }
	if(searchResults.size() == 0) { return std::make_pair(false,AKI::I3d(0,0,0));}
	else {
		//make a function that returns the closest one of vector
		 return std::make_pair(searchResults[0]->useable,searchResults[0]->location);
	}
}

// a depth count can be added to the treeSearchResult vector to keep tract of what depth each was found
void EntSight::searchTreeChildren(std::unique_ptr<Node>& parent, std::vector<std::unique_ptr<TreeSearchResult> > &searchResult, TileID::TileIDList tileLookingFor) {
	if(parent != NULL) {
		if(parent->block.slab == tileLookingFor) {searchResult.emplace_back(std::make_unique<TreeSearchResult>(true,parent->location)); }

		for(int i = 0; i < parent->getNumChildren(); ++i) {
			searchTreeChildren(parent->getChild(i),searchResult,tileLookingFor);
		}
	}
}

//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
bool EntSight::watchYourStep(AKI::I3d nPos) {
	AKI::I3d newPos = (sightTree->location + nPos);
	//maybe build this into the I3d class
	newPos = {newPos.x,newPos.y,newPos.z};

	for(int i = 0; i < sightTree->getNumChildren(); ++i) {
		if(sightTree->children[i]->location == newPos) {
			//get referance to infill f and slab t
			auto& f = tileManager->vptrTiles[sightTree->children[i]->block.infill];
			auto& s = tileManager->vptrTiles[sightTree->children[i]->block.slab];
			if(s->isWalkable() && !f->isSolid()) { return true;	}
		}
	}
	return false;

}



