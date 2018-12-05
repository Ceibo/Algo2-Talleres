#ifndef PILA_H
#define PILA_H
typedef unsigned long Nat;
#include <string>
#include <ostream>
#include <iostream>
#include <cassert>

using namespace std;

// Los datos de un elemento de pila
struct ElemPila {
  public:
      int id;
      string nombre;
      string descripcion;
  
    // Como mostrar un elemento de pila
  friend ostream& operator<<(ostream& os, const ElemPila& a) {
     os << "{Id:" << a.id << ", " << "Nombre:" << a.nombre << ", Descripción:" << a.descripcion <<"}";
     return os;
  }

};

class Pila {

  private:

    struct Nodo {
      ElemPila elem;
      Nodo* sig;
    };

    Nodo* prim;
    Nat tam;

    void destruir();

  public:

  // Constructor y destructor
    Pila(); 
    ~Pila();
    
  // Generadores
    void apilar(ElemPila& elem);
  
  // Observadores básicos
    bool esVacia();
    ElemPila& tope();
    void desapilar();

  // Otras operaciones
    Nat tamanio() const;

  // Asignacion
    Pila& operator=(const Pila & aCopiar);

  // Muestra la lista en un ostream
  // formato de salida: [e_0, e_1, e_2, ...]
  // donde e_i es el resultado del "mostrar" del ElemPila i
    void mostrar(ostream& os) const;

  friend ostream& operator<<(ostream& os, const Pila &p) {
    p.mostrar(os);
    return os;
  }

};
#endif