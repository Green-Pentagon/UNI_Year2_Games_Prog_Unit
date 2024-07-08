#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "level.h"
#include "EditorCommands.h"
class EditorCommands;

using namespace std;

class LevelEditor
{
	sf::RenderWindow& window;
	Level* level;
	int tileSize;
	void DrawTiles();
	void DrawMap();
	void DrawUI();
	vector<string> tileNames;

	// numbers for screen placement
	const int tileScreenSize = 32;
	const int tileAreaWidth = 256;
	int windowWidth;
	int windowHeight;
	int pixFactor;

	// editing
	int selectedTile = 0;
	sf::Texture cursor;
	int cursorX, cursorY;

	// undo/redo system
	vector<shared_ptr<EditorCommands>> undoStack;
	vector<shared_ptr<EditorCommands>> redoStack;
	void Undo();
	void Redo();

	void DrawCursor(int i, int j, const sf::Color& color)
	{
		sf::Sprite spr;
		spr.setTexture(cursor);
		spr.setPosition(sf::Vector2f(i, j));
		spr.setColor(color);
		window.draw(spr);
	}
public:
	LevelEditor(sf::RenderWindow& window) : window(window)
	{
		windowWidth = window.getSize().x;
		windowHeight = window.getSize().y;
		// create a level, just big enough to show
		int nTilesX = (windowWidth - tileAreaWidth) / tileScreenSize;
		int nTilesY = windowHeight / tileScreenSize;
		level = new Level(nTilesX, nTilesY);
		cursor.loadFromFile("assets/cursor.png");
	}

	void LoadTileMap(const string& fileName, int tileSize);
	void Update();
	void Draw();
	Level* GetLevel() const { return level; }
};