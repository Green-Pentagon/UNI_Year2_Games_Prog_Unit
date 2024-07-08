#include "TileMap.h"

TileMap::TileMap(string textureFile, vector<string> layerFiles, int nTilesX, int nTilesY): nTilesX(nTilesX), nTilesY(nTilesY)
{
	for (string layer : layerFiles) {
		layers.push_back(TileLayer(layer));
	}

    //vector<int> testi = { 2,4,5,11,0,8 };
    //vector<int> testj = { 0,11,3,4,7,9 };
    //vector<int> expected0 = { 198, 171, 223, 174, 100, 100 };
    //vector<int> expected1 = { 93, -1, -1, 183, -1, -1 };
    //for (int i = 0; i < testi.size(); i++)
    //{
    //    int layer0ID = layers[0].GetId(testi[i], testj[i]);
    //    int layer1ID = layers[1].GetId(testi[i], testj[i]);
    //    if (layer0ID == expected0[i])
    //        cout << "test " << i << " passed for layer 0" << endl;
    //    else
    //        cout << "test " << i << " failed for layer 0, expected " << expected0[i] << " got " << layer0ID << endl;
    //    if (layer1ID == expected1[i])
    //        cout << "test " << i << " passed for layer 1" << endl;
    //    else
    //        cout << "test " << i << " failed for layer 1, expected " << expected1[i] << " got " << layer1ID << endl;
    //}

    texture.loadFromFile(textureFile);
    texture.setSmooth(false); // we don't want texture filtering on pixel art

    //vector<int> testIDs = { 0, 287, 54, 27 };
    //for (int i : testIDs) {
    //    sf::IntRect test = TexRectFromId(i);
    //    cout << "id: " << i << " rect: " << test.left << " " << test.top
    //        << " " << test.width << " " << test.height << endl;

    //}
    
}

void TileMap::DrawTile(sf::Vector2f pos, int pixelsPerTile, int tileID, sf::RenderWindow& window)
{
    if (tileID == -1)
        return; // id == -1 means no tile here
    sf::Sprite spr;
    spr.setTexture(texture);

    sf::IntRect texRect = TexRectFromId(tileID);
    spr.setTextureRect(texRect);
    spr.setPosition(pos);
    float spriteScale = (float)pixelsPerTile / abs(texRect.width);
    spr.setScale(sf::Vector2f(spriteScale, spriteScale));

    window.draw(spr);
}

void TileMap::DrawMap(sf::Vector2f pos, int pixelsPerTile, sf::RenderWindow& window)
{
    for (auto layer : layers)
    {
        for (int i = 0; i < layer.GetWidth(); i++)
        {
            for (int j = 0; j < layer.GetHeight(); j++)
            {
                sf::Vector2f thisTilePos = pos + sf::Vector2f(i * pixelsPerTile, j * pixelsPerTile);
                int id = layer.GetId(i, j);
                DrawTile(thisTilePos, pixelsPerTile, id, window);
            }
        }
    }
}

sf::IntRect TileMap::TexRectFromId(int id) {
    // detect flipping
    bool flipped = false;
    if (id & 0x80000000)
    {
        id = id & 0x7FFFFFFF;
        flipped = true;
    }

    int x0, y0; // coordinates of top left corner
    int sizeX; // size (x-axis) in pixels
    int sizeY; // size (y-axis) in pixels

    sizeX = texture.getSize().x / nTilesX;
    sizeY = texture.getSize().y / nTilesY;
    int row = id / nTilesX;
    int column = id % nTilesX;
    x0 = column * sizeX;
    y0 = row * sizeY;

    if (flipped)
        return sf::IntRect(x0 + sizeX, y0, -sizeX, sizeY);
    else
        return sf::IntRect(x0, y0, sizeX, sizeY);
}
