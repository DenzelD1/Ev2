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
        if(!(ss >> numNodos) || !ss.eof()) {
            cout << "El formato del archivo no es correcto" << endl;
            return vacio;
        }
    }
    
    if(numNodos < 1) {
        cout << "No es posible trabajar con esa cantidad de nodos. Minimo: 1" << endl;
        return vacio;
    } else if(numNodos > 26) {
        cout << "No es posible trabajar con esa cantidad de nodos. Maximo: 26" << endl;
        return vacio;
    }
    vector<vector<int>> matriz(numNodos, vector<int>(numNodos, 0));

    int lineas = 0;
    while(getline(archivo, linea)) {
        if(lineas >= numNodos) {
            cout << "El formato de la matriz no concuerda con la cantidad de nodos. Tiene fila(s) extra(s)" << endl;
            return vacio;
        }
        stringstream ss(linea);
        for(int i = 0; i < numNodos; i++) {
            if(!(ss >> matriz[lineas][i])) {
                cout << "Hay un error de formato en la fila " << lineas + 1 << " de la matriz: " << linea << endl;
                return vacio;
            }
            ss.ignore();
            if(matriz[lineas][i] < 0) {
                cout << "No es posible trabajar con pesos negativos" << endl;
                return vacio;
            }
        }
        if(ss >> linea) {
            cout << "Hay un error de formato en la fila " << lineas + 1 << " de la matriz: " << linea << endl;
            return vacio;
        }
        
        lineas++;
    } archivo.close();
    if(lineas == 0 || lineas != numNodos) {
        cout << "Cantidad de entradas incompatibles o no existen datos para la matriz" << endl;
        return vacio;
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
    cout << "Escribir la ruta del archivo txt:" << endl;
    string archivo;
    do {
        getline(cin, archivo);
        if(archivo.length() == 0) {
            cout << "Debe indicar una ruta" << endl;
        }
    } while(archivo.length() == 0);

    vector<vector<int>> matriz = leerArchivo(archivo);
    int tamano = matriz.size();
    Arbol* arbol = nullptr;
    if(tamano != 0) {
        arbol = new Arbol('A', 0);
        nodosLeidos(matriz);
        vector<int> distancia(tamano, INT_MAX);
        vector<bool> visitado(tamano, false);
        dijkstra(distancia, visitado, matriz, tamano, arbol);

        string caracter;
        int ascii;
        cout << "Ingrese el nodo destino:" << endl;
        do {
            getline(cin, caracter);
            if(caracter.length() == 0) {
                cout << "Ingrese un caracter" << endl;
            } else if(caracter.length() > 1) {
                cout << "Solo se permite un caracter" << endl;
            } else {
                ascii = caracter[0];
                if(ascii < 65 || ascii > (tamano + 64)) {
                    cout << "Debe ingresar uno de los nodos leidos exactamente como se muestra" << endl;
                }
            }
        } while(ascii < 65 || ascii > (tamano + 64));
        string algo = "hola";
        int algo2 = algo[0];
        cout << algo2 << endl;
        imprimirArbol(arbol);
    }
    return 0;
}