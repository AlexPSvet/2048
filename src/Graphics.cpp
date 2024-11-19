#include <SFML/Graphics.hpp> //Inclut la Bibliotheque SFML permettant de manipuler des éléments graphiques
#include "Game.h"
#include <iostream>
using namespace sf;

void Game::displayBackground(RenderWindow& window) {
    Sprite sprite;
    sprite.setTextureRect(IntRect(0, 0, 800, 1000)); //IMage rectangulaire de 800x1000 pixels
    sprite.setTexture(backgroundText); //backgroundText est une texture préalablement chargée
    window.draw(sprite);
}

void Game::displayTitle(RenderWindow& window) {
    int x = window.getSize().x;

    RectangleShape rectangle(Vector2f(350, 112.5)); //Création d'un rectangle pour le fond du titre
    rectangle.setFillColor(Color( 204, 8, 224 )); //Couleur du Rectangle
    rectangle.setPosition(Vector2f(x/3 - 40, 132.5));
    rectangle.setOutlineColor(Color( 99, 22, 89 )); //Couleur de Contour du Rectangle
    rectangle.setOutlineThickness(15);
    window.draw(rectangle); //Desinne le rectangle sur la fenetre

    Text text;
    text.setFont(gameFont);
    text.setString("2048");
    float size = rectangle.getSize().y;
    text.setCharacterSize(size / 2);
    text.setFillColor(Color( 111, 8, 97 ));
    Vector2f position = rectangle.getPosition();
    text.setPosition(Vector2f(position.x + size / 2, position.y + size / 4));
    window.draw(text);
}

void Game::displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();
    float xRectangle = 5 * size.x / 7;
    float yRectangle = size.y * 0.65;
    float margin = 10.0;
    float xCase = xRectangle / 4 - margin * 1.25;
    float yCase = yRectangle / 4 - margin * 1.25;
    float x_i = size.x / 7;
    float y_i = size.y * 0.35;

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
                rect.setFillColor(Color(234, 105, 172));
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
        displayTable(window);
        window.display();
    }
}