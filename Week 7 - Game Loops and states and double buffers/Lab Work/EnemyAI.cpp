#include "EnemyAI.h"
#include "Enemy.h"
#include <iostream>

// helper functions
float DistanceSquared(const sf::Vector2f& p0, const sf::Vector2f& p1)
{
    return (p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y);
}

sf::Vector2f MoveTowards(const sf::Vector2f& cur, const sf::Vector2f& target, float speed, float time)
{
    float distSq = DistanceSquared(cur, target);
    if (distSq < speed * speed * time * time)
        return target;
    sf::Vector2f direction = target - cur;
    direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
    return cur + direction * speed * time;
}

PatrolState::PatrolState(Enemy& owner) : EnemyState(owner)
{
    cout << "New PATROL State\n"; //DEBUG
    nextWaypoint = 1;
    direction = 1;
    if (owner.GetPatrol().size() < 2)
    {
        nextWaypoint = 0;
    }
}

EnemyState* PatrolState::Update(float dt, const sf::Vector2f& playerPos)
{
    sf::Vector2f waypointPos = owner.GetPatrol()[nextWaypoint];
    owner.SetPosition(MoveTowards(owner.GetPosition(), waypointPos, owner.GetSpeed(), dt));

    //checks if the distance from the Enemy and player is iwthin the visablilty range, if so enter chase state
    if (DistanceSquared(owner.GetPosition(), playerPos) < (owner.GetVisibilityRadius() * owner.GetVisibilityRadius())) {
        return new ChaseState(owner);
    }
    if (DistanceSquared(waypointPos, owner.GetPosition()) < 0.01f)
    {
        if (nextWaypoint == 0) //if the patrol has ended, return to idle state
        {
            return new IdleState(owner);
        }
        else if (nextWaypoint == owner.GetPatrol().size() - 1)//if still in patrol state, change direction to negative.
            {
                direction = -1;
            }
            nextWaypoint += direction;
            waypointPos = owner.GetPatrol()[nextWaypoint];
    }
    return nullptr;
}

IdleState::IdleState(Enemy& owner) : EnemyState(owner)
{
    cout << "New IDLE State\n"; //DEBUG
    owner.SetPosition(owner.GetPatrol()[0]);
    idleTimer = owner.GetIdleTime();
}

EnemyState* IdleState::Update(float dt, const sf::Vector2f& playerPos)
{
    idleTimer -= dt;
    if (idleTimer < 0.0f) {
        return new PatrolState(owner);
    }
    //checks if the distance from the Enemy and player is iwthin the visablilty range, if so enter chase state
    if (DistanceSquared(owner.GetPosition(), playerPos) < (owner.GetVisibilityRadius() * owner.GetVisibilityRadius())) {
        return new ChaseState(owner);
    }
    return nullptr;
    
}

ChaseState::ChaseState(Enemy& owner) : EnemyState(owner)
{
    cout << "New CHASE State\n"; //DEBUG
}

EnemyState* ChaseState::Update(float dt, const sf::Vector2f& playerPos)
{
    //checks if the distance from the enemy and player is still valid
    owner.SetPosition(MoveTowards(owner.GetPosition(), playerPos, owner.GetSpeed(), dt));
    if (DistanceSquared(owner.GetPosition(), playerPos) > (owner.GetVisibilityRadius() * owner.GetVisibilityRadius())) {
        return new ReturnState(owner);
    }

    return nullptr;
}

ReturnState::ReturnState(Enemy& owner) : EnemyState(owner)
{
    cout << "New RETURN State\n"; //DEBUG
}

EnemyState* ReturnState::Update(float dt, const sf::Vector2f& playerPos)
{
    owner.SetPosition(MoveTowards(owner.GetPosition(), owner.GetPatrol()[0], owner.GetSpeed(), dt));

    //checks if the distance from the Enemy and player is iwthin the visablilty range, if so enter chase state
    if (DistanceSquared(owner.GetPosition(), playerPos) < (owner.GetVisibilityRadius() * owner.GetVisibilityRadius())) {
        return new ChaseState(owner);
    }

    if (owner.GetPosition() == owner.GetPatrol()[0]) {
        return new IdleState(owner);
    }
    return nullptr;
}