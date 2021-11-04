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

	return searchTreeChildren(sightTree,tileLookingFor);




	//return std::make_pair(false,AKI::I3d(0,0,0));
}

/*
 * void preorder(struct node *root) {
   if (root != NULL) {
	  cout<<root->data<<" ";
	  preorder(root->left);
	  preorder(root->right);
   }
}
 *
 *
 * 	for(int i = 0; i < parent->getNumChildren(); ++i) {
		if(parent->children[i]->block.slab == tileLookingFor) {return std::make_pair(true,parent->children[i]->location);}
	}
	return std::make_pair(false,AKI::I3d(0,0,0));
 *
 *
 * */

std::pair<bool, AKI::I3d> EntSight::searchTreeChildren(std::unique_ptr<Node>& parent, TileID::TileIDList tileLookingFor) {
	if(parent == NULL) { return std::make_pair(false,AKI::I3d(0,0,0)); }
	if(parent->block.slab == tileLookingFor) {return std::make_pair(true,parent->location); }
	for(int i = 0; i < sightTree->getNumChildren(); ++i) {
		searchTreeChildren(parent->getChild(i),tileLookingFor);
	}
	return std::make_pair(false,AKI::I3d(0,0,0));
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



