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
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares
                int cantidadHijos(Nodo* n){
                    int res = 0;

                    for (int i = 0; i < 256; i++) {
                        if (n->siguientes[i] != NULL){
                            res++;
                        }
                    }

                    return res;
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
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d)/*: raiz(NULL), claves()*/ {

    raiz = NULL;

    Conj<string> conjClaves = d.Claves();
    for (int i = 0; i < d.Claves().cardinal(); i++) {

        //string aux = conjClaves.minimo();
        this->Definir(conjClaves.minimo(), d.Obtener(conjClaves.minimo()));
        conjClaves.remover(conjClaves.minimo());
    }

}

template <typename T>
DiccString<T>::~DiccString(){
    if (this->raiz != NULL) {
        borrarNodo(this->raiz);
        this->raiz = NULL;
    }
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){

    if (this->raiz == NULL) {
        this->raiz = new Nodo();
    }

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {

        if (aux->siguientes[int(clave[i])] != NULL) {

            //Si tiene siguiente para el caracter dado, sigo recorriendo.
            aux = aux->siguientes[int(clave[i])];

        }else{

            //Si no, creo los nuevos nodos. Una vez que no tiene siguiente para
            //un caracter, no va a tener para el resto de la palabra.

            aux->siguientes[int(clave[i])] = new Nodo;
            aux = aux->siguientes[int(clave[i])];

        }
    }

    if (aux->definicion != NULL){
        delete aux->definicion;
    }
    aux->definicion = new T(significado);


    this->claves.insertar(clave);
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    if (this->raiz == NULL) {
        return false;
    }

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {
        if (aux->siguientes == NULL || aux->siguientes[int(clave[i])] == NULL) {
            return false;
        }else{
            aux = aux->siguientes[int(clave[i])];
        }

        //if (aux->siguientes[int(clave[i])] != NULL) {
        //    aux = aux->siguientes[int(clave[i])];
        //}else{
        //    return false;
        //}
    }

    return aux->definicion != NULL;
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {
        aux = aux->siguientes[int(clave[i])];
    }

    return *aux->definicion;

}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {
        aux = aux->siguientes[int(clave[i])];
    }

    return *aux->definicion;
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {

    Nodo* aux = this->raiz;
    Nodo* padreAux = this->raiz;
    Nodo* hastaDondeEliminar = NULL;
    Nodo* padreHDE = NULL;
    int iHDE = 0;

    for (int i = 0; i < clave.length(); i++) {

        if (aux->definicion == NULL && cantidadHijos(aux) == 1 && hastaDondeEliminar == NULL){
            hastaDondeEliminar = aux;
            padreHDE = padreAux;
            iHDE = i-1;

        }else if ((cantidadHijos(aux) > 1 || aux->definicion != NULL) && (i != clave.length()-1)) {
            hastaDondeEliminar = NULL;
            padreHDE = NULL;
            iHDE = 0;

        }

/*
        if (i == clave.length()-1 && cantidadHijos(aux->siguientes[int(clave[i])]) == 0){
            hastaDondeEliminar = aux;
            padreHDE = padreAux;
            iHDE = i-1;
        }
*/
        padreAux = aux;
        if(cantidadHijos(padreAux) > 1 && i == clave.length()-1){
            padreHDE = padreAux;
            hastaDondeEliminar = aux->siguientes[int(clave[i])];
            iHDE = i;
        }
        aux = aux->siguientes[int(clave[i])];

    }

    if (hastaDondeEliminar == this->raiz && cantidadHijos(aux) == 0) {
        borrarNodo(this->raiz);
        this->raiz = NULL;
        claves.remover(clave);
        return;
    }

    if (cantidadHijos(aux) > 0){
        delete aux->definicion;
        aux->definicion = NULL;
    }else{
        borrarNodo(hastaDondeEliminar);
        padreHDE->siguientes[int(clave[iHDE])] = NULL;
    }

    claves.remover(clave);
}


#endif
