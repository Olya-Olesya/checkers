#include <SFML/Graphics.hpp>
#include "Checkers_placement.h"

///Процесс игры
/** ход обычной шакшки
* поедание шашки обычной шашкой
* шашка становится дамкой
* ход дамки
* поедание шашки дамкой

*начало игры
*конец игры
*/
class Game {
private:
	int how_many = 0; ///< количество шашек
	bool who_can_move = 0; ///< цвет шашки, которая ходит : 0 - ходит белая, 1 - ходит черная
	bool select_is_made = 0; ///< выбрана ли фигура: 0 - фигура не выбрана, 1 - фигура выбрана
	int choise_chacker; ///< номер выбранной для хода шашки
	float x; ///< номер клетки, в которой находится шашка по оси x
	float y; ///< номер клетки в которой шашка по оси у
	sf::Vector2i mause_position; ///< позиция мыши
	Checkers_placement checkers_on_board;
	std::vector <int> who_must_eat; ///< массив, в котором хранятся шашки, которые могут съесть
public:
	///Шашка на поле
	Checkers_placement & get_checkers_on_board() {
		return this->checkers_on_board;
	}
	///Передает координаты мыши
	void set_mause_position(sf::RenderWindow &_window) {
		this->mause_position = sf::Mouse::getPosition(_window);
	}
	///Диапазон клика, чтобы нажать на определенную клетку
	sf::Vector2i centre_on_square() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (mause_position.x < i * 90 + 180 && mause_position.x < (i + 1) * 90 + 180 &&
					mause_position.y < j * 90 + 180 && mause_position.y < (j + 1) * 90 + 180) {
					return sf::Vector2i(i * 90 + 97, j * 90 + 97);
				}
			}
		}
	}
	/** 
	*\brief Выбор шашки
	*\param _event событие нажатия на кнопку мыши
	
	* нажатие на клетку
	* отмена выбора
	* дальнейший ход
	*/
	void choise_of_chacker(sf::Event _event) {
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == sf::Mouse::Left || _event.key.code == sf::Mouse::Right) {
				set_mause_position(_window);
				///Отмена выбора фигуры
				if (_event.type == sf::Event::MouseButtonPressed) {
					if (_event.key.code == sf::Mouse::Right) {
						if (checkers_on_board.get_checker(choise_chacker).get_select() == 1 && select_is_made == 1) {
							checkers_on_board.get_checker(choise_chacker).leave_checker();
							select_is_made = 0;
							checkers_on_board.delete_backlight();
							return;
						}
					}
				}
				///если фигура не отменена, можно выбрать дальнейший ход
				if (_event.key.code == sf::Mouse::Left){
					for (int i = 0; i < checkers_on_board.get_size(); i++) {
						if (this->mause_position.x >= checkers_on_board.get_checker(i).get_position().x - 12 &&
							this->mause_position.x <= checkers_on_board.get_checker(i).get_position().x + 73 &&
							this->mause_position.y >= checkers_on_board.get_checker(i).get_position().y - 12 &&
							this->mause_position.y <= checkers_on_board.get_checker(i).get_position().y + 73) {
							if (checkers_on_board.get_checker(i).get_select() == 0 && select_is_made == 0) {
								if (checkers_on_board.get_checker(i).get_color() == who_can_move) {
									choise_chacker = i;
									select_is_made = 1;
									checkers_on_board.get_checker(choise_chacker).select_checker();
									std::cout << "Take" << endl;
									x = checkers_on_board.get_checker(choise_chacker).get_x();
									y = checkers_on_board.get_checker(choise_chacker).get_y();
									if (checkers_on_board.get_checker(choise_chacker).get_damka()) {
										damka_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color());
									}
									else {
										square_for_move();
									}
									return;
								}
							}
						}
					}
				}
			}
		}
	}
	
	/**
	*\brief Ход обычной шашки
	*\param _event событие нажатия на кнопку мыши
	
	* обычный ход
	* шашка доходит до края доски и становится дамкой
	* изменение координат
	* шашка перестает быть выбранной
	*снятие выделений с клеток
	*/
	void change_position(sf::Event _event) {
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == sf::Mouse::Left) {
				if (checkers_on_board.get_checker(choise_chacker).get_select() == 1 && select_is_made == 1) {
					set_mause_position(_window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 97) / 90, (centre_on_square().y - 97) / 90).get_backlight()) {
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board.get_checker(choise_chacker).get_damka() == 1) {
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							if (damka_eat_checker()) {
								x = (centre_on_square().x - 97) / 90;
								y = (centre_on_square().y - 97) / 90;
								checkers_on_board.delete_backlight();
								if (damka_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						else {
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							make_damka();
							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 97) / 90;
								y = (centre_on_square().y - 97) / 90;
								if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						checkers_on_board.get_board().get_all_squares((centre_on_square().x - 97) / 90, (centre_on_square().y - 97) / 90).square_employment(checkers_on_board.get_checker(choise_chacker).get_color());
						who_can_move = !who_can_move;
						checkers_on_board.get_checker(choise_chacker).leave_checker();
						select_is_made = 0;
						checkers_on_board.delete_backlight();
						return;
					}
				}
			}
		}
	}
	///Перемещение шашки в окне
	void make_move(sf::RenderWindow &_window, sf::Event _event) {
		choise_of_chacker(_window, _event);
		change_position(_window, _event);
	}
	
	///Варианты хода
	/**Проверка возможности пойти на одну из нижних клеток
	*Проверка возможности пойти на одну из верхних клеток
	*Проверка возможности съесть шашку
	*/
	void square_for_move() {
		///Проверка нижних клеток
		if (checkers_on_board.get_checker(choise_chacker).get_color()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0) {
				if (not_end_of_board(x + 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_backlight();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0) {
				if (not_end_of_board(x - 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).on_backlight();
				}
			}
		}
		///Проверка верхних клеток
		else {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0) {
				if (not_end_of_board(x + 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_backlight();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0) {
				if (not_end_of_board(x - 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_backlight();
				}
			}
		}
		///возможность съесть шашку
		if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {
			checkers_on_board.delete_backlight();
			chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color());
		}
	}
	
	///Варианты съесть шашку
	/** 
	*\brief проверка вариантов возможностей съесть шашку
	*\param _сolor цвет шашки, которой игрок собирается съесть другую
	
	*проверка клеток:
	*справа внизу
	*слева внизу
	*справа вверху
	*слева вверху
	*/
	bool chance_eat_checker(bool _color) {
		bool more = 1; </// сколько шашек можно съесть
		///Проверка правой нижней клетки
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) {
					if (not_end_of_board(x + 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}
					if (not_end_of_board(x - 1, y + 1) && checkers_on_board.get_board().get_all_squares(x -1, y + 1).get_employment() == 0) {
						checkers_on_board.get_board().get_all_squares(x -1 , y + 1).on_backlight();
						more = 0;
					}
				}
			}
		}
		///Проверка левой нижней клетки
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) {
					if (not_end_of_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}
					if (not_end_of_board(x + 1, y + 1) && checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0) {
						checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_backlight();
						more = 0;
					}
				}
			}
		}
		///Проверка правой верхней клетки
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) {
					if (not_end_of_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}
					if (not_end_of_board(x - 1, y - 1) && checkers_on_board.get_board().get_all_squares(x -1 , y -1).get_employment() == 0) {
						checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_backlight();
						more = 0;
					}
				}
			}
		}
		///Проверка левой верхней клетки
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) {
					if (not_end_of_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
					if (not_end_of_board(x + 1, y - 1) && checkers_on_board.get_board().get_all_squares(x + 1, y -1).get_employment() == 0) {
						checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_backlight();
						more = 0;
					}
				}
			}
		}
		return more;
	}
	
	///Шашка ест шашку
	bool eat_checker() {
		if ((centre_on_square().x - 97) / 90 - x == 2 || (centre_on_square().x - 97) / 90 - x == -2 &&
			(centre_on_square().y - 97) / 90 - y == 2 || (centre_on_square().y - 97) / 90 - y == -2) {
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(choise_chacker).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(choise_chacker).get_y() - y) / 2) {
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++) {
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
					}
					checkers_on_board.delete_checker();
					if (i < choise_chacker) {
						choise_chacker = choise_chacker - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}
	
	///Шашка становится дамкой
	void make_damka() {
		///Белая шашка становится дамкой
		if (checkers_on_board.get_checker(choise_chacker).get_color() == 0) {
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 0) {
				checkers_on_board.get_checker(choise_chacker).make_damka();
			}
		}
		///Черная шашка становится дамкой
		if (checkers_on_board.get_checker(choise_chacker).get_color() == 1) {
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 7) {
				checkers_on_board.get_checker(choise_chacker).make_damka();
			}
		}
	}
	
	///Варианты хода дамки
	/** 
	*\brief ходы дамки
	*\param _color цвет дамки
	
	* правая нижняя диагональ
	* левая нижняя диагональ
	* правая верхняя диагональ
	*левая верхняя диагональ
	*/
	bool damka_square_for_move(bool _color) {
		checkers_on_board.delete_backlight();
		///Проверка правой нижней диагонали
		int x_damka = x; ///< абсцисса дамки
		int y_damka = y; ///< ордината дамки
		while (1) {
			if (not_end_of_board(x_damka + 1, y_damka + 1)) {
				if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka + 1).get_employment() == 1) {
					if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka + 1).get_checker_color() == _color) {
						break;
					}
					else if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka + 1).get_checker_color() != _color) {
						if (not_end_of_board(x_damka + 2, y_damka + 2)) {
							if (checkers_on_board.get_board().get_all_squares(x_damka + 2, y_damka + 2).get_employment() == 0) {
								checkers_on_board.get_board().get_all_squares(x_damka + 2, y_damka + 2).on_backlight();
								x_damka = x_damka + 2;
								y_damka = y_damka + 2;
							}
							else break;
						}
						else break;
					}
				}
				else {
					checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka + 1).on_backlight();
					x_damka = x_damka + 1;
					y_damka = y_damka + 1;
				}
			}
			else break;
		}

		///Проверка левой нижней диагонали
		x_damka = x;
		y_damka = y;
		while (1) {
			if (not_end_of_board(x_damka - 1, y_damka + 1)) {
				if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka + 1).get_employment() == 1) {
					if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka + 1).get_checker_color() == _color) {
						break;
					}
					else if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka + 1).get_checker_color() != _color) {
						if (not_end_of_board(x_damka - 2, y_damka + 2)) {
							if (checkers_on_board.get_board().get_all_squares(x_damka - 2, y_damka + 2).get_employment() == 0) {
								checkers_on_board.get_board().get_all_squares(x_damka - 2, y_damka + 2).on_backlight();
								x_damka = x_damka - 2;
								y_damka = y_damka + 2;
							}
							else break;
						}
						else break;
					}
				}
				else {
					checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka + 1).on_backlight();
					x_damka = x_damka - 1;
					y_damka = y_damka + 1;
				}
			}
			else break;
		}

		///Проверка правой верхней диагонали
		x_damka = x;
		y_damka = y;
		while (1) {
			if (not_end_of_board(x_damka + 1, y_damka - 1)) {
				if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka - 1).get_employment() == 1) {
					if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka - 1).get_checker_color() == _color) {
						break;
					}
					else if (checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka - 1).get_checker_color() != _color) {
						if (not_end_of_board(x_damka + 2, y_damka - 2)) {
							if (checkers_on_board.get_board().get_all_squares(x_damka + 2, y_damka - 2).get_employment() == 0) {
								checkers_on_board.get_board().get_all_squares(x_damka + 2, y_damka - 2).on_backlight();
								x_damka = x_damka + 2;
								y_damka = y_damka - 2;
							}
							else break;
					    }
						else break;
					}
				}
				else {
					checkers_on_board.get_board().get_all_squares(x_damka + 1, y_damka - 1).on_backlight();
					x_damka = x_damka + 1;
					y_damka = y_damka - 1;
				}
			}
			else break;
		}

		///Проверка левой верхней диагонали
		x_damka = x;
		y_damka = y;
		while (1) {
			if (not_end_of_board(x_damka - 1, y_damka - 1)) {
				if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka - 1).get_employment() == 1) {
					if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka - 1).get_checker_color() == _color) {
						break;
					}
					else if (checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka - 1).get_checker_color() != _color) {
						if (not_end_of_board(x_damka - 2, y_damka - 2)) {
							if (checkers_on_board.get_board().get_all_squares(x_damka - 2, y_damka - 2).get_employment() == 0) {
								checkers_on_board.get_board().get_all_squares(x_damka - 2, y_damka - 2).on_backlight();
								x_damka = x_damka - 2;
								y_damka = y_damka - 2;
							}
							else break;
						}
						else break;
					}
				}
				else {
					checkers_on_board.get_board().get_all_squares(x_damka - 1, y_damka - 1).on_backlight();
					x_damka = x_damka - 1;
					y_damka = y_damka - 1;
				}
			}
			else break;
		}
	
		return 0;
	}
	
	///Дамка ищет и ест шашку
	/**которая находится на правой нижней диагонали
	*которая находится на левой нижней диагонали
	*которая находится на правой верхней диагонали
	*которая находится на левой верхней диагонали
	*поедание
	*/
	bool damka_eat_checker() {
		int x_eat = 0;
		int y_eat = 0;

		///По правой нижней диагонали
		if ((centre_on_square().x - 97) / 90 - x >= 2 && (centre_on_square().y - 97) / 90 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 97) / 90 - 1 && j < (centre_on_square().y - 97) / 90 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j + 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		///По правой верхней диагонали
		if ((centre_on_square().x - 97) / 90 - x >= 2 && y - (centre_on_square().y - 97) / 90 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 97) / 90 - 1 && j >(centre_on_square().y - 97) / 90 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j - 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		///По левой нижней диагонали
		if (x - (centre_on_square().x - 97) / 90 >= 2 && (centre_on_square().y - 97) - y / 90 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 97) / 90 + 1 && j < (centre_on_square().y - 97) / 90 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j + 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		///По левой верхней диагонали
		if (x - (centre_on_square().x - 97) / 90 >= 2 && y - (centre_on_square().y - 97) / 90 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 97) / 90 + 1 && j > (centre_on_square().y - 97) / 90 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j - 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}
		/// Дамка нашла шашку и ест
		for (int f = 0; f < checkers_on_board.get_size(); f++) {
			if (checkers_on_board.get_checker(f).get_x() == x_eat && checkers_on_board.get_checker(f).get_y() == y_eat) {
				checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(f).get_x(), checkers_on_board.get_checker(f).get_y()).square_free();

				for (int c = f; c < checkers_on_board.get_size() - 1; c++) {
					checkers_on_board.get_checker(c) = checkers_on_board.get_checker(c + 1);
				}
				checkers_on_board.delete_checker();
				if (f < choise_chacker) {
					choise_chacker = choise_chacker - 1;
				}
				return 1;
			}
		}
		return 0;
	}
	
	/**
	*\brief Проверка выхода за пределы поля
	*\param _x абсцисса проверяемой координаты
	*\param _y ордината проверяемой координаты
	*/
	
	bool not_end_of_board(float _x, float _y) {
		if (_x >= 0 && _x < 8 && _y >= 0 && _y < 8) {
			return 1;
		}
		return 0;
	}
	
	/**
	\brief Стартовый экран
	\param _window окно с изображением
	\param _event событие нажатия любой кнопки
	\param _start начата игра или нет (_start==0, если начата и _start==1, если не начата)
	*/
	void start_game(sf::RenderWindow &_window, sf::Event _event, bool &_start) {
		sf::Font font;
		font.loadFromFile("Font//20832.ttf");
		sf::Text t;
		t = sf::Text("", font, 200);
		t.setPosition(190, 200);
		t.setStyle(sf::Text::Bold);
		t.setString(L"Шашки");
		t.setFillColor(sf::Color::Black);
		while (1) {
			_window.clear(sf::Color(175, 218, 252));
			_window.draw(t);
			_window.display();
			while (_window.pollEvent(_event)) {
				if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
					_start = 0;
					return;
				}
			}
		}
	}
	
	/**
	*\brief Конец игры
	*\param _window окно с изображением
	*\param _event событие закрытия окна
	*/
	bool end_game(sf::RenderWindow &_window, sf::Event _event) {
		int black = 0;
		int white = 0;
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == 0) {
				white++;
			}
			if (checkers_on_board.get_checker(i).get_color() == 1) {
				black++;
			}
		}
		///Победа черных
		if (white == 0) {
			_window.clear(sf::Color(175, 218, 252));
			sf::Font font;
			font.loadFromFile("Font//20832.ttf");
			sf::Text t = sf::Text("", font, 100);
			t.setString(L"Black win");
			t.setFillColor(sf::Color::Black);
			t.setPosition(270, 270);
			_window.draw(t);
			if (_event.type == sf::Event::Closed)
				_window.close();
			return 0;		
		}
		/// Победа белых
		if (black == 0) {
			_window.clear(sf::Color(175, 218, 252));
			sf::Font font;
			font.loadFromFile("Font//20832.ttf");
			sf::Text t = sf::Text("", font, 100);
			t.setString(L"White win");
			t.setFillColor(sf::Color::Black);
			t.setPosition(270, 270);
			_window.draw(t);
			if (_event.type == sf::Event::Closed)
				_window.close();
			return 0;			
		}
		return 1;
	}
}; 
