#include <ostream>
#include <cassert>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 * 
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();
 
    // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     * 
     * ATENCION:
     * 
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     * 
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      // TODO completar...
    	T elemento;
    	Nodo* sig;
    	Nodo(const T& elem, Nodo* siguiente) : elemento(elem), sig(siguiente){}
    	Nodo();
    };

    Nodo* tope_;
    aed2::Nat tamanio_;
	void destruir();
};

template <typename T>
Pila<T>::Pila()
{
 	tope_ = NULL;
 	tamanio_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
	if(!esVacia()){
	Nodo* nodo = new Nodo(otra.tope(), NULL);
	tope_ = nodo;
	Nodo* actual = otra.tope_;
	Nodo* anterior = nodo;
	while(actual -> sig != NULL){
		Nodo* actual = actual -> sig;
		Nodo* siguiente = new Nodo(actual->elemento, NULL);
		anterior -> sig = siguiente;
		anterior = siguiente;
		tamanio_ ++;
		}
	}
}

template <typename T>
Pila<T>::~Pila()
{
	destruir();
}

template <typename T>
void Pila<T>::destruir()
{
	while(esVacia() == false){
		desapilar();
	}
}

template <typename T>
void Pila<T>::apilar(const T& elem)
{	 
	 tope_ = new Nodo(elem, tope_);
	 tamanio_ ++;

}

template <typename T>
void Pila<T>::desapilar()
{
	assert(esVacia() == false);
	Nodo* nodo = tope_ -> sig;
	delete tope_;
	tope_ = nodo;
	tamanio_ --;
}

template <typename T>
bool Pila<T>::esVacia() const
{
	return tamanio_ == 0;
}

template <typename T>
T& Pila<T>::tope()
{
	return tope_ -> elemento;
}

template <typename T>
const T& Pila<T>::tope() const
{
	return tope_ -> elemento;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
	return tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra)
{
    destruir();
	if(otra.tamanio_ > 0){
    	T vectorElementos[otra.tamanio_];
    	aed2::Nat i = 0;
    	Nodo* auxiliar = otra.tope_;
		while(i < otra.tamanio_){
			vectorElementos[i] = auxiliar -> elemento;
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

template <typename S>
std::ostream& operator << (std::ostream& os, const Pila<S>& pila)
{
	os << "[";
		typename Pila<S>::Nodo* aux = pila.tope_;
		while(aux != NULL){
			os << aux -> elemento;
			if(aux -> sig != NULL){
				os << ", ";
			}
			aux = aux -> sig;
		}
		os << "]";
}
