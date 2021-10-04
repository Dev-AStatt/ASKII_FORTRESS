#pragma once
#include "olcPixelGameEngine.h"

class InfoDisplay {
private:
	int PACK_SIZE;
	olc::PixelGameEngine* pge;

	std::string s;
	uint32_t gameTick = 0;
	bool finishedAnimation = false;
	uint32_t AnimationTickStart = 0;
	int updates = 0;
	uint32_t pastTick = 0;
	int currentMenuChoice = 0;
    int mapViewMenuX;

	std::vector<std::string> mainMenuChoices = {"New Game", "Continue Game", "Options", "Exit"};

    std::vector<std::string> confirmMenuChoices = {"Yes: Save",
                                                   "No:  Do Not Save"};

    std::vector<std::string> mapViewHotkeys = {"Arrow Keys: Move Camera",
                                               "+SHIFT:     Move x10",
                                               "SHIFT+<>:   Change Z Level",
                                               "I:          Inspection View",
                                               "S:          Save Game"};
	
	void TitleBoarderAnimation();

    void DrawGamemode(std::string sGamemode,int menuSpot = 2);
    void DrawMapZ(int aZl, int menuSpot = 3);
    void DrawMapViewHotkeys(int menuStart = 4);
    void debugDrawChunkOffset(olc::vi2d mvo,int menuSpot = 10);
    void DrawString(std::string str,int strPosX, int menuSpot, const olc::Pixel col = olc::WHITE);
public:
    InfoDisplay(int packSizeIn,olc::vi2d& mapBR, olc::PixelGameEngine* p);
	
    void DrawMapViewInfo(bool bDebug,olc::vi2d moveViewOffset, int activeZLayer);
    void DrawMapInspectionViewInfo(olc::vi2d inspPos,bool bDebug,olc::vi2d moveViewOffset, int activeZLayer);
	bool DrawTitleScreen();

	void DrawTick(uint32_t tick);
    int DrawMenu(std::vector<std::string>& menuChoices, olc::vi2d menuPos);

	int mainMenu() {
        return DrawMenu(mainMenuChoices, {PACK_SIZE * 16,10});
	}
    int confirmMenu() {
        return DrawMenu(confirmMenuChoices,{mapViewMenuX,2});
    }
    int newGameMenu() {
        return 0;
    }
};

