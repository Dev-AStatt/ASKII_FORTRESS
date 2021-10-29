#pragma once
#include "GameConfig.h"
#include "engine/graphicsengine.h"

namespace AKI {

class Popup {
private:
	bool		messageUp = false;
	olc::vi2d backgroundPos = {11,2};
	std::string	message;

	olc::vi2d blackTile = {0,2};
	olc::vi2d topBoarderTile = {13,2};
	olc::vi2d sideBoarderTile = {12,7};
	std::string sPress = "Press ";
	std::string sEnter = "Enter ";
	std::string sClose = "to close window ";
	std::shared_ptr<GameConfig> gameConfig;
	std::shared_ptr<GraphicsEngine> graphicsEngine;





public:

		 Popup()		{}
		 Popup(std::shared_ptr<GraphicsEngine> ge, std::shared_ptr<GameConfig> gc) {
			 graphicsEngine = ge;
			 gameConfig = gc;


		}
	bool getMessageUp() {return messageUp;}
	void closeMessage() {messageUp = false;}

	void PopupMessage(std::string m) {
		messageUp = true;
		message = m;
	}

	void drawPopup() {
		olc::vi2d xy = {16,16};
		olc::vi2d lengthWidth = {24,2};

		for(int y = xy.y; y <= xy.y + lengthWidth.y; ++y) {
			for(int x = xy.x; x <= xy.x + lengthWidth.x; ++x) {
				graphicsEngine->drawTile({x,y}, blackTile);
				if(y == xy.y) {
					graphicsEngine->drawTile({x,y}, topBoarderTile);
				}
				if(x == xy.x || x == xy.x + lengthWidth.x) {
					graphicsEngine->drawTile({x,y}, sideBoarderTile);
					if(y == xy.y || y == xy.y + lengthWidth.y) {
						graphicsEngine->drawTile({x,y}, topBoarderTile);
					}
				}
				if(y == xy.y + lengthWidth.y && x > xy.x + 14) {
					graphicsEngine->drawTile({x,y}, topBoarderTile);
				}

			}
		}

		drawColoredClose({xy.x + 1,xy.y +lengthWidth.y});
		graphicsEngine->drawString({xy.x + 1,xy.y + 1},message,olc::CYAN);

	}

	void drawColoredClose(olc::vi2d pos) {
		graphicsEngine->drawString(pos,sPress,olc::WHITE,{4,4});
		graphicsEngine->drawString(pos + olc::vi2d(3,0),sEnter,olc::GREEN,{4,4});
		graphicsEngine->drawString(pos + olc::vi2d(6,0),sClose,olc::WHITE,{4,4});
	}
};
}
