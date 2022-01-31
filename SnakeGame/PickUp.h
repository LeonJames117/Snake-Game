#include <SFML/Graphics.hpp>
#include <string>
#include <array>

class PickUp
{
	
private:
	
public:
	void Render(sf::RenderWindow& window);
	bool isAlive;
	std::string PickUpType;
	sf::Vector2f Position;
	PickUp(sf::Vector2f Pos);
};
