#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "ParticleSystem.h"

int main()
{
    // Create the main window
    // default: 800x600
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Program");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
   

    ParticleSystem ParticleSys(sf::Vector2f(0,150), "assets/blob.png");

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

        ParticleSys.Update(1.0f/60.0f);
        // Clear screen
        window.clear();

        ParticleSys.Draw(window);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}