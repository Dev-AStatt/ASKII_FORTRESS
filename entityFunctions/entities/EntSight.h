#pragma once
#include "mapFunctions/MapUtilTileIDList.h"
#include "GameConfig.h"
#include "objectFunctions/objecthandler.h"


class EntSight {
private:
	int viewDistance;
	std::shared_ptr<TileID::TileManager> tileManager;

	std::vector<int> slabsInView;
	std::vector<int> infillInView;
	std::vector<AKI::I3d> I3dCoordinatesInView;
	std::vector<AKI::I3d> I3dInteractCoords;
	std::vector<std::shared_ptr<Object>> objectPtrsInView;

public:
	EntSight(int vd, std::shared_ptr<TileID::TileManager> tm) {
		tileManager = tm;
		viewDistance = vd;
	}
	int getSlabIDInView(  int index) {
		if(index < (int)slabsInView.size()) {
			return slabsInView[index];
		} else return 0;
	}
	int getinfillIDInView(int index) {
		if(index < (int)slabsInView.size()) {
			return infillInView[index];
		} else return 0;
	}
	void clearCoordInView() {I3dCoordinatesInView.clear();}
	void clearSlabsInView() {slabsInView.clear();}
	void clearInfillInView(){infillInView.clear();}
	void setSlabsInView( std::vector<int> vSight) {slabsInView = vSight;}
	void setInfillInView(std::vector<int> vSight) {infillInView = vSight;}

	void addCoordsInView(AKI::I3d pos) {I3dCoordinatesInView.emplace_back(pos);}

	bool isSlabInView(TileID::TileIDList tileLookingFor) {
		std::vector<int>::iterator it = std::find(slabsInView.begin(), slabsInView.end(), tileLookingFor);
		if (it != slabsInView.end()) {
			std::cout << "Element Found ID:" << std::endl;
			return true;
		}
		else {
			std::cout << "Element Not Found" << std::endl;
			return false;
		}
	}


	//will currently return 0,0 if no tile is found
	AKI::I3d locateTile(TileID::TileIDList tileLookingFor, AKI::I3d& currentPos) {
		AKI::I3d closest = {-200,-200, -200}, temp;
		for (int i = 0; i < (int)slabsInView.size(); ++i) {
			if(slabsInView[i] == tileLookingFor) {
				temp = I3dCoordinatesInView[i];
				if(closerToEnt(closest,temp,currentPos)) {
					closest = temp;
				}
			}
		}
		return closest;
	}
	bool closerToEnt(AKI::I3d& oldXY, AKI::I3d& newXY, AKI::I3d& position) {
		olc::vi2d d = olc::vi2d(position.x,position.y) - olc::vi2d(oldXY.x,oldXY.y);
		//get the distance to the old match
		int oldDist = std::abs(d.x) + std::abs(d.y);
		d = olc::vi2d(position.x,position.y) - olc::vi2d(newXY.x,newXY.y);
		int newDist = std::abs(d.x) + std::abs(d.y);

		if(newDist < oldDist) { return true; }
		return false;
	}


	//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
	bool watchYourStep(AKI::I3d nPos) {
		//how many tiles are in a x row for our view distance
		int numInX = (viewDistance * 2) + 1;
		//find the center tile that contains our position
		int centerIndex = (numInX * 3) + viewDistance;
		//add the change nPos to our center index
		int index = centerIndex + (nPos.x) + (nPos.y * numInX);


		auto& f = tileManager->vptrTiles[getinfillIDInView(index)];

		auto& t = tileManager->vptrTiles[getSlabIDInView(index)];
		if(t->isWalkable() && f->isSolid()) {
			return true;
		}
		return false;
	}

};
