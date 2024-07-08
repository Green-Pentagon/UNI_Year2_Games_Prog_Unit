#include "ParticleComponents.h"
#include "Particle.h"
#include <random>
// random number generator, which all components can use
float Random()
{
	static mt19937 rng = mt19937(random_device()());
	static uniform_real_distribution<float> dist(0.0f, 1.0f);
	return dist(rng);
}

// component method definitions

void MoveComponent::Update(Particle& parent, float dt)
{
	parent.position += velocity * dt;
	velocity += acceleration * dt;

}

void AlphaOverTimeComponent::Update(Particle& parent, float dt)
{
	time += dt;
	float fTime = time / fadeTime;
	if (fTime > 1.0f)
		fTime = 1.0f;
	float alpha = alpha0 * (1.0f - fTime) + alpha1 * fTime;
	sf::Color currentColor = parent.sprite.getColor();
	currentColor.a = 255 * alpha;
	parent.sprite.setColor(currentColor);
}

void KillComponent::Update(Particle& parent, float dt)
{
	time += dt;
	if (time > killTime)
		parent.active = false;
}

void InitialPositionComponent::Init(Particle& parent)
{
	parent.position.x = minPos.x + (maxPos.x - minPos.x) * Random();
	parent.position.y = minPos.y + (maxPos.y - minPos.y) * Random();
}

void InitialVelocityComponent::Init(Particle& parent)
{
	MoveComponent* move = dynamic_cast<MoveComponent*>(parent.GetComponent("Move"));
	if (move != nullptr)
	{
		sf::Vector2f velocity;
		velocity.x = minVel.x + (maxVel.x - minVel.x) * Random();
		velocity.y = minVel.y + (maxVel.y - minVel.y) * Random();
		move->SetVelocity(velocity);
	}
}

void ColourOverTime::Update(Particle& parent, float dt) {
	time += dt;
	float fTime = time / fadeTime;
	if (fTime > 1.0f)
		fTime = 1.0f;
	sf::Color colour = sf::Color(colour0.r * (1.0f - fTime) + colour1.r * fTime,
								 colour0.g * (1.0f - fTime) + colour1.g * fTime,
								 colour0.b * (1.0f - fTime) + colour1.b * fTime, 255.0f );
	

	sf::Color currentColor = parent.sprite.getColor();
	currentColor = colour;

	parent.sprite.setColor(currentColor);
}

void ScaleOverTime::Update(Particle& parent, float dt) {
	time += dt;
	float fTime = time / fadeTime;
	if (fTime > 1.0f)
		fTime = 1.0f;

	sf::Vector2f scale = sf::Vector2f(scale0.x * (1.0f - fTime) + scale1.x * fTime,
									  scale0.y * (1.0f - fTime) + scale1.y * fTime);

	sf::Vector2f currentScale = parent.sprite.getScale();
	currentScale = scale;

	parent.sprite.setScale(scale);

}

void SpawnAtMousePosition::Init(Particle& parent) {
	parent.position = sf::Vector2f(sf::Mouse::getPosition(window));
}

void ScaleToVelocityComponent::Init(Particle& parent) {
	moveComponent = dynamic_cast<MoveComponent*>(parent.GetComponent("Move")) ;
}

void ScaleToVelocityComponent::Update(Particle& parent, float dt) {

	if (moveComponent != nullptr) {
		sf::Vector2f velocity = moveComponent->GetVelocity();
		sf::Vector2f scale = velocity / scaleFactor;
		float rotationAngle = atan2(velocity.x, -velocity.y) * 180.0f / 3.1415927f;

		parent.sprite.setScale(scale);
		parent.sprite.setRotation(rotationAngle);
	}

}