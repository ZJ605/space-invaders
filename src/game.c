#include "game.h"

void game_start(const int width, const int height) {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("failed to initialize SDL window\n");
		exit(0);
	}
	SDLDebug(IMG_Init(IMG_INIT_PNG));
	
	SDLDebug(SDL_Window* window = NULL);
	SDLDebug(SDL_Renderer* renderer = NULL);
	
	SDLDebug(window = SDL_CreateWindow(
		"Space Invaderes",
		100,
		100,
		width,
		height,
		SDL_WINDOW_SHOWN
	));

	SDLDebug(renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	));

	SDL_Event ev;
	
	bool window_start_menu = true;
	bool window_end_menu = true;
	bool exit = false;

	// game properties
	SI si = { .level = 0, .score = 0, .width = width, .height = height};
	
	if (renderer == NULL) printf("null renderer\n");	
	// game properties end
	
	// time and random
	time_t t;
	double tick = (double)CLOCKS_PER_SEC;
	srand((unsigned) time(&t));
	// time and random end

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (!SI_init(&si, renderer)) {
		printf("error initializing SI\n");
	}

	while (!exit) {
		
		while (window_start_menu) {
			while (SDL_PollEvent(&ev) > 0) {
				if (ev.type == SDL_QUIT) {
					exit = true;					
					window_start_menu = false;
				}
				if (ev.type == SDL_KEYDOWN) {
					if (ev.key.keysym.scancode == SDL_SCANCODE_UP ) {
						int index = List_button_get_focus(si.window_start_menu->List_buttons) - 1;
						if (index < 0) index = 0;
						List_button_set_focus(si.window_start_menu->List_buttons, index);
					}
					if (ev.key.keysym.scancode == SDL_SCANCODE_DOWN) {
						int index = List_button_get_focus(si.window_start_menu->List_buttons) + 1;
						if (index > si.window_start_menu->List_buttons->size - 2) index = si.window_start_menu->List_buttons->size-1;
						List_button_set_focus(si.window_start_menu->List_buttons, index);
					}
					if (ev.key.keysym.scancode == SDL_SCANCODE_RETURN) {
						window_start_menu = false;
						int index = List_button_get_focus(si.window_start_menu->List_buttons);						
						if (index == 1) exit = true;
					}
				}
			}
			Window_menu_render(si.window_start_menu);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}
		window_start_menu = true;

		while (!exit && !si.end) {

			while (SDL_PollEvent(&ev) > 0) {

				if (ev.type == SDL_QUIT) { 
					exit = true;
					window_start_menu = false;
				}

				if (ev.type == SDL_KEYUP) {
					if (ev.key.keysym.scancode == SDL_SCANCODE_UP) {
						List_return_ship(si.List_ships, 0)->up = false;
					}
					if (ev.key.keysym.scancode == SDL_SCANCODE_DOWN) {
						List_return_ship(si.List_ships, 0)->down = false;
					}
					if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
						List_return_ship(si.List_ships, 0)->left = false;
					}
					if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
						List_return_ship(si.List_ships, 0)->right = false;
					}
				}
				if (ev.type == SDL_KEYDOWN) {
					if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE)
						SI_fire_from_ship(&si, List_return_ship(si.List_ships, 0));
				}

				if (keystate[SDL_SCANCODE_UP]) {
					List_return_ship(si.List_ships, 0)->up = true;
				}
				if (keystate[SDL_SCANCODE_DOWN]) {
					List_return_ship(si.List_ships, 0)->down = true;
				}
				if (keystate[SDL_SCANCODE_LEFT]) {
					List_return_ship(si.List_ships, 0)->left = true;
				}
				if (keystate[SDL_SCANCODE_RIGHT]) {
					List_return_ship(si.List_ships, 0)->right = true;
				}
			}

			//enemies created and fire

			si.next_time = clock();
			si.time_gap = (double)((double)si.next_time - (double)si.start_time) / tick;
			float cislo = 100*si.time_gap + si.score;
			if (cislo > 200*si.enemy_count && Generate_random() > 50) {
				si.start_time = si.next_time;
				SI_create_enemy(&si);
				si.enemy_count++;									
			}

			clock_t now = clock();
			for (int i = (si.List_ships->size - 1); i > 0; i--) {
				Ship* s = List_return_ship(si.List_ships, i);
				clock_t shoot_ = now - s->last_shoot;
				if (shoot_ > 1000) {
					int cislo = si.score / 300 + Generate_random();
					if (cislo > 100) {
						SI_fire_from_ship(&si, List_return_ship(si.List_ships, i));
						s->last_shoot = now;
					}
				}
			}

			SI_update_state(&si);

			SI_update_positions(&si);

			SI_check_for_collisions(&si);

			SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
			SDL_RenderClear(renderer);

			SI_render(&si);

			SDL_RenderPresent(renderer);
			SDL_Delay(17);

		}
		Button_update_text(List_return_button(si.window_end_menu->List_buttons, 1), si.score_string);
		while (window_end_menu && si.end) {
			while (SDL_PollEvent(&ev) > 0) {
				if (ev.type == SDL_QUIT) {
					exit = true;
					window_end_menu = false;
				}
				if (ev.type == SDL_KEYDOWN) {
					if (ev.key.keysym.scancode == SDL_SCANCODE_RETURN) {
						window_end_menu = false;
					}
				}
			}
			Window_menu_render(si.window_end_menu);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}
		window_end_menu = true;
		si.end = false;
		
		
		SI_reset(&si);
	}

	SI_free(&si);

	SDLDebug(SDL_DestroyRenderer(renderer));
	SDLDebug(SDL_DestroyWindow(window));
	SDLDebug(IMG_Quit());
	SDLDebug(SDL_Quit());
}

