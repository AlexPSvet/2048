#include "Graphics.h"
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

bool Graphics::endAnimation(Case& caseObjet, int i, float xEnd, float yEnd) {
    MoveEvent& event = caseObjet.getEvents()[0];
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();

    if (jStart > jEnd || iStart > iEnd) {
        // Mouvement Gauche ou Mouvement Haut
        if ((event.getCurentX() < xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() < yEnd)) {
            caseObjet.removeAnimation(i);
            return true;
        }
    } else {
        // Mouvement Droite ou Mouvement Bas
        if ((event.getCurentX() > xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() > yEnd)) {
            caseObjet.removeAnimation(i);
            return true;
        }
    }
    return false;
}

void Graphics::drawAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float xMove, float yMove) {
    vector<MoveEvent>& events = caseObjet.getEvents();
    bool addAnimationDone = false;
    for (int i = 0; i < events.size(); i++) {
        MoveEvent& event = events[i];

        // Indices et valeurcontinue
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
            for (int k = 0; k < i; k++) {
                if (events[k].isAddAnimation()) {
                    continue;
                }
            }
            drawText(window, to_string(value), caseLenght, caseLenght, xEnd, yEnd, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);

            if (i != 0) {
                continue;
            } else if (!addAnimationDone) {
                addAnimationDone = true;
            } else {
                continue;
            }
        }

        if (addAnimationDone && i != 0) {
            continue;
        }

        if (endAnimation(caseObjet, i, xEnd, yEnd)) {
            continue;
        }

        event.setCurentX(event.getCurentX() + xMove);
        event.setCurentY(event.getCurentY() + yMove);

        drawText(window, to_string(value), caseLenght, caseLenght, event.getCurentX(), event.getCurentY(), caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
    }
}

void Graphics::checkAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float timeElapsed) {
    MoveEvent& event = caseObjet.getLastAnimation();
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();

    float movePixels = timeElapsed * ( 8 * unit * 60 );
    if (jStart < jEnd) {
        // Mouvement droite
        drawAnimation(window, caseObjet, caseLenght, margin, movePixels, 0);
    } else if (jStart > jEnd) {
        // Mouvement gauche
        drawAnimation(window, caseObjet, caseLenght, margin, - movePixels, 0);
    } else if (iStart < iEnd) {
        // Mouvement bas
        drawAnimation(window, caseObjet, caseLenght, margin, 0, movePixels);
    } else {
        // Mouvement haut
        drawAnimation(window, caseObjet, caseLenght, margin, 0, - movePixels);
    }
}

