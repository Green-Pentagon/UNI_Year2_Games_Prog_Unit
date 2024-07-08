#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std; //vector, string, etc. are a part of std:: library.


	class TileLayer {
		vector<vector<int>> ids;

	public:
		TileLayer(string layerFile) {
			ifstream inFile(layerFile);

			if (inFile.is_open())
			{
				string line;
				vector<int> temp;
				
				
				while (!inFile.eof())
				{
					temp.clear();
					inFile >> line;
					std::replace(line.begin(), line.end(), ',', ' ');
					int value;
					stringstream linestream(line);
					while (linestream >> value) {
						//cout << value << endl;
						temp.push_back(value);
					}
					ids.push_back(temp);


				}

			}
		}
		int GetId(int i, int j) { return ids[j][i]; }
		int GetHeight() { return ids.size(); }
		int GetWidth() { return ids[0].size(); }
	};


	class TileMap
	{
		std::vector<TileLayer> layers;
		int nTilesX;
		int nTilesY;
		sf::Texture texture;


	public:
		TileMap(string textureFile, vector<string> layerFiles, int nTilesX, int nTilesY);
		void DrawTile(sf::Vector2f pos, int pixelsPerTile, int tileID, sf::RenderWindow& window);
		void DrawMap(sf::Vector2f pos, int pixelsPerTile, sf::RenderWindow& window);
	private:
		sf::IntRect TexRectFromId(int id);
	};

