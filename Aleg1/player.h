#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class player : public entity
{
private:



protected:

	MYCLASSES playerClass;
	std::vector<entity*> close_to_player;


public:

	player();
	player(int,int);
	player(int,int, MYCLASSES cl);
	~player();
	void changeColor(int,int,int);
	int getPlayerClass(){return playerClass;};
	void setCloseToPlayer(entity& e);
	std::vector<entity*>* getCloseToPlayer();


};

#endif