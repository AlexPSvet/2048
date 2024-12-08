#include "Graphics.h"
using namespace sf;

Graphics::Graphics(Model& model) : model(model) {}

/** 
 * Fonction pour dessiner une image de fond pour le jeu.
 * Elle crée un sprite pour lui appliquer la texture étant
 * l'image de fond du jeu.
 * 
 * @param window la fenetre dans laquelle dessiner.
 **/
void Graphics::displayBackground(RenderWindow& window) {
    Sprite sprite;
    Vector2u size = window.getSize();
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
    sprite.setTexture(backgroundText);
    window.draw(sprite);
}

/** 
 * Fonction pour obtenir la couleur d'une tuile.
 * 
 * @param tileNumber le numéro de la tuile.
 * @return la couleur de la tuile sur le plateau.
 **/
Color Graphics::getColor(int tileNumber) {
    if (tileNumber == 2) {
        return Color( 204, 0, 255 );
    } else if (tileNumber == 4) {
        return Color( 135, 14, 166 );
    } else if (tileNumber == 8) {
        return Color( 189, 9, 147 );
    } else if (tileNumber == 16) {
        return Color( 118, 11, 93 );
    } else if (tileNumber == 32) {
        return Color( 86, 9, 160 );
    } else if (tileNumber == 64) {
        return Color( 16, 9, 160 );
    } else if (tileNumber == 128) {
        return Color( 20, 151, 206 );
    } else if (tileNumber == 256) {
        return Color( 20, 206, 108 );
    } else if (tileNumber == 512) {
        return Color( 172, 206, 20 );
    } else if (tileNumber == 1024) {
        return Color( 206, 100, 20 );
    } else if (tileNumber == 2048) {
        return Color( 227, 24, 4 );
    } else {
        return Color( 120, 13, 2 );
    } 
}

/** 
 * Fonction pour dessiner dans une fentre un rectangle
 * de taille fixe et a l'intérieur du text d'une taille
 * qui dépend de la taille du rectangle.
 * 
 * @param window la fentre dans laquelle dessiner la figure.
 * @param text le texte à afficher dans le rectangle.
 * @param width la largeur du rectangle.
 * @param height la longueur du rectangle.
 * @param x la coordonnée x du rectangle.
 * @param y la coordonnée y du rectangle.
 * @param marginWidth la largeur de la marge.
 * @param marginHeight la hauteur de la marge.
 * @param outline les pixels de bordure du rectangle.
 * @param fillColor la couleur à l'intérieur du rectangle.
 * @param outlineColor la couleur de la bordure du rectangle.
 * @param textColor la couleur du texte à l'intérieur du rectangle.
 **/
