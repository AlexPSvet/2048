#include "Console.h"
using namespace std;

Console::Console(Model& model) : model(model) {}

/** Retrouve le nombre le plus grand en caractères.
 * @return value la plus grande taille des numéros en chaîne de caractères.
 **/
int Console::getMaxTextLenght() {
    int maxValue = 0;
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            int value = model.validCase(i, j) ? model.getCase(i, j).getValue() : 0;
            if (value > maxValue) {
                maxValue = value;
            }
        }
    }
    return to_string(maxValue).size(); // Renvoie la longueur de la chaîne de caracteres equvialente au numéro
}

/** Affiche dans la console le tableau à deux dimensions avec les bordures. 
 **/
void Console::printConsole() {
    cout << endl;
    int longMax = getMaxTextLenght();

    cout << "Score actuel: " << model.getScore() << endl;
    cout << "Meilleur score : " << model.getBestScore() << endl;

    string border = "*";
    for (int a = 0; a < model.getColumns(); a++){
        border += string(longMax + 3, '*'); //Ajoute une séquence de (longMax + 3) caracteres '*'
    }

    for (int i = 0; i < model.getLines(); i++) {
        cout << border << endl;
        for (int j = 0; j < model.getColumns(); j++) {
            cout << "* " << setw(longMax) << (model.validCase(i, j) ? model.getCase(i, j).getValue() : 0) << " ";
        }
        cout << "*" << endl;
    }
    cout << border << endl;
    cout << endl;
}

/** Vérifier que la commande est valide à un type de mouvement.
 * @return answer la réponse vérifiée de l'utilisateur.
 **/
string Console::verifyAnswer() {
    string answer;
    cout << "Saisir une valeur de mouvement : ";
    cin >> answer;
    while (answer != "d" && answer != "g" && answer != "h" && answer != "b") {
        cout << "Votre commande est invalide." << endl;
        printConsole();
        cout << "Mouvemant haut : h\nMouvemant bas : b\nMouvemant gauche : g\nMouvemant droite : d\n" << endl;
        cout << "Saisir une valeur de mouvement : ";
        cin >> answer;
    }
    return answer;
}

/** Vérifie que la commande de l'utilisateur est un mouvement valide, et réalise le mouvement.
 **/
bool Console::validMovement() {
    string answer = verifyAnswer();
    if (answer == "g"){
        if (model.canMoveLeft()){
            model.moveLeft();
            return true;
        }
    } else if (answer == "d"){
        if (model.canMoveRight()){
            model.moveRight();
            return true;
        }
    } else if (answer == "h"){
        if (model.canMoveUp()){
            model.moveUp();
            return true;
        }
    } else if (answer == "b"){
        if (model.canMoveDown()){
            model.moveDown();
            return true;
        }
    }
    cout << "Le mouvement saisi est invalide." << endl;
    return false;
}

void Console::displayGame() {
    while (true) {
        printConsole();
        if (validMovement()) {
            model.setRandomElements(1);
            if (!model.canMove()) {
                cout << "Le jeu est fini." << endl;
                cout << "Score final : " << model.getScore() << endl;
                cout << "Best score : " << model.getBestScore() << endl;
                return;
            }
        }
    }
}