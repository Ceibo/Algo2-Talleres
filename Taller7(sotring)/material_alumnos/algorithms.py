from list_algorithms import presentar
import random

grupo= 'elegir nombre copado y no usar unicode' 

# ATENCION: 
#- descomentar el "@presentar" y dejarlo solamente en las implementaciones de los algoritmos a entregar
#- pueden agregar las funciones auxiliares que necesiten en este mismo archivo
#- solo se permite un unico envio


@presentar
def insertion_sort(a):
	i = 1
	for i in range(1, len(a)):
		j = i
		x = a[i]
		while j > 0 and a[j-1] > x:
			a[j], a[j-1] = a[j-1], a[j]
			j -= 1
		a[j] = x
	return a

def subindice_del_minimo_desde_i(a, i):
	j = i
	for i in range(i, len(a)-1):
		if a[i] > a[j]:
			j = i
	return j

@presentar
def selection_sort(a):
	i = 0
	while i <= len(a)-1:
		j = subindice_del_minimo_desde_i(a, i)
		a[i], a[j] = a[j], a[i]
		i += 1
	return a


#@presentar
def quicksort(a):
    return a

#@presentar
def heapsort(a):
    return a

#@presentar
def mergesort(lista):
	return a
