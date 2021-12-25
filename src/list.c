#include "list.h"

List* List_create(){
	List* l = (List*)malloc(sizeof(List));
	if (l == NULL) {
		printf("error creating list\n");
		return l;
	}
	else {
		l->head = NULL;
		l->tail = NULL;
		l->size = 0;
		return l;
	}
}

void List_add_missile(List* self, Missile* m)
{
	if (self->size == 0) {
		Node_missile* n = NULL;
		n = (Node_missile*)malloc(sizeof(Node_missile));
		if (n == NULL) return;
		n->data = m;
		n->next = NULL;
		n->prev = NULL;
		self->head = n;
		self->tail = n;
		self->size++;
	}
	else {
		Node_missile* n = (Node_missile*)malloc(sizeof(Node_missile));
		if (n == NULL) return;
		n->data = m;
		n->next = NULL;
		n->prev = self->head;
		((Node_missile*)self->head)->next = n;
		self->head = n;
		self->size++;		
	}	
}

void List_add_ship(List* self, Ship* m)
{
	if (self->size == 0) {
		Node_ship* n = NULL;
		n = (Node_ship*)malloc(sizeof(Node_ship));
		if (n == NULL) return;
		(Ship*)n->data = m;
		n->next = NULL;
		n->prev = NULL;
		self->head = n;
		self->tail = n;
		self->size++;
	}
	else {
		Node_ship* n = (Node_ship*)malloc(sizeof(Node_ship));
		if (n == NULL) return;
		n->data = m;
		n->next = NULL;
		n->prev = self->head;
		((Node_ship*)self->head)->next = n;
		self->head = n;
		self->size++;
	}	
}

void List_add_blast_info(List* self, Blast_info* bi)
{
	if (self->size == 0) {
		Node_blast_info* n = NULL;
		n = (Node_blast_info*)malloc(sizeof(Node_blast_info));
		if (n == NULL) return;
		(Blast_info*)n->data = bi;
		n->next = NULL;
		n->prev = NULL;
		self->head = n;
		self->tail = n;
		self->size++;
	}
	else {
		Node_blast_info* n = (Node_blast_info*)malloc(sizeof(Node_blast_info));
		if (n == NULL) return;
		n->data = bi;
		n->next = NULL;
		n->prev = self->head;
		((Node_blast_info*)self->head)->next = n;
		self->head = n;
		self->size++;
	}
}

void List_add_button(List* self, Button* bi)
{
	if (self->size == 0) {
		Node_button* n = NULL;
		n = (Node_button*)malloc(sizeof(Node_button));
		if (n == NULL) return;
		(Button*)n->data = bi;
		n->next = NULL;
		n->prev = NULL;
		self->head = n;
		self->tail = n;
		self->size++;
	}
	else {
		Node_button* n = (Node_button*)malloc(sizeof(Node_button));
		if (n == NULL) return;
		n->data = bi;
		n->next = NULL;
		n->prev = self->head;
		((Node_button*)self->head)->next = n;
		self->head = n;
		self->size++;
	}
}

Ship* List_return_ship(List* self, int index)
{
	if (self->size == 0) {
		return NULL;
	}
	Node_ship* n = (Node_ship*)self->tail;
	int counter = 0;
	while (true) {
		if (counter == index) return n->data;
		n = n->next;
		counter++;
	}
}

Missile* List_return_missile(List* self, int index)
{
	if (self->size == 0) return NULL;
	Node_missile* n = (Node_missile*)self->tail;
	int counter = 0;
	while (true) {
 		if (counter == index) return n->data;
		n = n->next;
		counter++;
	}	
}

Blast_info* List_return_blast_info(List* self, int index)
{
	if (self->size == 0) return NULL;
	Node_blast_info* n = (Node_blast_info*)self->tail;
	int counter = 0;
	while (true) {
		if (counter == index) return n->data;
		n = n->next;
		counter++;
	}
}

Button* List_return_button(List* self, int index)
{
	if (self->size == 0) return NULL;
	Node_button* n = (Node_button*)self->tail;
	int counter = 0;
	while (true) {
		if (counter == index) return n->data;
		n = n->next;
		counter++;
	}
}

bool List_remove_missile_node(List* self, int index)
{
	if (self->size == 0) return true;
	if (self->size == 1) {
		Missile_free(((Node_missile*)self->head)->data);
		free((Node_missile*)self->head);
		self->head = NULL;
		self->tail = NULL;
		self->size = 0;
		return true;
	}
	else if (self->size == index+1) {
		Missile_free(((Node_missile*)self->head)->data);
		Node_missile* n = (Node_missile*)self->head;
		(Node_missile*)self->head = n->prev;
		n->prev->next = NULL;
		free(n);
		self->size--;
		return true;
	}
	else if (index == 0) {
		Missile_free(((Node_missile*)self->tail)->data);
		Node_missile* n = (Node_missile*)self->tail;
		self->tail = n->next;
		((Node_missile*)(self->tail))->prev = NULL;
		free(((Node_missile*)self->tail)->prev);
		((Node_missile*)self->tail)->prev = NULL;
		self->size--;
		return true;
	}
	else {
		Node_missile* n = (Node_missile*)self->tail;
		if (n == NULL) return false;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}
		n->prev->next = n->next;
		n->next->prev = n->prev;
		Missile_free(n->data);
		n->data = NULL;
		free(n);		
		self->size--;
		return true;
	}	
}

