#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <vector>
#include "Constants.h"

class Snake {
private:
    std::vector<sf::Vector2i> body;
    sf::Vector2i direction;

public:
    Snake();
    bool canMove(const sf::Vector2i& newHead, const std::vector<std::vector<Terrain>>& landscape);
    bool move(const std::vector<std::vector<Terrain>>& landscape);
    void grow(sf::Music& eatSound);

    // Public getter methods
    const std::vector<sf::Vector2i>& getBody() const;
    const sf::Vector2i& getDirection() const;

    // Public setter method for direction
    void setDirection(const sf::Vector2i& newDirection);
    void reset();

};

#endif // SNAKE_H