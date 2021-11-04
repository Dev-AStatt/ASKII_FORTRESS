#include "Ent.h"

Ent::Ent(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
		 std::shared_ptr<TileID::TileManager> tm, std::string n) {
	constructEntBasics(tm,ge,gc);
	//These lines should be overwritten by inheriting classes
	decalSourcePos		= { 15,3 };
	entZPosition		= 0;
	position			= {1,1,0};
	viewDistance		= 3;
	thirst				= 100;
	tint				= olc::WHITE;
	sEntName			= n;
	sight = std::make_unique<EntSight>(viewDistance,tileManager);
}

void Ent::constructEntBasics(std::shared_ptr<TileID::TileManager> tm,
							 std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc) {
	gameConfig = gc;
	graphicsEngine = ge;
	tileManager = tm;
	Destination = std::make_unique<Memories::EntDest>();
	alive = true;

}

// O----------------------------------------------------O
// | Drawing of Entity Code						        |
// O----------------------------------------------------O

void Ent::DrawSelf(int activeZLayer, olc::vi2d& viewOffset) {
	if(activeZLayer == position.z) {
		olc::vi2d entFinalPos = {position.x + viewOffset.x,position.y + viewOffset.y };
		//the ent pos gets a + 1x1 to adjust for the header bar to match up
		//with the chunkxyz's so 0x0 is the same 0x0
		entFinalPos = entFinalPos + olc::vi2d(1,1);
		graphicsEngine->drawTile(entFinalPos,decalSourcePos,tint);

	}
}

// O----------------------------------------------------O
// | Utilities of Entity Code					        |
// O----------------------------------------------------O

int Ent::AKIRand(int from, int to) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(from, to); // define the range
	return distr(gen);
}


void Ent::updateInteractableCoords() {
	I3dInteractCoords.clear();
	//add directly above entity
	I3dInteractCoords.emplace_back(position.I3d_ZOffset(1));
	//add 1 space around and the space itself
	for(int y = notNegativeXY(position.y - 1); y <= position.y + 1; ++y) {
		for(int x = notNegativeXY(position.x - 1); x <= position.x + 1; ++x) {
			I3dInteractCoords.emplace_back(AKI::I3d(x,y,position.z));
		}
	}
	//add directly below Entity
	I3dInteractCoords.emplace_back(position.I3d_ZOffset(-1));
}

// O----------------------------------------------------O
// | Movement of Entity Code					        |
// O----------------------------------------------------O

//takes in the unit vector directions wanting to move. Ex: {-1, 0, 0}
void Ent::moveSelf(int x, int y ,int z) {
	//check if tile going to walk on is "walkable"
	if(sight->watchYourStep({x,y,z})) {
		position += AKI::I3d(x,y,z);


	}
}
// O----------------------------------------------------O
// | End Movement of Entity Code				        |
// O----------------------------------------------------O


// O----------------------------------------------------O
// | Start of Pathfinding Code					        |
// O----------------------------------------------------O


bool Ent::pathfinding() {
	if((int)vPriorities.size() <= 0) { return false;}

	//look if already has a destination with the same prioirity
	if(Destination->getPriority() == vPriorities[0]) {
		if(Destination->arivedAtDest(position)) {
			std::cout << sEntName << " Has Arived At Destination" << '\n';
		} else {
			//std::cout << sEntName << " Is Following A Destination" << '\n';
			moveSelfI3d(Destination->directionToDest(position));
		}
		return true;
	}
	if(vPriorities[0] == Memories::water) {

		auto searchResult = sight->searchTree(TileID::Water);
		if(!searchResult.first) {return false;} //if search result found nothing break
		//else
		//debug lines
		std::string s = sEntName + " Found Water";
		graphicsEngine->addDebugString(s);
		//
		Destination->setNewDest(searchResult.second,Memories::water,TileID::Water);
		//move tward tile
		moveSelfI3d(Destination->directionToDest(position));
		return true;
	}
	if(vPriorities[0] == Memories::food) {
		//check to see if there is anything edable in view
		if(!searchForFood()) { return false;}
		std::cout << sEntName << " Has Found Food" << '\n';
		//get location of food
		olc::vi2d tmp = locationOfFood();
		Destination->setNewDest({tmp.x,tmp.y,position.z},Memories::food,foodIDAt(tmp));	//set destindation of food
		moveSelfI3d(Destination->directionToDest(position));					//Go To Food
		return true;
	}
	return false;
}


int Ent::foodIDAt(olc::vi2d XY) {
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->getXPos() == XY.x &&objectPtrsInView[i]->getYPos() == XY.y) {
			return objectPtrsInView[i]->getID();
		}
	}
	return -1;
}

bool Ent::searchForFood() {
	if((int)objectPtrsInView.size() > 0) {
		for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
			if(objectPtrsInView[i]->isEdable()) {
				return true;
			}
		}
	}
	return false;
}

olc::vi2d Ent::locationOfFood() {
	AKI::I3d closest, tmp;
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->isEdable()) {
			closest = {objectPtrsInView[i]->getXPos(),objectPtrsInView[i]->getYPos(),position.z};
		}
	}
	for(int i = 0; i < (int)objectPtrsInView.size(); ++i) {
		if(objectPtrsInView[i]->isEdable()) {
			tmp = {objectPtrsInView[i]->getXPos(),objectPtrsInView[i]->getYPos(),position.z};
			if(true) {
				closest = tmp;
			}
		}
	}
	std::cout << sEntName << " Found Food At: " << "{" << std::to_string(closest.x)<< ", " << std::to_string(closest.y) << "}" << '\n';
	return {closest.x,closest.y};
}






















