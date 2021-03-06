#include "GameEngine.h"


GameEngine::GameEngine() {
	sAppName = "ASKII_FORTRESS";

}

// O----------------------------------------------------O
// | On User Create sets up before the game loop        |
// O----------------------------------------------------O

bool GameEngine::OnUserCreate()
{
	CURRENT_GAMEMODE = title;
	/*
	Setting up all the classes that the game engine will use

	Game Config:	What will manage all of the game variables that many classes need to view.
	Util Save Load: Class that is in charge of the I/O for saving and loading games. [IN PROGRESS]
	Graphics:		Graphics engine to communicate between ASKII and PGE.
	Chunk Manager:	Holds all the chunks of the game, completes map opperations.
	Popup:			Handles any game information that needs to be displayed as a notification
	*/
	gameConfig		= std::make_shared<AKI::GameConfig>(this);
	utilSL			= std::make_unique<EngineUtilSaveLoad>();
	graphicsEngine	= std::make_shared<AKI::GraphicsEngine> (gameConfig,this);
	chunkManager	= std::make_shared<Maps>				(graphicsEngine,gameConfig);
	popup			= std::make_shared<AKI::Popup>			(graphicsEngine,gameConfig);
	TextDisplay		= std::make_unique<InfoDisplay>			(graphicsEngine,gameConfig,this);
	insp			= std::make_unique<InspectionCursor>	(graphicsEngine,gameConfig);
	ObjHandler		= std::make_shared<ObjectHandler>		(graphicsEngine,gameConfig);
	EntHandler		= std::make_unique<EntitiesHandler>		(graphicsEngine,gameConfig,chunkManager,ObjHandler,popup);

	return true;
}
//
// This is the function that runs every "Tick" called by the OLC Engine
// fElapesedTime is the time that has passed from the last update.
//
bool GameEngine::OnUserUpdate(float fElapsedTime)
{
	updateTick(fElapsedTime);
	TextDisplay->DrawTick(gameTick);

    switch(CURRENT_GAMEMODE) {

	// O----------------------------------------------------O
	// | Map View is the normal running mode of the game	|
	// O----------------------------------------------------O
    case mapview:
        CommonRuntimeUpdates();
		TextDisplay->DrawMapViewInfo(bDebugInfo,chunkManager->moveViewOffset,chunkManager->activeZLayer);
	break;

	// O------------------------------------------------------------O
	// | This is the inspection mode, gameplay is paused			|
	// | and the curser is on the screen to interact with the game	|
	// O------------------------------------------------------------O
    case mapinspection:
        CommonRuntimeUpdates();
        insp->DrawSelf();
		TextDisplay->DrawMapInspectionViewInfo(insp->returnPos(),bDebugInfo, chunkManager->moveViewOffset, chunkManager->activeZLayer);
	break;

	// O----------------------------------------------------O
	// | Title Screen								        |
	// O----------------------------------------------------O
	case title:
		//commented out to remove title screen
		//if (TextDisplay->DrawTitleScreen()) {
		if(true) {
            DrawScreenBoarder();

            //this is the title menu and case is the
            //return options for
            //0: New Game
            //1: Continue
            //2: Options
            //3: Exit
            switch (TextDisplay->mainMenu()) {
            case 0:
                CURRENT_GAMEMODE = worldCreator;
                break;
            case 1:
				if(utilSL->loadchunks(chunkManager)) {
                    CURRENT_GAMEMODE = mapview;
                }
                break;
            case 3:
                //closes the program
                return false;
                break;
            default:
                break;
            }
        }
	break;

	// O--------------------------------------------------------O
	// | World Creator Screen with options for world settings	|
	// O--------------------------------------------------------O
    case worldCreator:
		worldSize = TextDisplay->newGameMenu();
        if (worldSize > 0) {
            //create new map
			chunkManager->newMap(worldSize);
			if(chunkManager->mapLoaded) {
                //create new Entities
                EntHandler->newGameEntities();
                    CURRENT_GAMEMODE = mapview;
            }
        }
	break;

	// O----------------------------------------------------O
	// | Currenty this is the save selection mode, although |
	// | This should be built to the pause game mode that	|
	// | will handle the pause class menu intactions.		|
	// O----------------------------------------------------O
    case confirm:
        DrawMapOutline();
        DrawChunksToScreen();
        //This draws the Y/N confirm menu for saving the game
        // 0: Yes save game
        // anything else, Mapview game mode
        switch (TextDisplay->confirmMenu()) {
        case 0:
            //save game
            if (utilSL->SaveConfig(worldSize) > 0) {
				if(utilSL->saveChunks(worldSize, chunkManager)) {
                    CURRENT_GAMEMODE = mapinspection;
                }
            }
            break;
        case 1:
            CURRENT_GAMEMODE = mapview;
            break;
        default:
            break;
        }
        //End of second switch statement

	break;

	// O--------------------------------------------------------O
	// | What happens when the game mode is paused				|
	// O--------------------------------------------------------O
	case pause:
		CommonRuntimeUpdates();
		//DrawScreenBoarder();
		popup->drawPopup();
		if(!popup->getMessageUp()) {CURRENT_GAMEMODE = mapview;}
	break;
//
//  Default game mode opperation when none is selected
//
    default:
        DrawMapOutline();
        break;

    }
	return true;

}

