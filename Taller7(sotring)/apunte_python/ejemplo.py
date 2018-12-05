#HOLA, SOY UN COMENTARIO!

# No hay ";" como en C++. 
# No hay "{}" para determinar un scope. Eso se hace con indentaciones
# No hay que especificar tipos!!


#Definimos la funcion
def pares1(lista):
    #recorremos la lista
    for i in range(len(lista)):
        #nos fijamos los multiplos de 2
        if ((lista[i] % 2) == 0):
            #imprimimos el valor
            print lista[i], #Parche para que se vea mejor la salida por consola 
    print ""            




def pares2(lista):
    for elem in lista:
        if ((elem % 2) == 0):
            print elem,
    print ""            #Parche para que se vea mejor la salida por consola


def factorial(n):
    res = 1
    #iteramos hasta n+1 porque range va no incluye el ultimo numero
    for i in range(1,n+1): #Preguntar.. "que pasa si no ponemos el 1 ??? "
        res *= i
    return res

#corremos la funcion pares
pares1(range(10))

pares2(range(10))

print "El factorial de 5 es:", factorial(5)


vec = [41, 12, 11, 7, 3 ,6]
elem_prim = vec[0]
ele_ult = vec[-1]
ele_ult2 = vec[len(vec)-1]
sub_vec = vec[1:3] # el ultimo es no inclusive
prefix = vec[:2]
sufix = vec[3:]	
