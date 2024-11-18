#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <iostream>
using namespace std;

void openGame() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "2048");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                cout << "Closing window." << endl;
                window.close();
                break;
            case sf::Event::MouseMoved:
                cout << "x: " + event.mouseMove.x << endl;
                cout << "y: " + event.mouseMove.y << endl;
                break;
            case sf::Event::MouseEntered:
                cout << "Mouse entered the window." << endl;
                break;
            case sf::Event::MouseLeft:
                cout << "Mouse left the window." << endl;
                break;
            }
        }
        window.clear();
        window.display();
    }
}