#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> table;

void afficherTableau(vector<int> tableau) {
    cout << "[";
    for (int i = 0; i < tableau.size(); i++) {
        cout << i;
        if (i != tableau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

void afficherTableau(vector<vector<int>> tableau) {
    cout << "[";
    for (int i = 0; i < tableau.size(); i++) {
        afficherTableau(tableau[i]);
        if (i != tableau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

vector<vector<int>> getEmptySlots() {
    vector<vector<int>> emptySlots = vector<vector<int>>(0);
    for (int i = 0; i < table.size(); i++) {
        vector<int> indexEmptySlots = vector<int>(0);
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                indexEmptySlots.push_back(j);
            }
        }
        emptySlots.push_back(indexEmptySlots);
    }
    return emptySlots;
}

void setRandomElement() {
    vector<int> indexWithValues = vector<int>(0);
    vector<vector<int>> emptySlots = getEmptySlots();
    for (int i = 0; i < emptySlots.size(); i++) {
        if (emptySlots[i].size() != 0) {
            indexWithValues.push_back(i);
        }
    }
    int k = (int) rand() % indexWithValues.size();
    int j = emptySlots[k][(int) rand() % emptySlots[indexWithValues[k]].size()];
    table[k][j] = 2;
}

string getText(string caractere, int max) {
    string texte = caractere;
    for (int i = 0; i < max - caractere.size(); i++) {
        texte += ' ';
    }
    return texte;
}

int getMaxTextLenght() {
    int k = 0;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if(k < table[i][j]) {
                k = table[i][j];
            }
        }
    }
    return to_string(k).size();
}

void moveLeft() {
    for (int i = 0; i < table.size(); i++) {
        int first0Index = -1;
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[i][j];
                table[i][j] = 0;
                table[i][first0Index] = value;
                first0Index += 1;
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < table.size(); i++) {
        int first0Index = -1;
        for (int j = table[i].size() - 1; j >= 0; j--) {
            if (table[i][j] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[i][j];
                table[i][j] = 0;
                table[i][first0Index] = value;
                first0Index -= 1;
            }
        }
    }
}

void moveDown() {
    for (int i = 0; i < 4; i++) {
        int first0Index = -1;
        for (int j = 3; j >= 0; j--) {
            if (table[j][i] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[j][i];
                table[j][i] = 0;
                table[first0Index][i] = value;
                first0Index -= 1;
            }
        }
    }    
}

void moveUp() {
    for (int i = 0; i < 4; i++) {
        int first0Index = -1;
        for (int j = 0; j < 4; j++) {
            if (table[j][i] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[j][i];
                table[j][i] = 0;
                table[first0Index][i] = value;
                first0Index += 1;
            }
        }
    }
}

void printConsole() {
    cout << endl;
    int longMax = getMaxTextLenght();
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            cout << " " << getText(to_string(table[i][j]), longMax) << " ";
        }
        cout << endl;
    }
}

void start() {
    table = vector<vector<int>>(4);
    for (int i = 0; i < 4; i++) {
        table[i] = {0, 0, 0, 0};
    }
    for (int i = 0; i < 5; i++) {
        setRandomElement();
    }
    while (true) {
        printConsole();
        string answer;
        cout << "Saisir une valeur de mouvement : ";
        cin >> answer;
        if (answer == "g") {
            moveLeft();
        } else if (answer == "d") {
            moveRight();
        } else if (answer == "h") {
            moveUp();
        } else if (answer == "b") {
            moveDown();
        }
    }
    
}

int main() {
    srand(time(0));
    start();
    return 0;
}