void Graphics::drawText (
    RenderWindow& window, 
    std::string text, 
    float width, float height, 
    int x, int y, 
    float marginWidth, float marginHeight,
    float outline,
    Color fillColor, Color outlineColor, Color textColor) 
{
    // Créer le rectangle de taille width x height.
    float widthRect = width - 2 * outline;
    float heightRect = height - 2 * outline;
    RectangleShape rect(Vector2f(widthRect, heightRect));
    rect.setPosition(x + outline, y + outline);
    rect.setFillColor(fillColor);
    rect.setOutlineColor(outlineColor);
    rect.setOutlineThickness(outline);
    window.draw(rect);
    // Désinner le texte en fonction de la taille de l'image.
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

/** 
 * Fonction pour vérifier si une animation dans le plateau est términée.
 * 
 * @param tile la case avec une animation à vérifier.
 * @param i l'indice de l'événement à vérifier dans la liste des événements
 * de la case.
 * @param xEnd la coordonnée de fin de mouvement pour x.
 * @param yEnd la coordonnées de fin de mouvement pour y.
 * @return true si le mouvement est fini, false sinon.
 **/
bool Graphics::endAnimation(Tile& tile, int i, float xEnd, float yEnd) {
    MoveEvent& event = tile.getEvents()[0];
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();

    if (jStart > jEnd || iStart > iEnd) {
        // Mouvement Gauche ou Mouvement Haut
        if ((event.getCurentX() < xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() < yEnd)) {
            tile.removeAnimation(i);
            return true;
        }
    } else {
        // Mouvement Droite ou Mouvement Bas
        if ((event.getCurentX() > xEnd && yEnd == event.getStartY()) || (xEnd == event.getStartX() && event.getCurentY() > yEnd)) {
            tile.removeAnimation(i);
            return true;
        }
    }
    return false;
}

/** 
 * Fonction pour dessiner les animations de mouvement pour une tuile spécifique.
 * On considère que deux tuiles rajoutées représentent en soi la meme 
 * tuile avec leurs animations rajoutées.
 * 
 * @param window la fenetre dans laquelle dessiner l'animation.
 * @param tile la tuile laquelle il faut dessiner en premier.
 * @param xMove la composante en x à rajouter dans la position de la tuile (inclus valeurs négatifs).
 * @param yMove la composante en y à rajouter dans la position de la tuile (inclus valeurs négatifs).
 **/
void Graphics::drawAnimation(RenderWindow& window, Tile& tile, float xMove, float yMove) {
    vector<MoveEvent>& events = tile.getEvents();
    for (int i = 0; i < events.size(); i++) {
        MoveEvent& event = events[i];

        // Indices et valeur de la tuile
        int iStart = event.getiStart();
        int jStart = event.getjStart();
        int iEnd = event.getiEnd();
        int jEnd = event.getjEnd();
        int value = event.getValue();
        // Calcul de coordonnées finales pour une animation.
        int signeX = xMove == 0 ? 0 : xMove / abs(xMove);
        int signeY = yMove == 0 ? 0 : yMove / abs(yMove);
        float xEnd = event.getStartX() + signeX * ( caseMargin + caseLenght ) * ( abs(event.getjStart() - event.getjEnd()) );
        float yEnd = event.getStartY() + signeY * ( caseMargin + caseLenght ) * ( abs(event.getiEnd() - event.getiStart()) );

        if (endAnimation(tile, i, xEnd, yEnd)) {
            break;
        }

        // Pour dessiner la case rajouté lors de son addition, on doit la dessiner lorsqu'elle
        // a finit de se déplacer, c'est-à-dire que si un mouvement c'est produit à 2 événements,
        // alors il ne faut pas la dessiner.
        // Les animations elles se dessinent une fois toutes les autres animations de mouvements términées.
        if (event.isAddAnimation()) {
            if (i - 2 >= 0) {
                continue;
            }

            drawText(window, to_string(value), caseLenght, caseLenght, xEnd, yEnd, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);

            if (i != 0) {
                continue;
            }
        }

        // Rajoute les composantes en x,y et dessine la case dans sa nouvelle position.
        event.setCurentX(event.getCurentX() + xMove);
        event.setCurentY(event.getCurentY() + yMove);

        drawText(window, to_string(value), caseLenght, caseLenght, event.getCurentX(), event.getCurentY(), caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
    }
}

/** 
 * Fonction qui vérifie selon le mouvement à effectuer quel composante en x,y
 * ajouter ou diminuer pour faire l'animation.
 * 
 * @param window la fenetre dans laquelle dessiner l'animation.
 * @param tile la tuile laquelle il faut dessiner en premier.
 * @param timeElapsed le temps passé pour dessiner l'image précédente du jeu.
 **/
void Graphics::checkAnimation(RenderWindow& window, Tile& tile, float timeElapsed) {
    // On obtient le premier mouvement pour savoir dans quel direction
    // le mouvement s'effectue.
    MoveEvent& event = tile.getFirstAnimation();
    float iStart = event.getiStart();
    float jStart = event.getjStart();
    float iEnd = event.getiEnd();
    float jEnd = event.getjEnd();
    // Produit en croix pour calculer le mouvement à faire
    // selon le temps mis pour produire une image.
    float movePixels = timeElapsed * ( 10 * unit * 60 );

    if (jStart < jEnd) {
        // Mouvement droite
        drawAnimation(window, tile, movePixels, 0);
    } else if (jStart > jEnd) {
        // Mouvement gauche
        drawAnimation(window, tile, - movePixels, 0);
    } else if (iStart < iEnd) {
        // Mouvement bas
        drawAnimation(window, tile, 0, movePixels);
    } else {
        // Mouvement haut
        drawAnimation(window, tile, 0, - movePixels);
    }
}

/** 
 * Fonction pour dessiner toutes les animations des cases.
 * 
 * @param window la fenetre dans laquelle dessiner l'animation.
 * @param timeElapsed le temps passé pour dessiner l'image précédente du jeu.
 **/
void Graphics::drawAnimations(RenderWindow& window, float timeElapsed) {
    int x = xRectangle + caseMargin;
    int y = yRectangle + caseMargin;
    bool noMoreEvents = false;
    for (Tile& tile : model.getTiles()) {
        for (MoveEvent& event : tile.getEvents()) {
            int iStart = event.getiStart();
            int jStart = event.getjStart();
            int iEnd = event.getiEnd();
            int jEnd = event.getjEnd();
            // Calcul des coordonnées initiales de la case.
            int yStart = y + iStart * ( caseMargin + caseLenght );
            int xStart = x + jStart * ( caseMargin + caseLenght );
            event.setStartX(xStart);
            event.setStartY(yStart);
            // Si les valeurs ne sont pas initialisées, les mettre à jour.
            if (event.getCurentX() == -1) {
                event.setCurentX(xStart);
                event.setCurentY(yStart);
            }
        }
        if (tile.hasAnimation()) {
            checkAnimation(window, tile, timeElapsed);
        }
    }
    // Vérifie si plus de mouvements à dessiner, pour ainsi
    // dessinner la nouvelle tuile et mettre à jour le score.
    if (!isCasesInAnimation() && isValidMovement) {
        model.setRandomElements(1);
        model.updateScore();
        isValidMovement = false;          
    }
}

/** 
 * Fonction pour dessiner le plateau avec toutes les cases qui ne sont
 * pas en animation.
 * 
 * @param window la fenetre dans laquelle dessiner.
 **/
void Graphics::displayTable(RenderWindow& window) {
    Vector2 size = window.getSize();

    // Dessiner le fond du plateau
    RectangleShape table(Vector2f(rectangleLenght, rectangleLenght));
    float outline = 5 * unit;
    table.setPosition(xRectangle, yRectangle);
    table.setFillColor(Color(113, 16, 66));
    table.setOutlineColor(Color(205, 54, 132));
    table.setOutlineThickness(outline);
    window.draw(table);

    // Dessiner les tuiles
    int x = xRectangle + caseMargin;
    int y = yRectangle + caseMargin;
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            if (model.validTile(i, j)) {
                Tile& tile = model.getTile(i, j);
                int value = tile.getValue();
                if (!tile.hasAnimation()) {
                    int x_case = x + j * ( caseMargin + caseLenght );
                    int y_case = y + i * ( caseMargin + caseLenght );
                    drawText(window, to_string(value), caseLenght, caseLenght, x_case, y_case, caseLenght * 0.1, caseLenght * 0.1, unit * 2, getColor(value), Color::Magenta, Color::White);
                }
            }
        }
    }
}

