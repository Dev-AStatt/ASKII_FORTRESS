#pragma once

enum objectIDs {
	meat,
};

class Object {
protected:
	int posX;
	int posY;
	int posZ;
	bool edable;
	int decalSourcePosX;
	int decalSourcePosY;
	int itemID;
	int basicColor;

	enum objectColor {
		white,

	};
public:
	Object() {}
	Object(int sourcePosX, int sourcePosY, int sourcePosZ) {
		posX = sourcePosX; posY = sourcePosY; posZ = sourcePosZ;
	}
	int getZPos()	{return posZ;}
	int getXPos()	{return posX;}
	int getYPos()	{return posY;}
	int getDecX()	{return decalSourcePosX;}
	int getDecY()	{return decalSourcePosY;}
	bool isEdable() {return edable;}
	int getID()		{return itemID;}
	int getBColor() {return basicColor;}

};

class ObjectMeat : public Object {
public:
	ObjectMeat() {}
	ObjectMeat(int sourcePosX, int sourcePosY, int sourcePosZ) {
		posX = sourcePosX; posY = sourcePosY; posZ = sourcePosZ;
		edable = true;
		itemID = meat;
		basicColor = white;
		decalSourcePosX = 0;
		decalSourcePosY = 14;
	}
};
