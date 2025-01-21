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
    if(lineas == 0 || lineas != numNodos) {
        cout << "Cantidad de entradas incompatibles o no existen datos para la matriz" << endl;
        return vacio;
    }
    return matriz;
}

void nodosLeidos(vector<vector<int>> matriz) {
    for(int i = 0; i < matriz.size(); i++) { 

    }
}
int main() {
    vector<vector<int>> matriz = leerArchivo("matriz.txt");
    char c1 = 'Y';
    int ZM = c1 + 1;
    c1 = c1 + 1;
    cout << "Ascii: " << ZM << endl;
    return 0;
}