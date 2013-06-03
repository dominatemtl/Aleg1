#ifndef ROOMS_H
#define ROOMS_H
#include "StdAfx.h"

enum GOBLINROOMS {HALL, EMPTYROOM, TREASUREROOM, TORTUREROOM};

class room
{
private:
protected:

	int location_x,location_y, size_x, size_y;
	ALLEGRO_COLOR backgroundColor;
	bool inScene;
	bool onMouse;

public:
	//	Constructors
	room(int r);
	room(int x, int y, int sX, int sY);
	room(int x, int y, int sX, int sY, ALLEGRO_COLOR color);
	//	Decontructor
	~room();
	bool isOnMouse(){return onMouse;};
	void setOnMouse(bool t){ onMouse = t;}
	bool isInScene(){return inScene;};
	void setInScene(bool t){ inScene = t;}

	void drawRoom();
	void setLocation(float pX, float pY);

	int getX(){ return location_x; };
	int getY(){ return location_y; };
	int getSizeX(){ return size_x; };
	int getSizeY(){ return size_y; };

	void rotate();

};


#endif