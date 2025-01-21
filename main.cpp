#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

class Arbol {

};

vector<vector<int>> leerArchivo(string nombreArchivo) {
    vector<vector<int>> vacio;
    ifstream archivo(nombreArchivo);
    if(!archivo.is_open()) {
        cout << "No se ha logrado abrir el archivo" << endl;
        return vacio;
    } else if(archivo.peek() == EOF) {
        cout << "El archivo esta vacio" << endl;
        return vacio;
    }

    int numNodos;
    string linea;
    if(getline(archivo, linea)) {
        stringstream ss(linea);
        ss >> numNodos;
    }

    vector<vector<int>> matriz(numNodos, vector<int>(numNodos, 0));

    int lineas = 0;
    while(getline(archivo, linea)) {
        stringstream ss(linea);
        for(int i = 0; i < numNodos; i++) {
            ss >> matriz[lineas][i];
            ss.ignore();
        }
        lineas++;
    } archivo.close();

    return matriz;
}

int main() {
    vector<vector<int>> matriz = leerArchivo("matriz.txt");

    for(int i = 0; i < matriz.size(); i++) {
        for(int j = 0; j < matriz.size(); j++) {
            cout << matriz[i][j] << "  ";
        } cout << endl;
    }
    return 0;
}