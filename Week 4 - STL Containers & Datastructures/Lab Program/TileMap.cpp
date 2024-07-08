#include "TileMap.h"

TileMap::TileMap(string textureFile, vector<string> layerFiles, int nTilesX, int nTilesY): nTilesX(nTilesX), nTilesY(nTilesY)
{
	for (string layer : layerFiles) {
		layers.push_back(TileLayer(layer));
	}

    vector<int> testi = { 2,4,5,11,0,8 };
    vector<int> testj = { 0,11,3,4,7,9 };
    vector<int> expected0 = { 198, 171, 223, 174, 100, 100 };
    vector<int> expected1 = { 93, -1, -1, 183, -1, -1 };
    for (int i = 0; i < testi.size(); i++)
    {
        int layer0ID = layers[0].GetId(testi[i], testj[i]);
        int layer1ID = layers[1].GetId(testi[i], testj[i]);
        if (layer0ID == expected0[i])
            cout << "test " << i << " passed for layer 0" << endl;
        else
            cout << "test " << i << " failed for layer 0, expected " << expected0[i] << " got " << layer0ID << endl;
        if (layer1ID == expected1[i])
            cout << "test " << i << " passed for layer 1" << endl;
        else
            cout << "test " << i << " failed for layer 1, expected " << expected1[i] << " got " << layer1ID << endl;
    }
}

void TileMap::DrawTile(sf::Vector2i pos, int pixelsPerTile, int tileID, sf::RenderWindow& window)
{
}

void TileMap::DrawMap(sf::Vector2i pos, int pixelsPerTile, sf::RenderWindow& window)
{
}
