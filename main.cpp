#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <sstream>
using namespace std;

class Arbol {
    public:
        pair<char, int> nodo;
        vector<Arbol*> siguiente;
        Arbol(char n, int pesoAcumulado) {
            nodo.first = n;
            nodo.second = pesoAcumulado;
        }
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

Arbol* busquedaDeNodoInicial(Arbol* head, char nodoI) {
    queue<Arbol*> cola;
    cola.push(head);

    while(!cola.empty()) {
        Arbol* actual = cola.front();
        cola.pop();

        if(actual -> nodo.first == nodoI) return actual;
        for(int i = 0; i < actual -> siguiente.size(); i++) {
            cola.push(actual -> siguiente[i]);
        }
    }
    return nullptr;
}

void agregarArbol(int pesoDistancia, int nodoI, int nodoD, Arbol*& head) {
    nodoI = nodoI + 65;
    nodoD = nodoD + 65;
    char inicial = nodoI;
    char destino = nodoD;
    Arbol* nuevoHijo = nullptr;
    bool existeElNodo = false;
    if(head -> nodo.first == inicial) {
        if(head -> siguiente.size() == 0) {
            nuevoHijo = new Arbol(destino, pesoDistancia);
            head -> siguiente.push_back(nuevoHijo);
        } else {
            for(int i = 0; i < head -> siguiente.size(); i++) {
                if(head -> siguiente[i] -> nodo.first == destino) {
                    head -> siguiente[i] -> nodo.second = pesoDistancia;
                    existeElNodo = true;
                    break;
                }
            }
            if(!existeElNodo) {
                nuevoHijo = new Arbol(destino, pesoDistancia);
                head -> siguiente.push_back(nuevoHijo);
            }
        }
        
    } else {
        Arbol* nodoActual = busquedaDeNodoInicial(head, inicial);
        if(nodoActual != nullptr) {
            if(nodoActual -> siguiente.size() == 0) {
                nuevoHijo = new Arbol(destino, pesoDistancia);
                nodoActual -> siguiente.push_back(nuevoHijo);
            } else {
                for(int i = 0; i < nodoActual -> siguiente.size(); i++) {
                    if(nodoActual -> siguiente[i] -> nodo.first == destino) {
                        nodoActual -> siguiente[i] -> nodo.second = pesoDistancia;
                        existeElNodo = true;
                        break;
                    }
                }
                if(!existeElNodo) {
                    nuevoHijo = new Arbol(destino, pesoDistancia);
                    nodoActual -> siguiente.push_back(nuevoHijo);
                }
            }
        }
    }
}

void dijkstra(vector<int>& distancia, vector<bool>& visitado, vector<vector<int>> matriz, 
                int tamano, Arbol*& head) {
    distancia[0] = 0;
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
                    agregarArbol(dist, nodoActual, vecino, head);
                }
            }
        }
    }   

}

void imprimirArbol(Arbol* n) { 
    for(int i = 0; i < n -> siguiente.size(); i++) {
        cout << n -> siguiente[i] -> nodo.first << ": " << n -> siguiente[i] -> nodo.second << endl;
    }
    
}

int main() {
    string archivo;
    cout << "Escribir la ruta del archivo txt:" << endl;
    getline(cin, archivo);

    vector<vector<int>> matriz = leerArchivo(archivo);
    int tamano = matriz.size();
    Arbol* arbol = nullptr;
    if(tamano != 0) {
        arbol = new Arbol('A', 0);
        nodosLeidos(matriz);
        vector<int> distancia(tamano, INT_MAX);
        vector<bool> visitado(tamano, false);
        dijkstra(distancia, visitado, matriz, tamano, arbol);

        imprimirArbol(arbol);
    }

    cout << "***************" << endl;
    int num = 65;
    char a = num;
    cout << a << endl;
    return 0;
}