#include <iostream>
#include <ctime>
#include <cstdlib>

int aleatorio(){
  return rand()%26;
}

using namespace std; 

int main() { 

  //se crea la semilla
  srand(time(0));

  //se crea un array con 10 elementos
  int enteroArray[10];

  //se crea el puntero (tipo arreglo)
  int *puntero = enteroArray;

  //se llena el array con numeros aleatorios
  for(int i = 0; i<10 ; i++)
      enteroArray[i] = aleatorio();

  //se imprime con el puntero
  for(int i = 0; i < 0 ; i++)
    cout << "Valore en Array ["<<i+1<<"]: "<< *(puntero +1) << " \t Direcciones: " << puntero << endl;


}