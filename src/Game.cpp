
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;

}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;
	elephant.loadFromFile(
		"Return_of_the_mole/Data/Images/Critter Crossing Customs/elephant.png");
	moose.loadFromFile(
		"../Data/Images/Critter Crossing Customs/moose.png");
	penguin.loadFromFile(
		"../Data/Images/Critter Crossing Customs/penguin.png");
	animals[0] = {elephant};
	animals[1] = { moose };
	animals[2] = { penguin };
	elephantPassport.loadFromFile(
		"../Data/Images/Critter Crossing Customs/elephant passport.png");
	moosePassport.loadFromFile(
		"../Data/Images/Critter Crossing Customs/moose passport.png");
	penguinPassport.loadFromFile(
		"../Data/Images/Critter Crossing Customs/penguin passport.png");
	passports[0] = { elephantPassport };
	passports[1] = { moosePassport };
	passports[2] = { penguinPassport };
	newAnimal();
  return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
}

void Game::render()
{
	window.draw(*character);
	window.draw(*passport);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

}


void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;

	}
	else {
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

		passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

}

void Game::dragSprite(sf::Sprite* sprite) {
	if (sprite != nullptr) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}

void Game::mouseButtonPressed(sf::Event event) {
	if (event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf))
		{
			drag_offset = sf::Vector2f(clickf.x - passport->getPosition().x, clickf.y - passport->getPosition().y);
			dragged = passport;
		}
	}

}
void Game::mouseButtonReleased(sf::Event event) {
	if (event.mouseButton.button == sf::Mouse::Left) {
		dragged = nullptr;
		drag_offset = sf::Vector2f(0, 0);
	}
}