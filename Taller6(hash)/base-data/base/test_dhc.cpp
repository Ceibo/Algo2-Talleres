#include <iostream>
#include <fstream>
#include "DiccHashCerrado.hpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_Definido () {

	ASSERT(false);
}

void test_Definir () {

	ASSERT(false);
}

void test_String_Vacio () {

	ASSERT(false);
}

void test_Significado () {

	ASSERT(false);
}

void test_Borrar () {

	ASSERT(false);
}

void test_CantClaves () {

	ASSERT(false);
}

void test_claves(){
	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir("moncho",56);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar("juanca");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar("moncho");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );
}

void test_colisiones(){

	DiccHashCerrado<int> dh;

//	std::string archnom = "../data/uniforme.txt";
//	std::string archnom = "../data/gauss.txt";
	std::string archnom = "../data/libretas.txt";


	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		//if (val == 100) break;
	}
	archin.close();

	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
}

void test_redimensionado(){
	
	ASSERT(false);
}


int main() {

	RUN_TEST(test_Definido);
	RUN_TEST(test_Definir);
	RUN_TEST(test_String_Vacio);
	RUN_TEST(test_Significado);
	RUN_TEST(test_Borrar);
	RUN_TEST(test_CantClaves);
	RUN_TEST(test_claves);
	RUN_TEST(test_redimensionado);
	RUN_TEST(test_colisiones);

	return 0;
}
