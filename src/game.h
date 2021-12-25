#ifndef GAME_H
#define GAME_H

#include "headers.h"

#include "ship.h"
#include "list.h"

#include "SDL.h"
#include "SDL_image.h"

#include "alphabet.h"

void game_start(const int width, const int height);

typedef struct Blast_ {
	SDL_Renderer* renderer;
		
	SDL_Texture *blast_texture;
	
	List* List_blast_info;
	int end_time;

	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect rect3;
	SDL_Rect rect4;
	SDL_Rect rect5;
	SDL_Rect rect6;
	SDL_Rect rect7;
	SDL_Rect rect8;
	SDL_Rect rect9;
	SDL_Rect rect10;
	SDL_Rect rect11;
	SDL_Rect rect12;
	SDL_Rect rect13;
	SDL_Rect rect14;
	SDL_Rect rect15;
	SDL_Rect rect16;
	SDL_Rect rect17;
	SDL_Rect rect18;
	SDL_Rect rect19;
	SDL_Rect rect20;
} Blast;

typedef struct Textures_ {
	SDL_Texture* spaceT;
	SDL_Texture* missileT;
	SDL_Texture* friendShipT;
	SDL_Texture* enemyShipT;
	SDL_Texture* whiteRectangleT;
	SDL_Texture* greenRectangleT;
	SDL_Texture* whiteButtonT;
	SDL_Texture* blueRectangleT;
	
} Textures;

typedef struct Window_menu_ Window_menu;

struct Window_menu_ {
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect rect;
	Alphabet* alphabet;

	List* List_buttons;
};

typedef struct SI_ SI;

struct SI_ {
	int level;
	int score;
	int enemy_count;
	char score_string[5];
	char life_string[3];
	
	int width;
	int height;

	SDL_Rect window_rect;
	SDL_Rect score_rect;
	SDL_Rect life_rect;

	List* List_ships;
	
	List* List_missiles;

	Blast* Explosions;
	
	SDL_Renderer* renderer;

	Textures texs;

	Window_menu* window_start_menu;
	Window_menu* window_end_menu;

	Alphabet* alphabet;

	clock_t start_time;
	clock_t next_time;
	double time_gap;

	bool end;
};

Window_menu* Window_menu_create(SDL_Renderer* rend, int x, int y, int w, int h, Alphabet* alphabet);
void Window_menu_free(Window_menu** self);
void Window_menu_render(Window_menu* self);
void Window_add_button(Window_menu* self, Button* b);

bool SI_init(SI* self, SDL_Renderer* rend);
void SI_render(SI* self);
void SI_free(SI* self);
void SI_reset(SI* self);
void SI_fire_from_ship(SI* si, Ship* self);
int SI_update_positions(SI* self); // 0 if is inside window, 1 otherwise
void SI_create_enemy(SI* self);
void SI_check_for_collisions(SI* self);
void SI_update_score(SI* self, int newscore);
void SI_update_state(SI* self);

Blast* Blast_create(SDL_Renderer* rend);
void Blast_free(Blast** self);
void Blast_add_explosion(List* self, clock_t time, int x, int y, int w, int h);
void Blast_render_explosion(Blast* self);

void SI_end_game(SI* self);

int Generate_random(); // generates between 0 and 100

char* Int_to_string(int num);

#endif
