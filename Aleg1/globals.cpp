#include "globals.h"


const int FPS = 60;
int SCREEN_W = 680;
int SCREEN_H = 680;


bool keys[] = {false, false, false, false, false,false,false};

//ALLEGRO STRUCTS
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *tiles = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_KEYBOARD *keyboard = NULL;
ALLEGRO_TRANSFORM transform;
ALLEGRO_BITMAP *stone = NULL;

bool InitializeGame()
{
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}
	timer = al_create_timer(1.0 / FPS);						//TIMER
	if(!timer) 
	{
		fprintf(stderr, "failed to create timer!\n");
		return false;
	}
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	display = al_create_display(680, 680);		//DISPLAY
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return false;
	}
	al_set_window_title(display, "Big Bad Enemy Guy - By Rick LeMieux");

	if(!al_init_image_addon()) 
	{
		return false;
	}
	al_init_primitives_addon();
	al_init_font_addon(); //Initialize Font
	if(!al_init_ttf_addon()) 
	{
		fprintf(stderr, "failed to initialize allegro ttf addon!\n");
		return false;
	}
	if(!al_install_keyboard())
	{
		fprintf(stderr, "failed to install keyboard!\n");
		return false;
	}
	if(!al_install_mouse())
	{
		fprintf(stderr, "failed to install mouse!\n");
		return false;
	}
	
	//SEED RANDOM
	srand (time(NULL));

	return true;
}

void CleanUp()
{

	al_destroy_bitmap(tiles);
	al_destroy_bitmap(stone);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

}