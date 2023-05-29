#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

ifstream in("grammar.in");
map<string, set<string>> grammar;

bool verify(string word, string currNode)
{
    if (word.empty()) {
        /// Daca am ajuns la cuvantul vid, cautam pentru toate nodurile
        /// in care ajunge nodul curent pentru a vedea daca e (si) nod final
        for (auto node: grammar[currNode])
            if (node == "#")
                return true;
    } else if (word.length() == 1) {
        /// Daca cuvantul la care am ajuns are lungime 1 (este doar o litera), verificam daca
        /// litera respectiva se afla in nodurile in care ajunge nodul curent
        for (auto node : grammar[currNode]){
            if (node == word){
                return true;
            }
        }
    }

    for (auto node : grammar[currNode]) {
        /// Daca un nod are aceeasi prima litera ca litera curenta din cuvantul de verificat
        /// verificam daca cuvantul este acceptat si de restul nodului, verificand cuvantul
        /// fara litera curenta cu nodul fara litera care se potriveste
        if(word[0] == node[0] && node.length() > 1){
            if(verify(word.substr(1), node.substr(1,1))){
                return true;
            }
        }
    }

    return false;
}

void printGrammar(){
    /// Afisam gramatica din input
    for (auto node : grammar) {
        cout << node.first << ": ";
        for (auto dest : node.second){
            cout << dest << " ";
        }
        cout << endl;
    }
}

int main() {
    string line;
    while (getline(in, line)) {
        stringstream l(line);

        string nod, to;
        l >> nod;
        while (l >> to) {
            /// Daca nu avem nodul in gramatica, atunci il adaugam
            if (grammar[nod].empty()) {
                grammar.insert({nod, set<string>{}});
            }

            /// Adaugam "destinatia" la nodul curent
            grammar[nod].insert(to);
        }
    }


    while(true)
    {
        string input;
        cout << "Type '-1' to exit" << endl;
        cout << "Please enter the word to be verified:" << endl;
        getline(cin, input);
        if (input == "-1"){
            return 0;
        }

        if (verify(input, "S")) {
            cout << "OK" << endl;
        } else {
            cout << "!OK" << endl;
        }
        cout << endl;
    }

    return 0;
}