Window_menu* Window_menu_create(SDL_Renderer* rend, int x, int y, int w, int h, Alphabet* alphabet)
{
	Window_menu* wi = (Window_menu*)malloc(sizeof(Window_menu));
	if (wi == NULL) {
		printf("error creating window menu\n");
		return NULL;
	}

	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	wi->rect = r;

	SDLDebug(SDL_Surface* surf = IMG_Load("res/space.png"));
	SDLDebug(wi->texture = SDL_CreateTextureFromSurface(rend, surf));
	SDLDebug(SDL_FreeSurface(surf));

	wi->renderer = rend;
	wi->alphabet = alphabet;

	wi->List_buttons = List_create();
		
	return wi;
}

void Window_menu_free(Window_menu** self)
{
	SDL_DestroyTexture((*self)->texture);
	List_button_free(&((*self)->List_buttons));
	*self = NULL;
}

void Window_menu_render(Window_menu* self)
{
 	SDL_RenderCopy(self->renderer, self->texture, NULL, &self->rect);
	for (int i = self->List_buttons->size - 1; i > -1; i--) {
		Button* b = List_return_button(self->List_buttons, i);
		Button_render(b);
	}
}

void Window_add_button(Window_menu* self, Button* b)
{
	List_add_button(self->List_buttons, b);
}

