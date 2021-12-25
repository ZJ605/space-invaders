#ifndef ALPHABET_H
#define ALPHABET_H

#include "headers.h"

#include "SDL.h"
#include "SDL_image.h"

#include <string.h>

typedef struct Alphabet_ {
	SDL_Texture* alphabetTexture;
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect rect3;
	SDL_Rect rect4;
	SDL_Rect rect5;
	SDL_Rect rect6;
	SDL_Rect rect7;
	SDL_Rect rect8;
	SDL_Rect rect9;
	SDL_Rect rect0;
	SDL_Rect rectA;
	SDL_Rect rectB;
	SDL_Rect rectC;
	SDL_Rect rectD;
	SDL_Rect rectE;
	SDL_Rect rectF;
	SDL_Rect rectG;
	SDL_Rect rectH;
	SDL_Rect rectI;
	SDL_Rect rectJ;
	SDL_Rect rectK;
	SDL_Rect rectL;
	SDL_Rect rectM;
	SDL_Rect rectN;
	SDL_Rect rectO;
	SDL_Rect rectP;
	SDL_Rect rectQ;
	SDL_Rect rectR;
	SDL_Rect rectS;
	SDL_Rect rectT;
	SDL_Rect rectU;
	SDL_Rect rectV;
	SDL_Rect rectW;
	SDL_Rect rectX;
	SDL_Rect rectY;
	SDL_Rect rectZ;
} Alphabet;

Alphabet* Create_alphabet(SDL_Renderer* rend);
void Alphabet_render_text(Alphabet* a, char* text, int x, int y, int font, SDL_Renderer* rend);
void Alphabet_free(Alphabet** self);
#endif
