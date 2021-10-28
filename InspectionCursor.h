#pragma once
#include "engine/graphicsengine.h"

class InspectionCursor {
private:
    olc::vi2d decalSourcePos;
    olc::vi2d inspPosition;
    olc::Pixel tint;
	std::shared_ptr<AKI::GameConfig> gameConfig;
	std::shared_ptr<AKI::GraphicsEngine> graphicsEngine;


public:
    InspectionCursor() {};
	InspectionCursor(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc) {
		graphicsEngine = ge;
		gameConfig = gc;
        inspPosition = {1,1};
        decalSourcePos = { 8,5 };
        tint = olc::YELLOW;
    }
    void moveSelf(int x, int y) {
        //check if the move will put the cursor off of the screen or not
		if((inspPosition.x + x) >= 0 && (inspPosition.x + x) < gameConfig->getMapBR().x) {
            inspPosition.x = inspPosition.x + x;
        }
		if((inspPosition.y + y) >= 0 && (inspPosition.y + y) < gameConfig->getMapBR().y) {
            inspPosition.y = inspPosition.y + y;
        }
    }

    void DrawSelf() {
		graphicsEngine->drawTile((inspPosition + gameConfig->getMapTL()),decalSourcePos,tint);
    }

	olc::vi2d returnPos() { return inspPosition;}

};
