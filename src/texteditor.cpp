#include "texteditor.h"


void TextEditor::reset_meta_information() {
	size = 0;
	curr = 0;
	lines.clear();
	lines.push_back(0);
}

void TextEditor::update_meta_information(const char* text) {
	reset_meta_information();
	size_t i = 0;
	while (text[i] != 0) {
		if (text[i] == '\n') {
			lines.push_back(0);
			curr++;
		} else {
			lines[curr]++;	
			size++;
		}
		i++;
	}
	curr = 0;
}

TextEditor::TextEditor(WINDOW * win) : win_(win) {
	lines.push_back(0);
	size = 0;
	curr = 0;
}
	
size_t TextEditor::get_size() {
	return size;
}

std::unique_ptr<char[]> TextEditor::get_text() {
	size += (lines.size() - 1);
	std::unique_ptr<char[]> ptr(new char[size + 1]);
	for (size_t i = 0; i <= size; ++i) {
		ptr[i] = 0;
	}
	auto p = ptr.get();
	mvwinnstr(win_, 0, 0, p, lines[0]);
	for (size_t i = 1; i < lines.size(); ++i) {
		p += lines[i - 1];
		*p = '\n';
		p += 1;
		mvwinnstr(win_, i, 0, p, lines[i]);
	}
	return ptr;
}

void TextEditor::set_text(const char* text) {
	update_meta_information(text);
	werase(win_);
	mvwprintw(win_, 0, 0, text);
	wrefresh(win_);
}

inline void TextEditor::backspace_handler(int x, int y) {
	if (x == 0) {
		if (y != 0) {
			auto pos = lines[y - 1];
			if (lines[curr] == 0) {
				wdeleteln(win_);	
			} else {
				char buf[lines[curr] + 1];
				winnstr(win_, buf, lines[curr]);
				buf[lines[curr]] = 0;
				wdeleteln(win_);
				mvwaddstr(win_, y - 1, lines[y - 1], buf);
				lines[y - 1] += lines[curr];
			}
			lines.erase(lines.begin() + curr);
			curr--;
			wmove(win_, curr, pos);
		}
	} else {
		wmove(win_, y, x - 1);
		wdelch(win_);
		wrefresh(win_);
		lines[curr] -= 1;
		size -= 1;
	}
}

inline void TextEditor::enter_handler(int x, int y) {
	if (x == lines[curr]) {
		if (curr != lines.size() - 1) {
			winsdelln(win_, 1);
			curr++;
			lines.insert(lines.begin() + curr, 0);
		} else {
			curr++;
			lines.push_back(0);
		}
	} else {
		size_t sz = lines[curr] - x;
		char buf[sz + 1];
		lines[curr] -= sz;
		winnstr(win_, buf, sz);
		buf[sz] = 0;
		if (curr != lines.size() - 1) {
			wmove(win_, curr + 1, 0);
			winsdelln(win_, 1);
			curr++;
			lines.insert(lines.begin() + curr, sz);
		} else {
			curr++;
			lines.push_back(sz);
		}
		for (size_t i = 0; i != sz; ++i) {
			mvwdelch(win_, y, x);
		}
		mvwaddstr(win_, y + 1, 0, buf);
	}		
	wmove(win_, y + 1, 0);
}

void TextEditor::input() {
	wmove(win_, 0, 0);
	while(true) {
		int c = wgetch(win_);
		int x, y;
		getyx(win_, y, x);
		if (c == KEY_BACKSPACE) {
			backspace_handler(x, y);
		} else if ((char)c == '\n') {
			enter_handler(x, y);
		} else if (c == 1) {
			break;
		} else if (c == KEY_UP) {
			if (y > 0) {
				wmove(win_, y - 1, std::min((size_t)x, lines[curr - 1]));
				if (curr > 0) {
					curr--;
				}
			}	
		} else if (c == KEY_DOWN) {
			if (curr + 1 < lines.size()) {				
				wmove(win_, y + 1, std::min((size_t)x, lines[curr + 1]));
				curr++;
			}			
		} else if (c == KEY_LEFT) {
			wmove(win_, y, x - 1);	
		} else if (c == KEY_RIGHT) {
			if (x < lines[curr]) {
				wmove(win_, y, x + 1);	
			}
		} else {
			lines[curr]++;
			size++;
			winsch(win_, (chtype)c);
			wmove(win_, y, x + 1);
			wrefresh(win_);
		}
	}
}

