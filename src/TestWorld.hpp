#ifndef TESTWORLD_HPP
#define TESTWORLD_HPP
#include "GameWorld.hpp"
#include "Player.hpp"
class TestWorld : public GameWorld
{
private:
	Player *player;
	
	sf::Texture *txtr_player;
public:
	TestWorld();
	~TestWorld();
	void input(sf::Event &event);
	void draw(sf::RenderWindow &rwin, float interp);
	void update(float dt);
};
#endif