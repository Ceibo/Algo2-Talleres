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
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
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
                        for(int i = 0; i < 256; i++){
                            delete siguientes[i];
                        }
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares


               int cantHijos(Nodo* n){
                    int hijos = 0;
                    while(hijos < 256){
                        if (n -> siguientes[hijos] != NULL){
                            hijos++;
                        }
                        hijos++;
                    }
                    return hijos;
                }

                Nodo* raiz;
                int tam = 0;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){

    }

template <typename T>
DiccString<T>::DiccString(const DiccString& d){
    raiz = NULL;

    Conj<string> conjClaves = d.Claves();
    int i = 0;
    while(i < d.Claves().cardinal()){
        Definir(conjClaves.minimo(), d.Obtener(conjClaves.minimo()));
        conjClaves.remover(conjClaves.minimo());
        i++;
    }
}

/*template <typename T>
DiccString<T>::DiccString(const DiccString& d) : claves(d.claves) {
    raiz = d.raiz != NULL ? new Nodo(*d.raiz) : NULL;
}*/



//Tengo que fijarme que no sea null, por que si no estaria haciendo
//un double free o incursionando en alguna turbiedad.
template <typename T>
DiccString<T>::~DiccString(){
    if(raiz != NULL){
        delete raiz;
    }
}

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
    tam++;

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
//Ya hice esto y funciona asi que lo dejo, pero hago notar 
//que claves es un conjunto y podria haber usado las
//operaciones de Conj.cpp, como pertenece() y salia al toque con eso.

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
    ASSERT(Definido(clave));
    Nodo* x = raiz;
    int i = 0;
    //Tenia while(siguientes[j] != NULL && clave.length() > i)
    //pero con el ASSERT me lo puedo sacar de encima.
    //Lo mismo para el otro obtener, son lo mismo.
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

//Esta implementacion es como la que usamos en el tp, 
template <typename T>
void DiccString<T>::Borrar(const string& clave){
    ASSERT(Definido(clave));
 // if(Definido(clave)){
    Nodo* pivote = raiz;
    Nodo* ultimo = NULL;
    int desde = 0;
    int i = 0;
    while(clave.length() > i){
      pivote = pivote -> siguientes[int(clave[i])];
      if((pivote->definicion != NULL && clave.length() - 1 > i) || cantHijos(pivote) > 1){
        desde = i+1;
        ultimo = pivote;
      }
      i++;
    }
    T* sig = pivote -> definicion;
    pivote -> definicion = NULL;
    delete sig;
    claves.remover(clave);
    tam--;
    if(ultimo != NULL){
      Nodo* del = ultimo -> siguientes[int(clave[desde])];
      ultimo -> siguientes[int(clave[desde])] = NULL;
      //cantHijos--;
      delete del;
    } else{
      if(cantHijos(pivote) == 0){
        Nodo* dl = raiz -> siguientes[int(clave[0])];
        raiz -> siguientes[int(clave[0])] = NULL;
        delete dl;
      }
    }

    if(tam == 0){
      delete raiz;
      raiz = NULL;
    }
 // }
}

#endif