bool SI_init(SI* self, SDL_Renderer* rend)
{
	self->level = 0;
	self->score = 0;
	self->enemy_count = 0;
	self->score_string[0] = '0';
	self->score_string[1] = '0';
	self->score_string[2] = '0';
	self->score_string[3] = '0';
	self->score_string[4] = '\0';
	
	self->life_string[0] = '2';
	self->life_string[1] = '0';
	self->life_string[2] = '\n';
	self->renderer = rend;

	self->List_ships = List_create();
	Ship* s = Ship_create(0, self->width/2 - 25, self->height - 70, self->width, self->height, 5, 20);
	if (s == NULL) return false;
	List_add_ship(self->List_ships, s);
	if (self->List_ships->head == NULL) printf("chyba\n");

	self->List_missiles = List_create();

	IMG_Init(IMG_INIT_PNG);

	SDLDebug(SDL_Surface * surf0 = IMG_Load("res/space.png"));
	SDLDebug(self->texs.spaceT = SDL_CreateTextureFromSurface(rend, surf0));
	SDLDebug(SDL_FreeSurface(surf0));

	SDLDebug(SDL_Surface * surf1 = IMG_Load("res/missile.png"));
	SDLDebug(self->texs.missileT = SDL_CreateTextureFromSurface(rend, surf1));
	SDLDebug(SDL_FreeSurface(surf1));

	SDLDebug(SDL_Surface * surf2 = IMG_Load("res/ship1.png"));
	SDLDebug(self->texs.friendShipT = SDL_CreateTextureFromSurface(rend, surf2));
	SDLDebug(SDL_FreeSurface(surf2));

	SDLDebug(SDL_Surface * surf3 = IMG_Load("res/enemy1.png"));
	SDLDebug(self->texs.enemyShipT = SDL_CreateTextureFromSurface(rend, surf3));
	SDLDebug(SDL_FreeSurface(surf3));

	SDLDebug(SDL_Surface * surf4 = IMG_Load("res/white_rectangle.png"));
	SDLDebug(self->texs.whiteRectangleT = SDL_CreateTextureFromSurface(rend, surf4));
	SDLDebug(SDL_FreeSurface(surf4));

	SDLDebug(SDL_Surface * surf5 = IMG_Load("res/green_rectangle.png"));
	SDLDebug(self->texs.greenRectangleT = SDL_CreateTextureFromSurface(rend, surf5));
	SDLDebug(SDL_FreeSurface(surf5));

	SDLDebug(SDL_Surface * surf7 = IMG_Load("res/white_button.png"));
	SDLDebug(self->texs.whiteButtonT = SDL_CreateTextureFromSurface(rend, surf7));
	SDLDebug(SDL_FreeSurface(surf7));

	SDLDebug(SDL_Surface * surf8 = IMG_Load("res/blue_rectangle.png"));
	SDLDebug(self->texs.blueRectangleT = SDL_CreateTextureFromSurface(rend, surf8));
	SDLDebug(SDL_FreeSurface(surf8));

	self->window_rect.x = 0;
	self->window_rect.y = 0;
	self->window_rect.w = self->width;
	self->window_rect.h = self->height;

	self->score_rect.x = self->width - 97;
	self->score_rect.y = 5;
	self->score_rect.w = 100;
	self->score_rect.h = 60;

	self->life_rect.x = self->width - 97;
	self->life_rect.y = 65;
	self->life_rect.w = 100;
	self->life_rect.h = 60;

	self->alphabet = Create_alphabet(self->renderer);
	if (self->alphabet == NULL) printf("chyba");

	self->window_start_menu = Window_menu_create(self->renderer, 0, 0, self->width, self->height, self->alphabet);
	Button* btn = Button_create(rend, self->window_start_menu->rect.x + self->window_start_menu->rect.w / 4, self->window_start_menu->rect.y + self->window_start_menu->rect.h / 4, self->window_start_menu->rect.w / 2+40, 50, self->alphabet, "START NEW GAME");
	Button* btn1 = Button_create(rend, self->window_start_menu->rect.x + self->window_start_menu->rect.w / 4, self->window_start_menu->rect.y + self->window_start_menu->rect.h / 4 + 50, self->window_start_menu->rect.w / 2 + 40, 50, self->alphabet, "CLOSE GAME");
	List_add_button(self->window_start_menu->List_buttons, btn);
	List_add_button(self->window_start_menu->List_buttons, btn1);

	List_button_set_focus(self->window_start_menu->List_buttons,0);

	self->window_end_menu = Window_menu_create(self->renderer, 0, 0, self->width, self->height, self->alphabet);
	Button* btn2 = Button_create(rend, self->window_end_menu->rect.x + self->window_end_menu->rect.w / 4, self->window_end_menu->rect.y + self->window_end_menu->rect.h / 4, self->window_end_menu->rect.w / 2, 50, self->alphabet, "GAME OVER");
	Button* btn3 = Button_create(rend, self->window_end_menu->rect.x + self->window_end_menu->rect.w / 4, self->window_end_menu->rect.y + self->window_end_menu->rect.h / 4+50, self->window_end_menu->rect.w / 2, 50, self->alphabet, "SCORE");
	List_add_button(self->window_end_menu->List_buttons, btn2);
	List_add_button(self->window_end_menu->List_buttons, btn3);

	//List_button_set_focus(self->window_end_menu->List_buttons,0);

	SI_update_score(self, 0);

	self->Explosions = Blast_create(self->renderer);

	self->start_time = clock();

	self->end = false;
	  
	return true;
}

