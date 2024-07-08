#pragma once
#include "TextureManager.h"
#include <vector>
#include <string>
#include <random>

using namespace std;

class Solitare
{
    vector<string> deck;
    vector<string> suits = { "h", "c", "d", "s" };
    vector<string> values = { "2", "3", "4", "5", "6", "7", "8", "9", "t", "j", "q", "k", "a" };
    
    float cardScale = 2; //make the card size a variable, so you can tweak it
    int ySeparation = 10 * cardScale;
    int xSeparation = 40 * cardScale;

public:
	Solitare() {

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 13; i++)
            {
                string name = values[i] + suits[j];
                deck.push_back(name);
                TextureManager::Instance().AddTexture("assets/8BitDeckAssets.png", sf::IntRect(35*(i+1), 47 * j, 35, 47), name);
            }
        }
        TextureManager::Instance().AddTexture("assets/8BitDeckAssets.png", sf::IntRect(0, 47, 35, 47), "back");

        mt19937 rng = mt19937(random_device()());
        shuffle(deck.begin(), deck.end(), rng);
        
        //for (auto card : deck)
        //{
        //    cout << card << " ";
        //}
        //cout << endl;
	}
    const vector<string> GetDeck() {
        return deck;
    }

    const vector<int> GetSeperation() {
        return {xSeparation,ySeparation};
    }
};

