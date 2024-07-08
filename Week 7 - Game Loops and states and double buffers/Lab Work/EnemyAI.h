#pragma once
#include <SFML/Graphics.hpp>
class Enemy;

class EnemyState
{
protected:
    Enemy& owner;
public:
    EnemyState(Enemy& owner) : owner(owner) {}
    virtual EnemyState* Update(float dt, const sf::Vector2f& playerPos) = 0;
};

class PatrolState : public EnemyState
{
    int nextWaypoint;
    int direction;

public:
    PatrolState(Enemy& owner);
    virtual EnemyState* Update(float dt, const sf::Vector2f& playerPos) override;
};

class IdleState : public EnemyState
{
    float idleTimer;

public:
    IdleState(Enemy& owner);
    virtual EnemyState* Update(float dt, const sf::Vector2f& playerPos) override;
};

class ChaseState : public EnemyState
{
public:
    ChaseState(Enemy& owner);
    virtual EnemyState* Update(float dt, const sf::Vector2f& playerPos) override;
};

class ReturnState : public EnemyState
{
public:
    ReturnState(Enemy& owner);
    virtual EnemyState* Update(float dt, const sf::Vector2f& playerPos) override;
};
