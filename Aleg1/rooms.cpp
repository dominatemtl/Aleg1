#include "rooms.h"


room::room(int r)
{

	switch(r)
	{
	case HALL:
		size_x = 32;
		size_y = 64;
		break;
	case EMPTYROOM:
		size_x = 128;
		size_y = 128;
		break;
	}

	backgroundColor = al_map_rgb(255,0,255);
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
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	fprintf(stderr,"Drawing THE ROOM\n");
	al_hold_bitmap_drawing(1);
	al_draw_filled_rectangle(location_x,location_y, location_x + size_x, location_y + size_y, backgroundColor);
	al_hold_bitmap_drawing(0);
}
