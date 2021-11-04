#include "EntSight.h"

EntSight::EntSight(int vd, std::shared_ptr<TileID::TileManager> tm) {
	   tileManager = tm;
	   if(vd > 0 && vd < 100) {
		   viewDistance = vd;
	   }else {
		   std::cout << "Why did someone pass a broken view distance" << '\n';
	   }
}

std::pair<bool, AKI::I3d> EntSight::GetSlabInTree(TileID::TileIDList tileLookingFor) {
	//start by looking at our own feet. this saves time if it ever works.
	if(sightTree->block.slab == tileLookingFor) {return std::make_pair(true,sightTree->location);}
	//set up a vector of valid tiles that we are looking for.
	//pair is <usable, location of tile looking for>
	std::vector<std::pair<bool,AKI::I3d>> searchResults;
	//call recursive function and pass in search Results that will get filled.
	searchTreeChildren(sightTree,searchResults,tileLookingFor);

	//look at vector and see if any results came back. if not return false
	if(searchResults.size() == 1) {
		return std::make_pair(searchResults[0].first,searchResults[0].second); }
	if(searchResults.size() == 0) { return std::make_pair(false,AKI::I3d(0,0,0));}
	else {
		//make a function that returns the closest one of vector
		 return std::make_pair(searchResults[0].first,searchResults[0].second);
	}
}

// a depth count can be added to the treeSearchResult vector to keep tract of what depth each was found
// this will loop over and over checking down one branch of a tree at a time adding in any tiles it finds
void EntSight::searchTreeChildren(std::unique_ptr<Node>& parent, std::vector<std::pair<bool,AKI::I3d>>& searchResults, TileID::TileIDList tileLookingFor) {
	if(parent != NULL) {
		if(parent->block.slab == tileLookingFor) {searchResults.emplace_back(std::make_pair(true,parent->location)); }
		for(int i = 0; i < parent->getNumChildren(); ++i) {
			//call this function again with the child to be recursive
			searchTreeChildren(parent->getChild(i),searchResults,tileLookingFor);
		}
	}
}

//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
bool EntSight::watchYourStep(const AKI::I3d nPos) {
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



