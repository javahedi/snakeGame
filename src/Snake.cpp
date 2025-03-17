#include "Snake.h"

Snake::Snake() {
    body.push_back(sf::Vector2i(GRID_SIZE / 2, GRID_SIZE / 2));
    direction = sf::Vector2i(1, 0);
}

bool Snake::canMove(const sf::Vector2i& newHead, const std::vector<std::vector<Terrain>>& landscape) {
    // Check if the new head position is a wall or tree
    Terrain terrain = landscape[newHead.y][newHead.x];
    return terrain != TREE;
}

bool Snake::move(const std::vector<std::vector<Terrain>>& landscape) {
    // Calculate the new head position
    sf::Vector2i newHead = body[0] + direction;
    
    // Wrap around the grid boundaries
    if (newHead.x < 0) {
        newHead.x = GRID_SIZE - 1; // Wrap to the right side
    } else if (newHead.x >= GRID_SIZE) {
        newHead.x = 0; // Wrap to the left side
    }
    
    if (newHead.y < 0) {
        newHead.y = GRID_SIZE - 1; // Wrap to the bottom
    } else if (newHead.y >= GRID_SIZE) {
        newHead.y = 0; // Wrap to the top
    }
    
    // Check if snake head position is already in body, lose the game
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == newHead) {
            return false; // Game over
        }
    }
    
    // Check if the new head position is valid
    if (!canMove(newHead, landscape)) {
        return false; // Game over
    }

    // Insert the new head, and remove the tail
    body.insert(body.begin(), newHead);
    body.pop_back();

    return true;
}

void Snake::grow(sf::Music& eatSound) {   
    eatSound.play();
    body.push_back(body.back());
    // SCORE++;
}

void Snake::reset() {
    body.clear(); // Clear the existing body
    body.push_back(sf::Vector2i(GRID_SIZE / 2, GRID_SIZE / 2));
    direction = sf::Vector2i(1, 0);
}

// Getter implementations
const std::vector<sf::Vector2i>& Snake::getBody() const {
    return body;
}

const sf::Vector2i& Snake::getDirection() const {
    return direction;
}

// Setter implementation for direction
void Snake::setDirection(const sf::Vector2i& newDirection) {
    direction = newDirection;
}