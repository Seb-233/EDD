/***********
Autor: Sebastian M
Fecha: 21-08-2024
Tema: Taller00
***********/

#include <iostream>

using namespace std;

struct venta{
int cantidad;
double precio;
};

int main(){
venta *puntero, valor_venta;
puntero = &valor_venta;
cout << “Cantidad de productos: ”;
cin >> (*puntero).cantidad;
cout << “Precio del producto: ”;
cin >> (*puntero).precio;
cout << “Valor a pagar: ” << (*puntero).cantidad*(*puntero).precio << endl;
return 0;
}
