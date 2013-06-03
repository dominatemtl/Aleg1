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

	//	Store players in scene
	std::vector<player*> vpArray;
	//	Store entities in scene
	std::vector<entity*> veArray;
	//	Store rooms in scene
	std::vector<room*> roomArray;


	//	Store 800x800 sections of the map
	//	TOP LAYER
	std::vector<entity*> Map1;			// X: 0 - 800		: Y: 0 - 800
	std::vector<entity*> Map2;			// X: 801 - 1600	: Y: 0 - 800
	std::vector<entity*> Map3;			// X: 1601 - 2000	: Y: 0 - 800
	std::vector<entity*> Map4;			// X: 2601 - 3200	: Y: 0 - 800

	//	MIDDLE LAYER
	std::vector<entity*> Map5;			// X: 0 - 800		: Y: 801 - 1600
	std::vector<entity*> Map6;			// X: 801 - 1600	: Y: 801 - 1600
	std::vector<entity*> Map7;			// X: 1601 - 2000	: Y: 801 - 1600
	std::vector<entity*> Map8;			// X: 2601 - 3200	: Y: 801 - 1600

	//	MIDDLE LAYER 2
	std::vector<entity*> Map9;			// X: 0 - 800		: Y: 1601 - 2200
	std::vector<entity*> Map10;			// X: 801 - 1600	: Y: 1601 - 2200
	std::vector<entity*> Map11;			// X: 1601 - 2000	: Y: 1601 - 2200
	std::vector<entity*> Map12;			// X: 2601 - 3200	: Y: 1601 - 2200

	//	BOTTOM LAYER
	std::vector<entity*> Map13;			// X: 0 - 800		: Y: 2201 - 3200
	std::vector<entity*> Map14;			// X: 801 - 1600	: Y: 2201 - 3200
	std::vector<entity*> Map15;			// X: 1601 - 2000	: Y: 2201 - 3200
	std::vector<entity*> Map16;			// X: 2601 - 3200	: Y: 2201 - 3200



protected:



	

public:

	scenemanager();
	~scenemanager();


	void drawScene();
	void drawDebugUI();

	void addPlayer(player& p);
	player* getPlayer();

	void addEntity();
	void checkScene(int cX,int xY);
	void sceneMovement();

	//	COLLISION
	bool checkCollision(int);
	void updateNearbyObjects(int index);
	bool bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);

	void setActivePlayer(int);
	void moveActivePlayer();

	//	ROOMS
	void initRoom(int r);
	void initRoomClear();
	bool roomOnMouse();
	void setRoomLocation(float pX, float pY);	//	Follow the mouse
	void setRoomLocation(float pX, float pY, bool t);	//	Place tile
	void drawRooms();





};

#endif