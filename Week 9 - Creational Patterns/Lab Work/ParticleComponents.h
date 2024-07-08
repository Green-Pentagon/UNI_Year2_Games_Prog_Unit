#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Cloneable.h"
class Particle;
using namespace std;
class ParticleComponent : public ICloneable
{
protected:
	string name;
public:
	ParticleComponent(string name = "default") : name(name) {}
	virtual void Update(Particle& parent, float dt) {} // called when particle is updated
	virtual void Init(Particle& parent) {} // called when particle is spawned
	string GetName() { return name; }
	virtual ICloneable* clone() = 0;
};

class MoveComponent : public ParticleComponent
{
	// moves the parent particle using velocity and acceleration
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
public:
	MoveComponent(sf::Vector2f velocity, sf::Vector2f acceleration) : ParticleComponent("Move"), velocity(velocity), acceleration(acceleration) {}
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() override { return new MoveComponent(velocity, acceleration); }
	void SetVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	sf::Vector2f GetVelocity() { return velocity; }
};

class AlphaOverTimeComponent : public ParticleComponent
{
	// fades the sprite over time
	float alpha0;
	float alpha1;
	float fadeTime;
	float time;
public:
	AlphaOverTimeComponent(float alpha0, float alpha1, float fadeTime) :
		ParticleComponent("AlphaOverTime"), alpha0(alpha0), alpha1(alpha1), fadeTime(fadeTime), time(0.0f) {}
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() override { return new AlphaOverTimeComponent(alpha0, alpha1, fadeTime); }
};

class KillComponent : public ParticleComponent
{
	float time;
	float killTime;
public:
	KillComponent(float killTime) : ParticleComponent("Kill"), time(0.0f), killTime(killTime) {}
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() { return new KillComponent(killTime); }
};

class InitialPositionComponent : public ParticleComponent
{
	sf::Vector2f minPos;
	sf::Vector2f maxPos;
public:
	InitialPositionComponent(sf::Vector2f minPos, sf::Vector2f maxPos) : ParticleComponent("InitialPosition"), minPos(minPos), maxPos(maxPos) {}
	void Init(Particle& parent) override;
	ICloneable* clone() { return new InitialPositionComponent(minPos, maxPos); }
};

class InitialVelocityComponent : public ParticleComponent
{
	sf::Vector2f minVel;
	sf::Vector2f maxVel;
public:
	InitialVelocityComponent(sf::Vector2f minVel, sf::Vector2f maxVel) : ParticleComponent("InitialVelocity"), minVel(minVel), maxVel(maxVel) {}
	void Init(Particle& parent) override;
	ICloneable* clone() { return new InitialVelocityComponent(minVel, maxVel); }
};

class ColourOverTime : public ParticleComponent {
	sf::Color colour0;
	sf::Color colour1;
	float fadeTime;
	float time;
public:
	ColourOverTime(sf::Color colour0 , sf::Color colour1, float fadeTime):
		ParticleComponent("ColourOverTime"), colour0(colour0), colour1(colour1), fadeTime(fadeTime), time(0.0f) {}
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() override { return new ColourOverTime(colour0, colour1, fadeTime); }
};

class ScaleOverTime : public ParticleComponent {
	sf::Vector2f scale0;
	sf::Vector2f scale1;
	float fadeTime;
	float time;
public:
	ScaleOverTime(sf::Vector2f scale0, sf::Vector2f scale1, float fadeTime) :
		ParticleComponent("ColourOverTime"), scale0(scale0), scale1(scale1), fadeTime(fadeTime), time(0.0f) {}
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() override { return new ScaleOverTime(scale0, scale1, fadeTime); }
};

class SpawnAtMousePosition : public ParticleComponent {
	sf::RenderWindow& window;
public:
	SpawnAtMousePosition(sf::RenderWindow& window) :
		ParticleComponent("SpawnAtMousePosition"), window(window) {}
	void Init(Particle& parent) override;

	ICloneable* clone() override { return new SpawnAtMousePosition(window); }
};

class ScaleToVelocityComponent : public ParticleComponent {
	float scaleFactor;
	MoveComponent* moveComponent;
public:
	ScaleToVelocityComponent(float scaleFactor) : ParticleComponent("ScaleToVelocityComponent"), scaleFactor(scaleFactor) {}
	void Init(Particle& particle) override;
	void Update(Particle& parent, float dt) override;
	ICloneable* clone() override { return new ScaleToVelocityComponent(scaleFactor); }
};