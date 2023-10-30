import random
import sys
sys.setrecursionlimit(10000)

def menu():
    '''
    Funcion que despliega el menú del juego.
    '''

    #Despliega el banner del menú con las opciones
    print("╔══════════════════════════════╗")
    print("║      \033[1;31m" + "UN" + "\033[1;33m" + "ST" + "\033[1;32m" + "AB" + "\033[1;34m" + "LE" + "\033[0;m", end=" ")
    print("\033[1;31m" + "UN" + "\033[1;33m" + "IC" + "\033[1;32m" + "OR" + "\033[1;34m" + "NS" + "\033[0;m       ║")
    print("╠══════════════════════════════╣")
    print("║      \033[1;32m" + "1.Jugar" + "\033[0;m   \033[1;31m" + "2.Salir" + "\033[0;m       ║")
    print("╚══════════════════════════════╝")

    #Se solicita la opción al usuario
    opcion = input("Seleccione el número de la opción para continuar: ")
    
    #Procesador de opciones
    if opcion == "1":
        return inicio()
    elif opcion == "2":
        return "\033[5;31m" + "Saliste :((" + "\033[0;m"
    else:
        return "No se digitó ninguna de las opciones disponibles."

def inicio():
    '''
    Función que maneja el inicio del juego.
    '''

    # Se hace el mazo
    mazo = enlace()

    #Asignación de las manos, asignar_manos regresa dos valores: la mano y la lista de descarte actualizada
    asignacion = asignar_manos(mazo)
    mano1 = asignacion[0]
    mazo_nuevo = asignacion[1]
    asignacion = asignar_manos(mazo_nuevo)
    mano2 = asignacion[0]
    mazo_nuevo = asignacion[1]
    # Se va a la funcion turno primer jugador
    return turno(mazo, mano1, mano2, mazo_nuevo, [], [], 0)

def turno(mazo, mano1, mano2, mazo_nuevo, establo1, establo2, flag):
    '''
    Funcion que decide de quien es el turno
    '''
    #Validaciones de las entradas
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano1) != True:
        return "Error 02"
    elif verificar_matriz(mano2) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo1) != True:
        return "Error 05"
    elif verificar_matriz(establo2) != True:
        return "Error 06"
    elif type(flag) != int :
        return "Error 07"
    elif len(mano1) > 5:
        mano1= ajustar_mano(mano1)
        # Se verifica que la mano tenga 5 o menos cartas
        return turno_aux(mazo, mano1, mano2, mazo_nuevo, establo1, establo2, flag)
    else:
        return turno_aux(mazo, mano1, mano2, mazo_nuevo, establo1, establo2, flag)

def turno_aux(mazo, mano1, mano2, mazo_nuevo, establo1, establo2, flag):
    '''
    Funcion auxiliar de turno
    '''
    # Verifica que aun no haya un ganador o el mazo no haya acabado
    if len(establo1) == 5 and flag == 2:
        print("Jugador 1 ha ganado")
        return repetir(mazo)
    elif len(establo1) == 5 and flag == 1:
        print("Jugador 2 ha ganado")
        return repetir(mazo)
    elif mazo_nuevo == []:
        print("Se termino el juego")
        return repetir(mazo)
    # En caso de que alguien gane se da la opcion de volver a jugar
    else:
    # La flag permite saber de quien es el turno
    # La flag = 0es para indicar que es el inicio del turno
        if flag == 0:
            return turno_jugador(mazo, mano1, mano2, mazo_nuevo, establo1, establo2, 2)
        elif flag == 1:
            return turno_jugador(mazo, mano2, mano1, mazo_nuevo, establo2, establo1, 2)
        else:
            return turno_jugador(mazo, mano2, mano1, mazo_nuevo, establo2, establo1, 1)

def turno_jugador(mazo, mano_jugador, mano_rival, mazo_nuevo, establo_jugador, establo_rival, flag):
    '''
    Funcion que genera el turno del jugador 
    '''
    #Validaciones de las entradas
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano_jugador) != True:
        return "Error 02"
    elif verificar_matriz(mano_rival) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo_jugador) != True:
        return "Error 05"
    elif verificar_matriz(establo_rival) != True:
        return "Error 06"
    elif type(flag) != int :
        return "Error 07"
    else:
        return turno_jugador_aux(mazo, mano_jugador, mano_rival, mazo_nuevo, establo_jugador, establo_rival, flag)
    
