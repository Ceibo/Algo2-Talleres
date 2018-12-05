#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                BORRAR
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    ASSERT(Definido(clave));
    Nodo* x = raiz;
    int i = 0;
    int j = 0;
    //while( siguientes[j] != NULL && clave.length() > i ){
    //Tenia eso, pero con el assert me lo puedo sacar de encima.
    while(clave.length() > i){
        j = int(clave[i]);
        x = x -> siguientes[j];
        i++;    
    }
    return *x -> definicion;
}
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);

                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
                        //Esto lo agregue para borrar los punteros
                        //que crea el constructor.
                        int i = 0;
                        while(i < 256){
                            delete siguientes[i];
                        }
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares

                int hijos(Nodo* x){
                    int hijos = 0;
                    while(hijos < 256){
                        if(x -> siguientes[hijos] != NULL){
                            hijos++;
                        }
                        return hijos;
                    }
                }

                void borrarNodo(Nodo* n){

                    if (n != NULL){
                        for (int i = 0; i < 256; i++) {
                            if (n->siguientes[i] != NULL){
                                borrarNodo(n->siguientes[i]);
                            }
                        }

                        delete n;
                    }
                }
                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) : claves(d.claves) {
    raiz = d.raiz != NULL ? new Nodo(*d.raiz) : NULL;
}



/*
template <typename T>
DiccString<T>::DiccString(const DiccString& d){

    raiz = NULL;

    Conj<string> conjClaves = d.Claves();
    for (int i = 0; i < d.Claves().cardinal(); i++) {

        //string aux = conjClaves.minimo();
        this->Definir(conjClaves.minimo(), d.Obtener(conjClaves.minimo()));
        conjClaves.remover(conjClaves.minimo());
    }

}
*/

template <typename T>
DiccString<T>::~DiccString(){
    if(raiz != NULL){
        delete raiz;
        raiz = NULL;
    }
}
//Si no preguntara si es null estaria borrando algo null y suema medio feo


template<typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    //Este es el caso en que tenga que definir en un diccionario vacio
    if(raiz == NULL){
        raiz = new Nodo();
    }
    Nodo* x = raiz;
    //Si me dan un diccionario no vacio lo recorro hasta ver donde
    //va la clave que quiero definir.
    int i = 0;
    while (clave.length() > i){
        if(x -> siguientes[int(clave[i])] != NULL){
            x = x -> siguientes[int(clave[i])];
        } else {
            x -> siguientes[int(clave[i])] = new Nodo;
            x = x -> siguientes[int(clave[i])];
        }
        i++;
    }

    if (x -> definicion != NULL){
        delete x -> definicion;
    }
    x -> definicion = new T(significado);
    //insertar era funcion del conj.hpp
    claves.insertar(clave);

}

template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    if (raiz == NULL) {
        return false;
    }
    Nodo* x = raiz;
    int i = 0;
    //Quise de hacer un
    // int j = int(clave[i]), pero no funcionaba. por que???
    while(clave.length() > i){
        if(x -> siguientes == NULL || x -> siguientes[int(clave[i])] == NULL){
            return false;
        } else{
            x = x -> siguientes[int(clave[i])];
        }
        i++;
    }
    if(x -> definicion != NULL){
        return true;        
    } else {
        return false;
    }
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
    ASSERT(Definido(clave));
	Nodo* x = raiz;
	int i = 0;
    //while( siguientes[j] != NULL && clave.length() > i ){
    //Tenia eso, pero con el assert me lo puedo sacar de encima.
    while(clave.length() > i ){
        x = x -> siguientes[int(clave[i])];
        i++;    
    }
    return *x -> definicion;
}

template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    ASSERT(Definido(clave));
    Nodo* x = raiz;
    int i = 0;
    int j = 0;
    //Acá me deja hacer lo de j. Antes no podia, por que?.
	while(clave.length() > i){
		j = int(clave[i]);
		x = x -> siguientes[j];
		i++;	
	}
	return *x -> definicion;
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    Nodo* x = raiz;
    Nodo* padreDeX = raiz;
    Nodo* cuantosElimino = NULL;
    Nodo* padreDeCE = NULL;
    int CE = 0;

    for (int i = 0; i < clave.length(); i++) {

        if (x->definicion == NULL && hijos(x) == 1 && cuantosElimino == NULL){
            cuantosElimino = x;
            padreDeCE = padreDeX;
            CE = i-1;

        }else if ((hijos(x) > 1 || x->definicion != NULL) && (i != clave.length()-1)) {
            cuantosElimino = NULL;
            padreDeCE = NULL;
            CE = 0;

        }

        padreDeX = x;
        if(hijos(padreDeX) > 1 && i == clave.length()-1){
            padreDeCE = padreDeX;
            cuantosElimino = x->siguientes[int(clave[i])];
            CE = i;
        }
        x = x->siguientes[int(clave[i])];

    }

    if (cuantosElimino == this->raiz && hijos(x) == 0) {
        borrarNodo(this->raiz);
        this->raiz = NULL;
        claves.remover(clave);
        return;
    }

    if (hijos(x) > 0){
        delete x->definicion;
        x->definicion = NULL;
    }else{
        borrarNodo(cuantosElimino);
        padreDeCE->siguientes[int(clave[CE])] = NULL;
    }

    claves.remover(clave);
}

#endif
/*

template <typename T>
void DiccString<T>::Borrar(const string& clave){
	Nodo * aBorrar = raiz;
	Nodo * anteriorConHijos = raiz;
	int i = 0;
	int j = 0;
	while( clave.length() > i ){
		j = int(clave[i]);
		i++;
		int k = 0;
		for ( int w = 0; w < 256 ; w++){
			if (aBorrar -> siguientes[w] != NULL){
				k++;
			}
		}
		if ( k > 1 || aBorrar -> definicion != NULL ){
			anteriorConHijos = aBorrar; //y es el nodo que guarda el ultimo elemento hasta clave
			// que tiene un hijo o  mas, o tiene definicion
//            tamanho--; VER ESTOOOO
		}
		aBorrar = aBorrar -> siguientes[i];
		// ahora afuera del ciclo entiendo que tengo en x el lugar donde esta la clave
		//y en "y" el ultimo que tiene hijos (2 o mas) o tiene definicion.
	}


}
#endif
*/

/*

    for(int i = 0; i < clave.length(); i++){
       //Acá me fijo 
        if(x -> definicion == NULL && hijos(x) == 1 && cuantosElimino == NULL){
            cuantosElimino = x;
            padreDeCE = padreDeX;
            CE = i-1;
        }
        else if((hijos(x) > 1 || x -> definicion != NULL) && (clave.length()-1 != i)){
            cuantosElimino = NULL;
            padreDeCE = NULL;
            CE = 0;
        }
        padreDeX = x;
        if(hijos(padreDeX) > 1 && clave.length() == i+1){
            padreDeCE = padreDeX;
            cuantosElimino = x -> siguientes[int(clave[i])];
            CE = 1;
        }
        x = x -> siguientes[int(clave[i])];
    }

    if(cuantosElimino == raiz && hijos(x) == 0){
        borrarNodo(raiz);
        raiz = NULL;
        claves.remover(clave);
        return;
    }
    if(hijos(x) > 0){
        delete x -> definicion;
        x -> definicion = NULL;
    } else {
        borrarNodo(cuantosElimino);
        padreDeCE -> siguientes[int(clave[CE])] = NULL;
    }
    claves.remover(clave);
}
*/