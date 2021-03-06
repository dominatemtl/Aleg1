#include "entity.h"

entity::entity()
{
	//Location info
	x = 0;
	y= 0;

	//SPEED and SIze
	speed = 0;
	size = 32;

	//Graphic 
	pBitmapEntity = NULL;


	//Initialize sMove struct


}
entity::entity(int xStart,int yStart,int speedStart,int sizeStart)
{
	x = xStart;
	y= yStart;


	//SPEED and SIze
	speed = speedStart;
	size = sizeStart;

	//Graphic 
	
	pBitmapEntity = al_create_bitmap(sizeStart, sizeStart);
	al_set_target_bitmap(pBitmapEntity);
	al_clear_to_color(al_map_rgb(255, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(display));

	describe();

}

entity::~entity()
{

	al_destroy_bitmap(pBitmapEntity);

}

void entity::move(MYMOVEMENT movement)
{
	switch(movement)
	{

	case UP:
		y -= speed;
		break;
	case DOWN:
		y += speed;
		break;
	case LEFT:
		x -= speed;
		break;
	case RIGHT:
		x += speed;
		break;
	case STOP:
		sMove.shouldI = false;
		break;

	default:
		break;
	}

}

void entity::describe()
{

	fprintf(stderr, "PLAYER--X: %i Y: %i\n",x,y);
}

void entity::changeColor(int r, int g, int b)
{
	
	al_set_target_bitmap(pBitmapEntity);							
	al_clear_to_color(al_map_rgb(r, g, b));



}

ALLEGRO_BITMAP* entity::getBitmap()
{
	return pBitmapEntity;
}