def turno_jugador_aux(mazo, mano_jugador, mano_rival, mazo_nuevo, establo_jugador, establo_rival, flag):
    '''
    Funcion auxiliar de turno_jugador1
    '''
    #Se dan los prints 
    print("\n╔════\u001b[45;1m\u001b[1mEstablos\u001b[0m════════════════════════════════════════════════════════════════════════════════════╗")
    print("Establo del jugador actual:\n" + imprimir_lista(establo_jugador))
    print("Establo del jugador rival:\n" + imprimir_lista(establo_rival))
    print("╚══════════════════════════════════════════════════════════════════════════════════════════════╝")
    print("Inicia el turno, obtendrás una nueva carta.")


    # Se entrega una carta mas a la mano del jugador
    asignacion= dar_carta(mazo_nuevo,mano_jugador)
    mano_jugador= asignacion[0]
    mazo_nuevo= asignacion[1]
    print("\n╔════\u001b[45;1m\u001b[1mManos\u001b[0m═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗")
    print("Mano del jugador:\n" + imprimir_lista(mano_jugador))
    eleccion= seleccionar_carta(mano_jugador)
    print("--------------------------------------------------------------------------------------------------")
    #Se le pide el nombre de la carta que desea jugar
    return jugar_carta(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,eleccion,flag)

def imprimir_carta(carta):
    """
    Función que retorna una carta escrita
    """
    return f"{carta[0]} | {carta[1]} | {carta[2]} | {carta[3]}"

def imprimir_lista(listacartas):
    """
    Imprime todas las cartas de una lista
    """
    if not isinstance(listacartas, list):
        return "Error01"
    return imprimir_lista_aux(listacartas, 0, len(listacartas), "")

def imprimir_lista_aux(listacartas, indice, largo, res):
    """
    Funcion auxiliar
    """
    if indice == largo:
        return res
    if listacartas == []:
        return "No hay cartas aún."

    stringo = f"{indice + 1}. {imprimir_carta(listacartas[indice])}\n"
    return imprimir_lista_aux(listacartas, indice + 1, largo, res + stringo)

def seleccionar_carta(mano):
    '''
    Funcion que selecciona una carta
    '''
    # Validaciones
    if verificar_matriz(mano) != True:
        return "Error 01"
    else:
        # Se solicita una opcion 
        eleccion= input("Escriba el nombre de la carta que desea jugar: ")
        return seleccionar_carta_aux(mano,0,len(mano),eleccion)

def seleccionar_carta_aux(mano,ind,largo,eleccion):
    '''
    Funcion auxiliar de seleccionar_carta
    '''
    # Revisa si la carta elegida existe en el mazo si no rebota
    if ind >= largo:
        print("No selecciono ninguna carta de su mano, por favor vuelva a intentarlo")
        return seleccionar_carta(mano)
    elif mano[ind][0] == eleccion:
        return eleccion
    else:
        return seleccionar_carta_aux(mano,ind+1,largo,eleccion)
    

def jugar_carta(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,eleccion,flag):
    # La mano_jugador es la mano del jugador que le corresponde el turno 
    '''
    Funcion que simula el turno de un jugador
    '''
    #Mismas validaciones
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano_jugador) != True:
        return "Error 02"
    elif verificar_matriz(mano_rival) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo_jugador) != True:
            return "Error 05"
    elif verificar_matriz(establo_rival) != True:
            return "Error 06"
    elif type(eleccion) != str:
        return "Error 07"
    elif type(flag) != int :
        return "Error 08"
    else:
        return jugar_carta_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,eleccion,flag) 

def jugar_carta_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,eleccion,flag):
    '''
    Funcion auxiliar de jugar_carta
    '''
    # Se saca una carta para el jugador
    asignacion= sacar_carta(mano_jugador,eleccion)
    carta= asignacion[1]
    mano_jugador= asignacion[0]
    # Se compara de que tipo es la carta
    if carta[1] == "Desventaja":
        return sacrificar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)
    elif carta[1] == "Ventaja":
        return descartar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)
    elif carta[1] == "Magia":
        return robar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)
    else:
        return turno(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador + [carta],establo_rival,flag)

