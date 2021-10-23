#pragma once
#include "olcPixelGameEngine.h"
#include "mapFunctions/MapUtil_I3d.h"
#include "Object.h"

class ObjectHandler {

private:
	olc::vi2d PACK_SIZE;
	olc::vi2d mapTL;
	olc::vi2d mapBR;
	olc::PixelGameEngine* pge;
	std::vector<std::shared_ptr<Object>> vObjects;
	//These are pointers to sprites and Decals
	std::unique_ptr<olc::Sprite> sprTile;
	std::unique_ptr<olc::Decal> decTile;


	olc::Pixel colorExchanger(int c) {
		if(c == 0) {return olc::WHITE;	}
		if(c == 1) {return olc::GREY;	}
		return olc::WHITE;
	}

	void jumpstart() {
		createMeat({11,11}, 11);
		createMeat({5,2}, 11);
	}

	void constructDecal() {
			sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
			decTile = std::make_unique<olc::Decal>(sprTile.get());
	}
	void drawSingleObject(olc::vi2d posXY, olc::vi2d decalSourcePos,olc::vi2d& viewOffset, int bc);
	//bool visable(olc::vi2d posXY,int posZ, int activeZLayer,olc::vi2d viewOffset);
	bool visable(AKI::I3d pos, int activeZLayer,olc::vi2d viewOffset);
	bool isObjPtrAt(AKI::I3d pos);
public:
	ObjectHandler(olc::vi2d PS,olc::vi2d atStartTL,olc::vi2d atStartBR, olc::PixelGameEngine* p);
	void createMeat(olc::vi2d posXY, int posZ);
	//draw all objects
	//currently will draw them off screen
	void drawObjects(int activeZLayer,olc::vi2d& viewOffset);
	int ItemIDAtPosition(AKI::I3d pos);

	std::vector<std::shared_ptr<Object>> fillVectWithObjPtrs(std::vector<olc::vi2d>& vectPosXY, int z);
	std::shared_ptr<Object> getObjPtrAt(AKI::I3d pos);

};





