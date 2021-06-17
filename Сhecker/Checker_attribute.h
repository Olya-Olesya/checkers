#include <SFML/Graphics.hpp> 


/**Êëàññ, îïèñûâàþùèé àòðèáóòû øàøêè: öâåò, ïîëîæåíèå, ñòàòóñ; à òàêæå ìåòîäû âçÿòèÿ øàøêè è îòìåíà äàííîãî äåéñòâèÿ*/
class Checker_attribute {
private:
	sf::CircleShape checker = sf::CircleShape(38);

	bool checker_color; /**Ïåðåìåííàÿ, îáîçíà÷àþùàÿ öâåò øàøêè: 0 - áåëàÿ, 1 - ÷åðíàÿ*/
	bool damka = 0; /**Ïåðåìåííàÿ, îáîçíà÷àþùàÿ ñòàòóñ øàøêè: 0 - îáû÷íàÿ øàøêà, 1 - äàìêà*/
	bool select = 0; /**Ïåðåìåííàÿ, îáîçíà÷àþùàÿ âûáðàíà øàøêà èëè íåò (0 - íå âûáðàíà, 1 - âûáðàíà)*/

	sf::Texture texture;
	sf::Sprite sprite;

public:
	sf::CircleShape &get_checker() {
		return this->checker;
	}
	sf::Vector2f get_position() {
		return this->checker.getPosition();
	}
	float get_x() {
		return (this->get_position().x - 97) / 90;
	}
	float get_y() {
		return (this->get_position().y - 97) / 90;
	}
	bool get_color() {
		return this->checker_color;
	}
	bool get_select() {
		return this->select;
	}
	bool get_damka() {
		return this->damka;
	}

	void make_damka() {
		this->damka = 1;
	}
	void set_position(float _x_position, float _y_position) {
		this->checker.setPosition(_x_position, _y_position);
	}
	void set_color(sf::Color _color) {
		this->checker.setFillColor(_color);
	}
	void select_checker() {
		this->select = 1;
	}
	void leave_checker() {
		this->select = 0;
	}


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

	/**Ôóíêöèÿ ðèñóåò èçîáðàæåíèå äàìêè íà øàøêå*/
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
		this->texture = _checker.texture;
		this->sprite = _checker.sprite;
		this->select = _checker.select;
		this->damka = _checker.damka;
		this->checker_color = _checker.checker_color;
		if (_checker.checker_color == 0) {
			this->set_color(sf::Color(166, 189, 215));
		}
		else if (_checker.checker_color == 1) {
			this->set_color(sf::Color(0, 33, 55));
		}
		this->set_position(_checker.get_position().x, _checker.get_position().y);
		return (*this);
	}
};
