#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der; 
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;
		int n; // Este n me indica el cardinal.

		// funciones auxiliares
		void mostrarHijos(std::ostream& os , Nodo * nodo) const;

		

};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL){

	 }

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL) , n(0){
}

template <class T>
Conjunto<T>::~Conjunto(){
	Nodo * x = raiz_;
	while(x != NULL){
		remover(x -> valor);
	}
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const{
	Nodo * x = raiz_;
	if (x == NULL){
		return false;
	}
	else {
		while(x != NULL && x -> valor != clave){
			if (clave < x -> valor){
				x = x -> izq;
			}
			else {		
				x = x -> der;
			}
		}
		return x != NULL;
	}
}


//((clave > x -> valor) && (x -> der != NULL)) || ((clave < x -> valor) && (x -> izq != NULL))

template <class T>
void Conjunto<T>::insertar(const T& clave){
	Nodo * x = raiz_;
	Nodo * xpadre = raiz_;
	if (x == NULL){
		x = new Nodo(clave);
		n++;
	} else{
		while( x != NULL && x -> valor != clave ){
			if (clave < x -> valor){
				xpadre = x;
				x = x -> izq;
			} else if(clave > x -> valor){
				xpadre = x;
				x = x -> der;
			}
		}
		if ( x == NULL ){
			n++;
			if(clave > xpadre -> valor){
				xpadre -> der = new Nodo(clave);
			} else{
				xpadre -> izq = new Nodo(clave);
			}
		}
	}
}



template <class T>
unsigned int Conjunto<T>::cardinal() const {
	return n;
}


template <class T>
void Conjunto<T>::remover(const T& clave) {
	assert(pertenece(clave));
	Nodo * padre = NULL;
	Nodo * hijo = raiz_;

  //Este ciclo me deja con hijo = clave y padre como padre de clave.
	while (hijo -> valor != clave){
		padre = hijo;
		if (hijo -> valor < clave){
			hijo = hijo -> izq;
		} else {
			hijo = hijo -> der;
		}
	}
//Ahora el caso en que el hijo sea una hoja. Ook es parece estar bien
	if(hijo -> der == NULL && hijo -> izq == NULL){
		if(padre -> izq == hijo){
			padre -> izq = NULL;
		} else {
			padre -> der = NULL;
		}
		delete hijo;
//Ahora el caso en que el a borrar (hijo) tenga un hijo
//En este primer caso, el hijo esta a su derecha
//Considero los casos por separado, para tener en cuenta si
//pongo mando puntero de hijo del hijo a der o izq del padre.
	} else if (hijo -> der != NULL && hijo -> izq == NULL){
		if(padre -> izq == hijo){
			padre -> izq = hijo -> der;
		} else {
			padre -> der = hijo -> der;
		}
		delete hijo;
//Aca considero lo mismo que lo anterior, en caso de que el hijo
//este a la izquierda de su padre (a la derecha del padre puede haber algo o no)
	} else if (hijo -> izq != NULL && hijo -> der == NULL){
		if(padre -> izq == hijo){
			padre -> izq = hijo -> izq;
		} else {
			padre -> der = hijo -> izq;
		}
		delete hijo;
//Ahora arranco con el caso dificil, el caso en que tiene 2 hijos
//Tengo que considerar los casos en que el nodo A (que sabemos que tiene 2 hijos) 
//sea hijo unico o no. Para empezar, busco el mas grande de la izquierda o el mas chico de la dercha
//Se que esa ultima guarda es medio al pedo, pero por las dudas...
	} else if(hijo -> izq != NULL && hijo -> der != NULL){
//Aca me guardo en el nodo y el mas chico del lado derecho, para balancear. Asi arbitrariamente
		Nodo * max = hijo -> izq;
		Nodo * maxpadre = hijo;
		while(max -> der != NULL){
			maxpadre = max;
			max = max -> der;
		}
//Ahora tengo que meterlo en el lugar del que quiero eliminar, tengo que fijarme si el nodo A (que voy a eliminar)
//es hijo izquierdo o es hijo derecho, y despues borro e inserto lo que hace falta.
//Tengo que recordar que max puede tener hijo izquierdo tambien.
		if(max -> izq == NULL){
			hijo -> valor = max -> valor;
			maxpadre -> der = NULL;
		} else {
			maxpadre -> der = max -> izq;
		}

		if(padre -> izq == hijo){
			padre -> izq = max;
		} else {
			padre -> der = max;
		}
		hijo -> valor = max -> valor;
		delete max;
		//hace falta este ultimo delete?
	}
}

/*
template <class T>
const T&  Conjunto<T>::minimo() const {
	Nodo * x = raiz_;
	if(x -> izq == NULL){
	return x -> valor;
}
	else {
		while(x -> izq != NULL){
			x = x -> izq;
		}
		return x -> valor;
	}
}


template <class T>
const T&  Conjunto<T>::maximo() const {
	Nodo * x = raiz_;
	if(x -> der == NULL){
		return x -> valor;
	}
	else {
		while(x -> der != NULL){
			x = x -> der;
		}
		return x -> valor;
	}
}
*/

template <class T>
const T&  Conjunto<T>::minimo() const {
	Nodo * x = raiz_;
	while(x -> izq != NULL){
		x = x -> izq;
	}
	return x -> valor;
}


template <class T>
const T&  Conjunto<T>::maximo() const {
	Nodo * x = raiz_;
	while(x -> der != NULL){
		x = x -> der;
	}
	return x -> valor;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {
	if (raiz_ != NULL) {
		os << "(";
		mostrarHijos(os, raiz_ -> izq);
		os << ", ";
		mostrarHijos(os, raiz_ -> der);
		os << ", ";
		os << raiz_ -> valor;
		os << ")";
	}
}

template <class T>
void Conjunto<T>::mostrarHijos(std::ostream& os , Nodo * nodo) const {
	if (nodo == NULL){
		os << "NULL";
	}
	else {
	os << "(";
	mostrarHijos(os, nodo -> izq);
	os << ", ";
	mostrarHijos(os, nodo -> der);
	os << ", ";
	os << nodo -> valor;
	os << ")";
	}
}

#endif // CONJUNTO_HPP_