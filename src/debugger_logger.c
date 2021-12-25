#include "debugger_logger.h"

int SDLCall(const char* file, const int line) {
	const char* err = SDL_GetError();
	printf("SDL message: %s in file %s in line %i \n", err, file, line);
	SDL_ClearError();
	return 0;
}