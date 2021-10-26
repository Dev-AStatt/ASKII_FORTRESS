#pragma once

#include "GameConfig.h"
namespace AKI {

class Popup {
private:
	bool		messageUp = false;
	std::string	message;
	olc::PixelGameEngine* pge;

	std::shared_ptr<GameConfig> gameConfig;

	void setup() { gameConfig = std::make_unique<GameConfig>(pge); }

public:

		 Popup()		{}
		 Popup(olc::PixelGameEngine* p) {pge = p; setup();}
	bool getMessageUp() {return messageUp;}

	void PopupMessage(std::string m) {
		messageUp = true;
		message = m;
	}

	void drawPopup() {
		int textlines = 1;
		int t = (gameConfig->getScreenTileH()/2) - textlines;
		int l = (gameConfig->getScreenTileW()/3);
		olc::vi2d popupTL = {t,l};
		olc::vi2d popupBR = {(gameConfig->getScreenTileH()/2) + textlines,(gameConfig->getScreenTileW()/3)*2};
		pge->FillRect(popupTL.x,popupTL.y,popupBR.x,popupBR.y,olc::BLUE);


	}



};
}
