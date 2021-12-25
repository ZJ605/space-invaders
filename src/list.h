#ifndef LIST_H
#define LIST_H

#include "headers.h"

#include "ship.h"

#include "SDL.h"
#include "SDL_image.h"

typedef struct Node_missile_ Node_missile;
typedef struct Node_ship_ Node_ship;
typedef struct Node_blast_info_ Node_blast_info;
typedef struct Blast_info_ {
	clock_t starttime;
	SDL_Rect rect;
} Blast_info;
typedef struct Node_button_ Node_button;

typedef struct List_ List;

struct Node_missile_ {
	void* data;
	Node_missile* next;
	Node_missile* prev;
};

struct Node_ship_ {
	void* data;
	Node_ship* next;
	Node_ship* prev;
};

struct Node_blast_info_ {
	void* data;
	Node_blast_info* next;
	Node_blast_info* prev;
};

typedef struct Node_button_ Node_button;
struct Node_button_ {
	void* data;
	Node_button* next;
	Node_button* prev;
};

struct List_ {
	void* head;
	void* tail;
	int size;
};

List* List_create();

void List_add_missile(List* self, Missile* m);
void List_add_ship(List* self, Ship* m);
void List_add_blast_info(List* self, Blast_info* bi);
void List_add_button(List* self, Button* bi);

Ship* List_return_ship(List* self, int index);
Missile* List_return_missile(List* self, int index);
Blast_info* List_return_blast_info(List* self, int index);
Button* List_return_button(List* self, int index);

bool List_remove_missile_node(List* self, int index);
bool List_remove_ship_node(List* self, int index);
void List_remove_blast_info_node(List* self, int index);
void List_remove_button_node(List* self, int index);

bool List_missile_free(List** self);
bool List_ships_free(List** self);
void List_blast_info_free(List** self);
void List_button_free(List** self);

void List_button_set_focus(List* self, int index);
int List_button_get_focus(List* self);


#endif