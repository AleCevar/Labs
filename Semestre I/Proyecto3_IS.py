import random
import sys
sys.setrecursionlimit(10000)

#--------------------------- Validaciones ----------------------------------------------------------------------------------------------------------------------------------
def verificar_entrada_letras(entrada, opc, tablero, mun_arañ, mun_incen,turno_incendio):
    '''
    Funcion que cambia la letra de la columna a un nmero
    '''
    listaabc = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

    flag = False
    i = 0
    largo = len(listaabc)

    while i < largo: 

        for i in range(0, len(listaabc)):
            if listaabc[i] == entrada:
                flag = True


            if listaabc[i] == entrada and flag == True:
                return i
                                        
        i += 1

    print('\033[5;31m' + '\n --> Entrada invalida en la columna' + '\033[0;m')
    return opcion_disparo(opc, tablero, mun_arañ, mun_incen,turno_incendio)

def verificar_entrada(entrada):
    #Funcion que verifica la carta de carta que el usuario escoge

    entradas_permitidas = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"]

    for i in range(0, len(entradas_permitidas)):
        if entradas_permitidas[i] == entrada:
            return True
        
    return False

def volver_a_jugar():
    #Funcion para volver a jugar xD
    
    opc = input("\033[1;32m\nDesea volver a jugar? \n \033[1;34m 1 --> Si \n \033[1;31m 2 --> No \033[0;m \n ⮕ ")
    
    if opc ==  "1": 

        return opcion(opc)
    
    else:
         
        print('\033[4;36m' + "Gracias por jugar Battleship TEC xD" + '\033[0;m')
        exit()

def contar_cantidad_barcos(tablero, barco):
    #Funcion que cuenta cual es la cantidad de barcos de un tipo que existen en el tablero

    i = 0 
    cuenta = 0

    while i < len(tablero): 
        j = 0

        while j < len(tablero[0]):
            if tablero[i][j] == barco:
                cuenta += 1

            j += 1
        i += 1
    
    if cuenta-1 <= 0:
        return 1
    
    else:
        return cuenta


def recuento_barcos(tablero, recuento): 

    '''
    Funcion que devuelve una lista con los barcos que fueron afectados de cualquier forma en el tablero,
    unicamente en el turno actual, se usa en conjunto con imprimir_mensaje_destruccion() para saber cual mensaje debe imprimir
    de acuerdo a los barcos que se hayan afectado
    '''

    i = 0

    while i < len(tablero):

        j = 0

        while j < len(tablero[0]):
            
            if tablero[i][j] == 5:
                recuento += [5]
                    
            if tablero[i][j] == 10:
                recuento += [10]    

            #confirmar_hundir solo está reusando la funcion para buscar la segunda parte del barco
            if tablero[i][j] == 6 and confirmar_hundir(tablero, 3) == True: #en este caso True significa que no existe el barco 3 en el tablero
                # if encontró un 6 (barco grande del jugador 1 dañado) en el tablero AND la otra mitad del barco NO es un 3 (o sea que es un 6)
                #solo entra aquí si ambas partes del barco grande están dañadas

                if validar_existencia_barcos(recuento, 6) == False: 
                    #validar_existencia_barcos busca si un numero de barco (en este caso 6) se encuentra en la lista de recuento o no
                    #se asegura de que no exista un 6 en la lista de recuento para poder añadirlo por primera vez (si ya hay un 6, se ignora para que no salga el mensaje 2 veces)
                    recuento += [6] #este numero 6 se utilizará más adelante para imrpimir el mensaje de "se DESTRUYÓ el barco grande del jugador 1"

            elif tablero[i][j] == 6:
                #aquí entra si enoncotró un barco 6 (barco grande jugador 1 dañado) en el tablero y la otra mitad del barco sigue en pie)

                if validar_existencia_barcos(recuento, "6") == False and validar_existencia_barcos(recuento, "existe 6") == False:
                    #el str "6" se almacena en recuento para ser usado luego indicando que debe imprimirse "se DAÑÓ una parte del barco grande del jugdor 1"
                    '''
                    el "existe 6" se usa para mantener constancia de que ya se imprimió con anterioridad el mensaje de que se dañó el barco,
                    "existe 6" se va a agregar a recuento al final de un turno donde se haya impactado la mitad de un barco grande.
                    "existe 6" va a dictar que se cumpla o no se cumpla este mismo if, para que no se vuelva a añadir otro "6" str que cause que imprima el mensaje de nuevo
                    si "existe 6" se encuentra en recuento, signfica que ya salió el mensaje a imprimir y por lo tanto, no debe volver a salir nunca
                    '''
                    recuento += ["6"]

            #mismos comentarios de antes pero aplicados para el 7 (barco grande juagdor 2)
            if tablero[i][j] == 7 and confirmar_hundir(tablero, 4) == True:
                if validar_existencia_barcos(recuento, 7) == False:
                    recuento += [7]
                    
            elif tablero[i][j] == 7:
                if validar_existencia_barcos(recuento, "7") == False and validar_existencia_barcos(recuento, "existe 7") == False:
                    recuento += ["7"]
                    
            j += 1

        i += 1
        
    return recuento


def validar_existencia_barcos(recuento, barco):
    '''
    Valida si ya existe cierto barco en el recuento de los barcos derribados, con el fin de que el mensaje de derribo solo aparezca 1 vez
    #True --> Ya se contó la destrucción de ese barco en "recuento"
    #False --> No existe ese barco en recuento
    '''

    i = 0
    while i < len(recuento):
        if recuento[i] == barco:
            return True
        
        i += 1
        
    return False


def imprimir_mensaje_destruccion(recuento): 
    #Imprime los mensajes de destruccion de barcos de acuerdo al recuento que se llevó de cantidad de barcos que se destruyeron en el camino

    i = 0
    while i < len(recuento):

        if recuento[i] == 5:
            print("--> ❌ Se ha destruido un barco pequeño del jugador 1: 🛥️")

        elif recuento[i] == 10:
            print("--> ❌ Se ha destruido un barco pequeño del jugador 2: 🚤")

        elif recuento[i] == "6":
            print('--> ⭕ Se ha dañado una parte del barco grande del jugador 1: 🛳️')
            
        elif recuento[i] == 6:
            print('--> ❌ Se ha destruido el barco grande del jugador 1: 🛳️🛳️')

        elif recuento[i] == "7":
            print('--> ⭕ Se ha dañado una parte del barco grande del jugador 2: 🚢')
            
        elif recuento[i] == 7:
            print('--> ❌ Se ha destruido el barco grande del jugador 2: 🚢🚢')

        i += 1


