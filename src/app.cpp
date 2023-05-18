#include <ncurses.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "fsprocessor.h"
#include "texteditor.h"
#include "menu.h"


int main() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);
	FSProcessor fsp("data");

	WINDOW * textarea = newwin(max_y - 20, max_x, 0, 0);
	refresh();
	keypad(textarea, true);
	TextEditor te(textarea);

	WINDOW* menuwin = newwin(20, max_x, max_y - 20, 0);
	refresh();
	box(menuwin, 0, 0);
	wrefresh(menuwin);
	keypad(menuwin, true);
	Menu menu(menuwin, te, fsp);


	while (true) {
		te.input();
		menu.process();
	}
	endwin();
}
