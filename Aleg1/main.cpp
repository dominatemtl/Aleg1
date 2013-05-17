
#include "StdAfx.h"
#include "entity.h"
#include "player.h"
#include "SceneManager.h"

bool redraw = true;
int mouse;

int main(int argc, char **argv){

	//INITIALIZTIONS
	if(!InitializeGame())
	{
		fprintf(stderr, "failed to install mouse!\n");
		return false;
	}

//Move this font and drawing
	ALLEGRO_FONT *font_oj18 = NULL; //Pointer to font

	font_oj18 = al_load_ttf_font("orangejuice.ttf",50,0);
	if(!font_oj18) {
		fprintf(stderr, "failed to create font!\n");
		return 0;
	}



  

//CREATE OBJECTS
	scenemanager scene1;										//CREATE SCENE
	player p1;													//CREATE PLAYER
	player p2(300, 300);										//CREATE PLAYER					
	player p3(332, 332);										//CREATE PLAYER
	player p4(52, 52, WIZARD);									//CREATE PLAYER
	scene1.addPlayer(p1);										//ADD to SCENE
	scene1.addPlayer(p2);										//ADD to SCENE
	scene1.addPlayer(p3);										//ADD to SCENE
	scene1.addPlayer(p4);										//ADD to SCENE 		

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

	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	tile_map_create();
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
				mouse = 2;
				//Move this logic
				//It the right click movement.

				aP->sMove.shouldI = true;
				aP->sMove.dest_x = (ev.mouse.x / zoom) + scroll_x;
				aP->sMove.dest_y = (ev.mouse.y / zoom) + scroll_y;
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

				int mX, mY;

				mX = (ev.mouse.x / zoom) + scroll_x;
				mY = (ev.mouse.y / zoom) + scroll_y;

				mouse = 1;

				//Check for clicked on elements
				scene1.checkScene(mX, mY);
				al_set_target_bitmap(al_get_backbuffer(display));

			}
			

			//ALL of this
		}
	
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
           /* Left button scrolls. */
            if (mouse == 1) {
			

				float x = ev.mouse.dx / zoom;
                float y = ev.mouse.dy / zoom;
                scroll_x -= x * cos(rotate) + y * sin(rotate);
                scroll_y -= y * cos(rotate) - x * sin(rotate);

            }

			//Zoom translation & safeguards
			zoom += ev.mouse.dz * 0.1;
            if (zoom < 0.30) zoom = 0.30;
            if (zoom > 2) zoom = 2;

		}
	    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
		{
            mouse = 0;
        }


        if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            al_acknowledge_resize(display);
            redraw = true;
        }

		if(redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));


			
			scene1.drawScene();

			al_draw_text(font_oj18,al_map_rgb(255,255,255),10, 10, ALLEGRO_ALIGN_LEFT, "BBEG GAME - RGL");

			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font_oj18);



	return 0;
}
