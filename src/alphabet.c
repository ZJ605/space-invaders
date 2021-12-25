#include "ship.h"

#include "headers.h"
#include "alphabet.h"

Alphabet* Create_alphabet(SDL_Renderer* rend)
{
	Alphabet* a = (Alphabet*)malloc(sizeof(Alphabet));
	if (a == NULL) {
		printf("error createing alphabet\n");
		return NULL;
	}

	IMG_Init(IMG_INIT_PNG);

	SDL_Surface * surf = IMG_Load("res/alphabet2.png");
	a->alphabetTexture = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);

	a->rectA.x = 40;
	a->rectA.y = 0;
	a->rectA.w = 90;
	a->rectA.h = 90;

	a->rectB.x = 250;
	a->rectB.y = 0;
	a->rectB.w = 90;
	a->rectB.h = 90;

	a->rectC.x = 460;
	a->rectC.y = 0;
	a->rectC.w = 90;
	a->rectC.h = 90;

	a->rectD.x = 670;
	a->rectD.y = 0;
	a->rectD.w = 90;
	a->rectD.h = 90;

	a->rectE.x = 890;
	a->rectE.y = 0;
	a->rectE.w = 90;
	a->rectE.h = 90;

	a->rectF.x = 1100;
	a->rectF.y = 0;
	a->rectF.w = 90;
	a->rectF.h = 90;

	a->rectG.x = 40;
	a->rectG.y = 125;
	a->rectG.w = 90;
	a->rectG.h = 90;

	a->rectH.x = 250;
	a->rectH.y = 120;
	a->rectH.w = 90;
	a->rectH.h = 90;

	a->rectI.x = 420;
	a->rectI.y = 120;
	a->rectI.w = 90;
	a->rectI.h = 90;

	a->rectJ.x = 670;
	a->rectJ.y = 120;
	a->rectJ.w = 90;
	a->rectJ.h = 90;

	a->rectK.x = 850;
	a->rectK.y = 120;
	a->rectK.w = 90;
	a->rectK.h = 90;

	a->rectL.x = 1100;
	a->rectL.y = 120;
	a->rectL.w = 90;
	a->rectL.h = 90;

	a->rectM.x = 40;
	a->rectM.y = 250;
	a->rectM.w = 90;
	a->rectM.h = 90;

	a->rectN.x = 250;
	a->rectN.y = 250;
	a->rectN.w = 90;
	a->rectN.h = 90;

	a->rectO.x = 460;
	a->rectO.y = 250;
	a->rectO.w = 90;
	a->rectO.h = 90;

	a->rectP.x = 670;
	a->rectP.y = 250;
	a->rectP.w = 90;
	a->rectP.h = 90;

	a->rectQ.x = 870;
	a->rectQ.y = 250;
	a->rectQ.w = 90;
	a->rectQ.h = 90;

	a->rectR.x = 1100;
	a->rectR.y = 250;
	a->rectR.w = 90;
	a->rectR.h = 90;

	a->rectS.x = 30;
	a->rectS.y = 375;
	a->rectS.w = 90;
	a->rectS.h = 90;

	a->rectT.x = 230;
	a->rectT.y = 375;
	a->rectT.w = 90;
	a->rectT.h = 90;

	a->rectU.x = 410;
	a->rectU.y = 375;
	a->rectU.w = 90;
	a->rectU.h = 90;

	a->rectV.x = 650;
	a->rectV.y = 375;
	a->rectV.w = 90;
	a->rectV.h = 90;

	a->rectW.x = 890;
	a->rectW.y = 375;
	a->rectW.w = 90;
	a->rectW.h = 90;

	a->rectX.x = 1100;
	a->rectX.y = 375;
	a->rectX.w = 90;
	a->rectX.h = 90;

	a->rectY.x = 40;
	a->rectY.y = 505;
	a->rectY.w = 90;
	a->rectY.h = 90;

	a->rectZ.x = 200;
	a->rectZ.y = 505;
	a->rectZ.w = 90;
	a->rectZ.h = 90;

	a->rect0.x = 400;
	a->rect0.y = 500;
	a->rect0.w = 90;
	a->rect0.h = 90;

	a->rect1.x = 600;
	a->rect1.y = 500;
	a->rect1.w = 90;
	a->rect1.h = 90;

	a->rect2.x = 850;
	a->rect2.y = 505;
	a->rect2.w = 90;
	a->rect2.h = 90;

	a->rect3.x = 1100;
	a->rect3.y = 500;
	a->rect3.w = 90;
	a->rect3.h = 90;

	a->rect4.x = 50;
	a->rect4.y = 625;
	a->rect4.w = 90;
	a->rect4.h = 90;

	a->rect5.x = 250;
	a->rect5.y = 625;
	a->rect5.w = 90;
	a->rect5.h = 90;

	a->rect6.x = 480;
	a->rect6.y = 625;
	a->rect6.w = 90;
	a->rect6.h = 90;

	a->rect7.x = 670;
	a->rect7.y = 625;
	a->rect7.w = 90;
	a->rect7.h = 90;

	a->rect8.x = 890;
	a->rect8.y = 625;
	a->rect8.w = 90;
	a->rect8.h = 90;

	a->rect9.x = 1100;
	a->rect9.y = 625;
	a->rect9.w = 90;
	a->rect9.h = 90;

	return a;
}


