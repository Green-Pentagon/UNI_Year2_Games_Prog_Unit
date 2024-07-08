#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
using namespace std;


class SpriteTexture
{
public:
    string fileName;
    sf::IntRect rect;
};

class TextureManager
{
    unordered_map<string, sf::Texture> textures;
    unordered_map<string, SpriteTexture> sprites;

    TextureManager() {} // private constructor

public:
    static TextureManager& Instance()
    {
        static TextureManager instance; // static variable, only initialized once
        return instance;
    }

    void AddTexture(const string& fileName, const sf::IntRect& rect, const string& alias)
    {
        // make sure the texture is loaded
        AddTextureFile(fileName);
        sprites[alias] = SpriteTexture();
        sprites[alias].fileName = fileName;
        sprites[alias].rect = rect;

    }

    void SetSprite(const string& alias, sf::Sprite& spr)
    {
        // look for the alias
        if (sprites.find(alias) == sprites.end())
        {
            // can't find it, bail out
            return;
        }
        spr.setTexture(textures[sprites[alias].fileName]);
        spr.setTextureRect(sprites[alias].rect);
    }

private:
    void AddTextureFile(const string& fileName)
    {
        if (textures.find(fileName) == textures.end())
        {
            // we haven't seen this before, create a new entry in the map and load from file
            textures[fileName] = sf::Texture();
            textures[fileName].loadFromFile(fileName);
        }
    }
};


