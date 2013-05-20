#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "player.h"
#include "globals.h"


class scenemanager
{

private:

	int pIndex;
	int aP_index; //index location of the active player

	//FPS
	double fps;
	int frames_done;
	double old_time;

	//FONTS
	ALLEGRO_FONT *font_arial12;
	ALLEGRO_BITMAP *tmpBackground;

	player* pArray[3]; //POINTERS TO PLAYERS
	entity* eArray[32];//POINTS TO ENTITIES

	std::vector<player*> veArray;


protected:



	

public:

	scenemanager();
	~scenemanager();


	void drawScene();
	void drawDebugUI();

	void addPlayer(player& p);
	player* getPlayer();

	void addEntity(entity& e);
	void checkScene(int cX,int xY);
	void sceneMovement();
	bool checkCollision(int);

	void setActivePlayer(int);
	void moveActivePlayer();
	bool bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);




};

#endif