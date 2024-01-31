import sys
import heapq

class Nodo:
    def __init__(self, val):
        self.valor=val
        self.simbolo=0
        self.izq = None
        self.der = None
    
    def __lt__(self, otro):
        return self.valor < otro.valor

    def cruzar(self,otro):
        a = Nodo(self.valor+otro.valor)
        a.izq = self
        a.der = otro
        return a

if(len(sys.argv) != 2):
    sys.exit(1)
name = sys.argv[1]
with open(name,'rb') as entrada:
    content = entrada.read()

freq = [0]*257
codigos=["" for _ in range(257)]
cola=[]

binaryFile = name + '.huff'
table= name+'.table'
stats=name+'.stats'


def contarFreq():
    global freq
    for a in content:
        freq[a]+=1
    return 

def construir():
    for a in range(257):
        if freq[a]>0:
            o=Nodo(freq[a])
            o.simbolo=a
            heapq.heappush(cola, o)
    while 1 < len(cola):
        a = heapq.heappop(cola)
        b = heapq.heappop(cola)
        heapq.heappush(cola, a.cruzar(b))
    return heapq.heappop(cola)

def caminos(nod ,st):
    global codigos
    if(nod.izq==None): 
        codigos[nod.simbolo] = st
        return
    caminos(nod.izq, st+'1')
    caminos(nod.der, st+'0')     

def altura(nod, alt):
    if(nod.izq==None): return alt
    return max(altura(nod.izq, alt+1), altura(nod.der, alt+1))

def info(raiz):
    pila=[]
    alt=altura(raiz, 0)
    nivel=[0]*(alt+1)
    pila.append([raiz, 0])
    anchura=0
    while len(pila):
        nod, niv=pila.pop()
        nivel[niv]+=1
        anchura=max(anchura, nivel[niv])
        if(nod.izq!=None):
            pila.append([nod.izq, niv+1])
            pila.append([nod.der, niv+1])
    texto="Altura del árbol: "+str(alt)+"\n"+"Anchura del árbol: "+str(anchura)+"\n"
    texto+="Cantidad de nodo por nivel:\n"
    for i in range(alt+1):
        texto+="Nivel "+str(i)+": "+str(nivel[i])+'\n'
    texto+="Tabla de frecuencias original:\n"
    for i in range(257):
        if(freq[i]>0):
            texto+=str(i)+" : "+str(freq[i])+'\n'
    with open(stats, 'w') as escribir:
        escribir.write(texto)

def cambiarArchivo():
    comprimido=bytearray()
    texto=""
    for a in range(len(content)):
        texto += codigos[content[a]]
    cantMeter=8-len(texto)%8
    for i in range(cantMeter): texto+='0'
    byteInfo="{0:08b}".format(cantMeter)
    texto=byteInfo+texto
    for i in range(0, len(texto), 8):
        byte=int(texto[i:i+8], 2)
        comprimido.append(byte)
    with open(binaryFile,'wb') as escribir:
        escribir.write(comprimido)

def tabular():
    with open(table,'w') as escribir:
        tabla=""
        for i in range(257):
            if(codigos[i] != ''): 
                tabla += str(i) + ' ' + codigos[i] + '\n'
        escribir.write("%s" %tabla)

def huffman():
    contarFreq()
    raiz=construir()
    caminos(raiz, '')
    cambiarArchivo()
    tabular()
    info(raiz)

huffman()


