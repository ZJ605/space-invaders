#include "ship.h"

Button* Button_create(SDL_Renderer* rend, int x, int y, int w, int h, Alphabet* alphabet,  char* text)
{
	Button* btn = (Button*)malloc(sizeof(Button));
	if (btn == NULL) {
		printf("Error creating button\n");
		return NULL;
	}

	btn->renderer = rend;
	btn->rect.x = x;
	btn->rect.y = y;
	btn->rect.w = w;
	btn->rect.h = h;

	btn->focus_rect.x = x-20;
	btn->focus_rect.y = y+h/2-5;
	btn->focus_rect.w = 10;
	btn->focus_rect.h = 10;

	SDLDebug(SDL_Surface * surf = IMG_Load("res/white_button.png"));
	SDLDebug(btn->texture = SDL_CreateTextureFromSurface(rend, surf));
	SDLDebug(SDL_FreeSurface(surf));

	SDLDebug(SDL_Surface * surf1 = IMG_Load("res/green_rectangle.png"));
	SDLDebug(btn->focus_texture = SDL_CreateTextureFromSurface(rend, surf1));
	SDLDebug(SDL_FreeSurface(surf1));

	btn->alphabet = alphabet;

	char* t = (char*)malloc(sizeof(char)*strlen(text)+1);
	if (t == NULL) {
		printf("Error creating button\n");
		return NULL;
	}
	memcpy(t,text,strlen(text)*sizeof(char)+1);
	
	btn->text = t;
	
	btn->focus = false;

	return btn;
}

void Button_free(Button** self)
{
	SDL_DestroyTexture((*self)->texture);
	(*self)->texture = NULL;
	SDL_DestroyTexture((*self)->focus_texture);
	(*self)->focus_texture = NULL;
	free((*self)->text);
}

void Button_render(Button* self)
{
	if (self->focus) {
		SDL_RenderCopy(self->renderer, self->focus_texture, NULL, &self->focus_rect);
	}
	SDL_RenderCopy(self->renderer, self->texture, NULL, &self->rect);
	Alphabet_render_text(self->alphabet, self->text, self->rect.x+self->rect.w/2 - strlen(self->text)*10,self->rect.y+self->rect.h/2-15, 5, self->renderer);
}

void Button_update_text(Button* self, char* txt)
{
	
	free(self->text);
	
	char* t = (char*)malloc(sizeof(char) * strlen(txt) + 7);
	if (t == NULL) {
		printf("Error creating button\n");
		return;
	}
	*t = 'S';
	*(t+1) = 'C';
	*(t + 2) = 'O';
	*(t + 3) = 'R';
	*(t + 4) = 'E';
	*(t + 5) = ' ';
	
	memcpy(t+6, txt, strlen(txt) * sizeof(char) + 1);
	t[strlen(txt)+6] = '\0';
	self->text = t;
}

Missile* Missile_create(int status, int posx, int posy) {
	Missile* m = (Missile*)malloc(sizeof(Missile));
	if (m == NULL) return m;
	m->rect.x = posx;
	m->rect.y = posy;
	m->rect.w = 10;
	m->rect.h = 10;
	m->speed = 4;
	m->status = status;
	if (status) m->direction = 1;
	else m->direction = -1;
	
	return m;
}

bool Missile_free(Missile* self) {
	return true;
}

void Missile_update_position(Missile* self) {
	self->rect.y += self->direction * self->speed;	
}

Ship* Ship_create(int status, int posx, int posy, int width, int height, int speed, int life)
{
	Ship* s = NULL;
	s = (Ship*)malloc(sizeof(Ship));
	if (s == NULL) {
		printf("new ship is null\n");
		return s;
	}
	s->status = status;
	if (status) s->down = true;
	else s->down = false;
	s->up = false;
	s->left = false;
	s->right = false;
	s->max_life = life;
	s->life = s->max_life;
	s->cooldown = 10;
	s->cooldown_max = 10;
	s->speed = speed;
	s->rect.x = posx;
	s->rect.y = posy;
	s->rect.w = 50;
	s->rect.h = 50;
	if (status == 0) {
		s->rect_max_life.x = s->rect.x;
		s->rect_max_life.y = s->rect.y + 50;
		s->rect_max_life.w = s->rect.w;
		s->rect_max_life.h = 5;

		s->rect_life.x = s->rect.x;
		s->rect_life.y = s->rect.y + 50;
		s->rect_life.w = s->rect.w;
		s->rect_life.h = 5;

		s->rect_cool_down.x = s->rect.x;
		s->rect_cool_down.y = s->rect.y + 60;
		s->rect_cool_down.w = s->rect.w;
		s->rect_cool_down.h = 5;

		s->rect_cool_down_max.x = s->rect.x;
		s->rect_cool_down_max.y = s->rect.y + 60;
		s->rect_cool_down_max.w = s->rect.w;
		s->rect_cool_down_max.h = 5;
	}
	else {		
		s->rect_max_life.x = s->rect.x;
		s->rect_max_life.y = s->rect.y-5;
		s->rect_max_life.w = s->rect.w;
		s->rect_max_life.h = 5;

		s->rect_life.x = s->rect.x;
		s->rect_life.y = s->rect.y - 5;
		s->rect_life.w = s->rect.w;
		s->rect_life.h = 5;
	}

	s->last_shoot = clock();

	

	return s;
}

bool Ship_free(Ship* self) {
	return true;
}

void Ship_update_position(Ship* self) {
	self->rect.y += -1 * self->up * self->speed + self->down * self->speed;
	self->rect.x += -1 * self->left * self->speed + self->right * self->speed;	
	if (self->status == 0) {
		self->rect_max_life.x = self->rect.x;
		self->rect_max_life.y = self->rect.y+50;
		self->rect_max_life.w = self->rect.w;
		self->rect_max_life.h = 5;

		self->rect_life.x = self->rect.x;
		self->rect_life.y = self->rect.y + 50;
		self->rect_life.w = self->rect.w * self->life / self->max_life;
		self->rect_life.h = 5;

		self->rect_cool_down.x = self->rect.x;
		self->rect_cool_down.y = self->rect.y + 60;
		self->rect_cool_down.w = self->rect.w * self->cooldown / self->cooldown_max;
		self->rect_cool_down.h = 5;

		self->rect_cool_down_max.x = self->rect.x;
		self->rect_cool_down_max.y = self->rect.y + 60;
		self->rect_cool_down_max.w = self->rect.w;
		self->rect_cool_down_max.h = 5;
	}
	else {
		self->rect_max_life.x = self->rect.x;
		self->rect_max_life.y = self->rect.y-5;
		self->rect_max_life.w = self->rect.w;
		self->rect_max_life.h = 5;

		self->rect_life.x = self->rect.x;
		self->rect_life.y = self->rect.y - 5;
		self->rect_life.w = self->rect.w * self->life / self->max_life;
		self->rect_life.h = 5;
	}
}

bool Ships_check_for_collision(const Ship* s1, const Ship* s2)
{
	if ((powf(((float)s1->rect.x - (float)s2->rect.x), 2) + powf(((float)s1->rect.y - (float)s2->rect.y), 2)) < 1800)
		return true;
	return false;
}

bool Ship_missile_check_for_collision(const Ship* s, const Missile* m) {
	if (s->status != m->status) {
		if ((powf((((float)s->rect.x + 25) - ((float)m->rect.x + 5)), 2) + powf((((float)s->rect.y + 25) - ((float)m->rect.y + 5)), 2)) < 450)
			return true;
	}
	return false;
}