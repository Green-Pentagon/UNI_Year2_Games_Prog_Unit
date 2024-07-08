#pragma once
#include "LevelEditor.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "EditorCommands.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

void LevelEditor::LoadTileMap(const string& fileName, int nTileSize)
{
	tileSize = nTileSize;
	// load the texture to get the size, then use the texture manager for cutting up
	sf::Texture tex;
	tex.loadFromFile(fileName);
	sf::Vector2u textureSize = tex.getSize();
	int nx = textureSize.x / tileSize;
	int ny = textureSize.y / tileSize;
	pixFactor = tileScreenSize / tileSize;
	for (int j = 0; j < ny; j++)
	{
		for (int i = 0; i < nx; i++)
		{
			stringstream ss;
			ss << setw(3) << setfill('0') << j * nx + i;
			string name = ss.str();
			tileNames.push_back(name);
			TextureManager::Instance().AddTexture(fileName, sf::IntRect(i * tileSize, j * tileSize, tileSize, tileSize), name);
		}
	}
}

void LevelEditor::DrawTiles()
{
	sf::Sprite spr;
	int x = windowWidth - tileAreaWidth;
	int y = 0;
	spr.setScale(sf::Vector2f(pixFactor, pixFactor));
	int count = 0;
	for (auto t : tileNames)
	{
		TextureManager::Instance().SetSprite(t, spr);
		spr.setPosition(sf::Vector2f(x, y));
		window.draw(spr);
		if (count == selectedTile)
		{
			DrawCursor(x, y, sf::Color(255, 0, 0, 128));
		}
		x += tileSize * pixFactor;
		if (x == windowWidth)
		{
			x = windowWidth - tileAreaWidth;
			y += tileSize * pixFactor;
		}
		++count;
	}
}

void LevelEditor::DrawMap()
{
	sf::Sprite spr;
	spr.setScale(sf::Vector2f(pixFactor, pixFactor));
	for (int i = 0; i < level->GetNX(); i++)
	{
		for (int j = 0; j < level->GetNY(); j++)
		{
			int textureID = level->GetCellTexture(i, j);
			if (textureID != -1)
			{
				TextureManager::Instance().SetSprite(tileNames[textureID], spr);
				spr.setPosition(sf::Vector2f(i * tileScreenSize, j * tileScreenSize));
				window.draw(spr);
			}
		}
	}
}
void LevelEditor::DrawUI()
{
	DrawCursor(cursorX, cursorY, sf::Color(255, 255, 0, 128));
}

void LevelEditor::Undo()
{
	if (undoStack.size() > 0)
	{
		redoStack.push_back(undoStack.back());
		undoStack.back()->Undo();
		undoStack.pop_back();
	}
}

void LevelEditor::Redo() {
	if (redoStack.size() > 0) {
		redoStack.back()->Do();
		undoStack.push_back(redoStack.back());
		redoStack.pop_back();
	}
};

void LevelEditor::Update()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	cursorX = (mousePos.x / tileScreenSize) * tileScreenSize;
	cursorY = (mousePos.y / tileScreenSize) * tileScreenSize;

	if (cursorX >= (windowWidth - tileAreaWidth)) //if the cursor is within the tilemap section of the editor
	{
		int xTile = (cursorX - (windowWidth - tileAreaWidth)) / tileScreenSize;
		int yTile = cursorY / tileScreenSize;
		int tileIndex = yTile * (tileAreaWidth / tileScreenSize) + xTile;
		if (tileIndex < tileNames.size() && InputManager::Instance().ButtonPressed(sf::Mouse::Button::Left)) //if the index is valid and left mouse button is clicked
		{
			selectedTile = tileIndex;
		}
	}
	else {
		int iCell = cursorX / tileScreenSize;
		int jCell = cursorY / tileScreenSize;

		if (InputManager::Instance().ButtonPressed(sf::Mouse::Button::Left)) //place selected tile
		{
			shared_ptr<SetTileCommand> cmd = make_shared<SetTileCommand>(this, iCell, jCell, selectedTile);
			undoStack.push_back(cmd);
			redoStack.clear();
			cmd->Do();
		}
		else if (InputManager::Instance().ButtonPressed(sf::Mouse::Button::Right)) //remove a tile
		{
			shared_ptr<SetTileCommand> cmd = make_shared<SetTileCommand>(this, iCell, jCell, -1);
			undoStack.push_back(cmd);
			redoStack.clear();
			cmd->Do();
			//level->SetCellTexture(iCell, jCell, -1);
		}
	}

	if (InputManager::Instance().KeyDown(sf::Keyboard::LControl) ){
		if (InputManager::Instance().KeyPressed(sf::Keyboard::Z)) {
			Undo();
		}
		else if (InputManager::Instance().KeyPressed(sf::Keyboard::Y)) {
			Redo();
		}
		
	}
}

void LevelEditor::Draw()
{
	DrawTiles();
	DrawMap();
	DrawUI();

}