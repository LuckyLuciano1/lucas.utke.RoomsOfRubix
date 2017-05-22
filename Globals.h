#pragma once
const int SCREENW = 1920, SCREENH = 1080;//console size
const int LEVELW = 13, LEVELH = 13;//level size
const int TILEW = 100, TILEH = 100;//standard tile size for terrain
const int FPS = 60;
enum STATE { TITLE, PLAYING, LOST };
enum KEYS { UP, DOWN, LEFT, RIGHT, MOUSE_BUTTON, F_MAP, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, ENTER, SHIFT };
enum RENDERINGVERTICALITY { VERTICAL, HORIZONTAL };