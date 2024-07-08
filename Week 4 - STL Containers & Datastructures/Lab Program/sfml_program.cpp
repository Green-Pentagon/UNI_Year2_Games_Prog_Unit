#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "TileMap.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Program");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
   
    
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

        std::vector<std::string> tileLayerFiles = { "tiles/orthogonal-outside._Ground.csv", "tiles/orthogonal-outside._Fringe.csv" };
        TileMap tiles("tiles/buch-outdoor.png", tileLayerFiles, 24, 12);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}