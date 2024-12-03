#include "Graphics.h"
#include <iostream>
#include <vector>
using namespace sf;

Graphics::Graphics(Model& model) : model(model) {}

void Graphics::displayBackground(RenderWindow& window) {
    Sprite sprite;
    sprite.setTextureRect(IntRect(0, 0, 800, 800));
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

bool Graphics::endAnimation(int k, float xEnd, float yEnd) {
    vector<MoveLine>& movements = model.getMovements();
    MoveLine& line = movements[k];
    MoveEvent& event = line.get();
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();

    if (jStart > jEnd || iStart > iEnd) {
        // Mouvement Gauche ou Mouvement Haut
        if ((event.getCurentX() < xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() < yEnd)) {
            return true;
        }
    } else {
        // Mouvement Droite ou Mouvement Bas
        if ((event.getCurentX() > xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() > yEnd)) {
            return true;
        }
    }
    return false;
}

void Graphics::drawAnimation(RenderWindow& window, int k, float caseLenght, float margin, float xMove, float yMove) {
    MoveLine& line = model.getMovements()[k];
    for (int l = 0; l < line.getSize(); l++) {
        MoveEvent& event = line.get(l);

        // Indices et valeur
        int iStart = event.getiStart();
        int jStart = event.getjStart();
        int iEnd = event.getiEnd();
        int jEnd = event.getjEnd();
        int value = event.getValue();
        // Calcul coordonnées finales
        int signeX = xMove == 0 ? 0 : xMove / abs(xMove);
        int signeY = yMove == 0 ? 0 : yMove / abs(yMove);
        float xEnd = event.getStartX() + signeX * ( margin + caseLenght ) * ( abs(event.getjStart() - event.getjEnd()) );
        float yEnd = event.getStartY() + signeY * ( margin + caseLenght ) * ( abs(event.getiEnd() - event.getiStart()) );

        if (event.isAddAnimation()) {
            drawText(window, to_string(value), caseLenght, caseLenght, xEnd, yEnd, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
        }

        if (l != line.getPosition()) {
            continue;
        }

        event.setCurentX(event.getCurentX() + xMove);
        event.setCurentY(event.getCurentY() + yMove);

        if (endAnimation(k, xEnd, yEnd)) {
            if (!line.next()) {
                model.removeMoveLine(k);
                break;
            }
            continue;
        }

        drawText(window, to_string(value), caseLenght, caseLenght, event.getCurentX(), event.getCurentY(), caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
    }
}

void Graphics::checkAnimation(RenderWindow& window, int k, float caseLenght, float margin, float timeElapsed) {
    MoveEvent& event = model.getMovements()[k].get();
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();

    float movePixels = 2 * unit;
    if (jStart < jEnd) {
        // Mouvement droite
        drawAnimation(window, k, caseLenght, margin, movePixels, 0);
    } else if (jStart > jEnd) {
        // Mouvement gauche
        drawAnimation(window, k, caseLenght, margin, - movePixels, 0);
    } else if (iStart < iEnd) {
        // Mouvement bas
        drawAnimation(window, k, caseLenght, margin, 0, movePixels);
    } else {
        // Mouvement haut
        drawAnimation(window, k, caseLenght, margin, 0, - movePixels);
    }
}

void Graphics::displayTable(RenderWindow& window, float timeElapsed) {
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

    // Draw cases in animation
    int x = x_i + margin;
    int y = y_i + margin;
    vector<MoveLine>& movements = model.getMovements();
    for (int k = 0; k < movements.size(); k++) {
        MoveLine& line = movements[k];
        for (int l = 0; l < line.getSize(); l++) {
            MoveEvent& event = line.get(l);
            int iStart = event.getiStart();
            int jStart = event.getjStart();
            int yStart = y + iStart * ( margin + caseLenght );
            int xStart = x + jStart * ( margin + caseLenght );
            event.setStartX(xStart);
            event.setStartY(yStart);
            if (event.getCurentX() == -1) {
                event.setCurentX(xStart);
                event.setCurentY(yStart);
            }
        }
        checkAnimation(window, k, caseLenght, margin, timeElapsed);
    }

    // Draw other cases
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            if (model.validCase(i, j)) {
                Case& caseObjet = model.getCase(i, j);
                if (!isCaseInAnimation(caseObjet)) {
                    int value = caseObjet.getValue();
                    int x_case = x + j * ( margin + caseLenght );
                    int y_case = y + i * ( margin + caseLenght );
                    drawText(window, to_string(value), caseLenght, caseLenght, x_case, y_case, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
                }
                if (!isCasesInAnimation()) {
                    if (isValidMovement) {
                        model.setRandomElements(1);
                        if (!model.canMove()) {
                            // Loose / Win screen
                            return;
                        }
                        isValidMovement = false;
                    }
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
        10 * unit,
        Color( 204, 8, 224 ), Color( 99, 22, 89 ),
        Color( 111, 8, 97 ));
    // Best Score
    drawText(
        window, 
        "Best : " + to_string(model.getBestScore()), 
        160 * unit, 50 * unit, 
        20 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        15 * unit,
        Color( 236, 6, 132 ), Color( 139, 12, 105 ),
        Color( 255, 255, 255 ));
    // Score
    drawText(
        window, 
        "Score : " + to_string(model.getScore()), 
        160 * unit, 50 * unit, 
        220 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        15 * unit,
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

void Graphics::updateScreen(RenderWindow& window) {
    float elapsedTimeSec = clock.getElapsedTime().asSeconds();
    clock.restart();
    window.clear();
    displayBackground(window);
    displayInfo(window);
    displayTable(window, elapsedTimeSec);
    window.display();
}

void Graphics::displayGame() {
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
                    if (!isCasesInAnimation()) {
                        if (checkMovement(event)) {
                            model.updateScore();
                            isValidMovement = true;
                        }
                    }
                    break;
            }
        }
        updateScreen(window);
    }
}

bool Graphics::isCasesInAnimation() {
    for (Case& caseObjet : model.getCases()) {
        if (isCaseInAnimation(caseObjet)) {
            return true;
        }
    }
    return false;
}

bool Graphics::isCaseInAnimation(Case& caseObjet) {
    int i = caseObjet.getIndexI();
    int j = caseObjet.getIndexJ();
    vector<MoveLine>& movements = model.getMovements();
    for (int k = 0; k < movements.size(); k++) {
        if (movements[k].isCaseInAnimation(caseObjet)) {
            return true;
        }
    }
    return false;
}