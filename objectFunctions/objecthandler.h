#pragma once
#include "engine/graphicsengine.h"
#include "Object.h"

class ObjectHandler {

private:

	olc::vi2d mapTL;
	olc::vi2d mapBR;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::vector<std::shared_ptr<Object>> vObjects;

	olc::Pixel colorExchanger(int c) {
		if(c == 0) {return olc::WHITE;	}
		if(c == 1) {return olc::GREY;	}
		return olc::WHITE;
	}

	void jumpstart() {
		createMeat({11,11}, 11);
		createMeat({5,2}, 11);
	}

	void drawSingleObject(olc::vi2d posXY, olc::vi2d decalSourcePos,olc::vi2d& viewOffset, int bc);
	//bool visable(olc::vi2d posXY,int posZ, int activeZLayer,olc::vi2d viewOffset);
	bool visable(AKI::I3d pos, int activeZLayer,olc::vi2d viewOffset);
	bool isObjPtrAt(AKI::I3d pos);
public:
	ObjectHandler(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc);
	void createMeat(olc::vi2d posXY, int posZ);
	//draw all objects
	//currently will draw them off screen
	void drawObjects(int activeZLayer,olc::vi2d& viewOffset);
	int ItemIDAtPosition(AKI::I3d pos);

	std::vector<std::shared_ptr<Object>> fillVectWithObjPtrs(std::vector<AKI::I3d>& vectPos);
	std::shared_ptr<Object> getObjPtrAt(AKI::I3d pos);

};





