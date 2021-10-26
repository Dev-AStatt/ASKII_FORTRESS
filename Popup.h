#pragma once
//#include "libraries/olcPixelGameEngine.h"
#include "GameConfig.h"
namespace AKI {

class Popup {
private:
	bool		messageUp;
	std::string	message;

	//std::unique_ptr<GameConfig> decal;

	//void setup() { decal = std::make_unique<GameConfig>(); }

public:

		 Popup()		{}
	bool getMessageUp() {return messageUp;}

	void PopupMessage(std::string m) {
		messageUp = true;
		message = m;
	}

	void drawPopup() {

	}



};
}
