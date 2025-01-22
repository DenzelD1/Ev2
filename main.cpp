#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

class Arbol {

};

//Lee el archivo y rellena la matriz
vector<vector<int>> leerArchivo(string nombreArchivo) {
    vector<vector<int>> vacio;
    ifstream archivo(nombreArchivo);
    if(!archivo.is_open()) {
        cout << "No se ha logrado abrir el archivo o no existe" << endl;
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
            if(matriz[lineas][i] < 0) {
                cout << "No es posible trabajar con pesos negativos" << endl;
                return vacio;
            }
        }
        lineas++;
    } archivo.close();
    if(lineas == 0 || lineas != numNodos) {
        cout << "Cantidad de entradas incompatibles o no existen datos para la matriz" << endl;
        return vacio;
    } else if (numNodos < 1 || numNodos > 26) {
        cout << "Exceso o insuficiencia de nodos permitidos" << endl;
    }
    return matriz;
}

//Imprime todos los nodos presentes en la matriz
void nodosLeidos(vector<vector<int>> matriz) {
    cout << "Nodos leidos: ";
    char letra = 'A';
    for(int i = 0; i < matriz.size(); i++) { 
        cout << letra << " ";
        letra = letra + 1;
    } cout << endl;
}

void agregarArbol(int pesoDistancia, int nodo, Arbol*& arbol) {
    
}

void dijkstra(vector<int>& distancia, vector<bool>& visitado, vector<vector<int>> matriz, 
                int tamano, Arbol*& arbol) {
    distancia[0] = 0;
    agregarArbol(0, 0, arbol);
    for(int nodos = 0; nodos < tamano; nodos++) {
        int nodoActual = -1;
        
        for(int nodo = 0; nodo < tamano; nodo++) {
            if(!visitado[nodo] && (nodoActual == -1 || distancia[nodo] < distancia[nodoActual])) {
                nodoActual = nodo;
            }
        }

        if(distancia[nodoActual] == INT_MAX) {
            cout << "El nodo " << nodoActual << "no se puede acceder" << endl;
            break;
        }
        visitado[nodoActual] = true;
        for(int vecino = 0; vecino < tamano; vecino++) {
            if(matriz[nodoActual][vecino] != 0 && !visitado[vecino]) {
                int dist = distancia[nodoActual] + matriz[nodoActual][vecino];
                if(dist < distancia[vecino]) {
                    distancia[vecino] = dist;
                }
            }
        }
    }   

}

int main() {
    string archivo;
    cout << "Escribir la ruta del archivo txt:" << endl;
    getline(cin, archivo);

    vector<vector<int>> matriz = leerArchivo(archivo);
    int tamano = matriz.size();
    if(tamano != 0) {
        Arbol* arbol;
        nodosLeidos(matriz);
        vector<int> distancia(tamano, INT_MAX);
        vector<bool> visitado(tamano, false);
        dijkstra(distancia, visitado, matriz, tamano, arbol);
    }

    return 0;
}