# Ev2

Denzel Martin Delgado Urquieta, denzel.delgado@alumnos.ucn.cl, 21.401.250-2, ITI

# Ejecutar el programa

- Crear el ejecutable: "g++ main.cpp -o main.exe"
- Luego, para ejecutar el programa: "./main.exe

# Tema del codigo

El programa consiste en aplicar el algoritmo de Dijkstra, asimismo, la construcción de un arbol con las distancias más cortas para cada nodo. Para ello, se debe leer un archivo para transformarlo a matriz de adyacencia. 

Cuando se compruebe la lectura correcta de la matriz, este se enviará al algoritmo de dijkstra para calcular la distancia más corta, cuyo nodo inicial siempre es "A". Durante el proceso del algoritmo se irá construyendo el arbol que registrará las distancias calculadas por el metodo.

Una vez finalizado, el usuario podrá ingresar el nodo destino al cual quiere visualizar su ruta junto con la distancia más corta. Solicitándose al arbol construido con anterioridad.