#include "Game.h"
#include "Snake.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>
//Game Settings
int ScreenX = 800;
int ScreenY = 600;

//Pre-Functions Varable set up
bool GridSetup = false;
std::string PossiblePickUPTypes[3]{"Small", "Medium", "Large"};

//Functions

//Creates 2 arrays (one for x, one for y) that splits the two axis into 40 wide sections 
//based on the screen x and y
void Game::SetupGrid()
{
    if (GridSetup == false)
    {
        int XValue = 0;
        int YValue = 0;
        while (XValue <= ScreenX)
        {
            XValue = XValue + 40;
            XGrid.push_back(XValue);
            std::cout << XValue << " Added to XGrid" << std::endl;
        }
        while (YValue <= ScreenY)
        {
            YValue = YValue + 40;
            YGrid.push_back(YValue);
            std::cout << YValue << " Added to YGrid" << std::endl;
        }
        std::cout << "Grid Setup Complete" << std::endl;
        GridSetup = true;
    }
    
}

//Checks if the snake has colided with itself, the other snake, or a pick up, 
//and triggers the appropirate reponse
void Game::CheckSnakeColisons()
{
    for (Snake* snake : SnakesVect)
    {
        bool first = true;
        //Snake self colison check for game over condition
        for (sf::Vector2f Segment : snake->Segments)
        {
            if (first == true)
            {
                first = false;
            }
            else if (first == false)
            {
               if (snake->Player == 1)
               {
                    if (Segment == snake->Segments.front())
                    {
                        Winner = 2;
                        WinDecided = true;
                        WinReason = "Player 1 Hit themself";
                        GameOver = true;
                        break;
                    }   
               }
               
               else if (snake->Player == 2);
               {
                   if (Segment == snake->Segments.front()) 
                   {
                       Winner = 1;
                       WinDecided = true;
                       WinReason = "Player 2 Hit themself";
                       GameOver = true;
                       break;
                   }
               }  
            }
        }
        //Checks if the players have hit eachother's tails
        if (snake->Player == 1)
        {
            for (sf::Vector2f Segment : SnakesVect[1]->Segments)
            {
                if (Segment == snake->Segments.front()) 
                {
                    Winner = 2;
                    WinReason = "Player 1 Colided with Player 2's tail";
                    GameOver = true;
                    break;
                }
            }
            //checks for a head on colison
            if (snake->Segments.front() == SnakesVect[1]->Segments.front())
            {
                WinReason = "Points Victory After Head on Colision";
                GameOver = true;
                break;
            }
        }
        else if (snake->Player == 2)
        {
            for (sf::Vector2f Segment : SnakesVect[0]->Segments)
            {
               if (Segment == snake->Segments.front())
               {
                    Winner = 1;
                    WinReason = "Player 2 Colided with Player 1's tail";
                    GameOver = true;
                    break;
               }
            }
            if (snake->Segments.front() == SnakesVect[0]->Segments.front())
            {
                WinReason = "Points Victory After Head on Colision";
                GameOver = true;
                break;
            }
        }
        
        //Checks if the snake has hit the walls on the edge of the screen
        if (snake->Segments.front().x >= 800 or snake->Segments.front().x <= 0)
        {
            GameOver = true;
            if (snake->Player == 1)
            {
                Winner = 2;
                WinDecided = true;
                WinReason = "Player 1 Hit the wall";
                break;
            }
            else if (snake->Player == 2);
            {
                Winner = 1;
                WinDecided = true;
                WinReason = "Player 2 Hit the wall";
                break;
            }
        }

        if (snake->Segments.front().y >= 600 or snake->Segments.front().y <= 0)
        {
            GameOver = true;
            if (snake->Player == 1)
            {
                Winner = 2;
                WinDecided = true;
                WinReason = "Player 1 Hit the wall";
                break;
            }
            else if (snake->Player == 2);
            {
                Winner = 1;
                WinDecided = true;
                WinReason = "Player 2 Hit the wall";
                break;
            }
        }

        //Pickup colsion check (adds points and growth value based on pickup type, sets alive to false, 
        //and assigns new random location for next spawn)
        for (PickUp* PickUp : PickUpsArray)
        {
            if (PickUp->Position == snake->Segments.front())
            {
                if (PickUp->PickUpType == "Small")
                {
                    snake->Score = snake->Score + 5;
                    std::cout << "Picked up Small Pickup for 5 points!" << std::endl;
                    std::cout << "Total Score: " << snake->Score << std::endl;
                    snake->Growth++;
                }
                else if (PickUp->PickUpType == "Medium")
                {
                    snake->Score = snake->Score + 10;
                    std::cout << "Picked up Medium Pickup for 10 points!" << std::endl;
                    std::cout << "Total Score: " << snake->Score << std::endl;
                    snake->Growth = snake->Growth + 2;
                }
                else if (PickUp->PickUpType == "Large")
                {
                    snake->Score = snake->Score + 20;
                    std::cout << "Picked up Large Pickup for 20 points!" << std::endl;
                    std::cout << "Total Score: " << snake->Score << std::endl;
                    snake->Growth = snake->Growth + 5;
                }
                PickUp->isAlive = false;
                PickUp->Position.x = (RandomX());
                PickUp->Position.y = (RandomY());
                PickUp->PickUpType = PossiblePickUPTypes[rand() % 3 + 0];
                PickUpsSpawned--;

            }
        }
    }
      
}

