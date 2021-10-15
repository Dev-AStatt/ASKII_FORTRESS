#pragma once
#include <random>

#include "olcPixelGameEngine.h"

#include "mapFunctions/Tiles.h"
#include "mapFunctions/MapUtilTileIDList.h"


///
/// \brief The Ent class currently is not used for anything in this project
/// but is saved for later as this is how we can handle entities in the world.
///
class Ent {
private:
protected:
    std::string sEntName;
    olc::vi2d decalSourcePos;
    olc::vi2d entPositionXY;
    int entPositionZ;
    int viewDistance;
    olc::Pixel tint;
    olc::vi2d PACK_SIZE;
    olc::PixelGameEngine* pge;

    //These are pointers to sprites and Decals
    std::unique_ptr<olc::Sprite> sprTile;
    std::unique_ptr<olc::Decal> decTile;

    std::unique_ptr<TileID::cTileID> cTiles;

    //field of view
    std::vector<int> fieldOfView;


    void constructDecal() {
        sprTile = std::make_unique<olc::Sprite>("art/Phoebus_16x16_Next.png");
        decTile = std::make_unique<olc::Decal>(sprTile.get());
    }
    void constructEntBasics(olc::vi2d& PS, olc::PixelGameEngine* p) {
        PACK_SIZE = PS;
        pge = p;

        constructDecal();
        cTiles = std::make_unique<TileID::cTileID>(PACK_SIZE,pge);

    }

    //Randomizer function with default inputs
    int entRand(int from = 0, int to = 10) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(from, to); // define the range
        return distr(gen);
    }



public:
    Ent() {};
    Ent(olc::vi2d& PS, olc::PixelGameEngine* p) {
        constructEntBasics(PS,p);
        //These lines should be overwritten by inheriting classes
        decalSourcePos = { 15,3 };
        entPositionXY = {1,1};
        entPositionZ = 0;
        viewDistance = 3;
        tint = olc::WHITE;
    }
    std::string returnName() {
        return "";
    }
    int returnZpos() {
        return entPositionZ;
    }
    int returnViewDistance() {
        return viewDistance;
    }

    virtual void moveSelf(int x, int y) {

        if(watchYourStep(x,y)) {
            entPositionXY = entPositionXY + olc::vi2d(x,y);
        }
    }

    //returns true if you can walk on tile in the x,y direction
    bool watchYourStep(int x, int y) {
        //this function for index is wrong
        int index = (x+viewDistance) + ((y+viewDistance) * viewDistance);
        auto& t = cTiles->vptrTiles[fieldOfView[index]];
        if(t->isWalkable()) {
            return true;
        }
        return false;
    }

    virtual void DrawSelf(int activeZLayer, olc::vi2d& viewOffset) {
        if(activeZLayer == entPositionZ) {
            olc::vi2d entFinalPos = {entPositionXY.x + viewOffset.x,entPositionXY.y + viewOffset.y };
            //the ent pos gets a + 1x1 to adjust for the header bar to match up
            //with the chunkxyz's so 0x0 is the same 0x0
            pge->DrawPartialDecal((entFinalPos + olc::vi2d(1,1)) * PACK_SIZE, decTile.get(), decalSourcePos*PACK_SIZE, PACK_SIZE, olc::vi2d(1, 1), tint);
        }
    }

    virtual olc::vi2d& returnPos() {
        return entPositionXY;
    }

    virtual void updateSelf(int tick) {

    }

    virtual void giftOfSight(std::vector<int> vSight) {
        fieldOfView = vSight;
    }


};
//
// This is an example of an entity that can be created.
//  This is from an old implimantation of the inspection cursor
// that was moved to its own class.
//

//class EntHuman : public Ent {
//public:
//    EntHuman() {};
//    EntHuman(olc::vi2d& PS, olc::PixelGameEngine* p, olc::vi2d posXY, int posZ) {
//    constructEntBasics(PS,p);
//    decalSourcePos = { 0,4 };
//    entPositionXY = posXY;
//    entPositionZ = posZ;
//    tint = olc::WHITE;
//    }
//};
