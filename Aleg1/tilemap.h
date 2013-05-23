
#ifndef TILEMAP_H
#define TIMEMAP_H

#include "StdAfx.h"

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