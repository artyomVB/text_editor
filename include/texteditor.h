#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <ncurses.h>

class TextEditor {
private:
	WINDOW* win_ = nullptr;
	std::vector<size_t> lines;
	size_t size;
	size_t curr;

	void reset_meta_information();

	void update_meta_information(const char*);

public:
	TextEditor(WINDOW *);
	
	size_t get_size();

	std::unique_ptr<char[]> get_text();

	void set_text(const char*);

	inline void backspace_handler(int, int);

	inline void enter_handler(int, int);

	void input();
};

