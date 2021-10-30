#pragma once
#include "mapFunctions/MapUtilTileIDList.h"
#include "AKIConfig.h"
#include "objectFunctions/objecthandler.h"


class EntSight {
private:
	std::shared_ptr<TileID::TileManager> tileManager;

	std::vector<int> slabsInView;
	std::vector<int> infillInView;
	std::vector<AKI::I3d> I3dCoordinatesInView;
	std::vector<AKI::I3d> I3dInteractCoords;
	std::vector<std::shared_ptr<Object>> objectPtrsInView;

public:
	EntSight(std::shared_ptr<TileID::TileManager> tm) {
		tileManager = tm;
	}
	int getSlabIDInView(  int index) {return slabsInView[index];}
	int getinfillIDInView(int index) {return infillInView[index];}
	void setSlabsInView( std::vector<int> vSight) {slabsInView = vSight;}
	void setInfillInView(std::vector<int> vSight) {infillInView = vSight;}

	bool isSlabInView(TileID::TileIDList tileLookingFor) {
		std::vector<int>::iterator it = std::find(slabsInView.begin(), slabsInView.end(), slabsInView.size());
		if (it != slabsInView.end()) {
			std::cout << "Element Found ID:" << std::endl;
			return true;
		}
		else {
			std::cout << "Element Not Found" << std::endl;
			return false;
		}
	}
};
