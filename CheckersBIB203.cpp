#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


int main() {
	setlocale(LC_ALL, "rus");
	sf::Game sf::game;

	sf::RenderWindow sf::window(sf::VideoMode(500, 500), "Checkers");
	//рисуем шашки и поле

	bool start;
	start = true;
	while (sf::window.isOpen()) {
		sf::Event sf::event; 
		while (sf::window.pollEvent(sf::event)) {
			if (sf::event.type == sf::Event::Closed) { sf::window.close(); }
			game.make_move(sf::window, sf::event);
		}
		sf::window.clear(sf::Color(185, 48, 91));
		if (start) { game.start_game(sf::window, sf::event, start); }
		//рисуем конец игры	
		sf::window.display();
	}

	return 0;
}