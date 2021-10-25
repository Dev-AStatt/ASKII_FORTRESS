#pragma once
#include "GameEngine.h"
#include "Tilesets.h"
namespace AKI {

class Popup {
private:
	bool		messageUp;
	std::string	message;

	std::unique_ptr<Tileset> decal;

	void setup() { decal = std::make_unique<Tileset>(); }

public:

		 Popup()		{setup();}
	bool getMessageUp() {return messageUp;}

	void PopupMessage(std::string message) {
		messageUp = true;
		//this flags the game state as paused
		GAMEMODE_PAUSE();
	}

	void drawPopup() {

	}



};
}