void SI_render(SI* self) {
	
	SDL_RenderCopy(self->renderer, self->texs.spaceT, NULL, &self->window_rect);
	
	SDL_RenderCopy(self->renderer, self->texs.friendShipT, NULL, &List_return_ship(self->List_ships, 0)->rect);
	SDL_RenderCopy(self->renderer, self->texs.whiteRectangleT, NULL, &List_return_ship(self->List_ships, 0)->rect_max_life);
	SDL_RenderCopy(self->renderer, self->texs.greenRectangleT, NULL, &List_return_ship(self->List_ships, 0)->rect_life);
	SDL_RenderCopy(self->renderer, self->texs.whiteRectangleT, NULL, &List_return_ship(self->List_ships, 0)->rect_cool_down_max);
	SDL_RenderCopy(self->renderer, self->texs.blueRectangleT, NULL, &List_return_ship(self->List_ships, 0)->rect_cool_down);
	
	if (self->List_ships->size > 1) {
		for (int i = 1; i < self->List_ships->size; i++) {
			SDLDebug(SDL_RenderCopy(self->renderer, self->texs.enemyShipT, NULL, &List_return_ship(self->List_ships, i)->rect));
			SDLDebug(SDL_RenderCopy(self->renderer, self->texs.whiteRectangleT, NULL, &List_return_ship(self->List_ships, i)->rect_max_life));
			SDLDebug(SDL_RenderCopy(self->renderer, self->texs.greenRectangleT, NULL, &List_return_ship(self->List_ships, i)->rect_life));
		}
	}
	for (int i = 0; i < self->List_missiles->size; i++) {
		SDL_RenderCopy(self->renderer, self->texs.missileT , NULL, &List_return_missile(self->List_missiles, i)->rect);
	}
	
	SDL_RenderCopy(self->renderer, self->texs.whiteButtonT, NULL, &self->score_rect);
	Alphabet_render_text(self->alphabet, "SCORE", self->width - 80, 12, 3, self->renderer);
	Alphabet_render_text(self->alphabet, &(self->score_string), self->width - 90, 30, 5, self->renderer);
	
	SDL_RenderCopy(self->renderer, self->texs.whiteButtonT, NULL, &self->life_rect);
	Alphabet_render_text(self->alphabet, "LIFE", self->life_rect.x + self->life_rect.w/4, self->life_rect.y+self->life_rect.h/4-10, 3, self->renderer);
	Alphabet_render_text(self->alphabet, &(self->life_string), self->life_rect.x + self->life_rect.w / 4, self->life_rect.y + self->life_rect.h / 4 + 10, 5, self->renderer);

	Blast_render_explosion(self->Explosions);

}

void SI_free(SI* self) {	
	
	Window_menu_free(&(self->window_start_menu));
	Window_menu_free(&(self->window_end_menu));
	
	List_missile_free(&(self->List_missiles));
	List_ships_free(&(self->List_ships));
	
	SDL_DestroyTexture(self->texs.missileT);
	SDL_DestroyTexture(self->texs.friendShipT);
	SDL_DestroyTexture(self->texs.enemyShipT);
	SDL_DestroyTexture(self->texs.whiteRectangleT);
	SDL_DestroyTexture(self->texs.greenRectangleT);
	SDL_DestroyTexture(self->texs.whiteButtonT);
	SDL_DestroyTexture(self->texs.blueRectangleT);
	
	Alphabet_free(&(self->alphabet));

}

