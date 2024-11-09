#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> table;

vector<vector<int>> getEmptySlots() {
    vector<vector<int>> emptySlots = vector<vector<int>>(4);
    for (int i = 0; i < table.size(); i++) {
        vector<int> indexEmptySlots = vector<int>(0);
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                indexEmptySlots.push_back(j);
            }
        }
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
    int k = rand() % indexWithValues.size();
    int j = rand() % emptySlots[k].size();
    table[k][j] = 2;
}

void printConsole() {
    cout << endl;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            cout << " " << table[i][j] << " ";
        }
        cout << endl;
    }
}

void start() {
    table = vector<vector<int>>(4);
    for (int i = 0; i <= 4; i++) {
        table[i] = vector<int>(4);
    }
    setRandomElement();
    setRandomElement();
    printConsole();
    string value;
    cin >> value;
}

int main() {
    start();
    return 0;
}