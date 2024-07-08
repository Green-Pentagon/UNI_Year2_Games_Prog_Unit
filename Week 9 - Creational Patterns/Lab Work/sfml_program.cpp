#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    sf::Texture texture;
    texture.loadFromFile("assets/blob.png");
    Particle* prototype = new Particle();
    prototype->active = true;
    prototype->sprite.setTexture(texture);
    prototype->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    //prototype->AddComponent(new InitialPositionComponent(sf::Vector2f(400.0f, 500.0f), sf::Vector2f(450.0f, 550.0f)));
    prototype->AddComponent(new InitialVelocityComponent(sf::Vector2f(-50.0f, -500.0f), sf::Vector2f(50.0f, -300.0f)));
    prototype->AddComponent(new SpawnAtMousePosition(window));
    prototype->AddComponent(new MoveComponent(sf::Vector2f(0, 0), sf::Vector2f(0, 200)));
    prototype->AddComponent(new ScaleOverTime(sf::Vector2f(1.0f,1.0f), sf::Vector2f(0.0f,0.0f) , 3.0f));
    prototype->AddComponent(new ColourOverTime(sf::Color(255, 0, 0, 255), sf::Color(255, 255, 0, 255), 2.0f));
    prototype->AddComponent(new AlphaOverTimeComponent(1.0f, 0.0f, 2.0f));
    prototype->AddComponent(new ScaleToVelocityComponent(100));
    prototype->AddComponent(new KillComponent(4.5f));
    ParticleSystem particleSystem(prototype, 50.0f);
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
        particleSystem.Update(1.0f / 60.0f);
        particleSystem.Draw(window);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}