#include "GameEngine.h"

//project Push test
//1


//GLOBAL VARIABLES
int PACK_SIZE = 16;
int PACK_SCALE = 1;

int main()
{
	GameEngine game;

	int windowY =  (2* PACK_SIZE) + (PACK_SIZE * 16 * 2);
	int windowX = (3 * PACK_SIZE) + (PACK_SIZE * 16 * 4);



	//If you change the construct, you now also have to change the adjustment in Map.cpp
	if (game.Construct(windowX, windowY, PACK_SCALE, PACK_SCALE)) {
		//old (768, 384, 2, 2)
		game.Start();
	}
	
	return 0;
}

