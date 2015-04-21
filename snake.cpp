#include "snake.h"
#include <curses.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int targetX;
int targetY;
int maxX;
int maxY;

Snake* NewSnake(int x, int y, Direction direction) {
	// Create snake's head at the specified position
	Snake* snake = new Snake;
	snake->head = new Node;
	snake->head->x = x;
	snake->head->y = y;
	snake->head->prevNode = NULL;
	snake->tail = snake->head;
	
	snake->dir = direction;

	return snake;
}

void DeleteSnake(Snake* snake) {
	while(snake->tail != NULL) {
		Node* temp = snake->tail;
		snake->tail = snake->tail->prevNode;
		delete temp;
	}
	delete snake;
}

void SetDir(Snake* snake, Direction dir) {
	snake->dir = dir;
}

void Draw(Snake* snake) {
	Node* temp = snake->tail;
	
	while(temp != NULL) {
		mvaddch(temp->y, temp->x, '*');
	}	
}

void RemoveAtTail(Snake* snake) {
	if(snake->tail != NULL){
		Node* temp = snake->tail;
		mvaddch(temp->y, temp->x, ' ');
		snake->tail = snake->tail->prevNode;
		delete temp;
	}
	// Please implement this function
}

void InsertAtHead(Snake* snake, Node* newHead) {
	snake->head->prevNode = newHead ;
	snake->head = newHead ;
	// Please implement this function
}

bool MoveSnake(Snake* snake) {
	Node* newHead= new Node;
	switch(snake->dir){
		case KEY_UP:
			newHead->x = snake->head->x;
			newHead->y = snake->head->y-1;
			break;
		case KEY_DOWN:
			newHead->x = snake->head->x;
			newHead->y = snake->head->y+1;
			break;
		case KEY_LEFT:
			newHead->x = snake->head->x-1;
			newHead->y = snake->head->y;
			break;
		case KEY_RIGHT:
			newHead->x = snake->head->x+1;
			newHead->y = snake->head->y;
			break;
		default:
			break;
	}
	newHead->prevNode = NULL;
	if (snake->head->x<=0 || snake->head->x>=maxX || 
		snake->head->y<=0 ||snake->head->y>=maxY)
		return false;
	return true;
	// Please implement this function
}

void GenerateNewTarget(Snake* snake) {	
	targetX = rand() % maxX;
	targetY = rand() % maxY;

	// Should check to make sure the new target does not overlap with the snake body
	mvaddch(targetY, targetX, '$');
}

