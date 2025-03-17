#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"


class Landscape
{
private:
    std::vector<std::vector<Terrain>> landscape;    

public:
    Landscape();
    ~Landscape();

    void initializeLandscape();
    void drawLandscape(sf::RenderWindow& window, const sf::Texture& grassTexture, 
        const sf::Texture& treeTexture);
        std::vector<std::vector<Terrain>> getLandscape() const;
};


#endif //LANDSCAPE_H