void SI_reset(SI* self)
{
	self->level = 0;
	self->score = 0;
	self->enemy_count = 0;
	SI_update_score(self, 0);
	self->life_string[0] = '2';
	self->life_string[1] = '0';
	self->life_string[2] = '\0';

	List_ships_free(&(self->List_ships));
	self->List_ships = List_create();
	Ship* s = Ship_create(0, self->width / 2 - 25, self->height - 70, self->width, self->height, 5, 20);
	if (s == NULL) return;
	List_add_ship(self->List_ships, s);
	
	List_missile_free(&(self->List_missiles));

	self->List_missiles = List_create();

	List_blast_info_free(&(self->Explosions->List_blast_info));

	self->Explosions = Blast_create(self->renderer);

	self->start_time = clock();

}

void SI_fire_from_ship(SI* si, Ship* sh) {
	if (sh->cooldown == 0) {		
		return;
	}
	if (!sh->status) {		
		Missile* m = Missile_create(0, sh->rect.x + sh->rect.w / 2, sh->rect.y + sh->rect.h / 2 - 50);
		sh->cooldown--;
		if (sh->cooldown == 0) {
			sh->last_shoot = clock();
		}
		else ;
		List_add_missile(si->List_missiles, m);
	}
	else {
		Missile* m = Missile_create(1, sh->rect.x + sh->rect.w/2 - 10, sh->rect.y - sh->rect.h/2 + 50);
		List_add_missile(si->List_missiles, m);
	}
	
}

int SI_update_positions(SI* self) {
	Ship* s = List_return_ship(self->List_ships, 0);
	for (int i = self->List_ships->size - 1; i > -1; i--) {
		Ship* m = List_return_ship(self->List_ships, i);
		if (m == NULL) return -1;
		Ship_update_position(m);
		if (m->rect.x < -1) {
			if (m->status == 0)	m->rect.x = 0;
			else {
				List_remove_ship_node(self->List_ships, i);
				self->enemy_count--;
			}
		}
		if (m->rect.x > (self->width - m->rect.w)) {
			if (m->status == 0)	m->rect.x = (self->width - m->rect.w);
			else {
				self->enemy_count--;
				List_remove_ship_node(self->List_ships, i);
			}
		}
		if (m->rect.y < 0) {
			if (m->status == 0)	m->rect.y = 0;
			else {
				List_remove_ship_node(self->List_ships, i);
				self->enemy_count--;
			}
		}
		if (m->rect.y > (self->height - m->rect.h - 20)) {
			if (m->status == 0)	m->rect.y = (self->height - m ->rect.h - 20);
			else {
				s->life-=2;
				self->enemy_count--;
				if (s->life <= 0) self->end = true;
				List_remove_ship_node(self->List_ships, i);
			}
		}
	}	

	if (self->List_missiles->size == 0) return -1;
	for (int i = self->List_missiles->size-1; i > -1 ; i--) {
		Missile* m = List_return_missile(self->List_missiles, i);
		if (m == NULL) return -1;
		Missile_update_position(m);
		if ((m->rect.y < 0 || m->rect.y > self->height)) {
			List_remove_missile_node(self->List_missiles, i);			
		}
	}
	return 1;
}

int Generate_random()
{
	return rand()%100;
}

char* Int_to_string(int num)
{
	
	return NULL;
}

void SI_create_enemy(SI* self)
{
	int posx = (int)(self->width * Generate_random()/ 100);
	int speed = (Generate_random() + self->score/200 > 80) ? 2 : 1;
	Ship* s = Ship_create(1, posx, 0, self->width, self->height, speed, 10);
	if (s == NULL) {
		printf("error creating enemy ship");
		return;
	}
	List_add_ship(self->List_ships, s);
}

