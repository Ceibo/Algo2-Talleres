#include <iostream>
#include <string>
#include <cassert>
#include "Pila.h"


Pila::Pila(){
  prim = NULL;
  tam = 0;
}

Pila::~Pila(){
	destruir();
}

void Pila::destruir(){
	while (!esVacia()) {
		desapilar();
	}
}

void Pila::apilar(ElemPila& elem){
     Nodo* nodo = new Nodo;
     nodo -> sig = prim;
     nodo -> elem = elem;
     prim = nodo;
     tam++;
}

bool Pila::esVacia() {
    return tam == 0;
}

ElemPila& Pila::tope(){
    assert(!esVacia());
    return prim -> elem;
}

void Pila::desapilar(){
        assert(!esVacia());
    	Nodo* nodo = prim -> sig;
    	delete prim;
    	prim = nodo;
    	tam--;
}


Nat Pila::tamanio() const{
	return tam;
}

Pila& Pila::operator=(const Pila & aCopiar){
	destruir();
    if(aCopiar.tamanio() > 0){
	    ElemPila vectorElementos[aCopiar.tamanio()];
	    Nat i = 0;
	    Nodo* auxiliar = aCopiar.prim;
		while(i < aCopiar.tamanio()){
			vectorElementos[i] = auxiliar -> elem;
			auxiliar = auxiliar -> sig;
			i++;
		}
		while(i > 0){
			i--;
			apilar(vectorElementos[i]);
		}
	}
	return *this;		
}

void Pila::mostrar(ostream& os) const{
	os << "[";
	Nodo* aux = prim;
	while(aux != NULL){
		os << aux -> elem;
		if(aux -> sig != NULL){
			os << ", ";
		}
		aux = aux -> sig;
	}
	os << "]";
}
