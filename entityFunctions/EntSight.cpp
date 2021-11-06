#include "EntSight.h"

EntSight::EntSight(int vd, std::shared_ptr<Tiles::TileManager> tm) {
	   tileManager = tm;
	   if(vd > 0 && vd < 100) {
		   viewDistance = vd;
	   }else {
		   std::cout << "Why did someone pass a broken view distance" << '\n';
	   }
}

std::pair<bool, AKI::I3d> EntSight::GetSlabInTree(Tiles::IDList tileLookingFor) {
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
void EntSight::searchTreeChildren(std::unique_ptr<Node>& parent, std::vector<std::pair<bool,AKI::I3d>>& searchResults, Tiles::IDList tileLookingFor) {
	if(parent != NULL) {
		if(parent->block.slab == tileLookingFor) {searchResults.emplace_back(std::make_pair(true,parent->location)); }
		for(int i = 0; i < parent->getNumChildren(); ++i) {
			//call this function again with the child to be recursive
			searchTreeChildren(parent->getChild(i),searchResults,tileLookingFor);
		}
	}
}
//
//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
bool EntSight::watchYourStep(const AKI::I3d nPos) const {
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

bool EntSight::isCloser(AKI::I3d& pos, AKI::I3d &op1, AKI::I3d &op2) const {
	AKI::I3d distance1 = pos - op1;
	AKI::I3d distance2 = pos - op2;
	distance1.I3d_Abs();
	distance2.I3d_Abs();
	int distance1Sum = distance1.x + distance1.y + distance1.z;
	int distance2Sum = distance2.x + distance2.y + distance2.z;

	if(distance1Sum <= distance2Sum) {
		return true;
	} else return false;
}


void EntSight::updateInteractableCoords() {
	interactCoords.clear();
	//add directly above entity

	//this is kinda a hacky way to do this as getting the location of the
	//sight tree source is supposed to be the coordinate of the ent.
	interactCoords.emplace_back(sightTree->location.I3d_ZOffset(1));
	//add 1 space around and the space itself
	for(int y = (sightTree->location.y - 1); y <= sightTree->location.y + 1; ++y) {
		for(int x = (sightTree->location.x - 1); x <= sightTree->location.x + 1; ++x) {
			interactCoords.emplace_back(AKI::I3d(x,y,sightTree->location.z));
		}
	}
	//add directly below Entity
	interactCoords.emplace_back(sightTree->location.I3d_ZOffset(-1));
}




