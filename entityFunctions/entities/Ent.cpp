#include "Ent.h"

Ent::Ent(std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc,
		 std::shared_ptr<Tiles::TileManager> tm, std::string n) {

	//These lines should be overwritten by inheriting classes
	decalSourcePos		= { 15,3 };
	entZPosition		= 0;
	position			= {1,1,0};
	viewDistance		= 3;
	thirst				= 100;
	tint				= olc::WHITE;
	sEntName			= n;
	constructEntBasics(tm,ge,gc);
}

void Ent::constructEntBasics(std::shared_ptr<Tiles::TileManager> tm,
							 std::shared_ptr<AKI::GraphicsEngine> ge, std::shared_ptr<AKI::GameConfig> gc) {
	gameConfig = gc;
	graphicsEngine = ge;
	tileManager = tm;
	Destination = std::make_unique<Memories::EntDest>();
	entMemory = std::make_shared<Memories::EntMemory>();
	sight = std::make_unique<EntSight>(viewDistance,tileManager,entMemory);
	alive = true;

}

// O----------------------------------------------------O
// | Drawing of Entity Code						        |
// O----------------------------------------------------O

void Ent::DrawSelf(int activeZLayer, olc::vi2d& viewOffset) const {
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

int Ent::AKIRand(int from, int to) const {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(from, to); // define the range
	return distr(gen);
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
			//std::cout << sEntName << " Has Arived At Destination" << '\n';
			switch (Destination->getPriority()) {
			case Memories::water:
				drink();
				entMemory->addMemory(position,Memories::water,Tiles::Water);
				break;
			case Memories::food:
				eat();
				entMemory->addMemory(position,Memories::food,0);
				break;
			default:
				std::cout << "we fell out of switch in Ent Pathfinding" << '\n';
				break;
			}

		} else {
			//std::cout << sEntName << " Is Following A Destination" << '\n';
			moveSelfI3d(Destination->directionToDest(position));
		}
		return true;
	}
	if(vPriorities[0] == Memories::water) {
		auto vRemember = entMemory->rememberVector(Memories::water);
		if(vRemember.size() > 0) {
			Destination->setNewDest(vRemember[0].position,vRemember[0].priority,vRemember[0].id);
		} else {
			auto searchResult = sight->GetSlabInTree(Tiles::Water);
			if(!searchResult.first) {return false;} //if search result found nothing break
			//else
			//debug lines
			std::string s = sEntName + " Found Water";
			graphicsEngine->addDebugString(s);
			//
			Destination->setNewDest(searchResult.second,Memories::water,Tiles::Water);
			//move tward tile
			moveSelfI3d(Destination->directionToDest(position));
			return true;
		}
	}
	if(vPriorities[0] == Memories::food) {
		auto vRemember = entMemory->rememberVector(Memories::food);
		if(vRemember.size() > 0) {
			Destination->setNewDest(vRemember[0].position,vRemember[0].priority,vRemember[0].id);
		} else {
			//pair, first is a bool for found,
			auto searchResult = sight->getFoodLocInTree();
			if(!searchResult.first) {return false;} //if search finds nothing break
			std::string s = sEntName + " Found Food";
			graphicsEngine->addDebugString(s);
			//get location of food
			auto tmp = searchResult.second;
			Destination->setNewDest({tmp.x,tmp.y,position.z},Memories::food,0);	//set destindation of food
			moveSelfI3d(Destination->directionToDest(position));					//Go To Food
			return true;
		}
	}
	return false;
}



















