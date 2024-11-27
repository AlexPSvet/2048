#include "Graphics.h"
#include <iostream>
using namespace sf;

Graphics::Graphics(Model& model) : model(model) {
    this->model = model;
}

void Graphics::displayBackground(RenderWindow& window) {
    Sprite sprite;
    sprite.setTextureRect(IntRect(0, 0, 800, 1000));
    sprite.setTexture(backgroundText);
    window.draw(sprite);
}

Color Graphics::getColor(int caseNumber) {
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

void Graphics::drawText (
    RenderWindow& window, 
    std::string text, 
    float width, float height, 
    int x, int y, 
    float marginWidth, float marginHeight,
    float outline,
    Color fillColor, Color outlineColor, Color textColor) 
{
    // Créer le rectangle de taille width x height
    float widthRect = width - 2 * outline;
    float heightRect = height - 2 * outline;
    RectangleShape rect(Vector2f(widthRect, heightRect));
    rect.setPosition(x + outline, y + outline);
    rect.setFillColor(fillColor);
    rect.setOutlineColor(outlineColor);
    rect.setOutlineThickness(outline);
    window.draw(rect);
    // Désinner le texte
    Text textObject;
    textObject.setFont(gameFont);
    textObject.setString(text);
    int amountChar = text.size();
    float widthText = widthRect - 2 * marginWidth;
    float charSizeHeight = heightRect - 2 * marginHeight;
    float charSizeWidth = widthText / amountChar;
    textObject.setCharacterSize(charSizeWidth > charSizeHeight ? charSizeHeight : charSizeWidth);
    float positionX = rect.getPosition().x + ( widthRect - textObject.getCharacterSize() * amountChar ) / 2;
    float positionY = rect.getPosition().y + ( heightRect - textObject.getCharacterSize() ) / 2;
    textObject.setPosition(positionX, positionY);
    window.draw(textObject);
}

void Graphics::drawAnimLeftDown(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float xRemove, float yRemove) {
    vector<MoveEvent>& events = caseObjet.getEvents();
    MoveEvent event = events[0];
    for (int i = 0; i < events.size(); i++) {
        MoveEvent& event = events[i];
        if (event.isAddAnimation() && (i - 1 >= 0 && !events[i-1].isAddAnimation())) {
            continue;
        }
        int value = event.getValue();

        float xEnd = event.getStartX() - ( margin + caseLenght ) * ( event.getjStart() - event.getjEnd() );
        float yEnd = event.getStartY() - ( margin + caseLenght ) * ( event.getiStart() - event.getiEnd() );

        if (event.isAddAnimation()) {
            drawText(window, to_string(value), caseLenght, caseLenght, xEnd, yEnd, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
        }

        event.setCurentX(event.getCurentX() - xRemove);
        event.setCurentY(event.getCurentY() - yRemove);
        drawText(window, to_string(value), caseLenght, caseLenght, event.getCurentX(), event.getCurentY(), caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
        if ((event.getCurentX() < xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() < yEnd)) {
            caseObjet.removeLastAnimation();
        }
    }
}

void Graphics::drawAnimRightUp(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float xAdd, float yAdd) {
    // Draw static event cases.
    vector<MoveEvent>& events = caseObjet.getEvents();
    for (int i = 0; i < events.size(); i++) {
        MoveEvent& event = events[i];
        if (event.isAddAnimation() && (i - 1 >= 0 && !events[i-1].isAddAnimation())) {
            continue;
        }
        int value = event.getValue();

        float xEnd = event.getStartX() + ( margin + caseLenght ) * ( event.getjEnd() - event.getjStart() );
        float yEnd = event.getStartY() + ( margin + caseLenght ) * ( event.getiEnd() - event.getiStart() );

        if (event.isAddAnimation()) {
            drawText(window, to_string(value), caseLenght, caseLenght, xEnd, yEnd, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
        }

        event.setCurentX(event.getCurentX() + xAdd);
        event.setCurentY(event.getCurentY() + yAdd);    
        drawText(window, to_string(value), caseLenght, caseLenght, event.getCurentX(), event.getCurentY(), caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
        if ((event.getCurentX() > xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() > yEnd)) {
            caseObjet.removeLastAnimation();
        }
    }
}

void Graphics::drawAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin) {
    MoveEvent& event = caseObjet.getLastAnimation();
    int iStart = event.getiStart();
    int jStart = event.getjStart();
    int iEnd = event.getiEnd();
    int jEnd = event.getjEnd();
    if (jStart > jEnd) {
        // Mouvement gauche
        drawAnimLeftDown(window, caseObjet, caseLenght, margin, 20, 0);
    } else if (jStart < jEnd) {
        // Mouvement droite
        drawAnimRightUp(window, caseObjet, caseLenght, margin, 20, 0);
    } else if (iStart > iEnd) {
        // Mouvement bas
        drawAnimLeftDown(window, caseObjet, caseLenght, margin, 0, 20);
    } else if (iStart < iEnd) {
        // Mouvement haut
        drawAnimRightUp(window, caseObjet, caseLenght, margin, 0, 20);
    }
}

void Graphics::displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();
    float squareLenght = 200 * unit;
    float margin = 8 * unit;
    float caseLenght = 40 * unit;
    float x_i = 100 * unit;
    float y_i = 177.5 * unit;

    // Draw table background
    RectangleShape table(Vector2f(squareLenght, squareLenght));
    float outline = 5 * unit;
    table.setPosition(x_i, y_i);
    table.setFillColor(Color(113, 16, 66));
    table.setOutlineColor(Color(205, 54, 132));
    table.setOutlineThickness(outline);
    window.draw(table);

    // Draw cases
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            if (model.validCase(i, j)) {
                Case& caseObjet = model.getCase(i, j);
                int value = caseObjet.getValue();
                int x = x_i + margin;
                int y = y_i + margin;
                if (caseObjet.hasAnimation()) {
                    for (MoveEvent& event : caseObjet.getEvents()) {
                        int iStart = event.getiStart();
                        int jStart = event.getjStart();
                        int yStart = y + iStart * ( margin + caseLenght );
                        int xStart = x + jStart * ( margin + caseLenght );
                        event.setStartX(xStart);
                        event.setStartY(yStart);
                        if (event.getCurentX() == 0) {
                            event.setCurentX(xStart);
                        }
                        if (event.getCurentY() == 0) {
                            event.setCurentY(yStart);
                        }
                    }
                    drawAnimation(window, caseObjet, caseLenght, margin);
                    if (!model.isCasesInAnimation()) {
                        if (isValidMovement) {
                            model.setRandomElements(1);
                            isValidMovement = false;
                        }
                    }
                } else {
                    int x_case = x + j * ( margin + caseLenght );
                    int y_case = y + i * ( margin + caseLenght );
                    drawText(window, to_string(value), caseLenght, caseLenght, x_case, y_case, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
                }
            }
        }
    }
}

void Graphics::displayInfo(RenderWindow& window) {
    // Title
    drawText(
        window, 
        "2048", 
        100 * unit, 70 * unit, 
        150 * unit, 22.5 * unit, 
        5 * unit, 7 * unit,
        3 * unit,
        Color( 204, 8, 224 ), Color( 99, 22, 89 ),
        Color( 111, 8, 97 ));
    // Best Score
    drawText(
        window, 
        "Best Score : 0", 
        160 * unit, 50 * unit, 
        20 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        2 * unit,
        Color( 236, 6, 132 ), Color( 139, 12, 105 ),
        Color( 255, 255, 255 ));
    // Score
    drawText(
        window, 
        "Score : " + to_string(model.getScore()), 
        160 * unit, 50 * unit, 
        220 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        2 * unit,
        Color( 213, 183, 227 ), Color( 141, 98, 161 ),
        Color( 255, 255, 255 ));
}

bool Graphics::checkMovement(Event event) {
    switch (event.key.code) {
        case Keyboard::W:
        case Keyboard::Up:
            if (model.canMoveUp()) {
                model.moveUp();
                return true;
            }
            break;
        case Keyboard::A:
        case Keyboard::Left:
            if (model.canMoveLeft()) {
                model.moveLeft();
                return true;
            }
            break;
        case Keyboard::S:
        case Keyboard::Down:
            if (model.canMoveDown()) {
                model.moveDown();
                return true;
            }
            break;
        case Keyboard::D:
        case Keyboard::Right:
            if (model.canMoveRight()) {
                model.moveRight();
                return true;
            }
    }
    return false;
}

void Graphics::displayWindow() {
    RenderWindow window(VideoMode(600, 600), "2048");
    window.setFramerateLimit(60);
    backgroundText.loadFromFile("textures/background.png");
    backgroundText.setSmooth(true);
    gameFont.loadFromFile("fonts/prstart.ttf");

    Vector2u windowSize = window.getSize();
    unit = windowSize.x / 400.0;

    isValidMovement = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (!model.isCasesInAnimation()) {
                        if (model.canMove()) {
                            if (checkMovement(event)) {
                                isValidMovement = true;
                            }
                        } else {
                            model.clear();
                        }
                    }
                    break;
            }
        }
        window.clear();
        displayBackground(window);
        displayInfo(window);
        displayTable(window);
        window.display();
    }
}