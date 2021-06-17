#include <SFML/Graphics.hpp>
#include <vector>
#include "Checker_attribute.h"
#include "Board.h"

/**Класс, описывающий методы для расставления шашек на поле*/
class Checkers_placement {
private:
	vector <Checker_attribute> checkers;
	Board board;
public:
	Board &get_board() {
		return this->board;
	}

	Checker_attribute &get_checker(int _i) {
		return this->checkers[_i];
	}

	int get_size() {
		return this->checkers.size();
	}

	/**Функция расставляет шашки на доске*/
	void start_game() {
		for (int i = 0; i < 24; i++) {

			/**Расставляются черные шашки в три ряда*/
			if (i < 4) {
				checkers.push_back(Checker_attribute((float)i * 180 + 187, (float)97, 1));
				board.get_all_squares(i * 2 + 1, 0).square_employment(1);
			}
			else if (i >= 4 && i < 8) {
				checkers.push_back(Checker_attribute((float)(i - 4) * 180 + 97, (float)187, 1));
				board.get_all_squares((i - 4) * 2, 1).square_employment(1);
			}
			else if (i >= 8 && i < 12) {
				checkers.push_back(Checker_attribute((float)(i - 8) * 180 + 187, (float)277, 1));
				board.get_all_squares((i - 8) * 2 + 1, 2).square_employment(1);
			}

		    /**Расставляются белые шашки в три ряда*/
			else if (i >= 12 && i < 16) {
				checkers.push_back(Checker_attribute((float)(i - 12) * 180 + 97, (float)547, 0));
				board.get_all_squares((i - 12) * 2, 5).square_employment(0);
			}
			else if (i >= 16 && i < 20) {
				checkers.push_back(Checker_attribute((float)(i - 16) * 180 + 187, (float)637, 0));
				board.get_all_squares((i - 16) * 2 + 1, 6).square_employment(0);
			}
			else if (i >= 20 && i < 24) {
				checkers.push_back(Checker_attribute((float)(i - 20) * 180 + 97, (float)727, 0));
				board.get_all_squares((i - 20) * 2, 7).square_employment(0);
			}
		}
	}

	/**Удаление шашки с поля*/
	void delete_checker() {
		checkers.pop_back();
	}

	Checkers_placement() {
		start_game();
	};

	/**Запуск функций рисования доски и шашек*/
	void draw_checkers(sf::RenderWindow &_window) {
		board.draw_board(_window);
		for (int i = 0; i < checkers.size(); i++) {
			checkers[i].draw_checker(_window);
		}
	}
	/**Снятие выделения с клетки*/
	void delete_backlight() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				this->board.get_all_squares(i, j).off_backlight();
			}
		}
	}
};