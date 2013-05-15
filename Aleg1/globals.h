#ifndef _GLOBALS1_H
#define _GLOBALS1_H

const int FPS = 60;
const int SCREEN_W = 680;
const int SCREEN_H = 680;

//GLOBAL ENUMERATORS
extern bool keys[];
extern enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_SPACE};
extern enum MYMOUSE {LEFT_CLICK = 1, RIGHT_CLICK};

extern enum MYCLASSES {WIZARD, FIGHTER, DRUID, RANGER, ROGUE, NONE};


#endif