def eliminar_barcos(tablero):
    #Elimina los barcos del tablero que hayan sido destruidos
    
    i = 0
    while i < len(tablero):
        j = 0

        while j < len(tablero[0]):
            if tablero[i][j] == 5:
                tablero[i][j] = 0
            
            if tablero[i][j] == 10:
                tablero[i][j] = 0
                
                
            if tablero[i][j] == 6 and confirmar_hundir(tablero, 3) == True:
                tablero[i][j] = 0
               
                
            if tablero[i][j] == 7 and confirmar_hundir(tablero, 4) == True:
                tablero[i][j] = 0
                
                
            j += 1
            
        i += 1
    
    return tablero


def confirmar_hundir(tablero, barco):
    #busca que la otra mitad del barco no exista para poder confirmar su hundimiento

    i = 0
    while i < len(tablero):
        j = 0

        while j < len(tablero[0]):
            if tablero[i][j] == barco:
                return False
            j += 1 
        i += 1

    return True


def copiar_tablero(tablero):
    #Funcion que hace una copia de una matriz que se le pase

    i = 0
    tablero_resultante = []

    while i < len(tablero):
        j = 0
        fila = []

        while j < len(tablero[0]):
            fila += [tablero[i][j]]
            j += 1

        tablero_resultante += [fila]
        i += 1

    return tablero_resultante


def validar_destruccion_barcos_grandes(tablero, elemento):
    '''
    Funcion para verificar si los barcos grandes se destruyeron
    True --> Todavia quedan barcos
    False --> Ya no quedan barcos
    '''

    i = 0 
    largo_filas = len(tablero)
    cantidad_de_destruidos = 0 
    flag = True
    largo_columnas = len(tablero[0])
    
    while i < largo_filas: 

        j = 0 
        
        while j < largo_columnas: 

            if tablero[i][j] == elemento: 
                cantidad_de_detruidos += 1 
                
            elif cantidad_de_destruidos == 2: 
                flag = False
                break
            
            j += 1

        i += 1


def validacion_sin_barcos(tablero, elemento1, elemento2): 
    '''
    Funcion que verifica si alguno de los jugadores aun tiene barcos en el tablero 
    False --> El jugador ya no tiene barcos en el tablero 
    True --> El jugador aun tiene barcos en el tablero 
    '''

    i = 0
    filas = len(tablero)
    flag = False
    columnas = len(tablero[0])
    while i < filas: 

        j = 0
        
        while j < columnas: 

            if tablero [i][j] == elemento1 or tablero[i][j] == elemento2:
                flag = True 
                break

            j += 1 

        i += 1

    return flag


def coordenada_disparo_existen (coordenada_fila, coordenado_columna, tablero):
    '''
    Funcion que verifica si las coordenadas que el jugador elige para el disparo existen
    True --> Las coordenadas existen 
    False --> Las coordendas no existen 
    '''

    flag = False 
    largo_filas = len(tablero)
    i = 0 

    while i < largo_filas: 
        
        j = 0 
        largo_columnas = len(tablero[1])

        while j < largo_columnas: 

            if i == coordenada_fila and j == coordenado_columna:
                
                flag =  True 
                break 
            
            j += 1

        i =+ 1

    return flag 


def cantidad_de_mun(municion_de_disparo): 
    '''
    Funcion que regula la cantidad de disparos
    True -->  Aun le qued
    '''

    if municion_de_disparo == 0: 
        return False

    else: 
        return True 


#-------------------------- MOVIMIENTO DEL BARCO ---------------------------------------------------
def coordenadas(tablero):
    '''
    Funcion que saca las coordenadas de los barcos
    '''
    fila  = 0 
    largo_fila = len(tablero)
    res= [] 
    largo_columna = len(tablero[0])
    
    while fila < largo_fila:
        
        columna = 0 
        
        while columna < largo_columna:
            if tablero[fila][columna] == 1:
                res += [[1,fila,columna]]
            elif tablero[fila][columna] == 2:
                res += [[2,fila,columna]]
            elif tablero[fila][columna] == 3:
                res += [[3,fila,columna]]
            elif tablero[fila][columna] == 4:
                res += [[4,fila,columna]]
            elif tablero[fila][columna] == 6:
                res += [[6,fila,columna]]
            elif tablero[fila][columna] == 7:
                res += [[7,fila,columna]]

            columna += 1
        fila += 1
    return res


def avanzar(tablero):
    '''
    Funcion que regula el movimiento de los barcos 
    '''
    
    ubicaciones= coordenadas(tablero)
    num= 1
    #print (imprimir_tablero(tablero))
    while num < 3:
        ind=0
        while ind < 2:
            asignacion= sacar_lista(ubicaciones,num)
            if asignacion[0] == []:
                break
            else:
                barco_viejo= asignacion[0]
                ubicaciones= asignacion[1]

                asignacion= calcular_mov(barco_viejo,tablero,num)
                barco_nuevo= asignacion[0]
                tipo= asignacion[1]

                tablero[barco_viejo[0]][barco_viejo[1]] = 0
                tablero[barco_nuevo[0]][barco_nuevo[1]] = tipo
                
                ind= cantidad_barcos(ubicaciones,num)    
        num += 1

    while num < 5:
        asignacion= sacar_lista(ubicaciones,num)
        if asignacion[0] == []:
            num += 1
            continue
        else:
            barco= asignacion[0]
            ubicaciones= asignacion[1]
            barco_viejo1= barco[0]
            barco_viejo2= barco[1]

            tipo1= tablero[barco_viejo1[0]][barco_viejo1[1]]
            tipo2= tablero[barco_viejo2[0]][barco_viejo2[1]]

            asignacion= calcular_mov_grande(barco_viejo1,barco_viejo2,tablero,tipo1,tipo2)
            barco_nuevo1= asignacion[0]
            tipo1= asignacion[1]
            barco_nuevo2= asignacion[2]
            tipo2= asignacion[3]

            tablero[barco_viejo1[0]][barco_viejo1[1]]= 0
            tablero[barco_nuevo1[0]][barco_nuevo1[1]]= tipo1

            tablero[barco_viejo2[0]][barco_viejo2[1]]= 0
            tablero[barco_nuevo2[0]][barco_nuevo2[1]]= tipo2

            num += 1
    

    return tablero


def calcular_mov(barco,tablero,num):
    '''
    #Define la funcion que debe seguir dependiendo de la orientacion
    '''
    # 0 es derecha, 1 es abajo, 2 es izqueirda y 3 es arriba
    asignacion= definir_valores()
    if asignacion[0] == 0:
        return mov_derecha(barco,tablero,asignacion[1],num)
    elif asignacion[0] == 1:
        return mov_abajo(barco,tablero,asignacion[1],num)
    elif asignacion[0] == 2:
        return mov_izquierda(barco,tablero,asignacion[1],num)
    else:
        return mov_arriba(barco,tablero,asignacion[1],num)


