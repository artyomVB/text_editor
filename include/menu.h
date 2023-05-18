#pragma once
#include <memory>
#include <vector>
#include <string>
#include <ncurses.h>
#include "fsprocessor.h"
#include "texteditor.h"


class Menu {
private:
	WINDOW* win_ = nullptr;
	TextEditor& texteditor_;
	FSProcessor& fsp_;
	
	void clear_screen();
	
	void print_hello_message();

public:
	Menu(WINDOW*, TextEditor&, FSProcessor&);

	void handle_save();

	int handle_choose();

	void process();	
};

