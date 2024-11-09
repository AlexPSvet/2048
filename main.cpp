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

string caractere(string caractere, int max) {
    string texte = caractere;
    for (int i = 0; i < max - caractere.size(); i++) {
        texte += ' ';
    }
    return texte;
}

int caractereMax() {
    int k = 0;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if(k < table[i][j]) {
                k = table[i][j];
            }
        }
    }
    return k;
}

void printConsole() {
    cout << endl;
    int longmax = to_string(caractereMax()).size();
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            cout << " " << caractere(to_string(table[i][j]), longmax) << " ";
        }
        cout << endl;
    }
}

void start() {
    table = vector<vector<int>>(4);
    for (int i = 0; i < 4; i++) {
        table[i] = {0, 0, 0, 0};
    }
    for (int i = 0; i < 2; i++) {
        setRandomElement();
    }
    printConsole();
    string value;
    cin >> value;
}

int main() {
    srand(time(0));
    start();
    return 0;
}