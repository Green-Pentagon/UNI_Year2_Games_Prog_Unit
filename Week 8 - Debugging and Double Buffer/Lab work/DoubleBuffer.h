#pragma once
#include <vector>

using namespace std;

class TwoDimensionalIntBuffer
{
	vector<vector<int>> buffer;
public:
	TwoDimensionalIntBuffer(int nx, int ny)
	{
		// initialize the buffers with zeros
		for (int i = 0; i < nx; i++)
		{
			vector<int> line(ny, 0); // vector constructor which fixes length
			buffer.push_back(line);
		}
	}
	int Get(int i, int j) { return buffer[i][j]; }
	void Set(int i, int j, int value) { buffer[i][j] = value; }
};

class DoubleBuffer
{
	vector<TwoDimensionalIntBuffer> buffers;
	int curBuffer = 0;
public:
	DoubleBuffer() {}
	DoubleBuffer(int nx, int ny)
	{
		buffers.push_back(TwoDimensionalIntBuffer(nx, ny));
		buffers.push_back(TwoDimensionalIntBuffer(nx, ny));
	}
	int Get(int i, int j) { return buffers[curBuffer].Get(i, j); }
	void Set(int i, int j, int value) { buffers[curBuffer ^ 1].Set(i, j, value); }
	void Flip() { curBuffer ^= 1; }
};
