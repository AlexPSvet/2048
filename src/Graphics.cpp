#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
using namespace sf;

void Game::displayBackground(RenderWindow& window) {
    Sprite sprite;
    sprite.setTextureRect(IntRect(0, 0, 800, 1000));
    sprite.setTexture(backgroundText);
    window.draw(sprite);
}

Color Game::getColor(int caseNumber) {
    if (caseNumber == 2) {
        return Color( 204, 0, 255 );
    } else if (caseNumber == 4) {
        return Color( 135, 14, 166 );
    } else if (caseNumber == 8) {
        return Color( 189, 9, 147 );
    } else if (caseNumber == 16) {
        return Color( 118, 11, 93 );
    } else if (caseNumber == 32) {
        return Color( 86, 9, 160 );
    } else if (caseNumber == 64) {
        return Color( 16, 9, 160 );
    } else if (caseNumber == 128) {
        return Color( 20, 151, 206 );
    } else if (caseNumber == 256) {
        return Color( 20, 206, 108 );
    } else if (caseNumber == 512) {
        return Color( 172, 206, 20 );
    } else if (caseNumber == 1024) {
        return Color( 206, 100, 20 );
    } else if (caseNumber == 2048) {
        return Color( 227, 24, 4 );
    } else {
        return Color( 120, 13, 2 );
    } 
}

void Game::displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();
    float xRectangle = xUnit * 150;
    float yRectangle = yUnit * 120;
    float margin = 10.0;
    float xCase = xRectangle / 4 - margin * 1.25;
    float yCase = yRectangle / 4 - margin * 1.25;
    float x_i = xUnit * 25;
    float y_i = yUnit * 75;

    RectangleShape table(Vector2f(xRectangle, yRectangle));
    float outline = 20.0;
    y_i -= outline;
    table.setPosition(x_i, y_i);
    table.setFillColor(Color(113, 16, 66));
    table.setOutlineColor(Color(205, 54, 132));
    table.setOutlineThickness(outline);
    window.draw(table);

    for (int i = 0; i < plateau.size(); i++) {
        for (int j = 0; j < plateau[i].size(); j++) {
            if (plateau[i][j] != 0) {
                RectangleShape rect(Vector2f(xCase, yCase));
                int x = x_i + j * xCase + (j+1) * margin;
                int y = y_i + i * yCase + (i+1) * margin;
                rect.setPosition(Vector2f(x, y));
                rect.setFillColor(getColor(plateau[i][j]));
                window.draw(rect);

                Text text;
                text.setFont(gameFont);
                text.setString(std::to_string(plateau[i][j]));
                int amountCharacters = text.getString().getSize();
                text.setCharacterSize( (xCase - 10 * xUnit) / amountCharacters);
                text.setFillColor(Color( 244, 169, 255 ));
                int textSize = amountCharacters * text.getCharacterSize();
                float positionX = x + ( xCase - textSize ) / 2;
                float positionY = y + ( yCase - text.getCharacterSize() ) / 2;
                text.setPosition(Vector2f(positionX, positionY));
                window.draw(text);
            }
        }
    }
}

void Game::displayTitle(RenderWindow& window) {
    RectangleShape rectangle(Vector2f(xUnit * 100, yUnit * 25));
    rectangle.setFillColor(Color( 204, 8, 224 ));
    rectangle.setPosition(Vector2f(xUnit * 50, yUnit * 10));
    rectangle.setOutlineColor(Color( 99, 22, 89 ));
    rectangle.setOutlineThickness(15);
    window.draw(rectangle);

    Text text;
    text.setFont(gameFont);
    text.setString("2048");
    text.setCharacterSize(yUnit * 25 / 2);
    text.setFillColor(Color( 111, 8, 97 ));
    Vector2f position = rectangle.getPosition();
    Vector2f rectangleSize = rectangle.getSize();
    int textSize = text.getCharacterSize() * 4;
    float positionX = position.x + ( rectangleSize.x - textSize ) / 2;
    float positionY = position.y + ( rectangleSize.y - text.getCharacterSize() ) / 2;
    text.setPosition(Vector2f(positionX, positionY));
    window.draw(text);
}

void Game::displayScore(RenderWindow& window) {
    // Creates text score
    Text text;
    text.setFont(gameFont);
    text.setFillColor(Color( 111, 8, 97 ));
    int textCharSize = 25;
    text.setCharacterSize(textCharSize);
    text.setString("Score : " + to_string(score));
    int charAmount = text.getString().getSize();
    int textSize = textCharSize * charAmount;

    // Creates background depending on text width
    Vector2 size = window.getSize();
    float xSize = textSize + xUnit * 10;
    float xUnitsLeft = ( 200 - ( xSize ) / xUnit ) / 2;
    float ySize = yUnit * 15;
    RectangleShape background(Vector2f(xSize, ySize));
    background.setPosition(Vector2f(xUnitsLeft * xUnit, yUnit * 45));
    window.draw(background);

    // Displays text
    Vector2f positionBack = background.getPosition();
    float positionX = positionBack.x + ( 1 - textSize / xSize ) * xSize / 2;
    float positionY = positionBack.y + ( 1 - textCharSize / ySize ) * ySize / 2;
    text.setPosition(Vector2f(positionX, positionY));
    window.draw(text);
}

bool Game::checkMovement(Event event) {
    switch (event.key.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            if (canMoveUp()) {
                moveUp();
                return true;
            }
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            if (canMoveLeft()) {
                moveLeft();
                return true;
            }
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            if (canMoveDown()) {
                moveDown();
                return true;
            }
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            if (canMoveRight()) {
                moveRight();
                return true;
            }
    }
    return false;
}

void Game::displayWindow() {
    RenderWindow window(VideoMode(600, 600), "2048");
    window.setFramerateLimit(30);
    backgroundText.loadFromFile("textures/background.png");
    backgroundText.setSmooth(true);
    gameFont.loadFromFile("fonts/prstart.ttf");

    Vector2u windowSize = window.getSize();
    xUnit = windowSize.x / 200;
    yUnit = windowSize.y / 200;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (canMove()) {
                    if (checkMovement(event)) {
                        setRandomElements(1);
                    }
                } else {
                    clear();
                }
                break;
            }
        }
        window.clear();
        displayBackground(window);
        displayTitle(window);
        displayScore(window);
        displayTable(window);
        window.display();
    }
}