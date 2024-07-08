#pragma once
#include <SFML/Graphics.hpp>
class ParticleSystem;

class Particle
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    ParticleSystem& parent;
    //int dummyMemory[1000]; //debug chunk of dummy memory


public:
    Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, ParticleSystem& parent) :
        position(position), velocity(velocity), parent(parent) {}
    void Update(float deltaTime);
    sf::Vector2f GetPosition() { return position; }
    sf::Vector2f GetVelocity() { return velocity; }

    void Draw(sf::RenderWindow& window, sf::Texture& texture)
    {
        sf::Sprite sprite(texture);
        sprite.setScale(sf::Vector2f(0.1f, 0.1f));
        sprite.setColor(sf::Color(255, (position.x / window.getSize().x) * 255, (position.y / window.getSize().y) * 255));

        sprite.setPosition(GetPosition());
        window.draw(sprite, sf::BlendAdd);

    }
};

