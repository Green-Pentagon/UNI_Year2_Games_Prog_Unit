#pragma once
#include <SFML/Graphics.hpp>
#include "DoubleBuffer.h"


class Cave
{
	int nx;
	int ny;
	DoubleBuffer caveBuffer;

	int CountNeighbours(int i, int j, int neighbourhoodSize);

public:
	Cave(int nx, int ny);

	void GenerateCave();

	void Draw(sf::RenderWindow& window, int pixelsPerCell);
	
};

