// Game.cpp
#include "Game.h"

Game::Game()
    : window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Snake Game"),
      SCORE(0), gameOver(false), snakeSpeed(250.0f), elapsedTime(0.0f),
      gameOverText(font, ""), scoreText(font, ""),
      playButtonText(font, ""), exitButtonText(font, "") ,
      sloweButtonText(font, ""), mediumButtonText(font, ""),
      fastButtonText(font, ""){  // Initialize sf::Text objects with font
        loadResources();
        scene.initializeLandscape();
        initializeButtons(); // Initialize buttons
}

void Game::loadResources() {
    // Load textures
    if (!bodyTexture.loadFromFile("figures/bodySnake.png") ||
        !headTexture.loadFromFile("figures/headSnake.png") ||
        !foodTexture.loadFromFile("figures/food.png") ||
        !grassTexture.loadFromFile("figures/grass.png") ||
        !treeTexture.loadFromFile("figures/tree.png")) {
        std::cerr << "Failed to load textures!" << std::endl;
        exit(-1);
    }

    // Load sounds
    if (!moveSnake.openFromFile("sounds/move.mp3") ||
        !eatApple.openFromFile("sounds/eat.mp3")   ||
        !hitTree.openFromFile("sounds/hit.mp3") ) {
        std::cerr << "Failed to load sounds!" << std::endl;
        exit(-1);
    }

    // Load font
    if (!font.openFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(-1);
    }

    // Set up game over text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition({WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 4.0f});
    //gameOverText.setPosition({(WINDOW_WIDTH - gameOverText.getLocalBounds().width) / 2.0f, WINDOW_HEIGHT / 2.0f});

    // Set up score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10, WINDOW_HEIGHT - 40});

}



void Game::initializeButtons() {
    playButton.setSize(sf::Vector2f(150, 50));
    playButton.setPosition( { WINDOW_WIDTH / 2.0f   - playButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f + 50} );
    playButton.setFillColor(sf::Color::Green);

    playButtonText.setFont(font);
    playButtonText.setString("Play Again");
    playButtonText.setCharacterSize(30);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setPosition({ WINDOW_WIDTH / 2.0f  - playButton.getSize().x / 2.0f  , WINDOW_HEIGHT / 2.0f + 50});
    

    // Exit button
    exitButton.setSize(sf::Vector2f(100, 50));
    exitButton.setPosition({WINDOW_WIDTH / 2.0f  - exitButton.getSize().x / 2.0f , WINDOW_HEIGHT / 2.0f + 120});
    exitButton.setFillColor(sf::Color::Red);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(30);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition({WINDOW_WIDTH / 2.0f  - exitButton.getSize().x / 4.0f  , WINDOW_HEIGHT / 2.0f + 120});
    
}

bool Game::isMouseOverButton(const sf::RectangleShape& button) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}


void Game::initializeMenu() {
    sloweButton.setSize(sf::Vector2f(150, 50));
    sloweButton.setPosition({WINDOW_WIDTH  / 2.0f - sloweButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f - 100});
    sloweButton.setFillColor(sf::Color::White);


    sloweButtonText.setFont(font);
    sloweButtonText.setString("Slowe");
    sloweButtonText.setCharacterSize(30);
    sloweButtonText.setFillColor(sf::Color::Blue);
    sloweButtonText.setPosition({WINDOW_WIDTH  / 2.0f - sloweButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f - 100});


    mediumButton.setSize(sf::Vector2f(150, 50));
    mediumButton.setPosition({WINDOW_WIDTH  / 2.0f - mediumButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f});
    mediumButton.setFillColor(sf::Color::White);


    mediumButtonText.setFont(font);
    mediumButtonText.setString("Medium");
    mediumButtonText.setCharacterSize(30);
    mediumButtonText.setFillColor(sf::Color::Blue);
    mediumButtonText.setPosition({WINDOW_WIDTH / 2.0f - mediumButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f});


    fastButton.setSize(sf::Vector2f(150, 50));
    fastButton.setPosition({WINDOW_WIDTH / 2.0f - fastButton.getSize().x / 2.0f, WINDOW_HEIGHT / 2.0f + 100});
    fastButton.setFillColor(sf::Color::White);


    fastButtonText.setFont(font);
    fastButtonText.setString("Fast");
    fastButtonText.setCharacterSize(30);
    fastButtonText.setFillColor(sf::Color::Blue);
    fastButtonText.setPosition({WINDOW_WIDTH / 2.0f - fastButton.getSize().x / 2.0f , WINDOW_HEIGHT / 2.0f + 100});

    // Set initial state
    inMenu           = true;
    snakeSpeedSlow   = 400.0f; // Slower speed for simple difficulty
    snakeSpeedMedium = 250.0f; // Medium speed for intermediate difficulty
    snakeSpeedFast   = 150.0f; // Faster speed for hard difficulty

}


