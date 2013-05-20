#ifndef ENTITY_H
#define ENTITY_H
#include "StdAfx.h"
#include "globals.h"

struct Movement
{
	bool shouldI;
	int start_x;
	int start_y;
	int dest_x;
	int dest_y;
};

enum MYMOVEMENT {LEFT, RIGHT, UP, DOWN, STOP};


class entity
{

private:
protected:
	
	ALLEGRO_BITMAP *pBitmapEntity;
	int size;
	int x;
	int y;
	int speed;
	bool colided;
	
	

public:
	Movement sMove;


	entity();
	entity(int,int,int,int);
	~entity();
	int getX(){return x;};
	int getY(){return y;};
	void move(MYMOVEMENT direction);
	void moveX(int nX){ x = nX; };
	void moveY(int nY){ x = nY; };
	ALLEGRO_BITMAP* getBitmap();
	int getSpeed(){return speed;};
	int getSize(){return size;};
	bool getColisionStatus(){return colided;};
	void setColisionStatus(bool c){ colided = c;};
	//void makeActive();
	void describe();

	void changeColor(int,int,int);

};

#endif