#include "InfoDisplay.h"

InfoDisplay::InfoDisplay(int packSizeIn,olc::vi2d& mapBR, olc::PixelGameEngine* p) {
	PACK_SIZE = packSizeIn;
	pge = p;
    //ActiveMap = m;
	finishedAnimation = false;
    mapViewMenuX = PACK_SIZE * mapBR.x + (PACK_SIZE * 3);
}

void InfoDisplay::DrawTick(uint32_t tick) {
	gameTick = tick;
	s = "t:" + std::to_string(gameTick);
	pge->DrawStringDecal(olc::vi2d(PACK_SIZE, 5), s);
}

bool InfoDisplay::DrawTitleScreen() {
	if (!finishedAnimation) {
		TitleBoarderAnimation();
		return false;
}
	else {
		
		return true;
	}
}

//
//This is a title screen animation for game startup that scrolls 
// the outside of the boarder around. 
//
void InfoDisplay::TitleBoarderAnimation() {

	int tTileMax = pge->ScreenWidth() / PACK_SIZE;
	int rTileMax = (pge->ScreenHeight() / PACK_SIZE) + tTileMax;
	int bTileMax = tTileMax + rTileMax;
	int lTileMax = bTileMax + rTileMax - tTileMax;

	if (AnimationTickStart == 0) {
		updates = 0;
		AnimationTickStart = gameTick;
}
	if (gameTick != pastTick) {
		if ((gameTick - AnimationTickStart) % 1 == 0) {
			pastTick = gameTick;
			++updates;
			++updates;
		}
	}
	//These two lines are for debugging printing the update value to the screen while the animation is running.
	//s = "updates:" + std::to_string(updates);
	//pge->DrawStringDecal(olc::vi2d(PACK_SIZE * 16 * 3 + (PACK_SIZE * 3), PACK_SIZE * 2), s);

	if (updates <= tTileMax) {
		pge->FillRect(olc::vi2d(0, 0), olc::vi2d(updates * PACK_SIZE, PACK_SIZE), olc::DARK_GREY);
	}
	else if (updates > tTileMax && updates <= rTileMax) {
		pge->FillRect(olc::vi2d(pge->ScreenWidth() - PACK_SIZE, 0), olc::vi2d(pge->ScreenWidth(), (updates - tTileMax) * PACK_SIZE), olc::DARK_GREY);
	}
	else if (updates > rTileMax && updates <= bTileMax) {
		pge->FillRect(olc::vi2d(pge->ScreenWidth() - ((updates - rTileMax) * PACK_SIZE), pge->ScreenHeight() - PACK_SIZE), olc::vi2d(pge->ScreenWidth(), pge->ScreenHeight()), olc::DARK_GREY);
	}
	else if (updates > bTileMax && updates <= lTileMax) {
		pge->FillRect(olc::vi2d(0, pge->ScreenHeight() - ((updates - bTileMax) * PACK_SIZE)), olc::vi2d(PACK_SIZE, pge->ScreenHeight()), olc::DARK_GREY);
	}
	if (updates >= lTileMax) {
		finishedAnimation = true;
	}
}

void InfoDisplay::DrawMapViewInfo(bool bDebug, olc::vi2d moveViewOffset, int activeZLayer) {
    //Constant Draw Info
    DrawMapZ(activeZLayer);
    DrawGamemode("Map-View Mode");
    DrawMapViewHotkeys();
    //Debug Information
    if(bDebug) {
        debugDrawChunkOffset(moveViewOffset);
    }

}

void InfoDisplay::DrawMapInspectionViewInfo(olc::vi2d inspPos, bool bDebug, olc::vi2d moveViewOffset,int activeZLayer){
    //Constant Draw Info
    DrawMapZ(activeZLayer);
    DrawGamemode("Inspection Mode");
    DrawMapViewHotkeys();

    if(bDebug) {
        debugDrawChunkOffset(moveViewOffset);
        //inspector cursor debug info
        s = "Insp Position: {" + std::to_string(inspPos.x) + "," + std::to_string(inspPos.y) + "}";
        DrawString(s,mapViewMenuX,11);

    }

}

//Draws the debug information for chunk offset into 10th slot
void InfoDisplay::debugDrawChunkOffset(olc::vi2d mvo, int menuSpot) {
    //Draw moveViewOffset information.
    s = "Chunk Offset: {" + std::to_string(mvo.x) + "," + std::to_string(mvo.y) + "}";
    DrawString(s,mapViewMenuX,menuSpot);

}



//Draws the passed game mode title into 2nd slot
void InfoDisplay::DrawGamemode(std::string sGamemode, int menuSpot) {
    DrawString("Gamemode: " + sGamemode, mapViewMenuX,menuSpot);

}

//Draws active map Z layer into 3rd spot
void InfoDisplay::DrawMapZ(int aZl, int menuSpot) {
    //Draw Z Level information

    s = "Z Level: " + std::to_string(aZl);
    DrawString(s, mapViewMenuX,menuSpot);
}

//Draws the menu hotkeys with a default start pos of 4
void InfoDisplay::DrawMapViewHotkeys(int menuStart){

    int menuSpot;
    for (int i = 0; i < (int)mapViewHotkeys.size(); ++i) {
        menuSpot = menuStart + i;
        DrawString(mapViewHotkeys[i],mapViewMenuX,menuSpot);

    }
}
// Uses the Drawstring decal of pge to draw string str at menu spot, and x at strPosX, ::Defaut mapViewMenuX, default white color
void InfoDisplay::DrawString(std::string str,int strPosX, int menuSpot, const olc::Pixel col) {
    pge->DrawStringDecal(olc::vi2d(strPosX, PACK_SIZE * menuSpot), str, col);
}

int InfoDisplay::DrawMenu(std::vector<std::string>& menuChoices, olc::vi2d menuPos) {
	//Draw Choices
    for (int i = 0; i < (int)menuChoices.size(); ++i) {
		if (i == currentMenuChoice) {
			//Hilight the currnet one Red
            DrawString(menuChoices[i],menuPos.x, menuPos.y + i,olc::RED);

		}
		else {
            DrawString(menuChoices[i],menuPos.x, menuPos.y + i);
        }
	}

	//Choice Selection
	if (pge->GetKey(olc::Key::UP).bReleased) {
        if (currentMenuChoice - 1 >= 0 && (currentMenuChoice - 1) < (int)menuChoices.size()) {
			--currentMenuChoice;
		}
	}
	if (pge->GetKey(olc::Key::DOWN).bReleased) {
        if (currentMenuChoice + 1 >= 0 && (currentMenuChoice + 1) < (int)menuChoices.size()) {
			++currentMenuChoice;
		}
	}
	if (pge->GetKey(olc::Key::ENTER).bReleased) {
		return currentMenuChoice;
	}


	return -1;
}

