#include "Particle.h"
#include <iostream>
#include <random>


using namespace std;
class ParticleSystem
{
    sf::Vector2f gravity;
    sf::Texture texture;
    constexpr const static int numParticles = 1000;
    unique_ptr<Particle> particles[numParticles];

    unique_ptr<Particle> Spawn()
    {
        sf::Vector2f velocity;
        sf::Vector2f position;

        random_device rd;
        uniform_real_distribution<float> dist(0.0f, 1.0f);
        position.x = 512.0f;
        position.y = 700.0f;
        velocity.x = -40.0f + 80.0f * dist(rd);
        velocity.y = -100.0 - 400.0f * dist(rd);
        return make_unique<Particle>(position, velocity, *this);
    }

public:
    ParticleSystem(sf::Vector2f gravity, const string& textureFile) : gravity(gravity)
    {
        if (!texture.loadFromFile(textureFile))
            cerr << "Failed to load texture " << textureFile << endl;
        for (int i = 0; i < numParticles; i++) {
            particles[i] = Spawn();
            
        }
    }
    void Update(float deltaTime)
    {
        for (int i = 0; i < numParticles; i++)
        {
            particles[i]->Update(deltaTime);
            if (particles[i]->GetPosition().y > 700.0f)
            {
                //delete particles[i]; //garbage collection
                particles[i] = Spawn();
            }

        }
    }
    void Draw(sf::RenderWindow& window)
    {
        //sf::Sprite sprite(texture);
        //sprite.setScale(sf::Vector2f(0.1f, 0.1f));
        //sprite.setColor(sf::Color(255, 64, 64));
        for (int i = 0; i < numParticles; i++)
        {
            particles[i]->Draw(window, texture);
        }
    }
    sf::Vector2f GetGravity() { return gravity; }
};