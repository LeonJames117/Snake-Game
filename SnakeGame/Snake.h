#pragma once

#include <SFML/Graphics.hpp>
#include <list>



enum Direction
{
	EUp,
	EDown,
	ELeft,
	ERight
};

class Snake
{
private:
public:
	Snake(sf::Vector2f Pos, int play);
	void Update();
	void Render(sf::RenderWindow& window);
	void ChangeDirection (Direction newDrection);
	std::list <sf::Vector2f> Segments;
	int direction = Direction::EUp;
	int Growth = 0;
	int Player;
	int Score = 0;
};

