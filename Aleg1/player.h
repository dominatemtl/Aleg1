#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class player : public entity
{
private:



protected:

	MYCLASSES playerClass;

public:

	player();
	player(int,int);
	player(int,int, MYCLASSES cl);
	~player();
	ALLEGRO_BITMAP* getPlayerBitmap();

	void changeColor(int,int,int);
	int getPlayerClass(){return playerClass;};

};

#endif