def sacar_carta(mano,eleccion):
    #Validaciones
    '''
    Funcion que procesa la eleccion de la carta y la elimina de la mano
    '''
    if verificar_matriz(mano) != True:
        return "Error 01"
    elif type(eleccion) != str:
        return "Error 02"
    else:
        return sacar_carta_aux(mano,eleccion,0,len(mano),[],[])

def sacar_carta_aux(mano,eleccion,ind,largo,carta,mano_nuevo):
    '''
    Funcion auxiliar de seleccion_carta_aux
    '''
    # Se busca el nombre de la carta dentro de la mano
    if ind >= largo:
        return [mano_nuevo,carta]
    elif mano[ind][0] == eleccion:
        return sacar_carta_aux(mano,eleccion,ind+1,largo,carta+mano[ind],mano_nuevo)
    else:
        return sacar_carta_aux(mano,eleccion,ind+1,largo,carta,mano_nuevo+[mano[ind]])

def sacrificar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag):
    '''
    Funcion que sacrifica una carta de un establo
    '''
    #Validaciones
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano_jugador) != True:
        return "Error 02"
    elif verificar_matriz(mano_rival) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo_jugador) != True:
            return "Error 05"
    elif verificar_matriz(establo_rival) != True:
            return "Error 06"
    elif type(flag) != int :
        return "Error 07"
    # Aqui se valida que si el establo esta vacio no haga nada
    elif establo_jugador == []:
        return turno(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)
    # Aqui que si solo hay un carta en el establo que la quite
    elif len(establo_jugador) == 1:
        return sacrificar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,0,0,len(establo_jugador),[])
    # Se obtiene una posicion de la carta del establo a matar
    posicion= random.randint(0,((len(establo_jugador)-1)))
    return sacrificar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,0,len(establo_jugador),[])
    
def sacrificar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind,largo,nuevo_establo):
    '''
    Funcion auxiliar de sacrificar
    '''
    # Se mueven todas las cartas del establo menos la posicion que se mato
    if ind >= largo:
        return turno(mazo,mano_jugador,mano_rival,mazo_nuevo,nuevo_establo,establo_rival,flag)
    elif posicion == ind:
        return sacrificar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind+1,largo,nuevo_establo)
    else:
        return sacrificar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind+1,largo,nuevo_establo + [establo_jugador[ind]])

def descartar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag):
    '''
    Funcion que descarta una carta de un jugador
    '''
    # Mismas validaciones
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano_jugador) != True:
        return "Error 02"
    elif verificar_matriz(mano_rival) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo_jugador) != True:
            return "Error 05"
    elif verificar_matriz(establo_rival) != True:
            return "Error 06"
    elif type(flag) != int :
        return "Error 07"
    # Si la mano solo tiene una se busca quitar esa
    elif len(mano_rival) == 1:
        return descartar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,0,0,len(mano_rival),[]) 
    # Se saca una posicion a eliminar
    posicion= random.randint(0,((len(mano_rival)-1)))
    return descartar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,0,len(mano_rival),[])

def descartar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind,largo,nueva_mano):
    '''
    Funcion auxiliar de descartar
    '''
    #Se pasan todas las cartas a una nueva mano menos la posicion no deseada
    if ind >= largo:
        return turno(mazo,mano_jugador,nueva_mano,mazo_nuevo,establo_jugador,establo_rival,flag)
    elif posicion == ind:
        return descartar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind+1,largo,nueva_mano)
    else:
        return descartar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag,posicion,ind+1,largo,nueva_mano + [mano_rival[ind]])

def robar(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag):
    '''
    Funcion que hace que una carta entre a un establo
    '''
    # Mismas validaciones
    if verificar_matriz(mazo) != True:
        return "Error 01"
    elif verificar_matriz(mano_jugador) != True:
        return "Error 02"
    elif verificar_matriz(mano_rival) != True:
        return "Error 03"
    elif verificar_matriz(mazo_nuevo) != True:
        return "Error 04"
    elif verificar_matriz(establo_jugador) != True:
            return "Error 05"
    elif verificar_matriz(establo_rival) != True:
            return "Error 06"
    elif type(flag) != int :
        return "Error 07"
    # Se verifica que el mazo no este vacio 
    elif mazo_nuevo == []:
        return turno(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)
    else:
        return robar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)

