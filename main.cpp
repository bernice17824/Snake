#include <curses.h>
#include <unistd.h>
#include "snake.h"

using namespace std;
extern int maxX;
extern int maxY;

int main() {
	int c;
	bool gameEnded = false;
	
	initscr();
	cbreak();		// Disable buffering, making input available to the program immediately
	timeout(1000);		// Wait user's input for at most 1s
	keypad(stdscr, TRUE);	// Enable input from arrow keys
	curs_set(0); 			// Hide cursor
	getmaxyx(stdscr, maxY, maxX);	// Get max X and Y of the terminal
	printw("%d %d", maxX, maxY);
	
	Snake* snake = NewSnake(1,1, RIGHT);
	GenerateNewTarget(snake);
	
	while (!gameEnded) {
		c = getch();
		switch (c) {
		case KEY_UP:
			SetDir(snake, UP);
			break;
		case KEY_DOWN:
			SetDir(snake, DOWN);
			break;
		case KEY_LEFT:
			SetDir(snake, LEFT);
			break;
		case KEY_RIGHT:
			SetDir(snake, RIGHT);
			break;
		default:
			break;
		}

		if (c == 'q' || c == 'Q') break;
		gameEnded = !MoveSnake(snake);
	}
	
	DeleteSnake(snake);
	endwin();	// Restores the terminal after Curses activity
}