void GameEngine::CommonRuntimeUpdates() {
    DrawMapOutline();
    DrawChunksToScreen();
    ActionUpdates();
	EntHandler->drawEntities(chunkManager->activeZLayer,chunkManager->moveViewOffset);
	ObjHandler->drawObjects(chunkManager->activeZLayer,chunkManager->moveViewOffset);
	graphicsEngine->updateTick(gameTick);
    UserInput();
	GameStateChecks();
}


void GameEngine::GameStateChecks() {
	if(popup->getMessageUp()) {GAMEMODE_PAUSE();}

}

void GameEngine::ActionUpdates() {
    if(tickUpdate) {
        EntHandler->updateEntities(gameTick);
    }
}

void GameEngine::DrawChunksToScreen() {
	if (chunkManager->mapLoaded) {
		chunkManager->DrawActiveChunks();
	}
	
}

void GameEngine::DrawMapOutline() {
	DrawScreenBoarder();
	//This draws the map sepperator from commands
	FillRect(olc::vi2d(gameConfig->getPackSizeInt() * 3 * 16 + gameConfig->getPackSizeInt(), 0), olc::vi2d(gameConfig->getPackSizeInt(), ScreenHeight()), olc::DARK_GREY);
}

//
//Void will use set screen Width and Hight along with the pack size to 
// Draw a boarder one tile thick around the screen.
//
void GameEngine::DrawScreenBoarder() {
	Clear(olc::BLANK);
	//Draws top bar
	FillRect(olc::vi2d(0, 0), olc::vi2d(ScreenWidth(), gameConfig->getPackSizeInt()), olc::DARK_GREY);
	//Draws Bottom Bar
	FillRect(olc::vi2d(0, ScreenHeight() - gameConfig->getPackSizeInt()), olc::vi2d(ScreenWidth(), ScreenHeight()), olc::DARK_GREY);
	//Draws Right Bar
	FillRect(olc::vi2d(0, 0), olc::vi2d(gameConfig->getPackSizeInt(), ScreenHeight()), olc::DARK_GREY);
	//Draws Left Bar
	FillRect(olc::vi2d(ScreenWidth() - gameConfig->getPackSizeInt(), 0), olc::vi2d(ScreenWidth(), ScreenHeight()), olc::DARK_GREY);
}

