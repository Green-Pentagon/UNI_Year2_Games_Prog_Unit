#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "EnemyAI.h"

using namespace std;

class Enemy
{
	vector<sf::Vector2f> patrol;
	float visibilityRadius;
	float speed;
	float idleTime;

	int sheet_width = 4;
	int sheet_height = 4;
	int xSeperation = 16;
	int ySeperation = 12;
	sf::Sprite spr;
	sf::Vector2f position;
	EnemyState* state;



	void InitAssets()
	{
		// texture from https://stealthix.itch.io/animated-slimes
		
		for (int x = 0; x < sheet_width; x++) {
			for (int y = 0; y < sheet_height; y++) {
				string name = "slime" + to_string(x) + to_string(y);
				TextureManager::Instance().AddTexture("assets/Slime_Medium_Green.png", sf::IntRect(32*x, 32*y, 32, 32), name );
			}
		}
		TextureManager::Instance().SetTextureFiltering("assets/Slime_Medium_Green.png", false);
		TextureManager::Instance().SetSprite("slime21", spr);
		spr.setOrigin(sf::Vector2f(16, 16));
		spr.setScale(sf::Vector2f(2, 2));
	}
public:
	Enemy(const vector<sf::Vector2f> patrol, float visibilityRadius, float speed, float idleTime) : patrol(patrol), visibilityRadius(visibilityRadius), speed(speed), idleTime(idleTime)
	{
		InitAssets();
		state = new IdleState(*this);
	}
	void Update(float dt, const sf::Vector2f& playerPos)
	{
		// update the state
		EnemyState* newState = state->Update(dt, playerPos);
		if (newState != nullptr)
		{
			delete state;
			state = newState;
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		spr.setPosition(position);
		window.draw(spr);
	}
	const vector<sf::Vector2f>& GetPatrol() const { return patrol; }
	const sf::Vector2f& GetPosition() const { return position; }
	const vector<int> GetSeperation() {
		return { xSeperation,ySeperation };
	}
	float GetSpeed() const { return speed; }
	float GetVisibilityRadius() const { return visibilityRadius; }
	float GetIdleTime() const { return idleTime; }
	void SetPosition(const sf::Vector2f& pos) { position = pos; }

};