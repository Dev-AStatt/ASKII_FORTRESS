#pragma once
#include "libraries/olcPixelGameEngine.h"
#include "mapFunctions/Maps.h"
#include "InfoDisplay.h"
#include "InspectionCursor.h"
#include "EngineUtilSaveLoad.h"
#include "entityFunctions/entitieshandler.h"
#include "objectFunctions/objecthandler.h"
#include "Popup.h"
#include "GameConfig.h"



// O----------------------------------------------------O
// | Game Engine								        |
// O----------------------------------------------------O


//game engine is abstract is the explination I got for why OnUserCreate() must happen
class GameEngine : public olc::PixelGameEngine
{
private:



//Classes
	Maps chunkMap;
	std::unique_ptr<InfoDisplay> TextDisplay;
    std::unique_ptr<EngineUtilSaveLoad> utilSL;
    std::unique_ptr<EntitiesHandler> EntHandler;
	std::unique_ptr<InspectionCursor> insp;
	std::shared_ptr<ObjectHandler> ObjHandler;
	std::shared_ptr<AKI::Popup> popup;
	std::unique_ptr<AKI::GameConfig> gameConfig;


	int nLayerBackground = 0;
	//30 ticks per second.
	uint32_t gameTick = 0;
	float stopwatch = 0;

//Constants for UpdateFlashPlayer through calls.
	float timeAcc;
	bool flash;
	bool focusMenu = false;
    bool tickUpdate = false;

	olc::vi2d mapOutline;
//playable map size
    int chunkSize = 16;
    int worldSize;
	olc::vi2d mapAreaTopLeft;
    olc::vi2d mapAreaBottomRight;
//debug functions
    bool bDebugInfo = false;

//Private Functions;
	void togglegamemode();
	void updateTick(float fElapsedTime);
    void CommonRuntimeUpdates();
    void ActionUpdates();
	void DrawMapOutline();
	void DrawScreenBoarder();
	void DrawChunksToScreen();
	void UserInput();
	void GameStateChecks();

public:
	// O----------------------------------------------------O
	// | Other Methods should be able to pause game			|
	// | without having to pass a pointer to the game       |
	// O----------------------------------------------------O


	int CURRENT_GAMEMODE;
	enum eGameMode {
		mapview,
		menu,
		title,
		worldCreator,
		mapinspection,
		confirm,
		pause,
	};
	void GAMEMODE_PAUSE() {CURRENT_GAMEMODE = pause;}
	void GAMEMODE_RESUME() {CURRENT_GAMEMODE = pause;}



	GameEngine();
    virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;


};
