#ifndef _GLOBALS1_H
#define _GLOBALS1_H
#include "StdAfx.h"

extern const int FPS;
extern int SCREEN_W;
extern int SCREEN_H;
extern int SCREEN_W_CENTER;
extern int SCREEN_H_CENTER;
//GLOBAL ENUMERATORS

extern enum MYKEYS{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_SPACE, KEY_N, KEY_1, KEY_2};
extern enum MYMOUSE {LEFT_CLICK = 1, RIGHT_CLICK};
extern enum MYCLASSES {WIZARD, FIGHTER, DRUID, RANGER, ROGUE, NONE};

extern bool keys[];

//ALLEGRO STRUCTS

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_BITMAP *tiles;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_KEYBOARD *keyboard;

extern ALLEGRO_BITMAP *stone;
extern ALLEGRO_TRANSFORM transform;

//srand((int)time(NULL));

//FUNCTIONS
bool InitializeGame();
void CleanUp();

#endif