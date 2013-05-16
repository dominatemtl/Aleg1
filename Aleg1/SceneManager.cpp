#include "SceneManager.h"

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
}
void scenemanager::drawScene()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//DRAW TILEMAP
//	drawTilemap();

	//DRAW PLAYERS


  //  ALLEGRO_TRANSFORM transform;
    float w, h;

	if(scroll_x < 0)
		scroll_x = 0;
	 if((scroll_x + SCREEN_W) / zoom > 3200)
	//	scroll_x = 3200 * zoom;
	
	if(scroll_y < 0)
		scroll_y = 0;
	

  //  w = al_get_display_width(display);
  //  h = al_get_display_height(display);
 //
 //   /* Initialize transformation. */
    al_identity_transform(&transform);
 //   /* Move to scroll position. */
    al_translate_transform(&transform, -scroll_x, -scroll_y);
   /* Rotate and scale around the center first. */
  //  al_rotate_transform(&transform, rotate);
    al_scale_transform(&transform, zoom, zoom);
   /* Move scroll position to screen center. */
  // al_translate_transform(&transform, w , h);
    /* All subsequent drawing is transformed. */
    al_use_transform(&transform);




	tile_map_draw();

	for(int i =0; i < pIndex ; i++)
	{
		if(pArray[i]->getPlayerClass() == WIZARD)
		{
			al_draw_bitmap_region(pArray[i]->getPlayerBitmap(),0, 0, 60, 96, pArray[i]->getX(), pArray[i]->getY(),0);
		
			
		}
		else
		{
			al_draw_bitmap(pArray[i]->getPlayerBitmap(), pArray[i]->getX(), pArray[i]->getY(), 0);
		}
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
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670, 5, ALLEGRO_ALIGN_RIGHT,"%4.f",fps);
	al_draw_text(font_arial12,al_map_rgb(255,255,255),650, 5, ALLEGRO_ALIGN_RIGHT, "FPS");

	al_draw_text(font_arial12,al_map_rgb(255,255,255),650, 18, ALLEGRO_ALIGN_RIGHT, "Selected player");
	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670, 18, ALLEGRO_ALIGN_RIGHT,"%i",aP_index);

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670, 31, ALLEGRO_ALIGN_RIGHT, "X: %i Y: %i",pArray[aP_index]->getX(),pArray[aP_index]->getY());

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670, 43, ALLEGRO_ALIGN_RIGHT, "Dest-X: %i Dest-Y: %i",pArray[aP_index]->sMove.dest_x,pArray[aP_index]->sMove.dest_y);

	al_draw_textf(font_arial12,al_map_rgb(255,255,255),670, 56, ALLEGRO_ALIGN_RIGHT, "Zoom Level: %f",zoom);
}
void scenemanager::drawTilemap()
{
	//al_draw_bitmap(tmpBackground,-87,81,0);
}
void scenemanager::sceneMovement()
{
	//Itterate through all players moving them if needed.
	for(int i =0; i < pIndex ; i++)
	{
		if(pArray[i]->sMove.shouldI) //See if the object should move
		{

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
void scenemanager::addPlayer(player& p)
{
	pArray[pIndex] = &p;

	if(pIndex == 0 )
		setActivePlayer(0);

	pIndex++;

}
player* scenemanager::getPlayer()
{
	return pArray[aP_index];
}
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

void scenemanager::addEntity(entity& e)
{


}
bool scenemanager::checkCollision(int index)
{
	//check x,y object against other members of the array
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

	return false;
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



