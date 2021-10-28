#pragma once

#include "GameConfig.h"
namespace AKI {

class Popup {
private:
	bool		messageUp = false;
	std::string	message;
	olc::PixelGameEngine* pge;
	olc::vi2d blackTile = {0,2};
	olc::vi2d topBoarderTile = {13,2};
	olc::vi2d sideBoarderTile = {12,7};
	std::string sPress = "Press ";
	std::string sEnter = "Enter ";
	std::string sClose = "to close window ";
	std::shared_ptr<GameConfig> gameConfig;



	void setup() { gameConfig = std::make_unique<GameConfig>(pge); }

public:

		 Popup()		{}
		 Popup(olc::PixelGameEngine* p) {
			 pge = p;
			 setup();


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
				drawTile({x,y}, blackTile);
				if(y == xy.y) {
					drawTile({x,y}, topBoarderTile);
				}
				if(x == xy.x || x == xy.x + lengthWidth.x) {
					drawTile({x,y}, sideBoarderTile);
					if(y == xy.y || y == xy.y + lengthWidth.y) {
						drawTile({x,y}, topBoarderTile);
					}
				}
				if(y == xy.y + lengthWidth.y && x > xy.x + 14) {
					drawTile({x,y}, topBoarderTile);
				}

			}
		}
		drawColoredClose({xy.x + 1,xy.y +lengthWidth.y});

	}

	void drawColoredClose(olc::vi2d pos) {
		drawCloseString(pos,sPress);
		drawCloseString(pos + olc::vi2d(3,0),sEnter,olc::GREEN);
		drawCloseString(pos + olc::vi2d(6,0),sClose);
	}

	void drawTile(olc::vi2d tilePos, olc::vi2d& decalPos) {
		pge->DrawPartialDecal(tilePos * gameConfig->getPackSize(),
							  gameConfig->decTile.get(),
							  decalPos*gameConfig->getPackSize(),
							  gameConfig->getPackSize(),
							  olc::vi2d(1, 1),
							  olc::WHITE);
	}
	void drawString(olc::vi2d pos,std::string str, const olc::Pixel col = olc::WHITE) {
		pge->DrawStringDecal(pos * gameConfig->getPackSize(), str, col);
	}

	void drawCloseString(olc::vi2d pos,std::string str, const olc::Pixel col = olc::WHITE) {
		pge->DrawStringDecal(pos * gameConfig->getPackSize() + olc::vi2d(4,4), str, col);
	}

};
}
