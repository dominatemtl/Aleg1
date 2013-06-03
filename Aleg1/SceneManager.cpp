#include "SceneManager.h"

//	CONSTRUCTOR and DECONSTRUCTOR
scenemanager::scenemanager()
{
	//CREATE index and player pointers
	pIndex = 0;
	pArray[0] = NULL;
	pArray[1] = NULL;
	pArray[2] = NULL;

	aP_index = 0;	//default active player is 0

	font_arial12 = al_load_ttf_font("arial.ttf",14,0);

	// FPS 
	fps = 0;
	frames_done = 0;
	old_time = al_get_time();

	//TILEMAP
	tmpBackground = al_load_bitmap("tmpTILEMAP.png");



}
scenemanager::~scenemanager()
{
	al_destroy_font(font_arial12);
	al_destroy_bitmap(tmpBackground);

	//CLEAN UP Vector objects
	size_t sz = veArray.size();
	for (size_t i = 0; i < sz; ++i)
		delete veArray[i];

	for (int i = 0; i < roomArray.size(); ++i)
		delete roomArray[i];
}

//	Screen drawing functions
void scenemanager::drawScene()
{

	al_clear_to_color(al_map_rgb(0, 0, 0));

	//CAMERA CONSTRAINTS
	if(scroll_x < 0)
		scroll_x = 0;
	if(scroll_x + (SCREEN_W / zoom)  > 3200 )
		scroll_x = 3200 - (SCREEN_W / zoom);
	if(scroll_y < -72 / zoom)
		scroll_y = -72 / zoom;
	if(scroll_y + (SCREEN_H / zoom)  > 3200 )
		scroll_y = 3200 - (SCREEN_H / zoom);

	

	//CAMERA SCALE AND TRANSLATE
	al_identity_transform(&transform);
	al_translate_transform(&transform, -scroll_x, -scroll_y);
	al_scale_transform(&transform, zoom, zoom);
	al_use_transform(&transform);

	//DRAW MAP
	tile_map_draw();
	drawRooms();
	

	for(int i =0; i < pIndex ; i++)
	{
		if(pArray[i]->getPlayerClass() == WIZARD)
		{
			al_draw_bitmap_region(pArray[i]->getBitmap(),0, 0, 60, 96, pArray[i]->getX(), pArray[i]->getY(),0);


		}
		else
		{
			al_draw_bitmap(pArray[i]->getBitmap(), pArray[i]->getX(), pArray[i]->getY(), 0);
		}
	}

	//VECTOR TESTING


	for(int i = 0; i < veArray.size() ; i++)
	{
		al_draw_bitmap(veArray[i]->getBitmap(), veArray[i]->getX(), veArray[i]->getY(), 0);

	}

	

	al_identity_transform(&transform);
	al_use_transform(&transform);

	//DRAW Debug information
	drawDebugUI();


}
void scenemanager::drawDebugUI()
{
	//FPS
	double game_time = al_get_time();
	if(game_time - old_time >= 1.0) 
	{
		fps = frames_done / (game_time - old_time);

		frames_done = 0;
		old_time = game_time;
	}
	frames_done++;

	al_draw_filled_rectangle(0, 0, SCREEN_W, 72, al_map_rgb(0,0,0));

	//DRAW
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),460 + (SCREEN_W - 680), 5, ALLEGRO_ALIGN_CENTER, "SCREEN_W:%i",SCREEN_W);
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),460 + (SCREEN_W - 680), 18, ALLEGRO_ALIGN_CENTER, "SCREEN_H:%i",SCREEN_H);

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),460 + (SCREEN_W - 680), 31, ALLEGRO_ALIGN_CENTER, "Scroll_x:%i",(int)scroll_x);
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),460 + (SCREEN_W - 680), 43, ALLEGRO_ALIGN_CENTER, "Scroll_y:%i",(int)scroll_y);


	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670 + (SCREEN_W - 680), 5, ALLEGRO_ALIGN_RIGHT,"%4.f",fps);
	al_draw_text(font_arial12,al_map_rgb(255,255,255),650 + (SCREEN_W - 680), 5, ALLEGRO_ALIGN_RIGHT, "FPS");

	al_draw_text(font_arial12,al_map_rgb(255,255,255),650 + (SCREEN_W - 680), 18, ALLEGRO_ALIGN_RIGHT, "Selected player");
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670 + (SCREEN_W - 680), 18, ALLEGRO_ALIGN_RIGHT,"%i",aP_index);

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670 + (SCREEN_W - 680), 31, ALLEGRO_ALIGN_RIGHT, "X: %i Y: %i",pArray[aP_index]->getX(),pArray[aP_index]->getY());

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670 + (SCREEN_W - 680), 43, ALLEGRO_ALIGN_RIGHT, "Dest-X: %i Dest-Y: %i",pArray[aP_index]->sMove.dest_x,pArray[aP_index]->sMove.dest_y);

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670 + (SCREEN_W - 680), 56, ALLEGRO_ALIGN_RIGHT, "Zoom Level: %f",zoom);
}
void scenemanager::drawRooms()
{
	for(int i = 0; i < roomArray.size(); i++)
	{

		if(roomArray[i]->isOnMouse())
		{
			roomArray[i]->drawRoom();
		}
		if(roomArray[i]->isInScene())
		{
			roomArray[i]->drawRoom();
		}

	}

}