void Game::handleMenuInput() {
    // Event handeling
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
            if (isMouseOverButton(sloweButton)) {
               snakeSpeed = snakeSpeedSlow;
               inMenu = false;
            }else if (isMouseOverButton(mediumButton)) {
                snakeSpeed = snakeSpeedMedium;
                inMenu = false;
            }else if (isMouseOverButton(fastButton)) {
                snakeSpeed = snakeSpeedFast;
                inMenu = false;
            }
        }
    }
}



void Game::handleInput() {
    // Event handeling
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
            

        /*
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                // Left mouse button pressed
                if (gameOver) {
                    resetGame(); // Restart the game
                }
            } else if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                // Right mouse button pressed
                if (gameOver) {
                    window.close(); // Close the window
                }
            }
        }
        */
        if (gameOver){
            
            if (moveSnake.getStatus() != sf::SoundSource::Status::Playing) {
                moveSnake.play();
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (isMouseOverButton(playButton)) {
                    moveSnake.stop();
                    resetGame();

                }else if (isMouseOverButton(exitButton)) {
                    moveSnake.stop();
                    window.close(); 
                }
                
            }
        } else {
            if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyEvent->code){
                    case sf::Keyboard::Key::Up:
                        // Prevent reversing direction
                        if (snake.getDirection().y == 0) {
                            snake.setDirection(sf::Vector2i(0,-1)); // Move up
                        }
                        break;
                    case sf::Keyboard::Key::Down:
                        // Prevent reversing direction
                        if (snake.getDirection().y == 0) {
                            snake.setDirection(sf::Vector2i(0,1)); // Move down
                        }
                        break;
                    case sf::Keyboard::Key::Left:
                        // Prevent reversing direction
                        if (snake.getDirection().x == 0) {
                            snake.setDirection( sf::Vector2i(-1,0)); // Move left
                        }
                        break;
                    case sf::Keyboard::Key::Right:
                        // Prevent reversing direction
                        if (snake.getDirection().x == 0) {
                            snake.setDirection(sf::Vector2i(1,0)); // Move right
                        }
                        break;
                    default:
                        break;
                }  
            }
        }
        
    }
}

void Game::update() {
    sf::Time deltaTime = clock.restart();
    elapsedTime += deltaTime.asMilliseconds();

    if (!gameOver && elapsedTime >= snakeSpeed) {
        if (!snake.move(scene.getLandscape())) {
            gameOver = true;
            hitTree.play();
        }
        elapsedTime = 0.0f;
    }

    if (!gameOver && snake.getBody()[0] == food.getPosition()) {
        snake.grow(eatApple);
        food.respawn(snake, scene.getLandscape());
        SCORE++;
    }

}


void Game::renderMenu() {
    window.clear();

    // Draw buttons
    window.draw(sloweButton);
    window.draw(sloweButtonText);

    window.draw(mediumButton);
    window.draw(mediumButtonText);

    window.draw(fastButton);
    window.draw(fastButtonText);

    window.display();

}


