#include "Food.h"

// Constructor implementation
Food::Food() {
    // Initialize the food position (optional)
    position = sf::Vector2i(1, 1); // Default invalid position
}

// Respawn the food at a valid position
void Food::respawn(Snake& snake, const std::vector<std::vector<Terrain>>& landscape) {
    bool validPosition = false;

    while (!validPosition) {
        position.x = rand() % GRID_SIZE;
        position.y = rand() % GRID_SIZE;

        // Check if the position is not occupied by the snake's body
        validPosition = true;
        for (const auto& segment : snake.getBody()) {
            if (segment.x == position.x && segment.y == position.y) {
                validPosition = false;
                break;
            }
        }

        // Ensure the food is placed on grass
        if (validPosition && landscape[position.y][position.x] != GRASS) {
            validPosition = false;
        }
    }
}

// Getter for food position
sf::Vector2i Food::getPosition() const {
    return position;
}