#ifndef _GLOBALS1_H
#define _GLOBALS1_H
#include "StdAfx.h"

extern const int FPS;
extern const int SCREEN_W;
extern const int SCREEN_H;

//GLOBAL ENUMERATORS

extern enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_SPACE};
extern enum MYMOUSE {LEFT_CLICK = 1, RIGHT_CLICK};
extern enum MYCLASSES {WIZARD, FIGHTER, DRUID, RANGER, ROGUE, NONE};

extern bool keys[];

//ALLEGRO STRUCTS

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *tiles;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_KEYBOARD *keyboard;

extern ALLEGRO_TRANSFORM transform;

//srand((int)time(NULL));

//FUNCTIONS
bool InitializeGame();

#endif