#include "player.h"

player::player()
{
	
	x = 252;
	y = 252;

	speed = 4;
	size = 32;
	sMove.shouldI = false;
	sMove.dest_x = 0;
	sMove.dest_y = 0;

	colided = false;
	playerClass = NONE;

	pBitmapEntity = al_create_bitmap(size, size);
	al_set_target_bitmap(pBitmapEntity);							
	al_clear_to_color(al_map_rgb(255, 255, 000));
	
	describe();


}

player::player(int sX, int sY)
{
	x = sX;
	y = sY;

	speed = 4;
	size = 32;
	sMove.shouldI = false;
	sMove.dest_x = 0;
	sMove.dest_y = 0;
	colided = false;
	playerClass = NONE;


	pBitmapEntity = al_create_bitmap(size, size);
	al_set_target_bitmap(pBitmapEntity);							
	al_clear_to_color(al_map_rgb(255, 255, 0));
	describe();

}
player::player(int sX, int sY, MYCLASSES cl)
{



	if(cl == WIZARD)
	{

		x = sX + SCREEN_W;
		y = sY;

		speed = 4;
		size = 92;
		sMove.shouldI = false;
		sMove.dest_x = 0;
		sMove.dest_y = 0;
		colided = false;
		playerClass = WIZARD;

		pBitmapEntity = al_load_bitmap("wizard.png");
		al_set_target_bitmap(pBitmapEntity);
		al_convert_mask_to_alpha(pBitmapEntity,al_map_rgb(255,0,255));
		describe();
	}

}

player::~player()
{
//	al_destroy_bitmap(pBitmapEntity);
}

void player::changeColor(int r, int g, int b)
{

	al_set_target_bitmap(pBitmapEntity);							
	al_clear_to_color(al_map_rgb(r, g, b));

	


}

void player::setCloseToPlayer(entity& e)
{

	if(std::find(close_to_player.begin(), close_to_player.end(), &e) != close_to_player.end())
	{
		fprintf(stderr,"entity already in array\n");
	}
	else
	{
		close_to_player.push_back(&e);

	}

	//Remove unused elements

}

std::vector<entity*>* player::getCloseToPlayer()
{

	return &close_to_player;
}

void player::setMapsectionLocation(int MapSection)
{

	inMapSection = MapSection;


}
