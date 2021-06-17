cmake_minimum_required(VERSION 3.8)	 

project(Checker)			

add_executable(Checker main.cpp Board.h Checker.h Checkers_on_board.h Game.h Square.h)


set(SFML_STATIC_LIBRARIES TRUE)
find package (SFML COMPONENTS graphics windows system)
target_link_libraries(Checker sfml-graphics sfml-window)

mkdir --parents ../myapp-build
cd ../myapp-build

cmake -G "Visual Studio 2019"
