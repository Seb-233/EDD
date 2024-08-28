  /*
   * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
   * 
   *  Laboratorio BST
   *  Autor: Juan Manuel Lopez
   *  Fecha Agosto 2024
   * 
   * Este código implementa un árbol binario de búsqueda (BST) en C++.
   * Incluye funciones para insertar, recorrer y eliminar nodos en el BST.
   * 
   * Partes críticas:
   * 1. Estructura `Nodo`: Define la estructura de un nodo en el BST, 
   *    que contiene un valor `dato` y punteros a los nodos izquierdo y derecho.
   *
   * 2. Función `nuevoNodo`: Crea un nuevo nodo con el valor proporcionado.
   *
   * 3. Funciones de Recorrido (Preorden, Postorden, Inorden): 
   *    Estas funciones realizan un recorrido del árbol en distintos órdenes.
   * 
   * 4. Función `insertarBST`: Inserta un nuevo nodo en el BST, manteniendo el orden del árbol.
   *
   * 5. Función `minValorNodo`: Encuentra el nodo con el menor valor en un subárbol.
   *
   * 6. Función `borrarNodo`: Elimina un nodo específico del BST, reorganizando el árbol 
   *    según sea necesario para mantener la propiedad del BST.
   *
   * <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
   */

#include <iostream>
using namespace std;

struct Nodo{
  int dato; // Dato a almacenar en el nodo
  struct Nodo *left, *right; // Punteros a los nodos izquierdo y derecho
};	

struct Nodo *nuevoNodo(int dato){
  struct Nodo *temporal = new struct Nodo();
  temporal->dato = dato;
  temporal->left = temporal->right = NULL;
  return temporal;
}

/******* Preorder *********/
void preOrdenT(struct Nodo *raiz){
  if (raiz == NULL)
    return;
  cout << raiz->dato << "->"; 
  preOrdenT(raiz->left);
  preOrdenT(raiz->right);
}

/******* Postorder *********/
void postOrdenT(struct Nodo *raiz){
  if (raiz == NULL)
    return;
  postOrdenT(raiz->left);
  postOrdenT(raiz->right);
  cout << raiz->dato << "->"; 
}

/******* Inorder *********/
void inOrdenT(struct Nodo *raiz){
  if (raiz == NULL)
    return;
  inOrdenT(raiz->left);
  cout << raiz->dato << "->"; 
  inOrdenT(raiz->right);
}

/****** Insertar nuevo nodo, dado un valor (BST) ********/
struct Nodo *insertarBST(struct Nodo *nodo, int newDato){
  if (nodo == NULL)
    return nuevoNodo(newDato);
  if (newDato < nodo->dato)
    nodo->left = insertarBST(nodo->left, newDato);
  else
    nodo->right = insertarBST(nodo->right, newDato);

  return nodo;
}


/****** función que retorna el nodo con menor valor en un BST ********/
struct Nodo *minValorNodo(struct Nodo *nodo){
  struct Nodo *actual = nodo;
  /* Se busca iterativamente el elemento menor a la izquierda */
  while(actual && actual->left != NULL)
    actual = actual->left;
  return actual;
}


/****** función que elimina un nodo con valor en un BST ********/
struct Nodo *borrarNodo(struct Nodo *nodo, int dato){
  /* = Árbol vacío = */
  if (nodo == NULL)
    return nodo;
  /* = Si el valor es menor a la raíz, ir por la izquierda = */
  if (dato < nodo->dato)
    nodo->left = borrarNodo(nodo->left, dato);
  /* = Si el valor es mayor a la raíz, ir por la derecha = */
  else if (dato > nodo->dato)
    nodo->right = borrarNodo(nodo->right, dato);
  /* = El valor está en la misma raíz = */
  else {
    /* = Nodo con solo un hijo o sin hijos = */	
    if (nodo->left == NULL){
      struct Nodo *temporal = nodo->right;
      free(nodo);
      return temporal;
    } else if (nodo->right == NULL){
      struct Nodo *temporal = nodo->left;
      free(nodo);
      return temporal;
    }
    /* = Nodo con ambos hijos, tomar el sucesor y borrar el nodo = */
    struct Nodo *temp = minValorNodo(nodo->right);
    /* = Copiar el contenido InOrder sucesor al nodo = */
    nodo->dato = temp->dato;
    /* = Borrar el InOrder sucesor = */
    nodo->right = borrarNodo(nodo->right, temp->dato);
  }
  return nodo;
}


int main(){
    struct Nodo *arbol1 = NULL; 
    arbol1 = insertarBST(arbol1, 50);
    arbol1 = insertarBST(arbol1, 25);
    arbol1 = insertarBST(arbol1, 75);
    arbol1 = insertarBST(arbol1, 15);
    arbol1 = insertarBST(arbol1, 35);
    arbol1 = insertarBST(arbol1, 65);
    arbol1 = insertarBST(arbol1, 85);

    cout << "\n -PreOrden ";  
    preOrdenT(arbol1);
    cout << "\n -PostOrden "; 
    postOrdenT(arbol1);
    cout << "\n -InOrden ";
    inOrdenT(arbol1);

    // Eliminar un nodo y realizar recorrido nuevamente
    cout << "\nSe elimina el nodo(25)" << endl;
    arbol1 = borrarNodo(arbol1, 25);
    inOrdenT(arbol1);


    struct Nodo *arbolPruebas = NULL;
    arbolPruebas = insertarBST(arbolPruebas, 7);
    arbolPruebas = insertarBST(arbolPruebas, 3);
    arbolPruebas = insertarBST(arbolPruebas, 20);
    arbolPruebas = insertarBST(arbolPruebas, 0);
    arbolPruebas = insertarBST(arbolPruebas, 5);
    arbolPruebas = insertarBST(arbolPruebas, 4);
    arbolPruebas = insertarBST(arbolPruebas, 6);
    arbolPruebas = insertarBST(arbolPruebas, -3);
    arbolPruebas = insertarBST(arbolPruebas, 1);
    arbolPruebas = insertarBST(arbolPruebas, 15);
    arbolPruebas = insertarBST(arbolPruebas, 25);
    arbolPruebas = insertarBST(arbolPruebas, 30);

    cout << "\n -PreOrden ";  
      preOrdenT(arbolPruebas);
    cout << "\n -PostOrden "; 
      postOrdenT(arbolPruebas);
    cout << "\n -InOrden ";
      inOrdenT(arbolPruebas);
  
    
    return 0;
}
