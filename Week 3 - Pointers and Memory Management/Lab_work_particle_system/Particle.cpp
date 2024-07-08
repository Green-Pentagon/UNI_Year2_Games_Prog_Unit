#include "Particle.h"
#include "ParticleSystem.h"

void Particle::Update(float deltaTime)
{
	position = position + velocity * deltaTime;
	velocity = velocity + parent.GetGravity() * deltaTime;
}