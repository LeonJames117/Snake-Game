#pragma once
#include <vector>
#include "Snake.h"
#include "PickUp.h"
#include <array>
class Game
{
private:
	std::vector <Snake*> SnakesVect;
	PickUp* PickUpsArray[5];
	std::vector <int> XGrid;
	std::vector <int> YGrid;
	int PickUpsSpawned = 0;
	int Winner;
	bool GameOver = false;
	bool WinDecided = false;
	std::string WinReason;
	int RandomX();
	int RandomY();
	void SetupGrid();
	void CheckSnakeColisons();
	void ShowEndScreen(sf::RenderWindow& window);
public:
	void Run();
	
	
};



