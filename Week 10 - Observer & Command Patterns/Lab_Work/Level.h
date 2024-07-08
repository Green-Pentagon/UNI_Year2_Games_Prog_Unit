#pragma once

#include <vector>
using namespace std;

class Level
{
	int nx, ny;
	vector<vector<int>> level;
public:
	Level(int nx, int ny) : nx(nx), ny(ny)
	{
		// fill cells with '-1' (no texture)
		for (int i = 0; i < nx; i++)
		{
			vector<int> column(ny, -1);
			level.push_back(column);
		}
	}
	int GetNX() const { return nx; }
	int GetNY() const { return ny; }
	int GetCellTexture(int i, int j) const { return level[i][j]; }
	void SetCellTexture(int i, int j, int textureId)
	{
		level[i][j] = textureId;
	}
};