#include "menu.h"

void Menu::clear_screen() {
	werase(win_);
	box(win_, 0, 0);
	wrefresh(win_);
}
	
void Menu::print_hello_message() {
	clear_screen();
	mvwprintw(win_, 1, 1, "Press Ctrl+A to enter menu");
	wrefresh(win_);
}

Menu::Menu(WINDOW* win, TextEditor& texteditor, FSProcessor& fsp) : win_(win), texteditor_(texteditor), fsp_(fsp) {
	wmove(win_, 1, 1);
	print_hello_message();
}

void Menu::handle_save() {
	clear_screen();
	std::string name = "";
	mvwprintw(win_, 1, 1, "Enter name:\n");
	wmove(win_, 2, 1);
	wrefresh(win_);
	while(true) {
		int c = getch();
		if (c == KEY_BACKSPACE) {
			int x, y;
			getyx(win_, y, x);
			wmove(win_, y, x - 1);
			wdelch(win_);
			wrefresh(win_);
			continue;
		} else if (c == '\n') {
			auto ptr = texteditor_.get_text();
			fsp_.save_file(name, ptr.get(), texteditor_.get_size());
			break;
		}
		waddch(win_, (char)c);
		name.push_back((char)c);
		wrefresh(win_);
	}
}

int Menu::handle_choose() {	
	clear_screen();
	int choice = 0;
	while(true) {
		std::vector<std::string> files = fsp_.get_files();
		files.push_back("exit");
		for (int i = 0; i != files.size(); ++i) {
			if (choice == i) {
				wattron(win_, A_REVERSE);
			}
			mvwprintw(win_, i + 1, 1, files[i].c_str());
			wattroff(win_, A_REVERSE);
		}
		int c = wgetch(win_);
		if (c == KEY_DOWN) {
			choice = (choice == files.size() - 1) ? choice : ++choice;
		} else if (c == KEY_UP) {
			choice = (choice == 0) ? choice : --choice;
		} else if ((char)c == '\n') {
			if (choice == files.size() - 1) {
				return 1;			
			} else {
				auto ptr = fsp_.read_file(files[choice]);
				texteditor_.set_text(ptr.get());
				break;
			}
		}
	}
	return 0;
}

void Menu::process() {
	clear_screen();
	std::vector<std::string> options{"save", "select another note", "continue enter text"};
	int choice = 0;
	while(true) {
		for (int i = 0; i != 3; ++i) {
			if (choice == i) {
				wattron(win_, A_REVERSE);
			}
			mvwprintw(win_, i+1, 1, options[i].c_str());
			wattroff(win_, A_REVERSE);
			wrefresh(win_);
		}
		int c = wgetch(win_);
		if (c == KEY_DOWN) {
			choice = (choice == 2) ? choice : ++choice;
		} else if (c == KEY_UP) {
			choice = (choice == 0) ? choice : --choice;
		} else if ((char)c == '\n') {
			if (choice == 0) {
				handle_save();
				break;
			} else if (choice == 1) {
				int code = handle_choose();
				if (code == 0) {
					break;
				} else {
					clear_screen();
				}	
			} else {
				break;
			}
		}
			
	}
	print_hello_message();
}	