def robar_aux(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag):
    '''
    Funcion auxiliar de entrar_establo
    '''
    # Se da una carta al jugador y se modifica el mazo
    asignacion= dar_carta(mazo_nuevo,mano_jugador)
    mazo_nuevo= asignacion[1]
    mano_jugador= asignacion[0]
    return turno(mazo,mano_jugador,mano_rival,mazo_nuevo,establo_jugador,establo_rival,flag)

def enlace():
    '''
    Funcion que enlaza generar_mazo y retornar_contenido
    '''
    #Define el archivo como una variable
    nombre_archivo= "Mazo.txt"

    #Obtiene el contenido
    contenido= retornar_contenido(nombre_archivo)

    #Genera el mazo y lo retorna
    mazo= generar_mazo(contenido)
    return mazo

def generar_mazo(contenido):
    '''
    Funcion que genera el mazo a usar
    '''
    # Validaciones para la variable contenido
    if type(contenido) != str:
        return "Error 01"
    # Retorna a la auxiliar
    else:
        return generar_mazo_aux(contenido,[],[],"",0,len(contenido))
        # Se entrega contenido
        # Se genera una variable para dar la respues, otra de indice y otra de largo
        # Se da una variable info, que es donde se almacen la informacion de UNA carta
        # Se da la variable temporal para almacenar los componentes de la carta 

def generar_mazo_aux(contenido,res,info,temporal,ind,largo):
    '''
    Funcion que hace el contenido del txt en diferentes listas, separadas por carta
    '''
    # Genera una condicion de parada cuando todo el contenido haya sido recorrido y retorna res
    if ind >= largo:
        return res 
    
    # Busca una "," y si la encuentra introduce temporal en info y resetea temporal
    elif contenido[ind] == ",":
        return generar_mazo_aux(contenido,res,info+[temporal],"",ind+2,largo)
    
    # Busca un "\n" y si la encuentra introduce info y temporal a res y resetea ambos
    elif contenido[ind] == "\n":
        return generar_mazo_aux(contenido,res+[info + [temporal]],[],"",ind+1,largo)

    # Si no encuentra nada de lo que buscaba, introduce el caracter en temporal
    else:
        return generar_mazo_aux(contenido,res,info,temporal + contenido[ind],ind+1,largo) 


def retornar_contenido(nombre_archivo):
    '''
    Funcion que retorna el contenido del txt del mazo
    '''
    #Validacion para nombre_archivo
    if type(nombre_archivo) != str:
        return "Error 01"
    #Retorna a la auxiliar
    else:
        return retornar_contenido_aux(nombre_archivo)

def retornar_contenido_aux(nombre_archivo):
    '''
    Funcion auxiliar de retornar_contenido
    '''
    directorio = nombre_archivo
    manejador_archivo = open(directorio, encoding="utf-8")
    contenidos = manejador_archivo.read()
    return contenidos

def asignar_manos(mazo):
    '''
    Funcion que asgina la mano inicial de un jugador
    '''

    # Validacion de las las entradas
    if type(mazo) != list:
        return "Error 01"
    else:
        return asignar_manos_aux(mazo,0,[])

def asignar_manos_aux(mazo,ind,mano):
    '''
    Funcion auxiliar de asignar_manos
    '''

    # Para cuando se hayan repartido 4 cartas
    if ind == 4:
        return [mano,mazo] # retorna la mano y el mazo actualizado
    else:
        #crea un temporal para almacenar los resultados y se los asigna a su lugar
        temporal= dar_carta(mazo,mano)
        return asignar_manos_aux(temporal[1],ind+1,temporal[0])

def dar_carta(mazo,mano):
    '''
    Funcion que le da una carta al jugador
    '''
    # Validaciones de mazo
    if type(mazo) != list:
        return "Error 01"
    elif type(mano) != list:
        return "Error 02"
    elif len(mazo) == 1:
        return dar_carta_aux(mazo,mano,[],0,len(mazo),0)
    else:
        # Se escoge un valor aleatorio
        posicion= random.randint(0,((len(mazo)-1)))
        return dar_carta_aux(mazo,mano,[],0,len(mazo),posicion)

