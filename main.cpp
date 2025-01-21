#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

class Arbol {

};

vector<vector<int>> leerArchivo(string nombreArchivo) {
    vector<vector<int>> matriz;
    ifstream archivo(nombreArchivo);
    if(!archivo.is_open()) {
        cout << "No se ha logrado abrir el archivo" << endl;
        return matriz;
    }
    int linea1 = 0;
    int numNodos;
    string linea;
    while(getline(archivo, linea)) {
        linea1++;
        stringstream ss(linea);

        if(linea1 == 1) {
            ss >> numNodos;
            ss.ignore();
        }
        
    } archivo.close();
    cout << numNodos << endl;
    return matriz;
}

int main() {
    cout << "Nodos leidos actualmente" << endl;
    vector<vector<int>> matriz = leerArchivo("matriz.txt");
    return 0;
}