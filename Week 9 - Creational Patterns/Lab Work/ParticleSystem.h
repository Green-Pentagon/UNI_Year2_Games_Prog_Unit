#pragma once
#include <vector>
#include <random>

#include "Particle.h"

using namespace std;

class ParticleSystem
{
	Particle* prototype;
	float spawnRate;
	vector<Particle*> particles;
	float t = 0.0f;

	mt19937 rng;
	uniform_real_distribution<float> dist;

	float Random()
	{
		return dist(rng);
	}
public:
	ParticleSystem(Particle* prototype, float spawnRate) : prototype(prototype), spawnRate(spawnRate)
	{
		rng = mt19937(random_device()());
		dist = uniform_real_distribution<float>(0.0f, 1.0f);
	}
	void Update(float dt)
	{
		// spawn any new particles
		t += dt;
		// mean number of particles expected to spawn
		float meanNumToSpawn = spawnRate * dt;
		int numToSpawn = (int)(meanNumToSpawn * 2 * Random());

		if (meanNumToSpawn < 1.0)
		{
			if (Random() < dt * spawnRate)
				numToSpawn = 1;
		}

		for (int i = 0; i < numToSpawn; i++)
		{
			Particle* newParticle = dynamic_cast<Particle*>(prototype->clone());
			newParticle->Init();
			particles.push_back(newParticle);
		}
		// update the particles, removing any that are not active
		auto it = particles.begin();
		while (it != particles.end())
		{
			(*it)->Update(dt);
			if ((*it)->active)
				it++;
			else
			{
				delete (*it);
				it = particles.erase(it);
			}
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		// draw the particles
		for (auto p : particles)
			p->Draw(window);
	}
};