void GameEngine::UserInput(){
    //Get if shift key is held for modifyers
    bool shift = GetKey(olc::Key::SHIFT).bHeld;



    //Toggle Debug info
	if(GetKey(olc::Key::D).bReleased) {
        bDebugInfo = !bDebugInfo;
		popup->PopupMessage("dick");
    }


    //Z layer changing
    if (shift && GetKey(olc::Key::COMMA).bReleased) {
		chunkManager->changeZLayer(-1);
    }
    if (shift && GetKey(olc::Key::PERIOD).bReleased) {
		chunkManager->changeZLayer(1);
    }
    //offset is going to be the jump distance when holding shift
    int offset;
    if(shift) { offset = 10;}
    else {offset = 1;}

	// O--------------------------------------------------------O
	// | MapView Checks for input								|
	// O--------------------------------------------------------O
	if (CURRENT_GAMEMODE == mapview) {
        if (GetKey(olc::Key::UP).bReleased) {
			chunkManager->changeMapViewOffset({ 0,offset });
        }
        if (GetKey(olc::Key::DOWN).bReleased) {
			chunkManager->changeMapViewOffset({ 0,-1 * offset });
        }
        if (GetKey(olc::Key::LEFT).bReleased) {
			chunkManager->changeMapViewOffset({ offset,0 });
        }
        if (GetKey(olc::Key::RIGHT).bReleased) {
			chunkManager->changeMapViewOffset({ -1 * offset,0 });
        }
        if (GetKey(olc::Key::Z).bReleased) {
			chunkManager->resetMapViewOffset();
        }
        if (GetKey(olc::Key::S).bReleased) {
            CURRENT_GAMEMODE = confirm;
        }
    }
	// O--------------------------------------------------------O
	// | Inspection mode checks for input						|
	// O--------------------------------------------------------O

    if (GetKey(olc::Key::I).bReleased) {
        togglegamemode();
    }
    //Inspection Mode Checks for input
	if (CURRENT_GAMEMODE == mapinspection) {
        if (GetKey(olc::Key::UP).bReleased) {
            insp->moveSelf(0,-1 * offset);
        }
        if (GetKey(olc::Key::DOWN).bReleased) {
            insp->moveSelf(0,offset);
        }
        if (GetKey(olc::Key::LEFT).bReleased) {
            insp->moveSelf(-1 * offset,0);
        }
        if (GetKey(olc::Key::RIGHT).bReleased) {
            insp->moveSelf(offset,0);
        }
        if (GetKey(olc::Key::ENTER).bReleased) {
            olc::vi2d pos = insp->returnPos();
			chunkManager->flipTileOnMap(pos);
        }
    }
	// O--------------------------------------------------------O
	// | Pause Checks for input									|
	// O--------------------------------------------------------O
	if (GetKey(olc::Key::ENTER).bReleased && CURRENT_GAMEMODE == pause) {
		popup->closeMessage();
		GAMEMODE_RESUME();
	}
}

void GameEngine::togglegamemode() {
        if (CURRENT_GAMEMODE == mapview) {
            CURRENT_GAMEMODE = mapinspection;
            return;
        }
        else {
            CURRENT_GAMEMODE = mapview;
        }
}


//Targets updating at 60 ticks per second
void GameEngine::updateTick(float ElapsedTime) {
	stopwatch = stopwatch + ElapsedTime;
	if (stopwatch >= 0.033) {
		stopwatch = 0;
		gameTick = gameTick + 1;
        tickUpdate = true;
	}
    else {tickUpdate = false;}
}
//edit


//
// pass a pointer to a class by &class
//


/*We are putting all the crap here that is code for future referance that is
* not currently needed at the moment but is helpful for featurs down the line

getkey(olc::key::up).breleased, getkey(olc::key::down).breleased,
getkey(olc::key::left).breleased, getkey(olc::key::right).breleased

//Stuff like this is to get key unput on presses
if (GetKey(olc::Key::S).bReleased) {
		//map.mapLoad();
	}
	if (GetKey(olc::Key::UP).bReleased) {

	}

*/
