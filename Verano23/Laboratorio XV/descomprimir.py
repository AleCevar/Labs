import sys

class Nodo:
    def __init__(self):
        self.simbolo=0
        self.izq = None
        self.der = None

if(len(sys.argv) != 4):
    sys.exit(1)
huff = sys.argv[1]
table = sys.argv[2]
name = sys.argv[3]

with open(table,'r') as entrada:
    contentTable = entrada.read()

with open(huff,'rb') as entrada:
    contentHuff = entrada.read()

huffBinary = ''
for n in range(1,len(contentHuff)):
    huffBinary += format(contentHuff[n], '08b')
huffBinary=huffBinary[:len(huffBinary)-contentHuff[0]]

raiz=Nodo()
estruc=[]

def recorrer(nod, num, pos):
    if(pos==len(estruc[num][1])):
        nod.simbolo=estruc[num][0]
        return
    if(estruc[num][1][pos]=='1'):
        if(nod.izq==None): nod.izq=Nodo()
        recorrer(nod.izq, num, pos+1)
    else:
        if(nod.der==None): nod.der=Nodo()
        recorrer(nod.der, num, pos+1)

def construir():
    partes = contentTable.split('\n')
    global estruc 
    estruc = [sub.split(' ') for sub in partes]
    for i in range(len(estruc)-1):
        estruc[i][0]=int(estruc[i][0])
        recorrer(raiz,i,0)

def traducir():
    nodoActual=raiz
    descomp=bytearray()
    for b in huffBinary:
        if(nodoActual.izq==None):
            descomp.append(nodoActual.simbolo)
            nodoActual=raiz
        if(b=='1'): nodoActual=nodoActual.izq
        else: nodoActual=nodoActual.der
    descomp.append(nodoActual.simbolo)
    with open(name,'wb') as escribir:
        escribir.write(descomp)
    
def desHuffman():
    construir()
    traducir()
    
desHuffman()