//	Player movement functions
void scenemanager::sceneMovement()
{
	//Itterate through all players moving them if needed.
	for(int i =0; i < pIndex ; i++)
	{
		if(pArray[i]->sMove.shouldI) //See if the object should move
		{

			//REWRITE TO CALL checkCollision once

			fprintf(stderr, "MOVED: X:%i Y:%i\n",pArray[i]->getX(),pArray[i]->getY());
			if(pArray[i]->getX() == pArray[i]->sMove.dest_x && pArray[i]->getY() == pArray[i]->sMove.dest_y) //Its there
			{
				pArray[i]->move(STOP);
				fprintf(stderr, "Im Here.\n");
			}
			if(pArray[i]->getX() > pArray[i]->sMove.dest_x)
			{
				pArray[i]->move(LEFT);
				if(checkCollision(aP_index))
				{
					pArray[i]->move(RIGHT);
				}

			}
			else if(pArray[i]->getX() < pArray[i]->sMove.dest_x)
			{
				pArray[i]->move(RIGHT);
				if(checkCollision(aP_index))
				{
					pArray[i]->move(LEFT);
				}

			}
			if(pArray[i]->getY() < pArray[i]->sMove.dest_y)
			{

				pArray[i]->move(DOWN);
				if(checkCollision(aP_index))
				{
					pArray[i]->move(UP);
				}

			}
			else if(pArray[i]->getY() > pArray[i]->sMove.dest_y)
			{
				pArray[i]->move(UP);
				if(checkCollision(aP_index))
				{
					pArray[i]->move(DOWN);
				}

			}

		}

	}
	//Move elements at the space time

	//check for collision



}
void scenemanager::moveActivePlayer()
{

	if(keys[KEY_UP] && pArray[aP_index]->getY() >= 4.0)
	{
		pArray[aP_index]->move(UP);
		pArray[aP_index]->sMove.shouldI = false;

		if(checkCollision(aP_index))
		{
			pArray[aP_index]->move(DOWN);

		}
	}
	if(keys[KEY_DOWN] && pArray[aP_index]->getY() <= 3200 - 32)
	{
		pArray[aP_index]->move(DOWN);
		pArray[aP_index]->sMove.shouldI = false;

		if(checkCollision(aP_index))
		{
			pArray[aP_index]->move(UP);

		}
	}
	if(keys[KEY_LEFT] && pArray[aP_index]->getX() >= 4.0)
	{
		pArray[aP_index]->move(LEFT);
		pArray[aP_index]->sMove.shouldI = false;

		if(checkCollision(aP_index))
		{
			pArray[aP_index]->move(RIGHT);

		}

	}
	if(keys[KEY_RIGHT] && pArray[aP_index]->getX() <= 3200 - 32)
	{
		pArray[aP_index]->move(RIGHT);
		pArray[aP_index]->sMove.shouldI = false;

		if(checkCollision(aP_index))
		{
			pArray[aP_index]->move(LEFT);

		}

	}




}
void scenemanager::addPlayer(player& p)
{
	pArray[pIndex] = &p;

	if(pIndex == 0 )
		setActivePlayer(0);

	pIndex++;

	vpArray.push_back(&p);

}
player* scenemanager::getPlayer()
{
	return pArray[aP_index];
}

