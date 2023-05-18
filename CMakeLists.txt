cmake_minimum_required(VERSION 3.8)

project(severstal_notes)

include_directories("include")

add_executable(app src/app.cpp src/fsprocessor.cpp src/texteditor.cpp src/menu.cpp)

target_link_libraries(app ncurses)

file(MAKE_DIRECTORY build/data)