def dar_carta_aux(mazo,mano,res,ind,largo,posicion):
    '''
    Funcion auxiliar de dar_carta
    '''
    if ind >= largo:
        return [mano,res] # Se retorna la mano con una cartar y el mazo sin la carta
    if posicion == ind:
        # Se compara al numero con el indice y cuando sea iguales se suma a mano la carta
        return dar_carta_aux(mazo,mano + [mazo[ind]],res,ind+1,largo,posicion)
    else:
        # Si no son iguales se van agregando al nuevo mazo
        return dar_carta_aux(mazo,mano,res + [mazo[ind]],ind + 1,largo,posicion)

def verificar_matriz(matriz):
    #Validaciones
    '''
    Funcion que verifica si la entrada es una matriz
    '''
    if type(matriz) != list:
        return False
    elif matriz == []:
        return True
    elif len(matriz) == 1:
        return True
    else:
        return verificar_matriz_aux(matriz)

def verificar_matriz_aux(matriz):
    '''
    Funcion auxiliar de verificar_matriz
    '''
    #Devuelve True or False dependiendo de las revisiones de filas y columnas
    filas= fila(matriz)
    columnas= columna(matriz)
    if filas == False or columnas == False:
        return False
    else: 
        return True
    
def fila(matriz):
    '''
    Funcion que verifica las filas de una matriz
    '''
    #Validaciones
    if type(matriz) != list:
        return "Error 01"
    else:
        return fila_aux(matriz,0,len(matriz))
    
def fila_aux(matriz,ind,largo):
    '''
    Funcion auxiliar de fila
    '''
    #Verifica las filas de la matriz
    if ind >= largo:
        return True
    elif type(matriz[ind]) != list:
        return False
    else:
        return fila_aux(matriz,ind+1,largo)
    
def columna(matriz):
    '''
    Funcion que verifica las columnas de una matriz
    '''
    #Validaciones
    if type(matriz) != list:
        return "Error 01"
    else:
        return columna_aux(matriz,0,len(matriz))
    
def columna_aux(matriz,ind,largo):
    '''
    Funcion auxiliar de fila
    '''
    #Verifica las columnas de la matriz
    if ind >= largo:
        return True
    elif len(matriz[0]) != len(matriz[ind]):
        return False
    else:
        return columna_aux(matriz,ind+1,largo)

def ajustar_mano(mano):
    '''
    Funcion que ajusta la mano de un jugador para que tenga 5 cartas maximo en caso de que tenga mas de 5
    '''
    #Validaciones
    if verificar_matriz(mano) != True:
        return "Error 01"
    # Se saca una posicion para eliminar
    posicion= random.randint(0,((len(mano)-1)))
    return ajustar_mano_aux(mano,posicion,0,len(mano),[])

def ajustar_mano_aux(mano,posicion,ind,largo,res):
    '''
    Funcion auxiliar de ajustar_mano
    '''
    # Se suman todas las posiciones menos la no deseada
    if ind >= largo:
        return res
    elif posicion == ind:
        return ajustar_mano_aux(mano,posicion,ind+1,largo,res)
    else:
        return ajustar_mano_aux(mano,posicion,ind+1,largo,res + [mano[ind]])


def repetir(mazo):
    '''
    Funcion que le da la opcion a los jugadores de repetir y volver a jugar
    '''
    # Validaciones
    if verificar_matriz(mazo) != True:
        return "Error 01"
    else:
        return repetir_aux(mazo)
    
def repetir_aux(mazo):
    '''
    Funcion auxiliar de repetir
    '''
    # Se despliega unas opciones
    print("Desea volver a jugar?")
    print('1. Si')
    print("Cualquier tecla. No")
    print("------------------------------------------------------------------------")
    opcion= input("Digite el numero de la opcion en la que desea continuar")
    # Si el jugador quiere continuar se asigna todo nuevamente
    if opcion == "1":
        asignacion= asignar_manos(mazo)
        mano1= asignacion[0]
        mazo_nuevo= asignacion[1]
        asignacion= asignar_manos(mazo_nuevo)
        mano2= asignacion[0]
        mazo_nuevo= asignacion[1]
        return turno(mazo,mano1,mano2,mazo_nuevo,[],[],0)
    else:
        print("\033[1;31m" + "2.Salir" + "\033[0;m")

print(menu())
