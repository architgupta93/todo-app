#include <ncurses.h>

int main()
{
   	initscr();	// creates stdscr object (constructor)
	raw();
	printw("Hello World\nWelcome to this page");
	getch();
	endwin();	// Frees up the memory associated with the stdscr object. This is a destructor f

	return 0;
}
