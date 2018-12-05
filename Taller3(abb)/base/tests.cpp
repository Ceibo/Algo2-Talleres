#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

void test_cardinal() {
	Conjunto<int> c;
	ASSERT_EQ(c.cardinal(),0);
	cout << endl << "Test Cardinal 0" << endl;

	c.insertar(10);
	ASSERT_EQ(c.cardinal(),1);
	cout << "Test Cardinal 1" << endl;
	c.insertar(11);
	cout << "Test Cardinal 2" << endl;
	c.insertar(12);
	cout << "Test Cardinal 3" << endl;
	c.insertar(40);
	c.insertar(31);
	c.insertar(3);
	c.insertar(9);
	c.insertar(15);
	ASSERT_EQ(c.cardinal(),8);
	cout << "Test Cardinal 4" << endl;
	c.insertar(3);
	c.insertar(33);
	c.insertar(35);
	c.insertar(6);
	c.insertar(3);
	ASSERT_EQ(c.cardinal(),11);
	cout << "Test Cardinal 5" << endl;
	cout << "Test Cardinal OK!" << endl;
}

void test_insertar() {
	Conjunto<int> c;
	cout <<  endl << "1" << endl;
	c.insertar(42);
	cout << "2" << endl;
	ASSERT( c.pertenece(42) );
	cout << "3" << endl;


	// Chequear insertar más elementos
	cout << "Test Insertar OK!" << endl;
}

void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
 	// - Borrar una hoja
 	// - Borrar un nodo interno con un hijo
 	// - Borrrun nodo interno con dos hijos
 	Conjunto<int> c;
 	c.insertar(42);
 	cout << "1" << endl;
 	c.insertar(44);
 	cout << "2" << endl;
 	c.insertar(104);
 	cout << "3" << endl;
 	c.insertar(450);
 	cout << "4" << endl;
 	c.insertar(-46);
 	cout << "5" << endl;
 	c.insertar(-460);
 	cout << "6" << endl;
 	c.insertar(130);
 	cout << "7" << endl;
 	c.insertar(43);
 	cout << "8" << endl;


	bool pertenencia;

	// caso que chequea borrar una hoja
	c.remover(44);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// Completar
 //	ASSERT( false );

}

void test_maximo() {
	// Completar
 	ASSERT( false );
}

void test_minimo() {
	// Completar
	ASSERT( false );
}

int main() {

	RUN_TEST(test_cardinal);
	RUN_TEST(test_insertar);
	RUN_TEST(test_remover);
	RUN_TEST(test_maximo);
	RUN_TEST(test_minimo);
	return 0;
}