#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p = Pila();
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());  
}

void test_apilar() {
  Pila p = Pila();
  ElemPila elem = {1, "Nico", "Alumno"};
  
  p.apilar(elem);  
  ASSERT_EQ(elem.id, p.tope().id);
  ASSERT_EQ(elem.nombre, p.tope().nombre);
  ASSERT_EQ(elem.descripcion, p.tope().descripcion);
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT(!p.esVacia());
}

void test_desapilar() {
  Pila p = Pila();
  ElemPila elem = {1, "Nico", "Alumno"};
  p.apilar(elem);
  ElemPila elemDesapilado = p.tope();
  p.desapilar();
  ASSERT_EQ(elem.id, elemDesapilado.id);
  ASSERT_EQ(elem.nombre, elemDesapilado.nombre);
  ASSERT_EQ(elem.descripcion, elemDesapilado.descripcion);
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());
}

void test_asignacion() {
  Pila p = Pila();
  ElemPila elem = {1, "Nico", "Alumno"};
  p.apilar(elem);
  Pila p2 = Pila();
  p2 = p;
  ASSERT_EQ(elem.id, p.tope().id);
  ASSERT_EQ(elem.nombre, p.tope().nombre);
  ASSERT_EQ(elem.descripcion, p.tope().descripcion);
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT(!p.esVacia());
  ASSERT_EQ(elem.id, p2.tope().id);
  ASSERT_EQ(elem.nombre, p2.tope().nombre);
  ASSERT_EQ(elem.descripcion, p2.tope().descripcion);
  ASSERT_EQ(p2.tamanio(), 1);
  ASSERT(!p2.esVacia());
}

void test_destructor() {
  Pila* p = new Pila();
  ElemPila elem = {1, "Nico", "Alumno"};
  p->apilar(elem);
  delete p;
  ASSERT_EQ(p->tamanio(), 0);
  ASSERT(p->esVacia());
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_asignacion);
  RUN_TEST(test_destructor)
  // HACER MAS TEST

  return 0;
}