void Alphabet_render_text(Alphabet* a, char* text, int x, int y, int font, SDL_Renderer* rend)
{
	SDL_Rect r;
	r.w = 4*font;
	r.h = 4*font;
	r.y = y + 5;
	for (int i = 0; i < strlen(text); i++) {
		r.x = x + i*r.w;
		if (text[i] == 'A')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectA, &r);
		else if (text[i] == 'B')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectB, &r);
		else if (text[i] == 'C')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectC, &r);
		else if (text[i] == 'D')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectD, &r);
		else if (text[i] == 'E')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectE, &r);
		else if (text[i] == 'F')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectF, &r);
		else if (text[i] == 'G')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectG, &r);
		else if (text[i] == 'H')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectH, &r);
		else if (text[i] == 'I')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectI, &r);
		else if (text[i] == 'J')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectJ, &r);
		else if (text[i] == 'K')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectK, &r);
		else if (text[i] == 'L')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectL, &r);
		else if (text[i] == 'M')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectM, &r);
		else if (text[i] == 'N')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectN, &r);
		else if (text[i] == 'O')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectO, &r);
		else if (text[i] == 'P')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectP, &r);
		else if (text[i] == 'Q')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectQ, &r);
		else if (text[i] == 'R')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectR, &r);
		else if (text[i] == 'S')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectS, &r);
		else if (text[i] == 'T')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectT, &r);
		else if (text[i] == 'U')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectU, &r);
		else if (text[i] == 'V')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectV, &r);
		else if (text[i] == 'W')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectW, &r);
		else if (text[i] == 'X')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectX, &r);
		else if (text[i] == 'Y')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectY, &r);
		else if (text[i] == 'Z')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rectZ, &r);
		else if (text[i] == '0')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect0, &r);
		else if (text[i] == '1')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect1, &r);
		else if (text[i] == '2')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect2, &r);
		else if (text[i] == '3')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect3, &r);
		else if (text[i] == '4')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect4, &r);
		else if (text[i] == '5')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect5, &r);
		else if (text[i] == '6')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect6, &r);
		else if (text[i] == '7')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect7, &r);
		else if (text[i] == '8')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect8, &r);
		else if (text[i] == '9')
			SDL_RenderCopy(rend, a->alphabetTexture, &a->rect9, &r);
	}
}

void Alphabet_free(Alphabet** self)
{
	SDL_DestroyTexture((*self)->alphabetTexture);
	(*self) = NULL;
}
