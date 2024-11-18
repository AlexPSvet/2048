#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <iostream>
using namespace sf;

void displayBackground(RenderWindow& window) {
    Texture texture;
    texture.setSmooth(true);
    texture.loadFromFile("textures/background.png");
    Sprite sprite;
    sprite.setTextureRect(IntRect(0, 0, 800, 1000));
    sprite.setTexture(texture);
    window.draw(sprite);
}

void displayTitle(RenderWindow& window) {
    int x = window.getSize().x;

    sf::RectangleShape rectangle(Vector2f(350, 112.5));
    rectangle.setFillColor(Color( 204, 8, 224 ));
    rectangle.setPosition(Vector2f(x/3 - 40, 132.5));
    rectangle.setOutlineColor(Color( 99, 22, 89 ));
    rectangle.setOutlineThickness(15);
    window.draw(rectangle);

    Font font;
    font.loadFromFile("fonts/prstart.ttf");
    Text text;
    text.setFont(font);
    text.setString("2048");
    text.setCharacterSize(70);
    text.setFillColor(Color( 111, 8, 97 ));
    text.setPosition(Vector2f(x/3, 150));
    window.draw(text);
}

void displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();
    sf::RectangleShape rectangle(Vector2f(5*size.x/7, size.y - size.y * 0.45));
    rectangle.setFillColor(Color(109, 32, 117));
    rectangle.setOutlineColor(Color( 155, 7, 134 ));
    rectangle.setOutlineThickness(12);
    rectangle.setPosition(Vector2f(size.x/7, size.y * 0.35));
    window.draw(rectangle);

    Vector2 rectSize = rectangle.getSize();
    float xCase = rectSize.x / 4;
    float yCase = rectSize.y / 4;
    Vector2f rectPos = rectangle.getPosition();
    float x_i = rectPos.x;
    float y_i = rectPos.y;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sf::RectangleShape rect(Vector2f(xCase, yCase));
            rect.setPosition(Vector2f(x_i, y_i));
            rect.setFillColor(Color(234, 105, 172));
            window.draw(rect);
            x_i += xCase;
        }
        x_i = rectPos.x;
        y_i += yCase;
    }
}

void displayWindow() {
    RenderWindow window(VideoMode(800, 1000), "2048");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseMoved:
                
                break;
            case Event::MouseEntered:
                
                break;
            case Event::MouseLeft:
                
                break;
            case Event::Resized:
                // Cancel resize
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