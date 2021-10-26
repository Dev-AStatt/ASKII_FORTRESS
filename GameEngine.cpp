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
	// Set the map outline point from screen width and hight
	mapOutline.x		=	(ScreenWidth() / 4) - 1;
	mapOutline.y		=	(ScreenHeight() - (PSIZEint * 32));
	mapAreaTopLeft		=	{1,1};
	mapAreaBottomRight	=	{chunkSize * 3, chunkSize * 2};
	//size of the texture pack in olc::vi2d
	PSIZEint	= 16;
	PACK_SIZE = {16,16};
	//Pointer Class
	chunkMap	=	Maps(PACK_SIZE,mapAreaTopLeft,mapAreaBottomRight, this);
	//Unique Pointers
	popup		=	std::make_shared<AKI::Popup>		();
	TextDisplay =	std::make_unique<InfoDisplay>		(PSIZEint,mapAreaBottomRight, this);
	insp		=	std::make_unique<InspectionCursor>	(PACK_SIZE,mapAreaTopLeft,mapAreaBottomRight,this);
	utilSL		=	std::make_unique<EngineUtilSaveLoad>();
	ObjHandler	=	std::make_shared<ObjectHandler>		(PACK_SIZE,mapAreaTopLeft,mapAreaBottomRight,this);
	EntHandler	=	std::make_unique<EntitiesHandler>	(PACK_SIZE,&chunkMap,ObjHandler,this);


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
        TextDisplay->DrawMapViewInfo(bDebugInfo,chunkMap.moveViewOffset,chunkMap.activeZLayer);
	break;

	// O------------------------------------------------------------O
	// | This is the inspection mode, gameplay is paused			|
	// | and the curser is on the screen to interact with the game	|
	// O------------------------------------------------------------O
    case mapinspection:
        CommonRuntimeUpdates();
        insp->DrawSelf();
        TextDisplay->DrawMapInspectionViewInfo(insp->returnPos(),bDebugInfo, chunkMap.moveViewOffset, chunkMap.activeZLayer);
	break;

	// O----------------------------------------------------O
	// | Title Screen								        |
	// O----------------------------------------------------O
    case title:
        if (TextDisplay->DrawTitleScreen()) {
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
                if(utilSL->loadchunks(&chunkMap)) {
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
            chunkMap.newMap(worldSize);
            if(chunkMap.mapLoaded) {
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
                if(utilSL->saveChunks(worldSize, &chunkMap)) {
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
    EntHandler->drawEntities(chunkMap.activeZLayer,mapAreaTopLeft,mapAreaBottomRight,chunkMap.moveViewOffset);
	ObjHandler->drawObjects(chunkMap.activeZLayer,chunkMap.moveViewOffset);
    UserInput();
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
	if (chunkMap.mapLoaded) {
		chunkMap.DrawActiveChunks();
	}
	
}

void GameEngine::DrawMapOutline() {
	DrawScreenBoarder();
	//This draws the map sepperator from commands
    FillRect(olc::vi2d(PACK_SIZE.x * 3 * 16 + PSIZEint, 0), olc::vi2d(PSIZEint, ScreenHeight()), olc::DARK_GREY);
}

//
//Void will use set screen Width and Hight along with the pack size to 
// Draw a boarder one tile thick around the screen.
//
void GameEngine::DrawScreenBoarder() {
	Clear(olc::BLANK);
	//Draws top bar
    FillRect(olc::vi2d(0, 0), olc::vi2d(ScreenWidth(), PSIZEint), olc::DARK_GREY);
	//Draws Bottom Bar
    FillRect(olc::vi2d(0, ScreenHeight() - PSIZEint), olc::vi2d(ScreenWidth(), ScreenHeight()), olc::DARK_GREY);
	//Draws Right Bar
    FillRect(olc::vi2d(0, 0), olc::vi2d(PSIZEint, ScreenHeight()), olc::DARK_GREY);
	//Draws Left Bar
    FillRect(olc::vi2d(ScreenWidth() - PSIZEint, 0), olc::vi2d(ScreenWidth(), ScreenHeight()), olc::DARK_GREY);
}

void GameEngine::UserInput(){
    //Get if shift key is held for modifyers
    bool shift = GetKey(olc::Key::SHIFT).bHeld;

    //Toggle Debug info
    if(!focusMenu && GetKey(olc::Key::D).bReleased) {
        bDebugInfo = !bDebugInfo;
    }


    //Z layer changing
    if (shift && GetKey(olc::Key::COMMA).bReleased) {
        chunkMap.changeZLayer(-1);
    }
    if (shift && GetKey(olc::Key::PERIOD).bReleased) {
        chunkMap.changeZLayer(1);
    }
    //offset is going to be the jump distance when holding shift
    int offset;
    if(shift) { offset = 10;}
    else {offset = 1;}

    //MapView Checks for input
    if (!focusMenu && CURRENT_GAMEMODE == mapview) {
        if (GetKey(olc::Key::UP).bReleased) {
            chunkMap.changeMapViewOffset({ 0,offset });
        }
        if (GetKey(olc::Key::DOWN).bReleased) {
            chunkMap.changeMapViewOffset({ 0,-1 * offset });
        }
        if (GetKey(olc::Key::LEFT).bReleased) {
            chunkMap.changeMapViewOffset({ offset,0 });
        }
        if (GetKey(olc::Key::RIGHT).bReleased) {
            chunkMap.changeMapViewOffset({ -1 * offset,0 });
        }
        if (GetKey(olc::Key::Z).bReleased) {
            chunkMap.resetMapViewOffset();
        }
        if (GetKey(olc::Key::S).bReleased) {
            CURRENT_GAMEMODE = confirm;
        }
    }
    //Toggle Inspection mode
    if (GetKey(olc::Key::I).bReleased) {
        togglegamemode();
    }
    //Inspection Mode Checks for input
    if (!focusMenu && CURRENT_GAMEMODE == mapinspection) {
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
            chunkMap.flipTileOnMap(pos);
        }
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
