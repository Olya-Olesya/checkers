#include <SFML/Graphics.hpp> 


/**
* Класс, описывающий атрибуты клетки: цвет, занятость, возможность сходить на эту клетку;
* а также методы для изменения этих атрибутов (кроме цвета)
*/
class Square_attribute {

private:
	bool checker_color; ///< Переменная, обозначающая цвет шашки: 0 - белая, 1 - черная
	bool backlight = 0; ///< Переменная, обозначающая статус клетки: 0 - обычная клетка, 1 - веделенная
	bool employment = 0; ///< Переменная, обозначающая занятость клетки: 0 - клетка свободна, 1 - занята
	sf::RectangleShape square = sf::RectangleShape(sf::Vector2f(90, 90));///< Рисует клетки доски 90х90 пикселей

public:
	///Возвращает клетку
	sf::RectangleShape &get_square() {
		return this->square;
	}
	/// Возвращает статус клетки (выделенная/обычная)
	bool get_backlight() {
		return this->backlight;
	}
	/// Возвращает информацию о клетке (занята/свободна)
	bool get_employment() {
		return this->employment;
	}
	/// Возвращает цвет шашки (0 - белая, 1 - черная)
	bool get_checker_color() {
		return this->checker_color;
	}
	/// Включает выделение клетки
	void on_backlight() {
		this->backlight = 1;
	}
	/// Выключает выделение клетки
	void off_backlight() {
		this->backlight = 0;
	}
	/// Меняет статус клетки на занятую и определяет цвет шашки на ней
	void square_employment(bool _color) {
		this->employment = 1;
		this->checker_color = _color;
	}
	/// Меняет статус клетки на свободную
	void square_free() {
		this->employment = 0;
	}
	/// Устанавливает цвет клетки
	void set_color(sf::Color _color) {
		this->square.setFillColor(_color);
	}
	/// Устанавливает позицию клетки
	void set_position(float _x, float _y) {
		this->square.setPosition(_x, _y);
	}
};