void SI_end_game(SI* self)
{
	self->end = true;	
}

void SI_check_for_collisions(SI* self)
{	
	
	Ship* me = List_return_ship(self->List_ships, 0);
	for (int i = self->List_ships->size - 1; i > 0; i--) {
		Ship* othership = List_return_ship(self->List_ships, i);
		if (Ships_check_for_collision(me, othership)) {
			List_remove_ship_node(self->List_ships, i);
			self->enemy_count--;
			me->life -= 5;
			SI_update_state(self);
			Blast_add_explosion(self->Explosions->List_blast_info, clock(), othership->rect.x, othership->rect.y, 80, 80);
			return;
		}
	}		
	
	if ((self->List_missiles->size)) {
		for (int i = self->List_ships->size - 1; i > -1; i--) {
			Ship* s = List_return_ship(self->List_ships, i);
			for (int j = self->List_missiles->size-1; j > -1; j--)				
				if (Ship_missile_check_for_collision(s, List_return_missile(self->List_missiles,j))) {
					s->life -= 3;
					if (s->life < 0) {
						if (s->status == 0) {
							self->end = true;
							return;
						}
						Blast_add_explosion(self->Explosions->List_blast_info, clock(), s->rect.x,s->rect.y,80,80);
						List_remove_ship_node(self->List_ships, i);
						self->enemy_count--;
						SI_update_score(self, self->score + 10);
					}
					List_remove_missile_node(self->List_missiles, j);
					break;
			}
		}
	}
}

void SI_update_score(SI* self, int newscore)
{
	self->score = newscore;
	int pom1 = self->score;
	int pom2 = 1;
	for (int i = 3; i > -1; i--){
		self->score_string[i] = '0' + pom1 % 10;
		pom1 /= 10;		
	}	
	self->score_string[4] = '\0';
}

void SI_update_state(SI* self)
{
	Ship* s = List_return_ship(self->List_ships, 0);
	if (s->cooldown == 0) {
		if ((clock() - s->last_shoot) > 2000)
			s->cooldown = s->cooldown_max;
	}
	
	int pom1 = s->life;
	if (pom1 <= 0) SI_end_game(self);
	int pom2 = 1;
	for (int i = 1; i > -1; i--) {
		self->life_string[i] = '0' + pom1 % 10;
		pom1 /= 10;
	}	
}

