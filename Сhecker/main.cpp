#include <SFML/Graphics.hpp>
#include "Game.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

/**Основная функция, генерирует окно, начинает игру и заканчивает её*/
int main() {
	setlocale(LC_ALL, "rus");
	/// Объект класса Game, содержащий всю логику игры
	Game game;
	bool start = 1;
	/// Создание окна приложения, размером 900х900 пикселей и заголовком "Checker"
	sf::RenderWindow window(sf::VideoMode(900, 900), "Checkers");
	/// Цикл, который действует, пока открыто окно
	while (window.isOpen()) {
		/// Создается событие
		sf::Event event; 
		/// Цикл, который работает, пока есть события в очереди
		while (window.pollEvent(event)) {
			/// "Запрос закрытия" событие: мы закрываем окно
			if (event.type == sf::Event::Closed)
				window.close();
			game.make_move(window, event);
		}
		///Отчистить экран и сделать фон
		window.clear(sf::Color(175, 218, 252));
		/// Начинаем игру, рисует стартовый экран
		if (start == 1) {
			game.start_game(window, event, start);
		}
		/// Рисует доску с шашками
		game.get_checkers_on_board().draw_checkers(window);
		/// Рисует конец игры
		game.end_game(window, event);
		/// Показ экрана
		window.display();
	}

	return 0;
}
