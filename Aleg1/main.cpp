
#include "StdAfx.h"
#include "globals.h"
#include "entity.h"
#include "player.h"
#include "SceneManager.h"


//ALLEGRO STRUCTS
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_KEYBOARD *keyboard = NULL;
ALLEGRO_FONT *font_oj18 = NULL; //Pointer to font


bool redraw = true;

int main(int argc, char **argv){

	//INITIALIZTIONS

	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return 0;
	}

	if(!al_init_image_addon()) 
	{

		return 0;
	}
	al_init_font_addon(); //Initialize Font
	if(!al_init_ttf_addon()) 
	{
		fprintf(stderr, "failed to initialize allegro ttf addon!\n");
		return 0;
	}
	if(!al_install_keyboard())
	{
		fprintf(stderr, "failed to install keyboard!\n");
		return 0;
	}
	font_oj18 = al_load_ttf_font("orangejuice.ttf",50,0);
	if(!font_oj18) {
		fprintf(stderr, "failed to create font!\n");
		return 0;
	}

	if(!al_install_mouse())
	{
		fprintf(stderr, "failed to install mouse!\n");
		return 0;
	}
	timer = al_create_timer(1.0 / FPS);						//TIMER
	if(!timer) 
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	display = al_create_display(SCREEN_W, SCREEN_H);		//DISPLAY
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}


	scenemanager scene1;										//CREATE SCENE
	player p1;													//CREATE PLAYER
	player p2(300, 300);										//CREATE PLAYER					
	player p3(332, 332);										//CREATE PLAYER
	player p4(52, 52, WIZARD);									//CREATE PLAYER
	scene1.addPlayer(p1);										//ADD to SCENE
	scene1.addPlayer(p2);										//ADD to SCENE
	scene1.addPlayer(p3);										//ADD to SCENE
	scene1.addPlayer(p4);										//ADD to SCENE 		

	al_set_target_bitmap(al_get_backbuffer(display)); //?


	event_queue = al_create_event_queue();			//EVENT QUEUE
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		//	al_destroy_bitmap(bouncer); MOVED TO ENTITY DECON
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}


	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	//	al_clear_to_color(al_map_rgb(0,0,0));
	//	al_flip_display();


	player* aP = NULL; // POINTER TO THE ACTIVE PLAYER
	al_start_timer(timer);

	//GAME LOOP
	while(1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);	//get event
		aP = scene1.getPlayer();				//pointer to active player

		if(ev.type == ALLEGRO_EVENT_TIMER) 
		{
			//The scene should handle moving the player.

			scene1.moveActivePlayer(); //Check for keypresses and move player

			if(keys[KEY_SPACE])
			{

				//PLACEHOLDER

			}

			scene1.sceneMovement(); //MOVE PLAYERS
			redraw = true; 
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN ) {

			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				keys[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[KEY_SPACE] = true;
				break;
			}
		}	   
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				keys[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[KEY_SPACE] = false;
				break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) // RIGHT CLICK ---- MOVE
		{

			if(ev.mouse.button == RIGHT_CLICK)
			{

				aP->sMove.shouldI = true;
				aP->sMove.dest_x = ev.mouse.x;
				aP->sMove.dest_y = ev.mouse.y;
				aP->sMove.start_x = aP->getX();
				aP->sMove.start_y = aP->getY();


				fprintf(stderr, "--BEGIN: X:%i Y:%i\n",aP->sMove.dest_x,aP->sMove.dest_y);

				while(!(aP->sMove.dest_x % aP->getSpeed() == 0))
				{


					fprintf(stderr, "INCREMENT X: %i\n",aP->sMove.dest_x % aP->getSpeed());
					aP->sMove.dest_x += (aP->sMove.dest_x % aP->getSpeed());
					fprintf(stderr, "NEW DEST: X:%i Y:%i\n",(int)aP->sMove.dest_x,(int)aP->sMove.dest_y);


				}
				while(!(aP->sMove.dest_y % aP->getSpeed() == 0))
				{
					fprintf(stderr, "INCREMENT Y: %i\n",aP->sMove.dest_y % aP->getSpeed());
					aP->sMove.dest_y += (aP->sMove.dest_y % aP->getSpeed());
					fprintf(stderr, "NEW DEST: X:%i Y:%i\n",aP->sMove.dest_x,(int)aP->sMove.dest_y);

				}

				fprintf(stderr, "LEAVING: X:%i Y:%i\n",aP->getX(),aP->getY());
				fprintf(stderr, "DEST: X:%i Y:%i\n",aP->sMove.dest_x,aP->sMove.dest_y);
			}
			else if(ev.mouse.button == LEFT_CLICK)										//LEFT CLICK
			{
				scene1.checkScene(ev.mouse.x, ev.mouse.y);
				al_set_target_bitmap(al_get_backbuffer(display));
			}


		}

		if(redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));

			scene1.drawScene();
	
			al_draw_text(font_oj18,al_map_rgb(255,255,255),SCREEN_W /2, 10, ALLEGRO_ALIGN_CENTRE, "BBEG GAME - RGL");
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font_oj18);



	return 0;
}
