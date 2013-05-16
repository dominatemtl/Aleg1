
#include "tilemap.h"
 


float zoom = 1.0, rotate;
float scroll_x, scroll_y;

/* Our window. */
//ALLEGRO_DISPLAY *display;
/* Our tiles atlas. */
//ALLEGRO_BITMAP *tiles;
/* Our icon and font. */
ALLEGRO_BITMAP *icon;

int tile_map[100][100];


 
/* Places a single tile into the tile atlas.
 * Normally you would load the tiles from a file.
 */
void tile_draw(int i, float x, float y, float w, float h) {
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR green = al_map_rgb(0, 102, 0);
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    switch (i) {
        case 0:
            al_draw_filled_rectangle(x, y, x + w, y + h, white);
            break;
        case 1:
            al_draw_filled_rectangle(x, y, x + w, y + h, blue);
        //    al_draw_filled_circle(x + w * 0.5, y + h * 0.5, w * 0.475, green);
            break;
        case 2:
            al_draw_filled_rectangle(x, y, x + w, y + h, green);
            break;
    }
}
 
/* Creates the tiles and a random 100x100 map. */
void tile_map_create(void) {
    int i;
    int x, y;
    /* Create the tile atlas. */
    tiles = al_create_bitmap(1024, 1024);
    al_set_target_bitmap(tiles);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    for (i = 0; i < 5; i++) {
        /* We draw the tiles a bit bigger (66x66 instead of 64x64)
         * to account for the linear filtering. Normally just leaving
         * the border transparent for sprites or repeating the border
         * for tiling tiles should work well.
         */
        tile_draw(i, i * 66, 0, 66, 66);
    }
    al_set_target_backbuffer(display);
 
    /* Create the random map. */
    for (x = 0; x < 100; x++) {
        for (y = 0; y < 100; y++) {
            tile_map[x][y] = rand() % 3;
        }
    }
 
    /* Center of map. */
    scroll_x = 100 * 32 / 2;
    scroll_y = 100 * 32 / 2;
}
 
/* Draws the complete map. */
void tile_map_draw(void) {
	int x,y;
    
    float w, h;
	

    w = al_get_display_width(display);
    h = al_get_display_height(display);
 
    /* Initialize transformation. */
    al_identity_transform(&transform);
    /* Move to scroll position. */
    al_translate_transform(&transform, -scroll_x, -scroll_y);
    /* Rotate and scale around the center first. */
  //  al_rotate_transform(&transform, rotate);
 //   al_scale_transform(&transform, zoom, zoom);
    /* Move scroll position to screen center. */
   // al_translate_transform(&transform, w * 0.5, h * 0.5);
    /* All subsequent drawing is transformed. */
    al_use_transform(&transform);
 
    al_clear_to_color(al_map_rgb(0, 0, 0));

 
    al_hold_bitmap_drawing(1);
    for (x = 0; x < 100; x++) {
        for (y = 0; y < 100; y++) {
            int i = tile_map[x][y];
            float u = 1 + i * 66;
            float v = 1;
            al_draw_scaled_bitmap(tiles, u, v, 64, 64,
                x * 32, y * 32, 32, 32, 0);

        }
    }
    al_hold_bitmap_drawing(0);

 
    al_identity_transform(&transform);
    al_use_transform(&transform);
}

//WIP
void tile_load_map(const char *&filename)
{

	int loadCounterX= 0, loadCounterY = 0, mapSizeX, mapSizeY;

	std::ifstream openfile(filename);
	if(openfile.is_open())
	{
		openfile >> mapSizeX >> mapSizeY;
		while(!openfile.eof())
		{

			//LOAD THE MAP

		}


	}
}
 
