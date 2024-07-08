#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "LevelEditor.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML window");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    LevelEditor* editor = new LevelEditor(window);
    editor->LoadTileMap("assets/galletcity_tiles.png", 8);

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
        InputManager::Instance().Update();
        editor->Update();
        editor->Draw();
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}