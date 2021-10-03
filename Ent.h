#pragma once
#include "olcPixelGameEngine.h"


///
/// \brief The Ent class currently is not used for anything in this project
/// but is saved for later as this is how we can handle entities in the world.
///
class Ent {
private:

public:
    Ent() {};
    Ent(olc::vi2d& PS, olc::PixelGameEngine* p) {

        PACK_SIZE = PS;
        pge = p;
        constructDecal();
        decalSourcePos = { 15,3 };
        entPosition = {1,1};
        tint = olc::WHITE;
    }
    std::string returnName() {
        return "";
    }
    virtual void moveSelf(int x, int y) {
        entPosition.x = entPosition.x + x;
        entPosition.y = entPosition.y + y;
    }

    virtual void DrawSelf() {
        //the ent pos gets a + 1x1 to adjust for the header bar to match up
        //with the chunkxyz's so 0x0 is the same 0x0
        pge->DrawPartialDecal((entPosition + olc::vi2d(1,1)) * PACK_SIZE, decTile.get(), decalSourcePos*PACK_SIZE, PACK_SIZE, olc::vi2d(1, 1), tint);
    }

    virtual olc::vi2d returnPos() {
        return entPosition;
    }

protected:
    std::string sEntName;
    olc::vi2d decalSourcePos;
    olc::vi2d entPosition;
    olc::Pixel tint;
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;
    //These are pointers to sprites and Decals
    std::unique_ptr<olc::Sprite> sprTile;
    std::unique_ptr<olc::Decal> decTile;

    void constructDecal() {
        sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
        decTile = std::make_unique<olc::Decal>(sprTile.get());
    }

};
//
// This is an example of an entity that can be created.
//  This is from an old implimantation of the inspection cursor
// that was moved to its own class.
//

//class InspectionEnt : public Ent {
//public:
//    InspectionEnt() {};
//    InspectionEnt(olc::vi2d& PS, olc::PixelGameEngine* p) {
//        PACK_SIZE = PS;
//        pge = p;
//        constructDecal();
//        entPosition = {1,1};
//        decalSourcePos = { 8,5 };
//        sEntName = "Inspection";
//        tint = olc::YELLOW;
//    }
//};
