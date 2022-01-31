#include "Snake.h"
#include <SFML/Graphics.hpp>
const float CircleRad(20.0f);
Snake::Snake(sf::Vector2f Pos, int play)
{
	Segments.push_front(Pos);
	Player = play;
}

void Snake::ChangeDirection(Direction newDrection)
{
	direction = newDrection;
}




//Updates Snakes Direction and handles growth
void Snake::Update()
{
	sf::Vector2f Position = Segments.front();
	switch (direction)
	{
	case Direction::EUp:
		Position.y -= CircleRad * 2.0f;
		break;
	case Direction::EDown:
		Position.y += CircleRad * 2.0f;
		break;
	case Direction::ELeft:
		Position.x -= CircleRad * 2.0f;
		break;
	case Direction::ERight:
		Position.x += CircleRad * 2.0f;
		break;
	
	}
	// Snake Movement
	Segments.push_front(Position);
	//Growth Based on Growth interger
	if (Growth > 0)
	{
		Growth--;
	}
	else
	{
		Segments.pop_back();
	}
	
}

//Draws Snake to the screen
void Snake::Render(sf::RenderWindow& window)
{
	sf::CircleShape circle(CircleRad);
	if (Player == 1)
	{
		circle.setFillColor(sf::Color::Blue);
	}
	else if (Player == 2)
	{
		circle.setFillColor(sf::Color::Magenta);
	}
	for (sf::Vector2f pos : Segments)
	{
		circle.setPosition(pos);
		window.draw(circle);
	}
	
}


