#pragma once
#include "ParticleComponents.h"
#include <vector>
#include <string>

using namespace std;

class Particle : public ICloneable
{
	vector<ParticleComponent*> components;
public:
	sf::Sprite sprite;
	sf::Vector2f position;
	bool active;
	~Particle()
	{
		for (auto c : components)
			delete c;
	}

	void AddComponent(ParticleComponent* component)
	{
		components.push_back(component);
	}

	void Init()
	{
		for (auto c : components)
			c->Init(*this);
	}
	void Update(float dt)
	{
		for (auto c : components)
			c->Update(*this, dt);
	}
	void Draw(sf::RenderWindow& window)
	{
		sprite.setPosition(position);
		window.draw(sprite, sf::BlendAdd);
	}

	ParticleComponent* GetComponent(string name)
	{
		// return first component which matches the name - allows components to modify each other
		for (auto c : components)
			if (c->GetName() == name)
				return c;
		return nullptr;
	}

	ICloneable* clone()
	{
		Particle* newParticle = new Particle();
		newParticle->sprite = sprite;
		newParticle->position = position;
		newParticle->active = true;
		for (auto c : components)
			newParticle->AddComponent(dynamic_cast<ParticleComponent*>(c->clone()));
		return newParticle;
	}
};