//Shows the end screen in the event of a game over
void Game::ShowEndScreen(sf::RenderWindow& window)
{
    sf::Font GameFont;
    GameFont.loadFromFile("Bahnschrift.ttf");
    if (!GameFont.loadFromFile("Bahnschrift.ttf"))
    {
        std::cout << "Could not Load Font" << std::endl;
    }
    //Setup and draw Game Over text to the screen
    sf::Text GameOverTxt;
    GameOverTxt.setFont(GameFont);
    GameOverTxt.setString("GAME OVER");
    GameOverTxt.setCharacterSize(40);
    GameOverTxt.setFillColor(sf::Color::White);
    GameOverTxt.setPosition(300, 200);
    window.draw(GameOverTxt);
    //Setup and draw Final Scores to the screen
    sf::Text GameOverP1PointsTxt;
    GameOverP1PointsTxt.setFont(GameFont);
    std::string P1StrPoints = std::to_string(SnakesVect[0]->Score);
    GameOverP1PointsTxt.setString("Player 1: " + P1StrPoints);
    GameOverP1PointsTxt.setCharacterSize(40);
    GameOverP1PointsTxt.setFillColor(sf::Color::White);
    GameOverP1PointsTxt.setPosition(310, 250);
    window.draw(GameOverP1PointsTxt);

    sf::Text GameOverP2PointsTxt;
    GameOverP2PointsTxt.setFont(GameFont);
    std::string P2StrPoints = std::to_string(SnakesVect[1]->Score);
    GameOverP2PointsTxt.setString("Player 2: " + P2StrPoints);
    GameOverP2PointsTxt.setCharacterSize(40);
    GameOverP2PointsTxt.setFillColor(sf::Color::White);
    GameOverP2PointsTxt.setPosition(310, 300);
    window.draw(GameOverP2PointsTxt);
    
    //Decide Points Winner
    sf::Text WinnerTxt;
    WinnerTxt.setFont(GameFont);
    if (WinDecided == false)
    {
        if (SnakesVect[0]->Score > SnakesVect[1]->Score)
        {
            Winner = 1;
        }

        else if (SnakesVect[1]->Score > SnakesVect[0]->Score)
        {
            Winner = 2;
        }
    }
    
    //displays the winner
    WinnerTxt.setCharacterSize(40);
    WinnerTxt.setFillColor(sf::Color::Green);
    WinnerTxt.setPosition(300, 350);
    std::string StrWinner = std::to_string(Winner);
    WinnerTxt.setString("Player " + StrWinner + " Wins!");
    window.draw(WinnerTxt);

    //Displays the reason for the game ending
    sf::Text WinReasonTxt;
    WinReasonTxt.setString(WinReason);
    WinReasonTxt.setFont(GameFont);
    WinReasonTxt.setCharacterSize(25);
    WinReasonTxt.setPosition(270, 400);
    window.draw(WinReasonTxt);

}

//Returns a random value from the x array from GridSetup()
int Game::RandomX()
{
    int x;
    if (XGrid.size() == 0)
    {
        std::cout << "Error XGrid size is 0" << std::endl;
        x = 40;
    }
    else
    {
        x = XGrid[rand() % XGrid.size()];
    }
    return x;
}

//Returns a random value from the y array from GridSetup()
int Game::RandomY()
{
    int y;
    if (YGrid.size() == 0)
    {
        std::cout << "Error YGrid size is 0" << std::endl;
        y = 40;
    }
    else
    {
        y = YGrid[rand() % YGrid.size()];
    }
    return y;
}

