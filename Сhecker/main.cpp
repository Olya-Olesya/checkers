#include <SFML/Graphics.hpp>
#include "Game.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

/**Основная функция, генерирует окно, начинает игру и заканчивает её*/
int main() {
	setlocale(LC_ALL, "rus");
	Game game;
	bool start = 1;
	sf::RenderWindow window(sf::VideoMode(900, 900), "Checkers");
	
	while (window.isOpen()) {
		sf::Event event; 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			game.make_move(window, event);
		}
		window.clear(sf::Color(175, 218, 252));
		if (start == 1) {
			game.start_game(window, event, start);
		}
		game.get_checkers_on_board().draw_checkers(window);
		game.end_game(window, event);	
		window.display();
	}

	return 0;
}
