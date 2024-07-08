#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    vector<Enemy*> enemies;

    vector<sf::Vector2f> patrol0 = { sf::Vector2f(100,100), sf::Vector2f(600, 100), sf::Vector2f(600, 300) };
    vector<sf::Vector2f> patrol1 = { sf::Vector2f(100,500), sf::Vector2f(300, 500) };

    enemies.push_back(new Enemy(patrol0, 100.0f, 50.0f, 2.0f));
    enemies.push_back(new Enemy(patrol1, 150.0f, 50.0f, 1.0f));

    sf::Vector2f playerPos = sf::Vector2f(400, 300);
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

        playerPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        // update enemies
        for (auto e : enemies)
            e->Update(1.0f / 60.0f, playerPos);
        // draw enemies
        for (auto e : enemies)
            e->Draw(window);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}