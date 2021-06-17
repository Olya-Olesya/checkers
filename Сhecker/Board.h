#include <SFML/Graphics.hpp>
#include "Square_attribute.h"
#include <iostream>
using namespace std;


/**Класс, описывающий методы создания и изменения непосредственно шахматной доски*/
class Board {
private:
	Square_attribute all_squares[8][8];
public:
	Board(){}
	Square_attribute &get_all_squares(int _i, int _j) {
		return this->all_squares[_i][_j];
	}

	/**Функция рисует шахматную доску*/
	void draw_board(sf::RenderWindow &_window) {
		/**Рисует 64 квадрата, из которых состоит шахматная доска*/
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(i * 90.0, j * 90.0);
				if ((i + j) % 2 == 1) all_squares[i - 1][j - 1].set_color(sf::Color(102, 102, 153));
				else all_squares[i - 1][j - 1].set_color(sf::Color(255, 255, 255));
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}

		/**Выделяет серым цветом квадраты, куда шашка может сходить*/
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_backlight() == 1) {
					sf::RectangleShape square_light(sf::Vector2f(90, 90));
					square_light.setPosition(i * 90, j * 90);
					all_squares[i - 1][j - 1].set_color(sf::Color(125, 127, 125));
				}
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}
		}

		/**Пишет координаты клеток шахматной доски*/
		sf::Font font;
		font.loadFromFile("Font//20832.ttf");
		sf::Text *sym[16];
		for (int i = 0; i < 16; i++) {
		sym[i] = new sf::Text("", font, 50);

		}
		sym[0]->setString(L"1");
		sym[1]->setString(L"2");
		sym[2]->setString(L"3");
		sym[3]->setString(L"4");
		sym[4]->setString(L"5");
		sym[5]->setString(L"6");
		sym[6]->setString(L"7");
		sym[7]->setString(L"8");
		sym[8]->setString(L"А");
		sym[9]->setString(L"B");
		sym[10]->setString(L"C");
		sym[11]->setString(L"D");
		sym[12]->setString(L"E");
		sym[13]->setString(L"F");
		sym[14]->setString(L"G");
		sym[15]->setString(L"H");

		for (int i = 0; i < 8; i++) {
			sym[i]->setFillColor(sf::Color::Black);
			sym[i]->setPosition(45, i * 90 + 105);
			_window.draw(*sym[i]);
			sym[i]->setPosition(830, i * 90 + 105);
			_window.draw(*sym[i]);
		}

		for (int i = 8; i < 16; i++) {
			sym[i]->setFillColor(sf::Color::Black);
			sym[i]->setPosition((i - 8) * 90 + 120, 20);
			_window.draw(*sym[i]);
			sym[i]->setPosition((i - 8) * 90 + 120, 825);
			_window.draw(*sym[i]);
		}
	}
};