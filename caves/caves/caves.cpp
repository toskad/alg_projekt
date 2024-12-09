/**
 * @file caves.cpp
 * @brief Program pro hledání všech možných cest v systému jeskyní.
 * @details Tento program čte graf jeskyní ze vstupního souboru a hledá všechny cesty
 *          z "start" do "end" za použití rekurze a správy navštívených uzlů.
 * @author Adam Toška
 * @date 8.12.2024
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cctype>
using namespace std;

/**
 * @brief Zjišťuje, zda je jeskyně malá (název obsahuje pouze malá písmena).
 * @param cave Název jeskyně.
 * @return `true`, pokud je jeskyně malá; jinak `false`.
 */
bool isSmallCave(const string& cave) {
    return islower(cave[0]);
}

/**
 * @brief Hledá všechny cesty z aktuální jeskyně do cílové jeskyně "end".
 * @param current Aktuální jeskyně.
 * @param graph Graf reprezentující spojení mezi jeskyněmi.
 * @param visited Množina navštívených malých jeskyní.
 * @param currentPath Aktuální cesta.
 * @param allPaths Vektor všech nalezených cest.
 */
void findPaths(const string& current,
    map<string, vector<string>>& graph,
    set<string>& visited,
    vector<string>& currentPath,
    vector<vector<string>>& allPaths)
{
    currentPath.push_back(current);

    if (current == "end") {
        allPaths.push_back(currentPath);
        currentPath.pop_back();         
        return;
    }

    if (isSmallCave(current)) {
        visited.insert(current);
    }
  
    for (const auto& neighbor : graph[current]) {

        if (visited.count(neighbor) == 0) {
            findPaths(neighbor, graph, visited, currentPath, allPaths);
        }
    }

    if (isSmallCave(current)) {
        visited.erase(current);
    }

    currentPath.pop_back();
    return;
}
/**
 * @brief Hlavní funkce programu.
 * @details Čte graf jeskyní ze souboru, hledá všechny cesty a vypisuje výsledky.
 * @return Návratový kód programu (0 = úspěch, 1 = chyba).
 */
int main() {
    string filename;
    cout << "Zadejte nazev vstupniho souboru: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) { 
        cerr << "Chyba: Nelze otevrit soubor " << filename << endl;
        return 1; 
    }

    string line;
    map<string, vector<string>> graph;


    while (getline(inputFile, line)) {
        stringstream ss(line);
        string cave1, cave2;
        getline(ss, cave1, '-');
        getline(ss, cave2, '-');


        graph[cave1].push_back(cave2);
        graph[cave2].push_back(cave1);
    }

    inputFile.close();


    vector<string> currentPath;
    vector<vector<string>> allPaths;
    set<string> visited;


    findPaths("start", graph, visited, currentPath, allPaths);


    cout << "Vsechny nalezene cesty:" << endl;
    for (const auto& path : allPaths) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << ",";
        }
        cout << endl;
    }


    cout << "Pocet nalezenych cest: " << allPaths.size() << endl;

    return 0;
}
