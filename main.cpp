#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include "Globals.h"
#include "Object.h"
#include "Room.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

using namespace std;

bool keys[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
enum KEYS { UP, DOWN, LEFT, RIGHT, MOUSE_BUTTON, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, ENTER, SHIFT };

int main()
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool redraw = true;
	bool doexit = false;
	bool render = false;

	double gameTime = 0;
	double frames = 0;
	double gameFPS = 0;

	double mouseX = 0;
	double mouseY = 0;

	double cameraXDir = 0;
	double cameraYDir = 0;

	double cameraXPos = 0;
	double cameraYPos = 0;

	//matrix for storing coordinates. used to keep track of what's where.
	char RoomMatrix[3][3][3] = {
	'A','B','C',
	'D','E','F',
	'G','H','I',
	
	'J','K','L',
	'M','_','N',
	'O','P','Q',
	
	'R','S','T',
	'U','V','W',
	'X','Y','Z'
	};

	//==============================================
	//PROJECT VARIABLES
	//==============================================
	ALLEGRO_BITMAP *PlayerImage = NULL;
	int state = -1;

	//defining 'room'
	Room *room = new Room();
	//creation of all rooms. Init() involves/will involve creation of level, objects, etc.
	room->Init('A', 0, 0, 0);
	room->Init('B', 1, 0, 0);
	room->Init('C', 2, 0, 0);

	room->Init('D', 0, 1, 0);
	room->Init('E', 1, 1, 0);
	room->Init('F', 2, 1, 0);

	room->Init('G', 0, 2, 0);
	room->Init('H', 1, 2, 0);
	room->Init('I', 1, 2, 0);

	room->Init('J', 0, 0, 1);
	room->Init('K', 1, 0, 1);
	room->Init('L', 2, 0, 1);

	room->Init('M', 0, 1, 1);
	room->Init('_', 1, 1, 1);//center of cube
	room->Init('N', 2, 1, 1);

	room->Init('O', 0, 2, 1);
	room->Init('P', 1, 2, 1);
	room->Init('Q', 2, 2, 1);

	room->Init('R', 0, 0, 2);
	room->Init('S', 1, 0, 2);
	room->Init('T', 2, 0, 2);

	room->Init('U', 0, 1, 2);
	room->Init('V', 1, 1, 2);
	room->Init('W', 2, 1, 2);

	room->Init('X', 0, 2, 2);
	room->Init('Y', 1, 2, 2);
	room->Init('Z', 2, 2, 2);

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18;

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())										//initialize Allegro
		return -1;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	if (SCREENW == disp_data.width && SCREENH == disp_data.height) {
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		display = al_create_display(disp_data.width, disp_data.height);
	}
	else {
		display = al_create_display(SCREENW - 100, SCREENH - 100);		//create our display object
	}

	if (!display)//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_install_mouse();

	//==============================================
	//PROJECT INIT
	//==============================================
	//insert font types, images, sounds, state images, etc
	font18 = al_load_font("arial.ttf", 18, 0);
	al_reserve_samples(15);

	srand(time(NULL));

	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.000 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	//game loop begin
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//INPUT
		//==============================================
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)//update mouse position
		{
			mouseX = ev.mouse.x;
			mouseY = ev.mouse.y;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = true;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = true;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = true;
				break;
			case ALLEGRO_KEY_4:
				keys[NUM_4] = true;
				break;
			case ALLEGRO_KEY_5:
				keys[NUM_5] = true;
				break;
			case ALLEGRO_KEY_6:
				keys[NUM_6] = true;
				break;
			case ALLEGRO_KEY_7:
				keys[NUM_7] = true;
				break;
			case ALLEGRO_KEY_8:
				keys[NUM_8] = true;
				break;
			case ALLEGRO_KEY_9:
				keys[NUM_9] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = true;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			keys[MOUSE_BUTTON] = true;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = false;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = false;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = false;
				break;
			case ALLEGRO_KEY_4:
				keys[NUM_4] = false;
				break;
			case ALLEGRO_KEY_5:
				keys[NUM_5] = false;
				break;
			case ALLEGRO_KEY_6:
				keys[NUM_6] = false;
				break;
			case ALLEGRO_KEY_7:
				keys[NUM_7] = false;
				break;
			case ALLEGRO_KEY_8:
				keys[NUM_8] = false;
				break;
			case ALLEGRO_KEY_9:
				keys[NUM_9] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = false;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			keys[MOUSE_BUTTON] = false;
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if (state == PLAYING)//if playing, receive movement and other stuff
			{
				//number keys (temporary, for testing purposes- do not plan on incorporating into gameplay)
				if (keys[NUM_1])
				{
					keys[NUM_1] = false;
				}
				if (keys[NUM_2])
				{
					keys[NUM_2] = false;
				}
				if (keys[NUM_3])
				{
					keys[NUM_3] = false;
				}
				if (keys[NUM_4])
				{
					keys[NUM_4] = false;
				}
				if (keys[NUM_5])
				{
					keys[NUM_5] = false;
				}
				if (keys[NUM_6])
				{
					keys[NUM_6] = false;
				}
				if (keys[NUM_7])
				{
					keys[NUM_7] = false;
				}
				if (keys[NUM_8])
				{
					keys[NUM_8] = false;
				}
				if (keys[NUM_9])
				{
					keys[NUM_9] = false;
				}

				//collisions

				//update

			}
			//=====================(PLAYING end)
			//cull the dead

		}

		//==============================================
		//RENDER
		//==============================================
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			//sort objects
			if (state == TITLE) {

			}
			else if (state == PLAYING) {

			}
			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end gameloop

	 //==============================================
	 //DESTROY PROJECT OBJECTS
	 //==============================================

	al_destroy_bitmap(PlayerImage);

	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}