Blast* Blast_create(SDL_Renderer* rend)
{
	Blast* b = (Blast*)malloc(sizeof(Blast));
	if (b == NULL) return NULL;
	
	SDLDebug(SDL_Surface * surf = IMG_Load("res/blast2.png"));
	SDLDebug(b->blast_texture = SDL_CreateTextureFromSurface(rend, surf));
	SDLDebug(SDL_FreeSurface(surf));

	b->renderer = rend;

	b->rect1.x = 0;
	b->rect1.y = 0;
	b->rect1.w = 185;
	b->rect1.h = 185;

	b->rect2.x = 190;
	b->rect2.y = 0;
	b->rect2.w = 185;
	b->rect2.h = 185;

	b->rect3.x = 380;
	b->rect3.y = 0;
	b->rect3.w = 185;
	b->rect3.h = 185;

	b->rect4.x = 570;
	b->rect4.y = 0;
	b->rect4.w = 185;
	b->rect4.h = 185;

	b->rect5.x = 760;
	b->rect5.y = 0;
	b->rect5.w = 185;
	b->rect5.h = 185;

	b->rect6.x = 0;
	b->rect6.y = 190;
	b->rect6.w = 185;
	b->rect6.h = 185;

	b->rect7.x = 190;
	b->rect7.y = 190;
	b->rect7.w = 185;
	b->rect7.h = 185;

	b->rect8.x = 380;
	b->rect8.y = 190;
	b->rect8.w = 185;
	b->rect8.h = 185;

	b->rect9.x = 570;
	b->rect9.y = 190;
	b->rect9.w = 185;
	b->rect9.h = 185;

	b->rect10.x = 760;
	b->rect10.y = 190;
	b->rect10.w = 185;
	b->rect10.h = 185;

	b->rect11.x = 0;
	b->rect11.y = 375;
	b->rect11.w = 185;
	b->rect11.h = 185;

	b->rect12.x = 190;
	b->rect12.y = 375;
	b->rect12.w = 185;
	b->rect12.h = 185;

	b->rect13.x = 380;
	b->rect13.y = 375;
	b->rect13.w = 185;
	b->rect13.h = 185;

	b->rect14.x = 570;
	b->rect14.y = 375;
	b->rect14.w = 185;
	b->rect14.h = 185;

	b->rect15.x = 760;
	b->rect15.y = 375;
	b->rect15.w = 185;
	b->rect15.h = 185;

	b->rect16.x = 0;
	b->rect16.y = 580;
	b->rect16.w = 185;
	b->rect16.h = 185;

	b->rect17.x = 190;
	b->rect17.y = 580;
	b->rect17.w = 185;
	b->rect17.h = 185;

	b->rect18.x = 380;
	b->rect18.y = 580;
	b->rect18.w = 185;
	b->rect18.h = 185;

	b->rect19.x = 570;
	b->rect19.y = 580;
	b->rect19.w = 185;
	b->rect19.h = 185;

	b->rect20.x = 760;
	b->rect20.y = 580;
	b->rect20.w = 185;
	b->rect20.h = 185;

	b->end_time = 10;
	b->List_blast_info = List_create();
	
	return b;
}

void Blast_free(Blast** self)
{
	SDL_DestroyTexture((*self)->blast_texture);
	(*self)->blast_texture = NULL;
}

void Blast_add_explosion(List* self, clock_t time, int x, int y, int w, int h)
{
	Blast_info* b = (Blast_info*)malloc(sizeof(Blast_info));
	if (b == NULL) return;
	b->rect.x = x;
	b->rect.y = y;
	b->rect.w = w;
	b->rect.h = h;
	b->starttime = time;

	List_add_blast_info(self, b);
}

void Blast_render_explosion(Blast* self)
{
	if (self->List_blast_info->size == 0) return;
	for (int i = self->List_blast_info->size-1; i > -1; i--) {
		Blast_info* bi = List_return_blast_info(self->List_blast_info, i);
		int a = 15;
		int t = clock() - bi->starttime;
		if (t < a*1) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect1), &bi->rect);
		}
		else if (t < 2*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect2), &bi->rect);
		}
		else if (t < 3*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect3), &bi->rect);
		}
		else if (t < 4*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect4), &bi->rect);
		}
		else if (t < 5*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect5), &bi->rect);
		}
		else if (t < 6*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect6), &bi->rect);
		}
		else if (t < 7*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect7), &bi->rect);
		}
		else if (t < 8*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect8), &bi->rect);
		}
		else if (t < 9*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect9), &bi->rect);
		}
		else if (t < 10*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect10), &bi->rect);
		}
		else if (t < 11*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect11), &bi->rect);
		}
		else if (t < 12*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect12), &bi->rect);
		}
		else if (t < 13*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect13), &bi->rect);
		}
		else if (t < 14*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect14), &bi->rect);
		}
		else if (t < 15*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect15), &bi->rect);
		}
		else if (t < 16*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect16), &bi->rect);
		}
		else if (t < 17*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect17), &bi->rect);
		}
		else if (t < 18*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect18), &bi->rect);
		}
		else if (t < 19*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect19), &bi->rect);
		}
		else if (t < 20*a) {
			SDL_RenderCopy(self->renderer, self->blast_texture, &(self->rect20), &bi->rect);
		}
		else {
			List_remove_blast_info_node(self->List_blast_info,i);
		}
	}
}
