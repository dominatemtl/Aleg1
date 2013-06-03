#include "rooms.h"


room::room(int r)
{

	switch(r)
	{
	case HALL:
		size_x = 64;
		size_y = 256;
		backgroundColor = al_map_rgb(0,0,0);
		break;
	case EMPTYROOM:
		size_x = 256;
		size_y = 256;
		backgroundColor = al_map_rgb(255,255,255);
		break;
	}

	inScene = false;
	onMouse = true;

}
room::room(int x, int y, int sX, int sY )
{
	location_x = x;
	location_y = y;
	size_x = sX;
	size_y = sY;
	inScene = false;
	onMouse = true;
}
room::room(int x, int y, int sX, int sY, ALLEGRO_COLOR color )
{
	location_x = x;
	location_y = y;
	size_x = sX;
	size_y = sY;
	backgroundColor = color;
	inScene = false;
	onMouse = true;
}
room::~room()
{


}
void room::drawRoom()
{

	al_draw_filled_rectangle(location_x,location_y, location_x + size_x, location_y + size_y, backgroundColor);
	
}
void room::setLocation(float pX, float pY)
{
	location_x = pX; 
	location_y = pY;
}

void room::rotate()
{

	int tempX, tempY, tempSizeX, tempSizeY;




}