def mov_derecha(barco,tablero,mov,num):
    '''
    Funcion que calcula la nueva posicion del barco cuando se mueve a la derecha
    '''
    
    pos_columna= barco[1]
    pos_columna += mov
    if pos_columna >= len(tablero[0]):
        dif= pos_columna - len(tablero[0])
        pos_columna= 0
        pos_columna += dif
        return verificacion_columna(barco,tablero,pos_columna,num)
    else:
        return verificacion_columna(barco,tablero,pos_columna,num)


def verificacion_columna(barco,tablero,mov,num):
    '''
    Funcion que verifica si el movimiento en las columnas se puede sar y calcula las consecuencias
    '''
    if tablero[barco[0]][mov] == 0:
        return [[barco[0],mov],num]
    else:
        return calcular_mov(barco,tablero,num)


def mov_abajo(barco,tablero,mov,num):
    '''
    print('abajo')
    Funcion que calcula la nueva posicion del barco cuando se mueve a abajo
    '''
    
    pos_fila= barco[0]
    pos_fila += mov
    if pos_fila >= len(tablero):
        dif= pos_fila - len(tablero)
        pos_fila= 0
        pos_fila += dif
        return verificacion_fila(barco,tablero,pos_fila,num)
    else:
        return verificacion_fila(barco,tablero,pos_fila,num)


def verificacion_fila(barco,tablero,mov,num):
    '''
    Funcion que verfica si el movimiento se puede dar y calcula las consecuencias
    '''
    if tablero[mov][barco[1]] == 0:
        return [[mov,barco[1]],num]
    else:
        return calcular_mov(barco,tablero,num)


def mov_izquierda(barco,tablero,mov,num):
    '''
    Funcion que calcula la nueva posicion del barco cuando se mueve a la izquierda
    '''
    
    pos_columna= barco[1]
    pos_columna -= mov
    if pos_columna < 0:
        pos_columna += 1
        dif= pos_columna
        pos_columna= len(tablero[0])-1
        pos_columna += dif
        return verificacion_columna(barco,tablero,pos_columna,num)
    else:
        return verificacion_columna(barco,tablero,pos_columna,num)
    

def mov_arriba(barco,tablero,mov,num):
    '''
    Funcion que calcula la nueva posicion del barco cuando se mueve a arriba
    '''
    
    pos_fila= barco[0]
    pos_fila -= mov
    if pos_fila < 0:
        pos_fila += 1
        dif= pos_fila
        pos_fila= len(tablero)-1
        pos_fila += dif 
        return verificacion_fila(barco,tablero,pos_fila,num)
    else:
        return verificacion_fila(barco,tablero,pos_fila,num)


def definir_valores():
    '''
    Funcion que define el valor de la orientacion y del numero de casillas que se va a mover
    '''
    return [random.randint(0,3),random.randint(1,3)]


def cantidad_barcos(coordenadas,num):
    '''
    Funcion que determina cuantos barcos del mismo numero quedan por mover
    '''
    ind= 0
    largo= len(coordenadas)
    while ind < largo:
        if coordenadas[ind][0] == num:
            return 1
        ind += 1
    return 2


def sacar_lista(coordenadas,num): 
    '''
    Funcion que saca coordenadas de un tipo de barcos en especifico de una lista de coordenadas
    '''

    i = 0 
    largo = len(coordenadas)
    res = []
    nueva_coordenadas= []
    while i < largo:   
        #print(i,res,nueva_coordenadas,coordenadas)
        if coordenadas[i][0] == num and num == 3:
            res += [[coordenadas[i][1]]+[coordenadas[i][2]]]

        elif num == 3 and coordenadas[i][0] == 6:
            res += [[coordenadas[i][1]]+[coordenadas[i][2]]]

        elif coordenadas[i][0] == num and num == 4:
            res += [[coordenadas[i][1]]+[coordenadas[i][2]]]  

        elif num == 4 and coordenadas[i][0] == 7:
            res += [[coordenadas[i][1]]+[coordenadas[i][2]]] 

        elif coordenadas[i][0] == num:
            res += [coordenadas[i][1]]+[coordenadas[i][2]]
            nueva_coordenadas += coordenadas[i+1:]
            break
        else: 
            nueva_coordenadas  += [coordenadas[i]]
        i += 1       
    return [res,nueva_coordenadas]


def calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2):
    '''
    Funcion que calcula el movimiento de un barco grande
    '''
    asignacion= definir_valores()
    if asignacion[0] == 0:
        return mov_grande_derecha(barco1,barco2,tablero,tipo1,tipo2,asignacion[1])
    elif asignacion[0] == 1:
        return mov_grande_abajo(barco1,barco2,tablero,tipo1,tipo2,asignacion[1])
    elif asignacion[0] == 2:
        return mov_grande_izquierda(barco1,barco2,tablero,tipo1,tipo2,asignacion[1])
    else:
        return mov_grande_arriba(barco1,barco2,tablero,tipo1,tipo2,asignacion[1])


def mov_grande_derecha(barco1,barco2,tablero,tipo1,tipo2,mov):
    '''
    Funcion que calcula el movimiento de un barco grande a la derecha
    '''
    pos_columna1= barco1[1]
    pos_columna2= barco2[1]
    pos_columna1 += mov
    pos_columna2 += mov
    if pos_columna1 >= len(tablero[0]):
        if pos_columna2 >= len(tablero[0]):
            dif= pos_columna1 - len(tablero[0])
            pos_columna1= 0
            pos_columna1 += dif
            dif= pos_columna2 - len(tablero[0])
            pos_columna2= 0
            pos_columna2 += dif
            return verificacion_grande_horizontal(barco1,barco2,tablero,tipo1,tipo2,pos_columna1,pos_columna2)
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    elif pos_columna2 >= len(tablero[0]):
         return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    else:
        return verificacion_grande_horizontal(barco1,barco2,tablero,tipo1,tipo2,pos_columna1,pos_columna2)


def verificacion_grande_horizontal(barco1,barco2,tablero,tipo1,tipo2,pos_columna1,pos_columna2):
    '''
    Funcion que verifica
    '''
    if tablero[barco1[0]][pos_columna1] == 0:
        if tablero[barco2[0]][pos_columna2] == 0:
            return [[barco1[0],pos_columna1],tipo1,[barco2[0],pos_columna2],tipo2]
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    else:
        return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)