//Game Start Function
void Game::Run()
{
    srand(time(NULL));
    sf::Clock clock;
    sf::Clock Timer;
    sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "C++ Snake ICA : A0053718");
    
    SetupGrid();

    //Sets default string and paramaters for the in game points counters and timer
    sf::Font GameFont;
    GameFont.loadFromFile("Bahnschrift.ttf");
    if (!GameFont.loadFromFile("Bahnschrift.ttf"))
    {
        std::cout << "Could not Load Font" << std::endl;
    }
    sf::Text Player1PointsTxt;
    Player1PointsTxt.setFont(GameFont);
    Player1PointsTxt.setCharacterSize(30);
    Player1PointsTxt.setFillColor(sf::Color::White);
    Player1PointsTxt.setPosition(0, 0);
    
    sf::Text Player2PointsTxt;
    Player2PointsTxt.setFont(GameFont);
    Player2PointsTxt.setCharacterSize(30);
    Player2PointsTxt.setFillColor(sf::Color::White);
    Player2PointsTxt.setPosition(0, 30);
    
    sf::Text TimerTxt;
    TimerTxt.setFont(GameFont);
    TimerTxt.setCharacterSize(30);
    TimerTxt.setFillColor(sf::Color::White);
    TimerTxt.setPosition(550, 0);

    //Adds the player snakes to the snakes vector
    SnakesVect.push_back(new Snake(sf::Vector2f(200,320), 1));
    SnakesVect.push_back(new Snake(sf::Vector2f(440, 320), 2));

    //Generates 5 PickUps with random locations and types (determining colour and points value)
    for (int i = 0; i <= 4; i++)
    {
        PickUpsArray[i] = new PickUp (sf::Vector2f(RandomX(), RandomY()));
        PickUpsArray[i]->PickUpType = PossiblePickUPTypes[rand() %3 + 0];
    }
    

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        //Game over check, if false game loop runs as normal, if not displays end screen
        if (GameOver == false)
        {
            //Checks for WASD input for player 1 direction change
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                SnakesVect[0]->ChangeDirection(Direction::EUp);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                SnakesVect[0]->ChangeDirection(Direction::ELeft);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                SnakesVect[0]->ChangeDirection(Direction::EDown);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                SnakesVect[0]->ChangeDirection(Direction::ERight);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                SnakesVect[1]->ChangeDirection(Direction::EUp);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                SnakesVect[1]->ChangeDirection(Direction::ELeft);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                SnakesVect[1]->ChangeDirection(Direction::EDown);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                SnakesVect[1]->ChangeDirection(Direction::ERight);
            }

            //Updates all snakes in the snakes vector
            for (Snake* snake : SnakesVect)
            {
                snake->Update();
                std::cout << "Growth: " << snake->Growth << std::endl;
            }


            // We must clear the window each time around the loop
            window.clear();

            CheckSnakeColisons();

            // Randomly decides if a pick up will try to spawn
            int DoesPickUpSpawn = rand() % 3 + 1;
            if (DoesPickUpSpawn == 3)
                for (PickUp* PickUp : PickUpsArray)
                {
                    if (PickUp->isAlive == false and PickUpsSpawned < 5)
                    {
                        //Checks that the pickup will not spawn inside a segment of the snake
                        //if it will new random values are assgined until it won't
                        for (Snake* snake : SnakesVect)
                        {
                            for (sf::Vector2f Segment : snake->Segments)
                            {
                                while (PickUp->Position == Segment)
                                {
                                    PickUp->Position.x = RandomX();
                                    PickUp->Position.y = RandomY();
                                }
                            }
                        }
                        
                        //Sets the pickup's status to alive and incriments the PickUpsSpawned counter
                        PickUp->isAlive = true;
                        PickUpsSpawned++;
                        break;
                    }
                    //Error handling/detection for pickup spawning error
                    if (PickUp->isAlive == true)
                    {

                    }
                    else
                    {
                         
                        std::cout << "Spawning error: " << PickUpsSpawned << " " << std::endl;
                    }
                }

            //Draws all currently alive pickups to the window
            for (PickUp* PickUp : PickUpsArray)
            {
                if (PickUp->isAlive == true)
                {
                    PickUp->Render(window);
                }
            }

            //Draws all snakes to the window
            for (Snake* snake : SnakesVect)
            {
                snake->Render(window);
                std::cout << "Snake is at Position " << snake->Segments.front().x << ", " << snake->Segments.front().y << std::endl;
            }

            //Updates and draws the points counters and timer to the window
            std::string P1StrPoints = std::to_string(SnakesVect[0]->Score);
            Player1PointsTxt.setString("P1 Points: " + P1StrPoints);
            window.draw(Player1PointsTxt);
            
            std::string P2StrPoints = std::to_string(SnakesVect[1]->Score);
            Player2PointsTxt.setString("P2 Points: " + P2StrPoints);
            window.draw(Player2PointsTxt);

            int Countdown = round(90 - Timer.getElapsedTime().asSeconds());
            std::string StrTimer = std::to_string(Countdown);
            TimerTxt.setString("Time: " + StrTimer);
            window.draw(TimerTxt);
            // Get the window to display its contents
            window.display();

            while (clock.getElapsedTime().asMilliseconds() < 500);
            clock.restart();
           
            // Checks game timer to see if time is up
            if (Timer.getElapsedTime().asSeconds() >= 90)
            {
                WinReason = "Time Up! Points Victory";
                GameOver = true;
            }
            else
            {
                std::cout << "Timer: " << Timer.getElapsedTime().asSeconds() << std::endl;
            }

        }
        //If the Game is over clears the window and displays the Game Over screen
        else if (GameOver == true)
        {
            window.clear();
            ShowEndScreen(window);
            window.display();
        }
    }

    //Deletes all pointers from containers before closing the game
    for (Snake* snake : SnakesVect)
    {
        delete snake;
    }

    for (PickUp* Pickup : PickUpsArray)
    {
        delete Pickup;
    }
    std::cout << "SnakeGame: Finished" << std::endl;



}