void Game::render() {
    window.clear();

    // Scale

    // Get the original size
    sf::Vector2u bodyTextureSize = bodyTexture.getSize();
    // Calculate the scaling factor to fit CELL_SIZE
    float bodyScaleX = static_cast<float>(CELL_SIZE) / bodyTextureSize.x;
    float bodyScaleY = static_cast<float>(CELL_SIZE) / bodyTextureSize.y;


    // Get the original size
    sf::Vector2u headTextureSize = headTexture.getSize();
    // Calculate the scaling factor to fit CELL_SIZE
    float headScaleX = static_cast<float>(CELL_SIZE) / headTextureSize.x;
    float headScaleY = static_cast<float>(CELL_SIZE) / headTextureSize.y;


    // Get the original size
    sf::Vector2u foodTextureSize = foodTexture.getSize();
    // Calculate the scaling factor to fit CELL_SIZE
    float foodScaleX = static_cast<float>(CELL_SIZE) / foodTextureSize.x;
    float foodScaleY = static_cast<float>(CELL_SIZE) / foodTextureSize.y;

    // Draw landscape
    scene.drawLandscape(window, grassTexture, treeTexture);

   
    ////////////////////////
    // Draw snake
    for (size_t i = 1; i < snake.getBody().size(); ++i) {
        sf::Sprite bodySprite(bodyTexture);
        bodySprite.setPosition(
                {static_cast<float>(snake.getBody()[i].x * CELL_SIZE),
                 static_cast<float>(snake.getBody()[i].y * CELL_SIZE)}
            );
        bodySprite.setScale({bodyScaleX, bodyScaleY});
        window.draw(bodySprite);
    }

    // Draw snake head
    sf::Sprite headSprite(headTexture);
    headSprite.setScale({headScaleX * 1.3f, headScaleY * 1.3f});

    // Set the origin to the center of the sprite
    headSprite.setOrigin({headTextureSize.x / 2.0f, headTextureSize.y / 2.0f});

    // Set the position and scale
    sf::Vector2f headPosition(
        {static_cast<float>(snake.getBody()[0].x * CELL_SIZE),
         static_cast<float>(snake.getBody()[0].y * CELL_SIZE)
        }
    );
    headSprite.setPosition(headPosition + sf::Vector2f(CELL_SIZE / 2.0f, CELL_SIZE / 2.0f));
    
    if (snake.getDirection() == sf::Vector2i(1,0)) {
        headSprite.setRotation(sf::degrees(180.f));
    }else if (snake.getDirection() == sf::Vector2i(-1,0))
    {
        headSprite.setRotation(sf::degrees(0.f));
    }else if (snake.getDirection() == sf::Vector2i(0,1))
    {
        headSprite.setRotation(sf::degrees(270.f));
    }else if (snake.getDirection() == sf::Vector2i(0,-1))
    {
        headSprite.setRotation(sf::degrees(90.f));
    }
    window.draw(headSprite);




    // Draw food
    sf::Sprite foodSprite(foodTexture);
    foodSprite.setPosition(
        {static_cast<float>(food.getPosition().x * CELL_SIZE),
        static_cast<float>(food.getPosition().y * CELL_SIZE)}
    );
    foodSprite.setScale({foodScaleX * 1.5f, foodScaleY * 1.5f});
    window.draw(foodSprite);

    // Draw game over screen
    if (gameOver) {
        scoreText.setString("Score: " + std::to_string(SCORE));
        window.draw(gameOverText);
        window.draw(scoreText);
        

        /*
       // Add instructions
       sf::Text instructions(font, "Click to play again\nRight-click to exit");
       instructions.setCharacterSize(30);
       instructions.setFillColor(sf::Color::White);
       instructions.setPosition({WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 2.0f + 100});
       window.draw(instructions);
       */
        // Draw buttons
        window.draw(playButton);
        window.draw(playButtonText);
        window.draw(exitButton);
        window.draw(exitButtonText);
    }
    window.display();
}


void Game::resetGame(){
    SCORE = 0;
    gameOver = false;
    snake.reset();
    food.respawn(snake, scene.getLandscape());
    elapsedTime = 0.0f;
    moveSnake.stop(); // Stop the music
}


void Game::run() {
    initializeMenu(); // Initialize the menu

    while (window.isOpen()) {
        if (inMenu) {
            handleMenuInput();
            renderMenu();
        } else {
            handleInput();
            if (!window.isOpen()) {
                break; // Exit the loop if the window is closed
            }
            update();
            render();
            sf::sleep(sf::milliseconds(16)); // ~60 FPS
            }
        
    }
}

