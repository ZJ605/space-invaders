#ifndef SHIP_H
#define SHIP_H

#include "headers.h"

#include "SDL.h"
#include "SDL_image.h"

#include "alphabet.h"

typedef struct Button_ Button;
struct Button_ {
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Rect focus_rect;
	SDL_Texture* texture;
	SDL_Texture* focus_texture;

	bool focus;

	Alphabet* alphabet;
	char * text;
};

typedef struct Missile_ Missile;

struct Missile_ {
	int status; //0 - friend, 1 - enemy
	int speed;
	int direction; //-1 - friend, 1 - enemy
	SDL_Rect rect;
};

Missile* Missile_create(int status, int posx, int posy);
bool Missile_free(Missile* self);
void Missile_update_position(Missile* self);

typedef struct Ship_ Ship;

struct Ship_ {
	int status; //0 - friend, 1 - enemy
	int life;
	int max_life;
	int speed;
	bool up;
	bool down;
	bool left;
	bool right;
	int cooldown_max;
	int cooldown;
	clock_t last_shoot;	
	SDL_Rect rect;
	SDL_Rect rect_life;
	SDL_Rect rect_max_life;
	SDL_Rect rect_cool_down;
	SDL_Rect rect_cool_down_max;
};

Button* Button_create(SDL_Renderer* rend, int x, int y, int w, int h, Alphabet* alphabet, char* text);
void Button_free(Button** self);
void Button_render(Button* self);
void Button_update_text(Button* self, char * text);

Ship* Ship_create(int status, int posx, int posy, int width, int height, int speed, int life);
bool Ship_free(Ship * self);
void Ship_update_position(Ship* self);

bool Ships_check_for_collision(const Ship* s1, const Ship* s2);
bool Ship_missile_check_for_collision(const Ship* s, const Missile* m);
#endif
