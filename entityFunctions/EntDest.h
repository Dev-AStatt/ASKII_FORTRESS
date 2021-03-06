#pragma once
#include "GameConfig.h"

//
// This is a class to hold the active destination for ents
//
namespace Memories {

enum priorities {
	food,
	water,
	social,
	recreation,
	reproduction
};

class EntDest {
private:
	int destinationX;
	int destinationY;
	int destinationZ;
	bool validDest;
	int tilePriorityID;
	int objPriorityID;
	int currentPrioirty;

public:
	int getX()	const			{return destinationX;}
	int getY()	const			{return destinationY;}
	int getZ()	const			{return destinationZ;}
	int getTilePriorityID() const	{return tilePriorityID;}
	int getObjPriorityID()	const	{return objPriorityID;}
	bool getValidDest()		const	{return validDest;}
	int getPriority()		const	{return currentPrioirty;}

	void setXYZ(AKI::I3d& n)	{destinationX = n.x;
								 destinationY = n.y;
								 destinationZ = n.z;}

	void setNewDest(AKI::I3d n, priorities pt, int ID) {
		setXYZ(n);
		currentPrioirty = pt;
		if(pt == water) {tilePriorityID = ID;}
		if(pt == food) {objPriorityID = ID;}
		validDest = true;
	}
	//currently only returns a 0 for z direction to destination
	AKI::I3d directionToDest(AKI::I3d& currentPos) const {
		int dX = 0;
		int dY = 0;
		int dZ = 0;
		if(currentPos.z == destinationZ) {
			if(destinationX > currentPos.x) { dX = 1;}
			else if(destinationX == currentPos.x) {dX = 0;}
			else {dX = -1;}
			if(destinationY > currentPos.y) { dY = 1;}
			else if(destinationY == currentPos.y) {dY = 0;}
			else {dY = -1;}
		}
		return {dX,dY,dZ};
	}
	bool arivedAtDest(AKI::I3d& currentPos) const {
		if(currentPos.z ==destinationZ) {
			for(int y = currentPos.y - 1; y <= currentPos.y + 1; ++y) {
				for(int x = currentPos.x - 1; x <= currentPos.x + 1; ++x) {
					if(destinationX == x && destinationY == y) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

}
