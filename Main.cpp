#include "GameEngine.h"

//
// <summary>
//	This is the start of Project ASKII FORTRESS, Created by Aaron Statt
//	Date: Late 2020 - Current
//	The goal of this project is to try and design a Dwarf Fortress like game
//	with Si-Fi spin on the same tile based map layout. This is to try and learn
//	as much about programming as I can while doing something fun while Jess is
//	watching TV.
//


int main()
{
	GameEngine game;
	//There are two variables that are needed at start. The texture pack size PACK_SIZE
	//and the scale of the game. This scales how may pixles match each pixle of the pack
	int PACK_SIZE = 16;
	int PACK_SCALE = 2;

	//This constructs how big the window will be. 16 is the chunk size; this is fixed through the
	//code and should not be changed.
	int windowY =  (2* PACK_SIZE) + (PACK_SIZE * 16 * 2);
	int windowX = (3 * PACK_SIZE) + (PACK_SIZE * 16 * 4);

	//If you change the construct, you now also have to change the adjustment in Map.cpp
	//(I dont know if this is true anymore: AS Oct21
	if (game.Construct(windowX, windowY, PACK_SCALE, PACK_SCALE)) {
		//old (768, 384, 2, 2)
		game.Start();
	}
	
	return 0;
}

