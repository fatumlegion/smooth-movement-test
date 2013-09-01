#include "TestWorld.hpp"

TestWorld::TestWorld()
{
	txtr_player = new sf::Texture();
	txtr_player->loadFromFile("res/images/player.png");
	
	player = new Player(*txtr_player);
}

TestWorld::~TestWorld()
{
	delete txtr_player;
	delete player;
}

void TestWorld::input(sf::Event &event)
{
	player->input(event);
}

void TestWorld::draw(sf::RenderWindow &rwin, float interp)
{
	player->draw(rwin, interp);
}

void TestWorld::update(float dt)
{
	player->update(dt);
}