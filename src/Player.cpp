#include "Player.hpp"

Player::Player(sf::Texture &txtr)
{
	self.setTexture(txtr);
	
	right = false;
	left = false;
	up = false;
	down = false;
	
	pos = sf::Vector2f(400, 350);	
	xs = 0.0f;
	fric = 1.1f;
	
	self.setPosition(pos);
	
	self.setOrigin(self.getTextureRect().width / 2, self.getTextureRect().height);
}

void Player::input(sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Right:
					right = true;
				break;
				case sf::Keyboard::Left:
					left = true;
				break;
				case sf::Keyboard::Up:
					up = true;
				break;
				case sf::Keyboard::Down:
					down = true;
				break;
			}
		break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
				case sf::Keyboard::Right:
					right = false;
				break;
				case sf::Keyboard::Left:
					left = false;
				break;
				case sf::Keyboard::Up:
					up = false;
				break;
				case sf::Keyboard::Down:
					down = false;
				break;
			}
		break;
	}
}

void Player::draw(sf::RenderWindow &rwin, float interp)
{
	sf::Vector2f posInterp = pos;
	
	if (pos.x != lastPos.x)
		posInterp.x += interp;
	if (pos.y != lastPos.y)
		posInterp.y += interp;
	
	self.setPosition(posInterp);
	rwin.draw(self);
	
	lastPos = pos;
}

void Player::update(float dt)
{	
	if (right == true && left == false)
	{
		xs += 0.5f;
	}
	
	if (right == false && left == true)
	{
		xs -= 0.5f;
	}
	
	if (up == true && down == false)
	{
		ys -= 0.5f;
	}
	
	if (up == false && down == true)
	{
		ys += 0.5f;
	}
	
	pos.x += xs;
	pos.y += ys;
	
	xs /= fric;
	ys /= fric;
}