//	Scene MENU's and Click checking
void scenemanager::checkScene(int cX, int cY) //CHECK TO SEE IF USER CLICKED ON A SCENE ELEMENT
{

	fprintf(stderr, "CHECK SCENE: X%i Y%i\n",cX,cY);

	for(int i =0; i < pIndex ; i++)
	{
		if(cX >= pArray[i]->getX() && cX <= pArray[i]->getX() + pArray[i]->getSize()
			&& cY >= pArray[i]->getY() && cY <= pArray[i]->getY() + pArray[i]->getSize()) 
		{
			pArray[i]->describe();

			setActivePlayer(i);
			fprintf(stderr, "Player: %i now active.\n",aP_index);

		}
	}

}
void scenemanager::addEntity()
{
	//	Generate random coordinates
	int rX = rand() % 3100;
	int rY = rand() % 3100;

	//	Dynamically create new entity
	entity* tempEnt = new entity(rX,rY,0,32);
	veArray.push_back(tempEnt);


	//	Add new entity to map segments
	//TOP
	//	MAP-1
	if(rX < 800 && rY < 800)
		Map1.push_back(tempEnt);
	//	MAP-2
	if(rX > 801	&& rX < 1600 && rY < 800)
		Map2.push_back(tempEnt);
	//	MAP-3
	if(rX > 1601 && rX < 2400 && rY < 800)
		Map3.push_back(tempEnt);
	//	MAP-4
	if(rX > 2401 && rX < 3200 && rY < 800)
		Map4.push_back(tempEnt);
	//MIDDLE1
	//	MAP-5
	if(rX < 800 && rY > 801 && rY < 1600)
		Map5.push_back(tempEnt);
	//	MAP-6
	if(rX > 801	&& rX < 1600 && rY > 801 && rY < 1600)
		Map6.push_back(tempEnt);
	//	MAP-7
	if(rX > 1601 && rX < 2400 && rY > 801 && rY < 1600)
		Map7.push_back(tempEnt);
	//	MAP-8
	if(rX > 2401 && rX < 3200 && rY > 801 && rY < 1600)
		Map8.push_back(tempEnt);

	//MIDDLE2
	//	MAP-9
	if(rX < 800 && rY < 800 && rY > 1601 && rY < 2400)
		Map9.push_back(tempEnt);
	//	MAP-10
	if(rX > 801	&& rX < 1600 && rY > 1601 && rY < 2400)
		Map10.push_back(tempEnt);
	//	MAP-11
	if(rX > 1601 && rX < 2400 && rY > 1601 && rY < 2400)
		Map11.push_back(tempEnt);
	//	MAP-12
	if(rX > 2401 && rX < 3200 && rY > 1601 && rY < 2400)
		Map12.push_back(tempEnt);
	//BOTTOM
	//	MAP-13
	if(rX < 800 && rY < 800 && rY > 2401 && rY < 3200)
		Map13.push_back(tempEnt);
	//	MAP-14
	if(rX > 801	&& rX < 1600 && rY > 2401 && rY < 3200)
		Map14.push_back(tempEnt);
	//	MAP-15
	if(rX > 1601 && rX < 2400 && rY > 2401 && rY < 3200)
		Map15.push_back(tempEnt);
	//	MAP-16
	if(rX > 2401 && rX < 3200 && rY > 2401 && rY < 3200)
		Map16.push_back(tempEnt);



}
void scenemanager::setActivePlayer(int i)
{

	if(!(aP_index == i))
	{

		if(pArray[i]->getPlayerClass() == WIZARD)
		{
			//
			fprintf(stderr, "I'm ad WIZARD HARRY!",i);
			pArray[aP_index]->changeColor(0,0,0);
			aP_index = i;
		}
		else
		{	
			fprintf(stderr, "setActivePlayer: %i\n",i);
			if(pArray[aP_index]->getPlayerClass() == NONE)
				pArray[aP_index]->changeColor(0,0,0);

			pArray[i]->changeColor(255,0,255);
			aP_index = i;

		}

	}

}

//	COLLISION
bool scenemanager::checkCollision(int index)
{

	//	Terrible spot for this
	updateNearbyObjects(index);

	//	Player vs. Player collision
	fprintf(stderr, "CHECK: %i\n",index);
	for(int i =0; i < pIndex ; i++) 
	{
		fprintf(stderr, "--AGAINST: %i\n",i);
		if(index == i)
		{
			//skip processing
		}
		else if(bounding_box_collision(pArray[index]->getX(),pArray[index]->getY(),pArray[index]->getSize(),pArray[index]->getSize(),
			pArray[i]->getX(),pArray[i]->getY(),pArray[i]->getSize(),pArray[i]->getSize()))
		{
			pArray[index]->setColisionStatus(true);
			pArray[index]->sMove.shouldI = false;
			fprintf(stderr, "OBECT:%i collided with OBJECT:%i\n",index,i);
			return true;
		}

	}

	// Check players against nearby entities

	std::vector<entity*>* pCloseEntity = pArray[index]->getCloseToPlayer();

	for(int i =0; i < pCloseEntity->size() ; i++) 
	{

		fprintf(stderr, "--AGAINST: %i\n",i);


		if(bounding_box_collision(pArray[index]->getX(),pArray[index]->getY(),pArray[index]->getSize(),pArray[index]->getSize(),
			(*pCloseEntity)[i]->getX(),(*pCloseEntity)[i]->getY(),(*pCloseEntity)[i]->getSize(),(*pCloseEntity)[i]->getSize()))
		{

			pArray[index]->setColisionStatus(true);
			pArray[index]->sMove.shouldI = false;
			fprintf(stderr, "OBECT:%i collided with OBJECT:%i\n",index,i);
			return true;

		}

	}



	/* WORKING CODE FOR OBJECT COLLISTION
	for(int i =0; i < veArray.size() ; i++) 
	{

	fprintf(stderr, "--AGAINST: %i\n",i);



	if(bounding_box_collision(pArray[index]->getX(),pArray[index]->getY(),pArray[index]->getSize(),pArray[index]->getSize(),
	veArray[i]->getX(),veArray[i]->getY(),veArray[i]->getSize(),veArray[i]->getSize()))
	{

	pArray[index]->setColisionStatus(true);
	pArray[index]->sMove.shouldI = false;
	fprintf(stderr, "OBECT:%i collided with OBJECT:%i\n",index,i);
	return true;

	}

	}
	*/

	return false;
}
bool scenemanager::bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
	if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
		(b1_y > b2_y + b2_h - 1) || // is b1 under b2?
		(b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
		(b2_y > b1_y + b1_h - 1))   // is b2 under b1?
	{
		// no collision

		return false;
	}

	// collision
	return true;
}
void scenemanager::updateNearbyObjects(int index)
{

	//	This function will update nearby objects with collision near the player so that I only have
	//	to do collision math against a small number. 

	//	ONLY CHECK AGAINST OBJECTS within a short distance of the moving object

	//	Break map into segments so 

	//TOP
	//	MAP-1
	if(pArray[index]->getX() < 800 && pArray[index]->getY() < 800)
	{

		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 1))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 1\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(1);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map1.size(); i++)
		{
			//	Check if player is close to object. If they are add a pointer to the entity that is close
			if(
				(pArray[index]->getX() - Map1[i]->getX() <= 34 && pArray[index]->getX() - Map1[i]->getX() >= -34)	// X
				&&
				(pArray[index]->getY() - Map1[i]->getY() <= 34 && pArray[index]->getY() - Map1[i]->getY() >= -34)	// Y
				)
			{
				pArray[index]->setCloseToPlayer(*(Map1[i]));
				fprintf(stderr,"Added to close_to_player vector\n");
			}
		}

	}

	//	MAP-2
	else if(pArray[index]->getX() > 801	&& pArray[index]->getX() < 1600 && pArray[index]->getY() < 800)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 2))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 2\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(2);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map2.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map2[i]->getX() <= 34 && pArray[index]->getX() - Map2[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map2[i]->getY() <= 34 && pArray[index]->getY() - Map2[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map2[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-3
	else if(pArray[index]->getX() > 1601 && pArray[index]->getX() < 2400 && pArray[index]->getY() < 800)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 3))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 3\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(3);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map3.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map3[i]->getX() <= 34 && pArray[index]->getX() - Map3[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map3[i]->getY() <= 34 && pArray[index]->getY() - Map3[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map3[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-4
	else if(pArray[index]->getX() > 2401 && pArray[index]->getX() < 3200 && pArray[index]->getY() < 800)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 4))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 4\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(4);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map4.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map4[i]->getX() <= 34 && pArray[index]->getX() - Map4[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map4[i]->getY() <= 34 && pArray[index]->getY() - Map4[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map4[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//MIDDLE1
	//	MAP-5
	else if(pArray[index]->getX() < 800 && pArray[index]->getY() > 801 && pArray[index]->getY() < 1600)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 5))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 5\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(5);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map5.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map5[i]->getX() <= 34 && pArray[index]->getX() - Map5[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map5[i]->getY() <= 34 && pArray[index]->getY() - Map5[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map5[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-6
	else if(pArray[index]->getX() > 801	&& pArray[index]->getX() < 1600 && pArray[index]->getY() > 801 && pArray[index]->getY() < 1600)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 6))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 6\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(6);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map6.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map6[i]->getX() <= 34 && pArray[index]->getX() - Map6[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map6[i]->getY() <= 34 && pArray[index]->getY() - Map6[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map6[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-7
	else if(pArray[index]->getX() > 1601 && pArray[index]->getX() < 2400 && pArray[index]->getY() > 801 && pArray[index]->getY() < 1600)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 7))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 7\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(7);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map7.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map7[i]->getX() <= 34 && pArray[index]->getX() - Map7[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map7[i]->getY() <= 34 && pArray[index]->getY() - Map7[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map7[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-8
	else if(pArray[index]->getX() > 2401 && pArray[index]->getX() < 3200 && pArray[index]->getY() > 801 && pArray[index]->getY() < 1600)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 8))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 8\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(8);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map8.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map8[i]->getX() <= 34 && pArray[index]->getX() - Map8[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map8[i]->getY() <= 34 && pArray[index]->getY() - Map8[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map8[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}

	//MIDDLE2
	//	MAP-9
	else if(pArray[index]->getX() < 800 && pArray[index]->getY() > 1601 && pArray[index]->getY() < 2400)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 9))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 9\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(9);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map9.size(); i++)
		{

			if(
				(pArray[index]->getX() - Map9[i]->getX() <= 34 && pArray[index]->getX() - Map9[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map9[i]->getY() <= 34 && pArray[index]->getY() - Map9[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map9[i]));
				//	ignore.push_back(i);
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-10
	else if(pArray[index]->getX() > 801	&& pArray[index]->getX() < 1600 && pArray[index]->getY() > 1601 && pArray[index]->getY() < 2400)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 10))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 10\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(10);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map10.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map10[i]->getX() <= 34 && pArray[index]->getX() - Map10[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map10[i]->getY() <= 34 && pArray[index]->getY() - Map10[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map10[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-11
	else if(pArray[index]->getX() > 1601 && pArray[index]->getX() < 2400 && pArray[index]->getY() > 1601 && pArray[index]->getY() < 2400)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 11))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 11\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(11);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map11.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map11[i]->getX() <= 34 && pArray[index]->getX() - Map11[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map11[i]->getY() <= 34 && pArray[index]->getY() - Map11[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map11[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-12
	else if(pArray[index]->getX() > 2401 && pArray[index]->getX() < 3200 && pArray[index]->getY() > 1601 && pArray[index]->getY() < 2400)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 12))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 12\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(12);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map12.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map12[i]->getX() <= 34 && pArray[index]->getX() - Map12[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map12[i]->getY() <= 34 && pArray[index]->getY() - Map12[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map12[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//BOTTOM
	//	MAP-13
	else if(pArray[index]->getX() < 800 && pArray[index]->getY() > 2401 && pArray[index]->getY() < 3200)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 13))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 13\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(13);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map13.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map13[i]->getX() <= 34 && pArray[index]->getX() - Map13[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map13[i]->getY() <= 34 && pArray[index]->getY() - Map13[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map13[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-14
	else if(pArray[index]->getX() > 801	&& pArray[index]->getX() < 1600 && pArray[index]->getY() > 2401 && pArray[index]->getY() < 3200)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 14))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 14\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(14);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map14.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map14[i]->getX() <= 34 && pArray[index]->getX() - Map14[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map14[i]->getY() <= 34 && pArray[index]->getY() - Map14[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map14[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-15
	else if(pArray[index]->getX() > 1601 && pArray[index]->getX() < 2400 && pArray[index]->getY() > 2401 && pArray[index]->getY() < 3200)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 15))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 15\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(15);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map15.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map15[i]->getX() <= 34 && pArray[index]->getX() - Map15[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map15[i]->getY() <= 34 && pArray[index]->getY() - Map15[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map15[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}
	//	MAP-16
	else if(pArray[index]->getX() > 2401 && pArray[index]->getX() < 3200 && pArray[index]->getY() > 2401 && pArray[index]->getY() < 3200)
	{
		//See if we already processed this MAP 800x800 section
		if(!(pArray[index]->getMapSectionLocation() == 16))	//	If player is new to map chunk
		{
			fprintf(stderr,"Clean Close_to_Player and SetMapsectionLocation = 16\n");
			pArray[index]->cleanCloseToPlayer();
			pArray[index]->setMapsectionLocation(16);
		}
		//	LOOP through entities in the map chunk
		for(int i = 0; i < Map16.size(); i++)
		{
			if(
				(pArray[index]->getX() - Map16[i]->getX() <= 34 && pArray[index]->getX() - Map16[i]->getX() >= -34) // X
				&&
				(pArray[index]->getY() - Map16[i]->getY() <= 34 && pArray[index]->getY() - Map16[i]->getY() >= -34)	// Y
				)
			{

				pArray[index]->setCloseToPlayer(*(Map16[i]));
				fprintf(stderr,"Added to close_to_player vector\n");

			}
		}
	}





}

//	ROOMS
void scenemanager::initRoom(int r)
{
	fprintf(stderr,"Initialized room %i\n", r);
	room* tempRoom = new room(r);
	roomArray.push_back(tempRoom);

}
void scenemanager::initRoomClear()
{
	fprintf(stderr,"Deleted room 1\n");
	delete roomArray.back();
	roomArray.pop_back();
}
bool scenemanager::roomOnMouse()
{
	for(int i = 0; i < roomArray.size(); i++)
	{

		if(roomArray[i]->isOnMouse())
		{
			return true;
		}
	}

	return false;

}
void scenemanager::setRoomLocation(float pX, float pY)
{
	//	TODO:	SNAP to other room sections
	//	TODO:	Prevent room overlap

	//	Snap to grid
	if((int)pX % 32 || (int)pY % 32)
	{
		pX -= ((int)pX % 32);
		pY -= ((int)pY % 32);
	}
	//	Loop through room array selecting only the room onMouse
	for(int i = 0; i < roomArray.size(); i++)
	{

		if(roomArray[i]->isOnMouse())
		{

			//	Center room tile on mouse
			int tempX, tempY;

			tempX = roomArray[i]->getSizeX() / 2;
			tempY = roomArray[i]->getSizeY() / 2;

			pX -= tempX;
			pY -= tempY;

			roomArray[i]->setLocation(pX,pY);

		}
	}

}
void scenemanager::setRoomLocation(float pX, float pY, bool t)	//	Place tile
{
	//	TODO:	SNAP to other room sections
	//	TODO:	Prevent room overlap

	//	Snap to grid
	if((int)pX % 32 || (int)pY % 32)
	{
		pX -= ((int)pX % 32);
		pY -= ((int)pY % 32);
	}

	//	Loop through room array selecting only the room onMouse
	for(int i = 0; i < roomArray.size(); i++)
	{

		if(roomArray[i]->isOnMouse())
		{
			//	Center room tile on mouse
			int tempX, tempY;

			tempX = roomArray[i]->getSizeX() / 2;
			tempY = roomArray[i]->getSizeY() / 2;

			pX -= tempX;
			pY -= tempY;

			roomArray[i]->setLocation(pX,pY);

			//	Drop room off the mouse and add to the scene
			if(t == false)
				roomArray[i]->setOnMouse(false);
				roomArray[i]->setInScene(true);
		}
	}

}



