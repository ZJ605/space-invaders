#ifndef LOGGER_DEBUGGER_H
#define LOGGER_DEBUGGER_H

#include "SDL.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

int SDLCall(const char* file, const int line);

#define PROFILE 1 //0 - debug, 1 - release

#ifndef PROFILE
#define PROFILE 1 
#endif
#if PROFILE == 0
	#define LOG(x) printf(x)
	#define SDLDebug(x) \
	SDL_ClearError();\
	x;\
	SDLCall(__FILE__, __LINE__);\
	
	#define MEAS_TIME(x) x

#elif PROFILE == 1
	#define LOG(x)
	#define SDLDebug(x) x
#endif

#endif
