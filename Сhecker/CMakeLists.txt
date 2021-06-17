cmake_minimum_required(VERSION 3.8)	 

project(Checker)			

add_executable(Checker main.cpp Board.h Checker_attribute.h Checkers_placement.h Game.h Square_attribute.h)


set(SFML_STATIC_LIBRARIES TRUE)
find_package (SFML COMPONENTS graphics windows system)
target_link_libraries(Checker sfml-graphics sfml-window)