def mov_grande_abajo(barco1,barco2,tablero,tipo1,tipo2,mov):
    '''
    Funcion que calcula el movimiento de un barco grande a abajo
    '''
    pos_fila1= barco1[0]
    pos_fila1 += mov
    pos_fila2= barco2[0]
    pos_fila2 += mov
    if pos_fila1 >= len(tablero):
        if pos_fila2 >= len(tablero):
            dif = pos_fila1 - len(tablero)
            pos_fila1= 0
            pos_fila1 += dif
            dif= pos_fila2 - len(tablero)
            pos_fila2= 0
            pos_fila2 += dif
            return verificacion_grande_vertical(barco1,barco2,tablero,tipo1,tipo2,pos_fila1,pos_fila2)
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    elif pos_fila2 >= len(tablero):
        return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    else:
        return verificacion_grande_vertical(barco1,barco2,tablero,tipo1,tipo2,pos_fila1,pos_fila2)


def verificacion_grande_vertical(barco1,barco2,tablero,tipo1,tipo2,pos_fila1,pos_fila2):
    '''
    Funcion que verifica si es posible el movimiento vertical
    '''
    if tablero[pos_fila1][barco1[1]] == 0:

        if tablero[pos_fila2][barco2[1]] == 0:
            return [[pos_fila1,barco1[1]],tipo1,[pos_fila2,barco2[1]],tipo2]
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    else:
        return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    

def mov_grande_izquierda(barco1,barco2,tablero,tipo1,tipo2,mov):
    '''
    Funcion que calcula el movimiento de un barco grande a la izquierda
    '''
    pos_columna1= barco1[1]
    pos_columna1 -= mov
    pos_columna2= barco2[1]
    pos_columna2 -= mov
    if pos_columna1 < 0:
        if pos_columna2 < 0:
            pos_columna1 += 1
            pos_columna1 += len(tablero[0])-1
            pos_columna2 += 1
            pos_columna2 += len(tablero[0])-1
            return verificacion_grande_horizontal(barco1,barco2,tablero,tipo1,tipo2,pos_columna1,pos_columna2)
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    elif pos_columna2 < 0:
        return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    else:
        return verificacion_grande_horizontal(barco1,barco2,tablero,tipo1,tipo2,pos_columna1,pos_columna2)


def mov_grande_arriba(barco1,barco2,tablero,tipo1,tipo2,mov):
    '''
    Funcion que calcula el movimiento de un barco grande a arriba
    '''
    pos_fila1= barco1[0]
    pos_fila1 -= mov
    pos_fila2= barco2[0]
    pos_fila2 -= mov

    if pos_fila1 < 0:
        if pos_fila2 < 0:
            pos_fila1 += 1
            pos_fila1 += len(tablero)-1
            pos_fila2 += 1
            pos_fila2 += len(tablero)-1
            return verificacion_grande_vertical(barco1,barco2,tablero,tipo1,tipo2,pos_fila1,pos_fila2)
        else:
            return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)
    elif pos_fila2 < 0:
        return calcular_mov_grande(barco1,barco2,tablero,tipo1,tipo2)

    else:
        return verificacion_grande_vertical(barco1,barco2,tablero,tipo1,tipo2,pos_fila1,pos_fila2)
    

#-----------------------------------------------------------------------------------------------------------------------------------

                                                                                                                         
def menu():
    #El menú principal
    print ('\033[0;34m' + '''
██████╗░░█████╗░████████╗████████╗██╗░░░░░███████╗  ░██████╗██╗░░██╗██╗██████╗░
██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░░░██╔════╝  ██╔════╝██║░░██║██║██╔══██╗
██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░░░█████╗░░  ╚█████╗░███████║██║██████╔╝
██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░░░██╔══╝░░  ░╚═══██╗██╔══██║██║██╔═══╝░
██████╦╝██║░░██║░░░██║░░░░░░██║░░░███████╗███████╗  ██████╔╝██║░░██║██║██║░░░░░
╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░╚══════╝╚══════╝  ╚═════╝░╚═╝░░╚═╝╚═╝╚═╝░░░░░''' + '\033[0;m') 


    opc = input("""
\033[1;36m 1. JUGAR \033[0;m
\033[1;31m 2. SALIR \033[0;m
 ⮕ : """)
    
    opcion(opc)


def opcion(opc):

    while True:

        if opc == "1":
            #falta validacion para que no se pueda poner algo que no sea un numero
            
            print('\033[1;36m' +"\n\t    --- NOTA ---"+ '\033[0;m')
            print('\033[1;36m' + "-->" + '\033[0;m' + " Tamaño máximo de tablero: 26x26 \n"'\033[1;36m' + "-->" '\033[0;m'+ " Tamaño mínimo de tablero: 5x5\n" )
            
            filas_tablero = input("Digite el numero de filas que debe tener el tablero:")
            columnas_tablero = input("Digite el numero de columnas que debe tener el tablero:")

            if verificar_entrada(filas_tablero) == True:
                filas_tablero = int(filas_tablero)
                
            else:
                print("\n-------------------------------------------------------------------------------\n")
                print('\033[5;31m' + "--> Las dimensiones del tablero solicitado no son posibles, vuelva a intentarlo\n"+ '\033[0;m')
                continue

                
                
            if verificar_entrada(columnas_tablero) == True:
                columnas_tablero = int(columnas_tablero)
            
            else:
                print("\n-------------------------------------------------------------------------------\n")
                print('\033[5;31m' + "--> Las dimensiones del tablero solicitado no son posibles, vuelva a intentarlo\n"+ '\033[0;m')
                continue

                
            
            if (filas_tablero < 5 or columnas_tablero < 5) or (filas_tablero > 26 or columnas_tablero > 26):

                print("\n-------------------------------------------------------------------------------\n")
                print('\033[5;31m' + "--> Las dimensiones del tablero solicitado no son posibles, vuelva a intentarlo\n"+ '\033[0;m')
                continue

            tablero = generar_tablero(filas_tablero,columnas_tablero)
            turno(tablero, 1)

        if opc == "2":
            print('\033[5;31m' + "\n¡HASTA PRONTO! 😘" + '\033[0;m')
            exit()

        else:
            opc = input('\033[5;31m' + "\n--> Opción invalida. Intentelo de nuevo: "+ '\033[0;m')
            return opcion(opc)
    

