// Game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Food.h"
#include "Landscape.h"
#include <iostream>


class Game {
private:
    sf::RenderWindow window;
    sf::Texture bodyTexture, headTexture, grassTexture, treeTexture, foodTexture;
    sf::Music moveSnake, eatApple, hitTree;
    sf::Font font;
    sf::Text gameOverText, scoreText;
    sf::Clock clock; 

    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;
    sf::Text playButtonText;
    sf::Text exitButtonText;

    sf::RectangleShape sloweButton;
    sf::RectangleShape mediumButton;
    sf::RectangleShape fastButton;
    sf::Text sloweButtonText; 
    sf::Text mediumButtonText; 
    sf::Text fastButtonText; 

    bool inMenu;   // Wheter game is in the menu
    float snakeSpeedSlow; 
    float snakeSpeedMedium; 
    float snakeSpeedFast; 


    Landscape scene;
    Snake snake;
    Food food;

    int SCORE;
    bool gameOver;
    float snakeSpeed;
    float elapsedTime;

    void loadResources();
    void handleInput();
    void update();
    void render();
    void resetGame();
    void initializeButtons();
    bool isMouseOverButton(const sf::RectangleShape& button);
    void initializeMenu();
    void handleMenuInput();
    void renderMenu();

public:
    Game();
    void run();
};

#endif // GAME_H