/*******
Fecha: 21 de agsto 20024
Autor: Sebastian M.
Tema: Taller 00 ,  punto 02
********/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct venta {
    int cantidad;
    double precio;
};


struct Cliente {
    string nombre;
    string nombreproducto;
    string direccion;
    string telefono;
};


void capturarDatosCliente(Cliente *cliente) {
  cout << "Nombre del cliente: ";
  getline(cin, cliente->nombre);


  cout << "Dirección del cliente: ";
  getline(cin, cliente->direccion);

  cout << "Teléfono del cliente: ";
  getline(cin, cliente->telefono);
  cout << "Nombre del producto: ";
  getline(cin, cliente->nombreproducto);

}


void imprimirFactura(Cliente *cliente, venta *ventaActual) {
    ofstream archivoFactura("factura.txt");

    if (archivoFactura.is_open()) {
        archivoFactura << "Factura de Venta\n";
        archivoFactura << "----------------\n";
        archivoFactura << "Nombre del cliente: " << cliente->nombre << endl;
        archivoFactura << "Dirección del cliente: " << cliente->direccion << endl;
        archivoFactura << "Teléfono del cliente: " << cliente->telefono << endl;
        archivoFactura << "Nombre del producto: " << cliente->nombreproducto << endl;
        archivoFactura << "Cantidad de productos: " << ventaActual->cantidad << endl;
        archivoFactura << "Precio por producto: $" << ventaActual->precio << endl;
        archivoFactura << "Valor a pagar: $" << ventaActual->cantidad * ventaActual->precio << endl;

        archivoFactura.close();
        cout << "Factura impresa en 'factura.txt'." << endl;
    } else {
        cout << "No se pudo abrir el archivo para escribir la factura." << endl;
    }
}


int main() {

   // Capturamos los datos del cliente
      Cliente cliente;
      capturarDatosCliente(&cliente);

      venta *puntero, valor_venta;
      puntero = &valor_venta;

      cout << "Cantidad de productos: ";
      cin >> (*puntero).cantidad;

      cout << "Precio del producto: ";
      cin >> (*puntero).precio;


      cout << "Valor a pagar: $" << (*puntero).cantidad * (*puntero).precio << endl;


      imprimirFactura(&cliente, puntero);

  return 0;

}