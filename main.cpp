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
#include "Player.h"
#include "Room.h"
#include "Camera.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

using namespace std;

bool compare(Object *L1, Object *L2);

vector<Room *> rooms;
vector<Room *>::iterator riter;


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

	char CurrentRoom = '_';

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
	Player *player = new Player();
	player->Init(SCREENW/2, SCREENH/2, 0, 0, 0, 50, 100);
	int state = PLAYING;

	Camera *camera = new Camera();
	camera->Init(0, 0);
	//defining all the rooms
	Room *roomA = new Room();
	Room *roomB = new Room();
	Room *roomC = new Room();
	Room *roomD = new Room();
	Room *roomE = new Room();
	Room *roomF = new Room();
	Room *roomG = new Room();
	Room *roomH = new Room();
	Room *roomI = new Room();
	Room *roomJ = new Room();
	Room *roomK = new Room();
	Room *roomL = new Room();
	Room *roomM = new Room();
	Room *room_ = new Room();
	Room *roomN = new Room();
	Room *roomO = new Room();
	Room *roomP = new Room();
	Room *roomQ = new Room();
	Room *roomR = new Room();
	Room *roomS = new Room();
	Room *roomT = new Room();
	Room *roomU = new Room();
	Room *roomV = new Room();
	Room *roomW = new Room();
	Room *roomX = new Room();
	Room *roomY = new Room();
	Room *roomZ = new Room();

	//creation of all rooms. Init() involves/will involve creation of level, objects, etc.
	roomA->Init('A', 0, 0, 0, player);
	roomB->Init('B', 1, 0, 0, player);
	roomC->Init('C', 2, 0, 0, player);

	roomD->Init('D', 0, 1, 0, player);
	roomE->Init('E', 1, 1, 0, player);
	roomF->Init('F', 2, 1, 0, player);

	roomG->Init('G', 0, 2, 0, player);
	roomH->Init('H', 1, 2, 0, player);
	roomI->Init('I', 2, 2, 0, player);

	roomJ->Init('J', 0, 0, 1, player);
	roomK->Init('K', 1, 0, 1, player);
	roomL->Init('L', 2, 0, 1, player);

	roomM->Init('M', 0, 1, 1, player);
	room_->Init('_', 1, 1, 1, player);//center of cube
	roomN->Init('N', 2, 1, 1, player);

	roomO->Init('O', 0, 2, 1, player);
	roomP->Init('P', 1, 2, 1, player);
	roomQ->Init('Q', 2, 2, 1, player);

	roomR->Init('R', 0, 0, 2, player);
	roomS->Init('S', 1, 0, 2, player);
	roomT->Init('T', 2, 0, 2, player);

	roomU->Init('U', 0, 1, 2, player);
	roomV->Init('V', 1, 1, 2, player);
	roomW->Init('W', 2, 1, 2, player);

	roomX->Init('X', 0, 2, 2, player);
	roomY->Init('Y', 1, 2, 2, player);
	roomZ->Init('Z', 2, 2, 2, player);

	//adding all rooms to 'rooms' vector
	rooms.push_back(roomA);
	rooms.push_back(roomB);
	rooms.push_back(roomC);
	rooms.push_back(roomD);
	rooms.push_back(roomE);
	rooms.push_back(roomF);
	rooms.push_back(roomG);
	rooms.push_back(roomH);
	rooms.push_back(roomI);
	rooms.push_back(roomJ);
	rooms.push_back(roomK);
	rooms.push_back(roomL);
	rooms.push_back(roomM);
	rooms.push_back(room_);
	rooms.push_back(roomN);
	rooms.push_back(roomO);
	rooms.push_back(roomP);
	rooms.push_back(roomQ);
	rooms.push_back(roomR);
	rooms.push_back(roomS);
	rooms.push_back(roomT);
	rooms.push_back(roomU);
	rooms.push_back(roomV);
	rooms.push_back(roomW);
	rooms.push_back(roomX);
	rooms.push_back(roomY);
	rooms.push_back(roomZ);
	for (riter = rooms.begin(); riter != rooms.end(); ++riter)
	{
		if ((*riter)->GetID() == CurrentRoom)
			(*riter)->ObjectUpdate(camera->GetCameraXDir(), camera->GetCameraYDir());
	}
	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	//ALLEGRO_FONT *font18;

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())										//initialize Allegro
		return -1;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//if (SCREENW == disp_data.width && SCREENH == disp_data.height) {
	//	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//	display = al_create_display(disp_data.width, disp_data.height);
	//}
	//else {
		display = al_create_display(SCREENW - 100, SCREENH - 100);		//create our display object
	//}

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
	//font18 = al_load_font("arial.ttf", 18, 0);
	//al_reserve_samples(15);

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
				for (riter = rooms.begin(); riter != rooms.end(); ++riter)
				{
					if ((*riter)->GetID() == CurrentRoom)
						(*riter)->ObjectCollision();
				}
				
				//update
				camera->Follow(player);
				for (riter = rooms.begin(); riter != rooms.end(); ++riter)
				{
					if ((*riter)->GetID() == CurrentRoom)
						(*riter)->ObjectUpdate(camera->GetCameraXDir(), camera->GetCameraYDir());
				}

			}
			//=====================(PLAYING end)
			//cull the dead
			for (riter = rooms.begin(); riter != rooms.end(); ++riter)
			{
				if ((*riter)->GetID() == CurrentRoom)
					(*riter)->ObjectDeletion();
			}
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
				for (riter = rooms.begin(); riter != rooms.end(); ++riter)
				{
					if ((*riter)->GetID() == CurrentRoom)
						(*riter)->ObjectRender();
				}
			}
			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end gameloop

	 //==============================================
	 //DESTROY PROJECT OBJECTS
	 //==============================================
	//SHELL OBJECTS=================================
	//al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