/** 
 * Fonction pour dessiner toutes les informations du jeu
 * dans la fenetre : le titre du jeu, le meilleur score
 * et le score actuel du jeu.
 * 
 * @param window la fenetre dans laquelle dessiner.
 **/
void Graphics::displayInfo(RenderWindow& window) {
    // Afficher le titre du jeu.
    drawText(
        window, 
        "2048", 
        100 * unit, 70 * unit, 
        150 * unit, 22.5 * unit, 
        5 * unit, 5 * unit,
        8 * unit,
        Color( 204, 8, 224 ), Color( 99, 22, 89 ),
        Color( 111, 8, 97 ));
    // Afficher le meilleur score de toutes les jeus.
    drawText(
        window, 
        "Meilleur : " + to_string(model.getBestScore()), 
        160 * unit, 50 * unit, 
        20 * unit, 105 * unit, 
        2 * unit, 2 * unit,
        5 * unit,
        Color( 236, 6, 132 ), Color( 139, 12, 105 ),
        Color( 255, 255, 255 ));
    // Afficher le score actuel du jeu.
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

/** 
 * Vérifier si le mouvement en question est valide, 
 * c'est-à-dire si un mouvement est réalisée.
 * 
 * @param window la fenetre dans laquelle dessiner.
 * @return true si un mouvement se réalise, false sinon.
 **/
bool Graphics::checkMovement(Event event) {
    switch (event.key.code) {
        case Keyboard::W:
        case Keyboard::Up:
            // Mouvement haut
            if (model.canMoveUp()) {
                model.moveUp();
                return true;
            }
            break;
        case Keyboard::A:
        case Keyboard::Left:
            // Mouvement gauche
            if (model.canMoveLeft()) {
                model.moveLeft();
                return true;
            }
            break;
        case Keyboard::S:
        case Keyboard::Down:
            // Mouvement bas
            if (model.canMoveDown()) {
                model.moveDown();
                return true;
            }
            break;
        case Keyboard::D:
        case Keyboard::Right:
            // Mouvement droite
            if (model.canMoveRight()) {
                model.moveRight();
                return true;
            }
    }
    return false;
}

/** 
 * Fonction pour dessiner tout le jeu, et vérifie
 * le temps mis par l'ordinateur pour afficher l'image.
 * 
 * @param window la fenetre dans laquelle dessiner.
 **/
void Graphics::updateGame(RenderWindow& window) {
    float elapsedTimeSec = clock.getElapsedTime().asSeconds();
    clock.restart();
    displayBackground(window);
    displayInfo(window);
    displayTable(window);
    if (isCasesInAnimation()) drawAnimations(window, elapsedTimeSec);
}

/** 
 * Fonction pour vérifier si des bouton sont appuyées.
 * 
 * @param window la fenetre dans laquelle vérifier.
 **/
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
    rectangle.setFillColor(sf::Color( 160, 5, 191, 175 ));
    rectangle.setPosition(xRectangle, yRectangle);
    window.draw(rectangle);
    float textWidth = rectangleLenght * 0.8;
    float textHeight = rectangleLenght * 0.3;
    float xrText = xRectangle + (rectangleLenght - textWidth) / 2;
    float yrText = (rectangleLenght - textHeight) / 4;
    Color fillColor = win ? Color( 47, 142, 11, 255 ) : Color( 231, 83, 24, 255 );
    Color outlineColor = Color( 255, 255, 255, 255 );
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
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
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
    for (Tile& tile : model.getTiles()) {
        if (tile.getEvents().size() != 0) {
            return true;
        }
    }
    return false;
}