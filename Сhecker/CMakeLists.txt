cmake_minimum_required(VERSION 3.8)	 

project(Checker)			

add_executable(main.cpp Board.h Checker.h Checkers_on_board.h Game.h Square.h)

mkdir --parents ../myapp-build
cd ../myapp-build


cmake -G "Visual Studio 2019"
