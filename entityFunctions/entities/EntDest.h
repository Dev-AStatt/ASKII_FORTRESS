#pragma once
#include "libraries/olcPixelGameEngine.h"

//
// This is a class to hold the active destination for ents
//
namespace Memory {

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
		int getX()				{return destinationX;}
		int getY()				{return destinationY;}
		int getZ()				{return destinationZ;}
		int getTilePriorityID()	{return tilePriorityID;}
		int getObjPriorityID()	{return objPriorityID;}
		bool getValidDest()		{return validDest;}
		int getPriority()		{return currentPrioirty;}

		void setXY(olc::vi2d& n)	{destinationX = n.x; destinationY = n.y;}
		void setZ(int z)			{destinationZ = z;}

		void setNewDest(olc::vi2d nXY, int nZ, priorities pt, int ID) {
			setXY(nXY);
			setZ(nZ);
			currentPrioirty = pt;
			if(pt == water) {tilePriorityID = ID;}
			if(pt == food) {objPriorityID = ID;}
			validDest = true;
		}
		olc::vi2d directionToDest(olc::vi2d& currentPosXY, int currentZ) {
			int dX = 0;
			int dY = 0;
			if(currentZ == destinationZ) {
				if(destinationX > currentPosXY.x) { dX = 1;}
				else if(destinationX == currentPosXY.x) {dX = 0;}
				else {dX = -1;}
				if(destinationY > currentPosXY.y) { dY = 1;}
				else if(destinationY == currentPosXY.y) {dY = 0;}
				else {dY = -1;}
			}
			return {dX,dY};
		}
		bool arivedAtDest(olc::vi2d& currentPosXY, int currentZ) {
			if(currentZ ==destinationZ) {
				for(int y = currentPosXY.y - 1; y <= currentPosXY.y + 1; ++y) {
					for(int x = currentPosXY.x - 1; x <= currentPosXY.x + 1; ++x) {
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
