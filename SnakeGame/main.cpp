/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>
#include "Game.h"
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>

int main()
{
    //Creates a new game object and runs it
    Game SnakeGame;
    SnakeGame.Run();
   
    std::cout << ("Code Ended");
}
