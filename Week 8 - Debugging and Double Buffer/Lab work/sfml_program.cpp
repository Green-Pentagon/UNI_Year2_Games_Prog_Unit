#include <SFML/Graphics.hpp>
#include "Cave.h"
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Program");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    Cave cave = Cave(800,600);
    
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

        cave.Draw(window,12);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}