def turno(tablero, jugador):

    print('\033[1;34m' + """
╭――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――╮
│                      --- SIMBOLOGÍA ---                      │
│                                                              │
│ > Casilla vacía: 🌊                  ㅤ            ㅤㅤ      │
│ > Casilla afectada por disparo: 💥               ㅤㅤ   ㅤ   │
│ > Casilla afectada por extension disparo incendiario:🔥ㅤㅤㅤ│
│                                                              │
│ > Barco pequeño destruido: ❌                          ㅤㅤㅤ│
│ > Barco grande dañado por disparo: ⭕  ㅤ  ㅤ             ㅤ │
│ > Barco grande destruido: ⭕ ⭕  ㅤ ㅤ  ㅤ ㅤ            ㅤㅤ│
│                    ㅤ   ㅤ  ㅤ  ㅤ                      ㅤㅤ │
│                                                              │
│ JUGADOR 1:   > Barcos pequeños:🛥️     ㅤㅤ ㅤ                 │
│              > Barco grande: 🛳️ 🛳️                             │
│                                                              │
│ JUGADOR 2:   > Barcos pequeños:🚤      ㅤㅤㅤ                │
│              > Barco grande: 🚢🚢                            │
│                                                              │
╰――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――╯""" + '\033[0;m')

    mun_arañ1 = 5
    mun_arañ2 = 5
    mun_incen1 = 1
    mun_incen2 = 1
    tipo_disparo = ""
    
    turno_incendio1= 'a'
    turno_incendio2= 'a'

    coord_fila_disparo = 0
    coord_colum_disparo = 0
    coord_fila_incendio1= 0
    coord_colum_incendio1= 0
    coord_fila_incendio2= 0
    coord_colum_incendio2= 0
    
    recuento = []

    imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)

    print("\n\t \033[1;34m JUGADOR 1: \033[0;m \nBarcos pequeños 🛥️  restantes:", contar_cantidad_barcos(tablero, 1))
    print("Barcos grandes 🛳️ 🛳️  restantes:", contar_cantidad_barcos(tablero, 3)-1, "\n")
    print("\t \033[1;34m JUGADOR 2: \033[0;m \nBarcos pequeños 🚤 restantes: ", contar_cantidad_barcos(tablero, 2))
    print("Barcos grandes 🚢🚢 restantes:", contar_cantidad_barcos(tablero, 4)-1, "\n")

    while True:
        
        if jugador%2 != 0:
            print('\033[3;36m' + "\n>>>>> TURNO JUGADOR 1️⃣" + '\033[0;m')
            
            if jugador != 1:
                imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, 0, 0)

            tablero = avanzar(tablero)
            tablero_original = copiar_tablero(tablero)

            if turno_incendio2 == 1:
                tablero = expandir_disparo_incendiario(tablero, coord_fila_incendio2, coord_colum_incendio2)
                recuento = recuento_barcos(tablero, recuento)
                tablero = eliminar_barcos(tablero)
            
            temp = disparar(tablero, mun_arañ1, mun_incen1,turno_incendio1)
            coord_fila_disparo = temp[0]
            coord_colum_disparo = temp[1]
            tipo_disparo = temp[2]
            turno_incendio1= temp[3]
            

            if tipo_disparo == 'disparo_araña':
                mun_arañ1 -= 1
            
            elif tipo_disparo == 'disparo_incendiario':
                mun_incen1 -= 1
                coord_fila_incendio1= coord_fila_disparo
                coord_colum_incendio1= coord_colum_disparo

            
            imprimir_tablero(tablero_original, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)
            print("🠇🠇🠇")
            imprimir_disparo(tablero, coord_fila_disparo, coord_colum_disparo, tipo_disparo, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)
            print("🠇🠇🠇")
            imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)

            recuento = recuento_barcos(tablero, recuento)
            imprimir_mensaje_destruccion(recuento)


            '''
            Estos if van a devolver un recuento distinto dependiendo del tipo de barcos que hayan afectado, este recuento será utilizado como base en el siguiente turno.
            Si en este turno se dañó a la mitad del barco grande del jugador 1, pero no se destruyó por completo, entonces dentro de recuento se almacenó un str '6';
            este '6' significa que se debe imprimir el mensaje de destrucción "se ha dañado tal barco" (cosa que se hace arriba de este comentario). 
            Como ya se imprimió el mensaje, se reemplaza este '6' en el recuento por un 'existe 6', que sirve para llevar constancia en el siguiente turno de que ya se imprimió
            el mensaje anteriormente y por lo tanto, hay cabida a que se imprima de nuevo pues no hay validación para "existe 6" dentro de la función imprimir_mensaje_destruccion()
            Por ultimo, cuando se destruya la segunda parte del barco, simplemente aparecerá el mensaje pues será contado como un int 6, cosa que activa el mensaje de
            destruccion completa de barco, luego de eso no se volverá a activar ningun mensaje pues no habrá interacción con este barco grande
            '''

            if (validar_existencia_barcos(recuento, '6') == True and validar_existencia_barcos(recuento, '7') == True) or (validar_existencia_barcos(recuento, "existe 6") == True and validar_existencia_barcos(recuento, "existe 7") == True):
                recuento = ["existe 6", "existe 7"]

            elif validar_existencia_barcos(recuento, '6') == True or validar_existencia_barcos(recuento, "existe 6") == True:
                recuento = ["existe 6"]

            elif validar_existencia_barcos(recuento, '7') == True or validar_existencia_barcos(recuento, "existe 7") == True:
                recuento = ["existe 7"]

            else:
                recuento = []  

            #print('aa', recuento)

            tablero = eliminar_barcos(tablero)

            jugador += 1

        else: 

            print('\033[3;36m' + "\n>>>>> TURNO JUGADOR 2️⃣" + '\033[0;m')

            imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, 0, 0)
            
            tablero = avanzar(tablero)
            tablero_original = copiar_tablero(tablero)
            
            if turno_incendio1 == 1:
                tablero = expandir_disparo_incendiario(tablero, coord_fila_incendio1, coord_colum_incendio1)
                recuento = recuento_barcos(tablero, recuento)
                tablero = eliminar_barcos(tablero)
            
            temp = disparar(tablero, mun_arañ2, mun_incen2,turno_incendio2)
            coord_fila_disparo = temp[0]
            coord_colum_disparo = temp[1]
            tipo_disparo = temp[2]
            turno_incendio2= temp[3]
            
            if tipo_disparo == 'disparo_araña':
                mun_arañ2 -= 1
            
            elif tipo_disparo == 'disparo_incendiario':
                mun_incen2 -= 1
                coord_fila_incendio2= coord_fila_disparo
                coord_colum_incendio2= coord_colum_disparo

            imprimir_tablero(tablero_original, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)
            print("🠇🠇🠇")
            imprimir_disparo(tablero, coord_fila_disparo, coord_colum_disparo, tipo_disparo, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)
            print("🠇🠇🠇")
            imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2)

            recuento = recuento_barcos(tablero, recuento)
            imprimir_mensaje_destruccion(recuento)

            #print('BB', recuento)

            if (validar_existencia_barcos(recuento, '6') == True and validar_existencia_barcos(recuento, '7') == True) or (validar_existencia_barcos(recuento, "existe 6") == True and validar_existencia_barcos(recuento, "existe 7") == True):
                recuento = ["existe 6", "existe 7"]

            elif validar_existencia_barcos(recuento, '6') == True or validar_existencia_barcos(recuento, "existe 6") == True:
                recuento = ["existe 6"]

            elif validar_existencia_barcos(recuento, '7') == True or validar_existencia_barcos(recuento, "existe 7") == True:
                recuento = ["existe 7"]

            else:
                recuento = []     

            #print('bb', recuento)     

            tablero = eliminar_barcos(tablero)
            
            jugador += 1

        print("\n\t \033[1;34m JUGADOR 1: \033[0;m \nBarcos pequeños 🛥️  restantes:", contar_cantidad_barcos(tablero, 1))
        print("Barcos grandes 🛳️ 🛳️  restantes:", contar_cantidad_barcos(tablero, 3)-1, "\n")
        print("\t \033[1;34m JUGADOR 2: \033[0;m \nBarcos pequeños 🚤 restantes: ", contar_cantidad_barcos(tablero, 2))
        print("Barcos grandes 🚢🚢 restantes:", contar_cantidad_barcos(tablero, 4)-1, "\n")

        if validacion_sin_barcos(tablero,1,3) == False and validacion_sin_barcos(tablero, 2, 4) == False:
            print('\033[1;31m' + 'Ya no quedan barcos. \nAmbos pierden >:/' + '\033[0;m')
            return volver_a_jugar()
        
        elif validacion_sin_barcos(tablero,1,3) == False:
            print('\033[1;32m' + 'El jugador 2 ha ganado. \n     Felicidades :D' + '\033[0;m')
            return volver_a_jugar()
        
        elif validacion_sin_barcos(tablero,2,4) == False:
            print('\033[1;32m' + 'El jugador 1 ha ganado. \n     Felicidades :D' + '\033[0;m')
            return volver_a_jugar()

        if 1 == turno_incendio1:
            tablero = expandir_disparo_incendiario(tablero, coord_fila_incendio1, coord_colum_incendio1)
            tablero_original = expandir_disparo_incendiario(tablero, coord_fila_incendio1, coord_colum_incendio1)
            
            turno_incendio1 += 1

        elif 2 == turno_incendio1:
            turno_incendio1= 'a'

        elif 0 == turno_incendio1:
            turno_incendio1 += 1

        if 1 == turno_incendio2:
            tablero = expandir_disparo_incendiario(tablero, coord_fila_incendio2, coord_colum_incendio2)
            tablero_original = expandir_disparo_incendiario(tablero, coord_fila_incendio2, coord_colum_incendio2)
            turno_incendio2 += 1

        elif 2 == turno_incendio2:
            turno_incendio2= 'a'
            
        elif 0 == turno_incendio2:
            turno_incendio2 += 1

            

