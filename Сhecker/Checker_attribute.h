#include <SFML/Graphics.hpp> 

///Атрибуты шашки
/**Описывает цвет, положение, статус шашки
* Описывает метод взятия шашки и отмену данного действия
*/
class Checker_attribute {
private:
	sf::CircleShape checker = sf::CircleShape(38); ///< радиус шашки 38 пикселей

	bool checker_color; ///< цвет шашки: 0 - белая, 1 - черная
	bool damka = 0; ///< статус шашки: 0 - обычная шашка, 1 - дамка
	bool select = 0; ///< показатель, выбрана шашка или нет (0 - не выбрана, 1 - выбрана)

	sf::Texture texture; ///< текстура для шашки
	sf::Sprite sprite; ///< обрезанная текстура (спрайт) для шашки

public:
	///Абсцисса положения шашки
	float get_x() {
		return (this->get_position().x - 97) / 90;
	}
	///Ордината положения шашки
	float get_y() {
		return (this->get_position().y - 97) / 90;
	}
	///Цвет шашки
	bool get_color() {
		return this->checker_color;
	}
	///Взята шашка или нет
	bool get_select() {
		return this->select;
	}
	///Статус шашки
	bool get_damka() {
		return this->damka;
	}
	
	///Создание шашки
	sf::CircleShape &get_checker() {
		return this->checker;
	}
	
	///Позиция шашки
	sf::Vector2f get_position() {
		return this->checker.getPosition();
	}
	
	///Смена статуса шашки с обычной на дамку
	void make_damka() {
		this->damka = 1;
	}
	/**
	*\brief Задает координаты шашки
	*\param _x_position абсцисса шашки
	*\param _y_position ордината шашки
	*/
	void set_position(float _x_position, float _y_position) {
		this->checker.setPosition(_x_position, _y_position);
	}
	
	/**
	*\brief Устанавливает цвет шашки
	*\param _color цвет шашки в палитре RGB
	*/
	void set_color(sf::Color _color) {
		this->checker.setFillColor(_color);
	}
	///Выбираем шашку
	void select_checker() {
		this->select = 1;
	}
	///Отменяем выбор
	void leave_checker() {
		this->select = 0;
	}

	
	
	
	///Окраска шашек
	/**Если шашка белая, то окрашивается в светло-голубой цвет
	*Если шашка черная, то окашивается в темно-синий
	
	*\brief окраска шашек
	
	* \param _x_position абсцисса шашки
	* \param _y_position ордината шашки
	* \param _color цвет шашки, если 0 - белые, если 1- черные
	*/
	Checker_attribute(float _x_position, float _y_position, bool _color) {
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(sf::Color(0, 0, 0));
		this->checker_color = _color;
		if (_color == 0) {
			this->set_color(sf::Color(166, 189, 215));
		}
		else if (_color == 1) {
			this->set_color(sf::Color(0, 33, 55));
		}
		this->set_position(_x_position, _y_position);
		this->select = 0;
	}

	///Рисует значок дамки на шашке
	/**Рисует значок черного цвета, если шашка белая
	*Рисует значок белого цвета, если шашка черная
	*/
	void draw_checker(sf::RenderWindow  &_window) {
		_window.draw(this->checker);
		if ((damka == 1) && (checker_color == 0)) {
			this->texture.loadFromFile("Images//damka_white.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
			this->sprite.setPosition(this->get_position().x + 13, this->get_position().y + 13);
		}
		if ((damka == 1) && (checker_color == 1)) {
			this->texture.loadFromFile("Images//damka_black.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
			this->sprite.setPosition(this->get_position().x + 13, this->get_position().y + 13);
		}
		_window.draw(this->sprite);
	}

	Checker_attribute operator = (Checker_attribute _checker) {
		/**
		* \brief Свойства шашки
		
		*\param _checker.texture текстура шашки
		*\param _checker.sprite обрезанная текстура шашки
		*\param _checker.select выбрана ли шашка
		*\param _checker.damka статус шашки
		*\param _checker.checker_color цвет шашки
		*/
		this->texture = _checker.texture;
		this->sprite = _checker.sprite;
		this->select = _checker.select;
		this->damka = _checker.damka;
		this->checker_color = _checker.checker_color;
		///Если шашка белая, то окрашивается в светло-голубой
		if (_checker.checker_color == 0) {
			this->set_color(sf::Color(166, 189, 215));
		}
		///Если шашка черная, то окрашивается в темно-синий
		else if (_checker.checker_color == 1) {
			this->set_color(sf::Color(0, 33, 55));
		}
		///Координаты шашки
		this->set_position(_checker.get_position().x, _checker.get_position().y);
		return (*this);
	}
};