bool List_remove_ship_node(List* self, int index) {	

	if (self->size == 0) return false;
	if (self->size == 1) {
		Ship_free(((Node_ship*)self->head)->data);
		free((Node_ship*)self->head);
		self->head = NULL;
		self->tail = NULL;
		self->size = 0;
	}
	else if (self->size == index + 1) {
		Ship_free(((Node_ship*)self->head)->data);
		Node_ship* n = (Node_ship*)self->head;
		(Node_ship*)self->head = n->prev;
		n->prev->next = NULL;
		free(n);
		self->size--;
	}
	else if (index == 0) {
		Ship_free(((Node_ship*)self->tail)->data);
		Node_ship* n = (Node_ship*)self->tail;
		self->tail = n->next;
		((Node_ship*)(self->tail))->prev = NULL;
		free(((Node_ship*)self->tail)->prev);
		((Node_ship*)self->tail)->prev = NULL;
		self->size--;
	}
	else {
		Node_ship* n = (Node_ship*)self->tail;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}
		n->prev->next = n->next;
		n->next->prev = n->prev;
		Ship_free(n->data);
		free(n);		
		self->size--;
	}
	return true;
}

void List_remove_blast_info_node(List* self, int index)
{
	if (self->size == 0) return;
	if (self->size == 1) {
		free(((Node_blast_info*)self->head)->data);
		free((Node_blast_info*)self->head);
		self->head = NULL;
		self->tail = NULL;
		self->size = 0;
	}
	else if (self->size == index + 1) {
		free(((Node_blast_info*)self->head)->data);
		Node_blast_info* n = (Node_blast_info*)self->head;
		(Node_blast_info*)self->head = n->prev;
		n->prev->next = NULL;
		free(n);
		self->size--;
	}
	else if (index == 0) {
		free(((Node_blast_info*)self->tail)->data);
		Node_blast_info* n = (Node_blast_info*)self->tail;
		self->tail = n->next;
		((Node_blast_info*)(self->tail))->prev = NULL;
		free(((Node_blast_info*)self->tail)->prev);
		((Node_blast_info*)self->tail)->prev = NULL;
		self->size--;
	}
	else {
		Node_blast_info* n = (Node_blast_info*)self->tail;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}
		n->prev->next = n->next;
		n->next->prev = n->prev;
		free(n->data);
		free(n);		
		self->size--;
	}
}

void List_remove_button_node(List* self, int index)
{
	if (self->size == 0) return;
	if (self->size == 1) {
		free(((Node_button*)self->head)->data);
		free((Node_button*)self->head);
		self->head = NULL;
		self->tail = NULL;
		self->size = 0;
	}
	else if (self->size == index + 1) {
		free(((Node_button*)self->head)->data);
		Node_button* n = (Node_button*)self->head;
		(Node_button*)self->head = n->prev;
		n->prev->next = NULL;
		free(n);
		self->size--;
	}
	else if (index == 0) {
		free(((Node_button*)self->tail)->data);
		Node_button* n = (Node_button*)self->tail;
		self->tail = n->next;
		((Node_button*)(self->tail))->prev = NULL;
		free(((Node_button*)self->tail)->prev);
		((Node_button*)self->tail)->prev = NULL;
		self->size--;
	}
	else {
		Node_button* n = (Node_button*)self->tail;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}
		n->prev->next = n->next;
		n->next->prev = n->prev;
		free(n->data);
		n->data = NULL;
		free(n);		
		self->size--;
	}
}

bool List_missile_free(List** self) {
	//printf("missile count %d\n", (*self)->size);
	if ((*self)->size == 0) return true;
	for (int i = (*self)->size-1; i > -1;  i--) {
		List_remove_missile_node(*self, i);
 	}
	return true;
}

bool List_ships_free(List** self) {
	//printf("ships count %d\n", (*self)->size);
	if ((*self)->size == 0) return true;
	//printf("ships number %d\n", (*self)->size);
	for (int i = (*self)->size-1; i > -1; i--) {
		List_remove_ship_node(*self, i);
	}
	return true;
}

void List_blast_info_free(List** self)
{
	if ((*self)->size == 0) return;
	Node_blast_info* b = (*self)->head;
	Node_blast_info* prev = b->prev;
	for (int i = (*self)->size - 1; i > -1; i--) {
		List_remove_blast_info_node(*self, i);
	}
}

void List_button_free(List** self)
{
	if ((*self)->size == 0) return;
	Node_button* b = (*self)->head;
	Node_button* prev = b->prev;
	for (int i = (*self)->size - 1; i > -1; i--) {
		List_remove_button_node(*self, i);
	}
}

void List_button_set_focus(List* self, int index)
{
	for (int i = 0; i < self->size; i++) {
		if (i == index) {
			List_return_button(self, i)->focus = true;
		}
		else
			List_return_button(self, i)->focus = false;
	}
}

int List_button_get_focus(List* self)
{
	if (self->size == 0) return -1;
	for (int i = 0; i < self->size; i++) {
		if (List_return_button(self, i)->focus == true)
			return i;
	}
	return -1;
}