//sorts object list
bool compare(Object *L1, Object *L2) {
	if ((*L1).GetY() + (*L1).GetBoundY() < (*L2).GetY() + (*L2).GetBoundY()) return true;
	if ((*L2).GetY() + (*L2).GetBoundY() < (*L1).GetY() + (*L1).GetBoundY()) return false;

	// a=b for primary condition, go to secondary
	//if ((*L1).BaseY < (*L2).BaseY) return true;
	//if ((*L2).BaseY < (*L1).BaseY) return false;

	// ...

	return false;
}

void Transition(char CurrentRoom, char RoomMatrix[3][3][3]) {

	int shuffle = rand() % 12 + 1;
	//Shuffling rooms like a Rubix Cube
	for (riter = rooms.begin(); riter != rooms.end(); ++riter)
	{
		(*riter)->Shuffle(shuffle);
	}
	//realigning RoomMatrix according to shuffle
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				for (riter = rooms.begin(); riter != rooms.end(); ++riter)
				{
					if ((*riter)->GetX() == x && (*riter)->GetY() == y && (*riter)->GetZ() == z)
						RoomMatrix[x][y][z] = (*riter)->GetID();
				}
			}
		}
	}
	//realigning all rooms adjacent to room in RoomMatrix
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				if (x + 1 < 3)
					(*riter)->SetXAdj(RoomMatrix[x + 1][y][z]);
				else
					(*riter)->SetXAdj('/');
				if (x - 1 > 0)
					(*riter)->SetNegXAdj(RoomMatrix[x-1][y][z]);
				else
					(*riter)->SetNegXAdj('/');
				if (y + 1 < 3)
					(*riter)->SetYAdj(RoomMatrix[x][y+1][z]);
				else
					(*riter)->SetYAdj('/');
				if (y - 1 > 0)
					(*riter)->SetNegYAdj(RoomMatrix[x][y-1][z]);
				else
					(*riter)->SetNegYAdj('/');
				if (z + 1 < 3)
					(*riter)->SetZAdj(RoomMatrix[x][y][z+1]);
				else
					(*riter)->SetZAdj('/');
				if (z - 1 > 0)
					(*riter)->SetNegZAdj(RoomMatrix[x][y][z-1]);
				else
					(*riter)->SetNegZAdj('/');
			}
		}
	}
}