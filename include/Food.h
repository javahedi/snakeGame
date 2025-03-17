#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"
#include "Snake.h"

class Food {
private:
    sf::Vector2i position;

public:
    Food();
    void respawn(Snake& snake, const std::vector<std::vector<Terrain>>& landscape);
    sf::Vector2i getPosition() const;
};

#endif // FOOD_H