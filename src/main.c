#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "ship.h"

#include "SDL.h"

const int WIDTH = 600;
const int HEIGHT = 800;

int main() {

	game_start(WIDTH, HEIGHT);

	return 0;
}