def disparar(tablero, mun_arañ, mun_incen,turno_incendio):

    print("\nSeleccione tipo de arma.")
    print("1. Disparo directo 🎯 - Dispara únicamente a una casilla. - Munición: ∞")
    print("2. Disparo araña 🕷️ - Dispara a 5 casillas en forma de X. - Munición restante:", mun_arañ)
    print("3. Disparo incendiario 🔥 - Dispara a 5 casillas en forma de + para luego expandirse. - Munición restante:", mun_incen)
    opc = input("⮕ : ")
    return opcion_disparo(opc, tablero, mun_arañ, mun_incen,turno_incendio)


def opcion_disparo(opc, tablero, mun_arañ, mun_incen,turno_incendio):

    while True:

        coordenada_fila = input("\nDigite la coordenada de la fila a la que desea disparar: ")
        coordenada_columna = input("Digite la coordenada de la columna a la que desea disparar: ")
            
        if verificar_entrada(coordenada_fila) == True:
            coordenada_fila = int(coordenada_fila)
                        
        else:
            print('\033[5;31m' + "\n --> Entrada inválida en la fila" + '\033[0;m')
            continue

        coordenada_columna= verificar_entrada_letras(coordenada_columna,opc,tablero, mun_arañ, mun_incen,turno_incendio)




        if opc == "1":
            return disparo_directo(tablero,turno_incendio, coordenada_fila, coordenada_columna)
            
        elif opc == "2":
                if cantidad_de_mun(mun_arañ) == False: 
                    
                    print ('No te quedan municiones de este disparo')
                    return disparar(tablero, mun_arañ, mun_incen, turno_incendio)
                
                else:

                    return disparo_araña(tablero, turno_incendio, coordenada_fila, coordenada_columna)
            
        elif opc == "3":
            if cantidad_de_mun(mun_incen) == False: 

                print ('No te quedan municiones de este disparo')
                return disparar(tablero, mun_arañ, mun_incen, turno_incendio)
            
            else:
                return disparo_incendiario(tablero, 0, coordenada_fila, coordenada_columna)
            
        else:
            opc = input('\033[1;31m' + "\n--> La opción de disparo seleccionada no existe. Intentelo de nuevo: " + '\033[0;m')
            return opcion_disparo(opc, tablero, mun_arañ, mun_incen, turno_incendio)

# --------------- TIPOS DE DISPARO ------------------------------------------------------------------------------------------

def disparo_directo(tablero, turno_incendio, coordenada_fila, coordenada_columna):

    if tablero[coordenada_fila][coordenada_columna] == 1:
        tablero[coordenada_fila][coordenada_columna] = 5
            
    if tablero[coordenada_fila][coordenada_columna] == 3:
        tablero[coordenada_fila][coordenada_columna] = 6

    if tablero[coordenada_fila][coordenada_columna] == 2:
        tablero[coordenada_fila][coordenada_columna] = 10
        
    if tablero[coordenada_fila][coordenada_columna] == 4:
        tablero[coordenada_fila][coordenada_columna] = 7

    return [coordenada_fila, coordenada_columna, "disparo_directo", turno_incendio]


