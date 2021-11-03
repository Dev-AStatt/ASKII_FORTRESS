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

	int currentDebth = 0;

	auto searchResult = searchTreeChildren(sightTree,tileLookingFor);
	if(searchResult.first) {return searchResult;}
	else {++currentDebth;}

	for(int i = 0; i < sightTree->getNumChildren(); ++i) {
		searchResult = searchTreeChildren(sightTree->children[i],tileLookingFor);
		if(searchResult.first) {return searchResult;}
	}


	return std::make_pair(false,AKI::I3d(0,0,0));
}

std::pair<bool, AKI::I3d> EntSight::searchTreeChildren(std::unique_ptr<Node>& parent, TileID::TileIDList tileLookingFor) {
	for(int i = 0; i < parent->getNumChildren(); ++i) {
		if(parent->children[i]->block.slab == tileLookingFor) {return std::make_pair(true,parent->children[i]->location);}
	}
	return std::make_pair(false,AKI::I3d(0,0,0));
}

//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
bool EntSight::watchYourStep(AKI::I3d nPos) {
	AKI::I3d newPos = (sightTree->location + nPos);
	//maybe build this into the I3d class
	newPos = {newPos.x%16,newPos.y%16,newPos.z};

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



