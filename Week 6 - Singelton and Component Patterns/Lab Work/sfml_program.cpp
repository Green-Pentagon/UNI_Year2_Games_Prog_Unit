//REFACTOR ME TO HAVE ALL THE ITEMS FROM SOLITARE IN THE CLASS





#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Solitare.h"
#include <iostream>



int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Program");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
   
    
    /*sf::Sprite spr;
    spr.setPosition(sf::Vector2f(100, 100));
    spr.setScale(sf::Vector2f(4, 4));*/

    sf::Sprite spr;
    float cardScale = 2; //make the card size a variable, so you can tweak it
    spr.setScale(sf::Vector2f(cardScale, cardScale));

    int ySeparation = 10 * cardScale;
    int xSeparation = 40 * cardScale;


    Solitare Game;

    // Start the game loop
    while (window.isOpen())
    {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        //TextureManager::Instance().SetSprite("2c", spr);
        //window.draw(spr);

        int xStart = 40 * cardScale;
        int yStart = 40 * cardScale;
        int currentCard = 0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7 - i; j++)
            {
                sf::Vector2f pos = sf::Vector2f(xStart + j * xSeparation, yStart);
                spr.setPosition(pos);
                if (j == 0) {
                    TextureManager::Instance().SetSprite(Game.GetDeck()[currentCard], spr);
                }
                else {
                    TextureManager::Instance().SetSprite("back", spr);
                }
                currentCard++;
                
                window.draw(spr);
            }
            yStart += ySeparation;
            xStart += xSeparation;
        }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}