def disparo_araña(tablero, turno_incendio, coordenada_fila, coordenada_columna):

    largo_fila = len(tablero)
    largo_columnas = len(tablero[1])


    if tablero[coordenada_fila][coordenada_columna] == 1:
        tablero[coordenada_fila][coordenada_columna] = 5
        
    if tablero[coordenada_fila][coordenada_columna] == 3:
        tablero[coordenada_fila][coordenada_columna] = 6
        
    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 5
        
    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 6

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 6

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 5

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 6
        
    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 6

    # Jugador 2

    if tablero[coordenada_fila][coordenada_columna] == 2:
        tablero[coordenada_fila][coordenada_columna] = 10

    if tablero[coordenada_fila][coordenada_columna] == 4:
        tablero[coordenada_fila][coordenada_columna] = 7
        
    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 2: 
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[(coordenada_fila-1) %  largo_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[(coordenada_fila-1) %  largo_fila][(coordenada_columna-1) % largo_columnas] = 7
        
    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 10

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 7

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 2:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 7
        
    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 10
    
    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 7

    
    return [coordenada_fila, coordenada_columna, "disparo_araña", turno_incendio]


def disparo_incendiario(tablero, turno_incendiario, coordenada_fila, coordenada_columna):

    largo_fila = len(tablero)
    largo_columnas =  len(tablero[1])


    if tablero[coordenada_fila][coordenada_columna] == 1:
        tablero[coordenada_fila][coordenada_columna] = 5

    if tablero[coordenada_fila][coordenada_columna] == 3:
        tablero[coordenada_fila][coordenada_columna] = 6
        
    if tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] == 1:
        tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] = 5

    if tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] == 3:
        tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] = 6

    if tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] = 6

    if tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] == 1:
        tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] = 5

    if tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] == 3:
        tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] = 6
        
    if tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] = 5

    if tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] = 6
        
    if tablero[coordenada_fila][coordenada_columna] == 2:
        tablero[coordenada_fila][coordenada_columna] = 10

    if tablero[coordenada_fila][coordenada_columna] == 4:
        tablero[coordenada_fila][coordenada_columna] = 7
        
    if tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] == 2:
        tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] = 10

    if tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] == 4:
        tablero[(coordenada_fila-1) % largo_fila][coordenada_columna] = 7

    if tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] = 10

    if tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[coordenada_fila][(coordenada_columna+1) % largo_columnas] = 7

    if tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] == 2:
        tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] = 10

    if tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] == 4:
        tablero[(coordenada_fila+1) % largo_fila][coordenada_columna] = 7
        
    if tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] == 2:
        tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[coordenada_fila][(coordenada_columna-1) % largo_columnas] = 7


    return [coordenada_fila, coordenada_columna, "disparo_incendiario",turno_incendiario]


