#pragma once
#include "Cave.h"
#include "DoubleBuffer.h"
#include "TextureManager.h"
#include <random>

using namespace std;

Cave::Cave(int nx, int ny) : nx(nx) , ny(ny)
{
	caveBuffer = DoubleBuffer(nx,ny);
	GenerateCave();
}

void Cave::GenerateCave() {
	// random number generator
	float p = 0.5f;
	int M = 1;
	int n = 5;
	int T = 5;

	mt19937 rng = mt19937(random_device()());
	uniform_real_distribution<float> dist(0, 1);
	caveBuffer = DoubleBuffer(nx, ny);
	
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			int val = dist(rng) < p ? 1 : 0;
			caveBuffer.Set(i, j, val);
		}
	}
	caveBuffer.Flip();

	for (int iteration = 0; iteration < n; iteration++) {
		for (int i = 0; i < nx; i++) {
			for (int j = 0; j < ny; j++) {
				if (CountNeighbours(i, j, M) >= T) {
					caveBuffer.Set(i, j, 1);
				}
				else {
					caveBuffer.Set(i, j, 0);
				}
			}
		}
		caveBuffer.Flip();
	}
	
	// load all the textures
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(0 * 32, 4 * 32, 32, 32), "1101");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(0 * 32, 5 * 32, 32, 32), "1001");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(0 * 32, 6 * 32, 32, 32), "1011");

	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(1 * 32, 4 * 32, 32, 32), "1100");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(1 * 32, 5 * 32, 32, 32), "0000");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(1 * 32, 6 * 32, 32, 32), "0011");

	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(2 * 32, 4 * 32, 32, 32), "1110");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(2 * 32, 5 * 32, 32, 32), "0110");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(2 * 32, 6 * 32, 32, 32), "0111");

	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(3 * 32, 5 * 32, 32, 32), "0010");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(3 * 32, 6 * 32, 32, 32), "0100");

	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(4 * 32, 5 * 32, 32, 32), "0001");
	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(4 * 32, 6 * 32, 32, 32), "1000");

	TextureManager::Instance().AddTexture("assets/grass.png", sf::IntRect(6 * 32, 2 * 32, 32, 32), "1111");
}

void Cave::Draw(sf::RenderWindow& window, int pixelsPerCell) {
	/*sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(pixelsPerCell, pixelsPerCell));
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			int value = caveBuffer.Get(i, j);
			rect.setPosition(sf::Vector2f(i * pixelsPerCell, j * pixelsPerCell));
			if (value == 1)
				rect.setFillColor(sf::Color(255, 255, 255, 255));
			else
				rect.setFillColor(sf::Color(0, 0, 0, 0));
			window.draw(rect);
		}
	}*/

	sf::Sprite spr;
	spr.setScale(sf::Vector2f((float)pixelsPerCell / 32, (float)pixelsPerCell / 32));
	for (int i = 0; i < nx-1; i++)
	{
		for (int j = 0; j < ny-1; j++)
		{
			string textureName = "0000";
			if (caveBuffer.Get(i, j) == 1) {
				textureName[0] = '1';
			}
			if (caveBuffer.Get(i+1, j) == 1) {
				textureName[1] = '1';
			}
			if (caveBuffer.Get(i+1, j+1) == 1) {
				textureName[2] = '1';
			}
			if (caveBuffer.Get(i, j+1) == 1) {
				textureName[3] = '1';
			}

			spr.setPosition(sf::Vector2f(i * pixelsPerCell, j * pixelsPerCell));
			TextureManager::Instance().SetSprite(textureName, spr);
			window.draw(spr);
		}
	}
}

int Cave::CountNeighbours(int i, int j, int M) {
	int count = 0;
	for (int ii = i - M; ii <= i+M; ii++) {
		for (int jj = j - M; jj <= j + M; jj++) {
			if (ii >= 0 && ii < nx && jj >= 0 && jj < ny)
			{
				if (caveBuffer.Get(ii, jj) == 1)
					count++;
			}
		}
	}

	return count;
}