void Graphics::displayTable(RenderWindow& window, float timeElapsed) {
    Vector2 size = window.getSize();

    // Draw table background
    RectangleShape table(Vector2f(rectangleLenght, rectangleLenght));
    float outline = 5 * unit;
    table.setPosition(xRectangle, yRectangle);
    table.setFillColor(Color(113, 16, 66));
    table.setOutlineColor(Color(205, 54, 132));
    table.setOutlineThickness(outline);
    window.draw(table);

    // Draw animation
    int x = xRectangle + caseMargin;
    int y = yRectangle + caseMargin;
    for (Case& caseObjet : model.getCases()) {
        for (MoveEvent& event : caseObjet.getEvents()) {
            int iStart = event.getiStart();
            int jStart = event.getjStart();
            int iEnd = event.getiEnd();
            int jEnd = event.getjEnd();
            int yStart = y + iStart * ( caseMargin + caseLenght );
            int xStart = x + jStart * ( caseMargin + caseLenght );
            event.setStartX(xStart);
            event.setStartY(yStart);
            if (event.getCurentX() == -1) {
                event.setCurentX(xStart);
                event.setCurentY(yStart);
            }
        }
        if (caseObjet.getEvents().size() != 0) {
            checkAnimation(window, caseObjet, caseLenght, caseMargin, timeElapsed);
            if (!isCasesInAnimation() && isValidMovement) {
                model.setRandomElements(1);
                model.updateScore();
                isValidMovement = false;          
            }
        }
    }

    // Draw other cases
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            if (model.validCase(i, j)) {
                Case& caseObjet = model.getCase(i, j);
                int value = caseObjet.getValue();
                if (!caseObjet.hasAnimation()) {
                    int x_case = x + j * ( caseMargin + caseLenght );
                    int y_case = y + i * ( caseMargin + caseLenght );
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
        5 * unit, 5 * unit,
        8 * unit,
        Color( 204, 8, 224 ), Color( 99, 22, 89 ),
        Color( 111, 8, 97 ));
    // Best Score
    drawText(
        window, 
        "Best : " + to_string(model.getBestScore()), 
        160 * unit, 50 * unit, 
        20 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        5 * unit,
        Color( 236, 6, 132 ), Color( 139, 12, 105 ),
        Color( 255, 255, 255 ));
    // Score
    drawText(
        window, 
        "Score : " + to_string(model.getScore()), 
        160 * unit, 50 * unit, 
        220 * unit, 105 * unit, 
        1 * unit, 1 * unit,
        5 * unit,
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

void Graphics::updateGame(RenderWindow& window) {
    float elapsedTimeSec = clock.getElapsedTime().asSeconds();
    clock.restart();
    displayBackground(window);
    displayInfo(window);
    displayTable(window, elapsedTimeSec);
}

void Graphics::checkButtons(RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    float x = mousePosition.x;
    float y = mousePosition.y;
    if (model.getGameState() == GameState::End) {
        float textWidth = rectangleLenght * 0.8;
        float textHeight = rectangleLenght * 0.3;
        float xButtonStart = xRectangle + (rectangleLenght - textWidth) / 2;
        float yButtonStart = yRectangle + 2.5 * (rectangleLenght - textHeight) / 4;
        float xButtonEnd = xButtonStart + textWidth;
        float yButtonEnd = yButtonStart + textHeight;
        if (x >= xButtonStart && x <= xButtonEnd && y >= yButtonStart && y <= yButtonEnd) {
            model.restart();
            model.setGameState(GameState::Running);
        }
    }
}

void Graphics::drawRestartMenu(RenderWindow& window) {
    bool win = model.didPlayerWin();
    Vector2u size = window.getSize();
    sf::RectangleShape rectangle(sf::Vector2f(rectangleLenght, rectangleLenght));
    rectangle.setFillColor(sf::Color( 160, 5, 191, 100 ));
    rectangle.setPosition(xRectangle, yRectangle);
    window.draw(rectangle);
    float textWidth = rectangleLenght * 0.8;
    float textHeight = rectangleLenght * 0.3;
    float xrText = xRectangle + (rectangleLenght - textWidth) / 2;
    float yrText = (rectangleLenght - textHeight) / 4;
    Color fillColor = win ? Color( 47, 142, 11, 140 ) : Color( 231, 83, 24, 140 );
    Color outlineColor = Color( 255, 255, 255, 0 );
    Color textColor = win ? Color( 31, 218, 229, 255) : Color( 225, 25, 104, 255 );
    string text = win ? "T'as gagné!" : "T'as perdu...";
    drawText(window, text, textWidth, textHeight, xrText, yRectangle + yrText, 5 * unit, 7 * unit, 10 * unit, fillColor, outlineColor, textColor);
    drawText(window, "RECOMMENCER", textWidth, textHeight, xrText, yRectangle + 2.5 * yrText, 5 * unit, 7 * unit, 10 * unit, fillColor, outlineColor, textColor);
}

void Graphics::updateUnits(RenderWindow& window) {
    Vector2u windowSize = window.getSize();
    unit = windowSize.x / 400.0;
    rectangleLenght = 200 * unit;
    caseMargin = 8 * unit;
    caseLenght = 40 * unit;
    xRectangle = 100 * unit;
    yRectangle = 177.5 * unit;
}

void Graphics::displayGame() {
    RenderWindow window(VideoMode(600, 600), "2048");
    window.setFramerateLimit(240);
    backgroundText.loadFromFile("textures/background.png");
    backgroundText.setSmooth(true);
    gameFont.loadFromFile("fonts/prstart.ttf");
    
    updateUnits(window);

    isValidMovement = false;
    model.setGameState(GameState::Running);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (!isCasesInAnimation()) {
                        if (model.canMove()) {
                            if (checkMovement(event)) {
                                isValidMovement = true;
                            }
                        } else {
                            model.setGameState(GameState::End);
                        }
                    }
                    break;
                case Event::MouseButtonPressed:
                    checkButtons(window);
                    break;
            }
        }
        window.clear();
        switch (model.getGameState()) {
            case GameState::Running:
                updateGame(window);
                break;
            case GameState::End:
                updateGame(window);
                drawRestartMenu(window);
                break;
        }
        window.display();
    }
}

bool Graphics::isCasesInAnimation() {
    for (Case& caseObjet : model.getCases()) {
        if (caseObjet.getEvents().size() != 0) {
            return true;
        }
    }
    return false;
}