def expandir_disparo_incendiario(tablero, coordenada_fila, coordenada_columna):
    largo_fila = len(tablero)
    largo_columnas = len(tablero[1])

    if tablero[coordenada_fila][coordenada_columna] == 1:
        tablero[coordenada_fila][coordenada_columna] = 5

    if tablero[coordenada_fila][coordenada_columna] == 3:
        tablero[coordenada_fila][coordenada_columna] = 6

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas]  == 1:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] = 5

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] == 3:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] = 6

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] = 6

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] = 5

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] = 6

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] == 1:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] = 5

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] == 3:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] = 6

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 5

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 6

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 6

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 1:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 5

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 3:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 6

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 1:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 5

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 3:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 6

    #Jugador 2

    if tablero[coordenada_fila][coordenada_columna] == 2:
        tablero[coordenada_fila][coordenada_columna] = 10

    if tablero[coordenada_fila][coordenada_columna] == 4:
        tablero[coordenada_fila][coordenada_columna] = 7

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas]  == 2:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] = 10

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] == 4:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] = 7

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] = 10

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] = 7

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] == 2:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] = 7

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] == 2:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] = 10

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] == 4:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] = 7

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 2:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 7

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 10

    if tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 7

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 2:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 10

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] == 4:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 7

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 2:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 10

    if tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] == 4:
        tablero[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 7

    return tablero

    
# ---------------------- CREAR TABLERO CON BARCOS INCLUIDO ---------------------------------------------------------------------------------------------------------

def generar_tablero(filas,columnas):
    ''''Funcion que genera el tablero para el juego'''
    if type(columnas) != int:
        return "Error 01"
    elif type(filas) != int:
        return "Error 02"

    tablero = generar_tablero_vacio(filas,columnas)
    generar_pequeños(tablero)
    generar_grandes(tablero)

    return tablero


def generar_tablero_vacio(tamaño_filas, tamaño_columnas):
    '''Funcion que genera una matriz vacia de las dimensiones deseadas por el usuario'''

    tablero = []
    i = 0
    
    while i < tamaño_filas:
        j = 0
        fila = []
        while j < tamaño_columnas:
            fila += [0]
            j += 1
        
        tablero += [fila]
        i += 1

    return tablero


def generar_pequeños(tablero): #genera barcos pequeños
    '''Funcion que genera los barcos pequeños de ambos jugadores en los tableros'''
    
    i = 0
    num_barco = 1

    while num_barco <= 2:
        while i < 2:
            pos_fila = random.randint(0,len(tablero)-1)
            pos_columna = random.randint(0,len(tablero[0])-1)
            #print(pos_fila,pos_columna,tablero)
            if tablero[pos_fila][pos_columna] == 0: #verifica que el espacio donde se pondrá el barco no esté ocupado
                tablero[pos_fila][pos_columna] = num_barco
                i += 1
                #nota: no necesita else pues si resulta que no es un espacio vacio [0], vuelve a repetir el while porque i no aumenta
        i = 0
        num_barco += 1

    return tablero


def generar_grandes(tablero): #genera barcos grandes
    '''Funcion que genera los barcos pequeños de ambos jugadores en los tableros'''
    
    i = 0
    num_barco = 3

    while num_barco <= 4:

        while i < 1:
            
            orientacion = random.randint(0,1) #0 es horizontal, 1 es vertical
            pos_fila = random.randint(0,len(tablero)-1)
            pos_columna = random.randint(0,len(tablero[0])-1)
            #print(orientacion,pos_fila,pos_columna)
            if tablero[pos_fila][pos_columna] == 0: #verifica que el espacio donde se pondrá el barco no esté ocupado

                #verificacion de barco horizontal
                if orientacion == 0:

                    #verifica que la otra mitad del barco quepa en el tablero si se da que la primera mitad se genera en un borde
                    #and verifica que la otra mitad del barco pueda generarse (o sea que no haya un barco ya ahí)
                    if pos_fila+1 != len(tablero[0]) and tablero[pos_fila+1][pos_columna] == 0:

                        tablero[pos_fila][pos_columna] = num_barco
                        tablero[pos_fila+1][pos_columna] = num_barco
                        i += 1

                else: #verificacion de barco vertical

                    #verifica que la otra mitad del barco quepa en el tablero si se da que la primera mitad se genera en un borde
                    #and verifica que la otra mitad del barco pueda generarse (o sea que no haya un barco ya ahí)
                    if pos_columna+1 != len(tablero) and tablero[pos_fila][pos_columna+1] == 0:

                        tablero[pos_fila][pos_columna] = num_barco
                        tablero[pos_fila][pos_columna+1] = num_barco
                        i += 1

        i = 0
        num_barco += 1

    return tablero        


# ------ IMPRIMIR TABLERO ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

def imprimir_formato_tablero(tablero):
    
    print("\n") #solo deja un espacio antes
    
    listaabc = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

    i= 0
    while i < len(tablero):
        j= 0
        while j < len(tablero[0]):
            print('||',tablero[i][j], end= ' ')
            j += 1
        print('|| ', i, '\n')
        i += 1

    i = 0
    while i < len(tablero[0]):
        print('   ',listaabc[i], end= ' ')
        i += 1
    print("\n")



def imprimir_tablero(tablero, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2):
    tablero_imprimible = copiar_tablero(tablero)
    largo_fila = len(tablero)
    largo_columnas =  len(tablero[1])

    if turno_incendio1 == 1:
        if tablero_imprimible[coord_fila_incendio1][coord_colum_incendio1] != 1 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 3 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 2 and tablero[coord_fila_incendio2][coord_colum_incendio1] != 4 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 6 and tablero[coord_fila_incendio2][coord_colum_incendio1] != 7:
            tablero_imprimible[coord_fila_incendio1][coord_colum_incendio1] = 9

        if tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 1 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 2 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 6 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

    elif turno_incendio2 == 1:
        if tablero_imprimible[coord_fila_incendio2][coord_colum_incendio2] != 1 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 3 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 2 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 4 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 6 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 7:
            tablero_imprimible[coord_fila_incendio2][coord_colum_incendio2] = 9

        if tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 1 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 2 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 6 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9

    imprimir_formato_tablero(cambiar_simbolos(tablero_imprimible))


def imprimir_disparo(tablero, coordenada_fila, coordenada_columna, tipo_disparo, coord_fila_incendio1, coord_colum_incendio1, coord_fila_incendio2, coord_colum_incendio2, turno_incendio1, turno_incendio2):
    tablero_imprimible_temp = copiar_tablero(tablero)
    largo_fila = len(tablero)
    largo_columnas =  len(tablero[1])

    if turno_incendio1 == 1:
        if tablero_imprimible_temp[coord_fila_incendio1][coord_colum_incendio1] != 1 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 3 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 2 and tablero[coord_fila_incendio2][coord_colum_incendio1] != 4 and tablero_imprimible_temp[coord_fila_incendio1][coord_colum_incendio1] != 6 and tablero[coord_fila_incendio1][coord_colum_incendio1] != 7:
            tablero_imprimible_temp[coord_fila_incendio1][coord_colum_incendio1] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 1 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 2 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas]  != 6 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1-1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio1+1) % largo_fila][(coord_colum_incendio1+1) % largo_columnas] = 9

    elif turno_incendio2 == 1:
        if tablero_imprimible_temp[coord_fila_incendio2][coord_colum_incendio2] != 1 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 3 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 2 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 4 and tablero_imprimible_temp[coord_fila_incendio2][coord_colum_incendio2] != 6 and tablero[coord_fila_incendio2][coord_colum_incendio2] != 7:
            tablero_imprimible_temp[coord_fila_incendio2][coord_colum_incendio2] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 1 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 2 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas]  != 6 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2-1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2-1) % largo_columnas] = 9

        if tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 1 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 3 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 2 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 4 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 6 and tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] != 7:
            tablero_imprimible_temp[(coord_fila_incendio2+1) % largo_fila][(coord_colum_incendio2+1) % largo_columnas] = 9


    if tipo_disparo == "disparo_directo":
        tablero_imprimible_temp[coordenada_fila][coordenada_columna] = 8
        imprimir_formato_tablero(cambiar_simbolos(tablero_imprimible_temp))

        
    elif tipo_disparo == "disparo_araña":
        tablero_imprimible_temp[coordenada_fila][coordenada_columna] = 8
        tablero_imprimible_temp[(coordenada_fila-1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila-1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila+1) % largo_fila][(coordenada_columna-1) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila+1) % largo_fila][(coordenada_columna+1) % largo_columnas] = 8
        imprimir_formato_tablero(cambiar_simbolos(tablero_imprimible_temp))

    elif tipo_disparo == "disparo_incendiario":
        tablero_imprimible_temp[coordenada_fila][coordenada_columna] = 8
        tablero_imprimible_temp[(coordenada_fila-1) % largo_fila][(coordenada_columna) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila) % largo_fila][(coordenada_columna+1) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila) % largo_fila][(coordenada_columna-1) % largo_columnas] = 8
        tablero_imprimible_temp[(coordenada_fila+1) % largo_fila][(coordenada_columna) % largo_columnas] = 8
        imprimir_formato_tablero(cambiar_simbolos(tablero_imprimible_temp))

    #imprimir_tablero(cambiar_simbolos(tablero_imprimible_temp))


def cambiar_simbolos(tablero):
    '''
    Funcion que cambia los simbolos del tablero
    ''' 
    tablero_imprimible = tablero
    i= 0
    largoi= len(tablero)
    largoj= len(tablero[0])

    while i < largoi:

        j= 0

        while j < largoj:
            if tablero_imprimible[i][j] == 0:
                tablero_imprimible[i][j] = '🌊' 
                
            elif tablero_imprimible[i][j] == 1:
                tablero_imprimible[i][j] = '🛥️ '

            elif tablero_imprimible[i][j] == 2:
                tablero_imprimible[i][j] = '🚤'

            elif tablero_imprimible[i][j] == 3:
                tablero_imprimible[i][j] = '🛳️ '
                
            elif tablero_imprimible[i][j] == 4:
                tablero_imprimible[i][j] = '🚢'
                
            elif tablero_imprimible[i][j] == 5:
                tablero_imprimible[i][j] = '❌'

            elif tablero_imprimible[i][j] == 6: 
                tablero_imprimible[i][j] = '⭕' 

            elif tablero_imprimible[i][j] == 7:
                tablero_imprimible [i][j] = '⭕'

            elif tablero_imprimible[i][j] == 8:
                tablero_imprimible [i][j] = '💥'

            elif tablero_imprimible[i][j] == 9:
                tablero_imprimible [i][j] = '🔥'

            elif tablero_imprimible[i][j] == 10:
                tablero_imprimible[i][j] = '❌'
            j += 1
        i += 1
                
    return tablero_imprimible

menu()