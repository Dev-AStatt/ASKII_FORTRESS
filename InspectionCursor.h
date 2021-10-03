#pragma once
#include "olcPixelGameEngine.h"

class InspectionCursor {
private:
    olc::vi2d decalSourcePos;
    olc::vi2d inspPosition;
    olc::Pixel tint;
    olc::vi2d PACK_SIZE;
    olc::vi2d mapTL;
    olc::vd2d mapBR;
    olc::PixelGameEngine* pge;
    //These are pointers to sprites and Decals
    std::unique_ptr<olc::Sprite> sprTile;
    std::unique_ptr<olc::Decal> decTile;

    void constructDecal() {
        sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
        decTile = std::make_unique<olc::Decal>(sprTile.get());
    }

public:
    InspectionCursor() {};
    InspectionCursor(olc::vi2d& atStartPS, olc::vi2d& atStartTL,olc::vi2d& atStartBR, olc::PixelGameEngine* p) {
        PACK_SIZE = atStartPS;
        mapTL = atStartTL;
        mapBR = atStartBR;
        pge = p;
        constructDecal();
        inspPosition = {1,1};
        decalSourcePos = { 8,5 };
        tint = olc::YELLOW;
    }
    void moveSelf(int x, int y) {
        //check if the move will put the cursor off of the screen or not
        if((inspPosition.x + x) >= 0 && (inspPosition.x + x) < mapBR.x) {
            inspPosition.x = inspPosition.x + x;
        }
        if((inspPosition.y + y) >= 0 && (inspPosition.y + y) < mapBR.y) {
            inspPosition.y = inspPosition.y + y;
        }

    }

    void DrawSelf() {
        pge->DrawPartialDecal((inspPosition + mapTL) * PACK_SIZE, decTile.get(), decalSourcePos*PACK_SIZE, PACK_SIZE, olc::vi2d(1, 1), tint);
    }

    olc::vi2d returnPos() {
        return inspPosition;
    }


};
