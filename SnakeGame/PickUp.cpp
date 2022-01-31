#include "PickUp.h"
#include <iostream>
const float CircleRad(20.0f);

PickUp::PickUp(sf::Vector2f Pos) 
{
	Position = Pos;
	isAlive = false;
} 

//Draws the pickup to the screen, setting it's fill colour based on it's type
void PickUp::Render(sf::RenderWindow& window)
{
	sf::CircleShape circle(CircleRad);
	circle.setPosition(Position);
	if (PickUpType == "Small")
	{
		circle.setFillColor(sf::Color::Green);
	}
	else if (PickUpType == "Medium")
	{
		circle.setFillColor(sf::Color::Yellow);
	}
	else if (PickUpType == "Large")
	{
		circle.setFillColor(sf::Color::Red);
	}
	else
	{
		circle.setFillColor(sf::Color::White);
		std::cout << "Invalid Pickup Type" << std::endl;
	}
	

	window.draw(circle);
}
