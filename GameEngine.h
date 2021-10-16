#pragma once
#include "olcPixelGameEngine.h"
#include "mapFunctions/Maps.h"
#include "InfoDisplay.h"
#include "InspectionCursor.h"
#include "EngineUtilSaveLoad.h"
#include "entityFunctions/entitieshandler.h"


//

//game engine is abstract is the explination I got for why OnUserCreate() must happen
class GameEngine : public olc::PixelGameEngine
{
private:
	enum eGameMode {
        mapview,
		menu,
		title,
        worldCreator,
        mapinspection,
        confirm,
	};


//Classes
	Maps chunkMap;
	std::unique_ptr<InfoDisplay> TextDisplay;
    std::unique_ptr<EngineUtilSaveLoad> utilSL;
    std::unique_ptr<EntitiesHandler> EntHandler;

	int nLayerBackground = 0;
	
	//30 ticks per second. 
	uint32_t gameTick = 0;
	float stopwatch = 0;


//Constants for UpdateFlashPlayer through calls.
	float timeAcc;
	bool flash;
	bool focusMenu = false;
    bool tickUpdate = false;

    int PSIZEint;
    olc::vi2d PACK_SIZE;
	olc::vi2d mapOutline;

    //InspectionIcon items (Move to class later?)
    void togglegamemode();
    std::unique_ptr<InspectionCursor> insp;
    //End of InspectionIcon stuff

    //playable map size
    int chunkSize = 16;
    int worldSize;
    olc::vi2d mapAreaTopLeft = {1,1};
    olc::vi2d mapAreaBottomRight;

    //debug functions
    bool bDebugInfo = false;

//Private Functions;
	void updateTick(float fElapsedTime);
    void CommonRuntimeUpdates();
    void ActionUpdates();
	void DrawMapOutline();
	void DrawScreenBoarder();
	void DrawChunksToScreen();
	void UserInput();

public:
	
	int CURRENT_GAMEMODE;
	GameEngine();
    virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;

};
