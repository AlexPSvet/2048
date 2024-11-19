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

void Game::displayTitle(RenderWindow& window) {
    int x = window.getSize().x;

    RectangleShape rectangle(Vector2f(350, 112.5));
    rectangle.setFillColor(Color( 204, 8, 224 ));
    rectangle.setPosition(Vector2f(x/3 - 40, 132.5));
    rectangle.setOutlineColor(Color( 99, 22, 89 ));
    rectangle.setOutlineThickness(15);
    window.draw(rectangle);

    Text text;
    text.setFont(gameFont);
    text.setString("2048");
    text.setCharacterSize(70);
    text.setFillColor(Color( 111, 8, 97 ));
    text.setPosition(Vector2f(x/3, 150));
    window.draw(text);
}

void Game::displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();
    float xCase = (5 * size.x / 7) / 4;
    float yCase = (size.y * 0.65) / 4;
    float x_i = size.x / 7;
    float y_i = size.y * 0.35;
    for (int i = 0; i < plateau.size(); i++) {
        for (int j = 0; j < plateau[i].size(); j++) {
            if (plateau[i][j] != 0) {
                RectangleShape rect(Vector2f(xCase, yCase));
                int x = x_i + j * xCase;
                int y = y_i + i * yCase;
                rect.setPosition(Vector2f(x, y));
                rect.setFillColor(Color(234, 105, 172));
                rect.setOutlineColor(Color(155, 7, 134));
                rect.setOutlineThickness(10);
                window.draw(rect);

                Text text;
                text.setFont(gameFont);
                text.setString(std::to_string(plateau[i][j]));
                text.setCharacterSize(25);
                text.setFillColor(Color( 111, 8, 97 ));
                text.setPosition(Vector2f(x, y));
                window.draw(text);
            }
        }
    }
}

bool Game::checkMovement(Event event) {
    switch (event.key.code) {
        case sf::Keyboard::W:
            if (canMoveUp()) {
                moveUp();
                return true;
            }
            break;
        case sf::Keyboard::A:
            if (canMoveLeft()) {
                moveLeft();
                return true;
            }
            break;
        case sf::Keyboard::S:
            if (canMoveDown()) {
                moveDown();
                return true;
            }
            break;
        case sf::Keyboard::D:
            if (canMoveRight()) {
                moveRight();
                return true;
            }
    }
    return false;
}

void Game::displayWindow() {
    RenderWindow window(VideoMode(800, 1000), "2048");
    window.setFramerateLimit(60);
    backgroundText.loadFromFile("textures/background.png");
    backgroundText.setSmooth(true);
    gameFont.loadFromFile("fonts/prstart.ttf");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (checkMovement(event)) {
                    setRandomElements(1);
                }
                break;
            }
        }
        window.clear();
        displayBackground(window);
        displayTitle(window);
        displayTable(window);
        window.display();
    }
}