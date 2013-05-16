
#ifndef TILEMAP_H
#define TIMEMAP_H
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
 
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
*/

#include "StdAfx.h"

/* Our icon and font. */
extern ALLEGRO_BITMAP *icon;

/* Our tilemap. */
extern int tile_map[100][100];
/* Camera parameters. */
extern float zoom , rotate;
extern float scroll_x, scroll_y;

void tile_draw(int i, float x, float y, float w, float h);
void tile_map_create(void);
void tile_map_draw(void);
void tile_load_map(const char *filename);
#endif

//test