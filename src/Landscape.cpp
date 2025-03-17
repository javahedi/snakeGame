#include "Landscape.h"

// Constructor
Landscape::Landscape() {
    // Initialize the landscape with GRID_SIZE x GRID_SIZE grid of GRASS
    landscape = std::vector<std::vector<Terrain>>(GRID_SIZE, std::vector<Terrain>(GRID_SIZE, GRASS));
}

// Destructor
Landscape::~Landscape() {
    // No dynamic memory to clean up
}


void Landscape::initializeLandscape() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            // Randomly assign terrain types
            int terrainType = rand() % 100;
            if (terrainType < 2) { // 2% chance of wall
                landscape[i][j] = TREE;
            } else { // 80% chance of grass
                landscape[i][j] = GRASS;
            }
        }
    }
}


void Landscape::drawLandscape(sf::RenderWindow& window, const sf::Texture& grassTexture, 
    const sf::Texture& treeTexture) {

    // Get the original size
    sf::Vector2u grassTextureSize = grassTexture.getSize();
    // Calculate the scaling factor to fit CELL_SIZE
    float grassScaleX = static_cast<float>(CELL_SIZE) / grassTextureSize.x;
    float grassScaleY = static_cast<float>(CELL_SIZE) / grassTextureSize.y;



    // Get the original size
    sf::Vector2u treeTextureSize = treeTexture.getSize();
    // Calculate the scaling factor to fit CELL_SIZE
    float treeScaleX = static_cast<float>(CELL_SIZE) / treeTextureSize.x;
    float treeScaleY = static_cast<float>(CELL_SIZE) / treeTextureSize.y;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            sf::Sprite sprite(grassTexture); // Initialize with grass texture
            switch (landscape[i][j]) {
                case GRASS:
                    sprite.setTexture(grassTexture);
                    sprite.setScale({grassScaleX * 0.98f, grassScaleY * 0.98f});

                    break;
                case TREE:
                    sprite.setTexture(treeTexture);
                    sprite.setScale({treeScaleX * 1.f, treeScaleY * 1.f});
                    break;
                }
            sprite.setPosition(
                {static_cast<float>(j * CELL_SIZE), 
                static_cast<float>(i * CELL_SIZE)}
            );
            window.draw(sprite);
        }
    }
}

std::vector<std::vector<Terrain>> Landscape::getLandscape() const {
    return landscape;
}