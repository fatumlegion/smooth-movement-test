#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
class Player
{
private:
	float xs, ys, fric, currentRotation, targetRotation;
	sf::Vector2f pos, lastPos;
	bool right, left, up, down;

	sf::Sprite self;
public:
	Player(sf::Texture &txtr);
	~Player() { }
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif