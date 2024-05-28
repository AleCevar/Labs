% https://www.ic.unicamp.br/~meidanis/courses/mc336/problemas-lisp/L-99_Ninety-Nine_Lisp_Problems.html
-module(p99).
-compile(export_all).

myLast([H])->H;
myLast([_H|T])->myLast(T).

myButLast([T,H])->[T,H];
myButLast([_H|T])->myButLast(T).

elementAt([H|_T],0)->H;
elementAt([_H|T],N)->elementAt(T,N-1).

llenght([])->0;
llenght([_H|T])->1+llenght(T).

rreverse(L)->rreverseAux(L,[]).

rreverseAux([],L)->L;
rreverseAux([H|T],L)->rreverseAux(T,[H|L]).

palindromo(L) -> rreverse(L)==L.

myFlatten([])->[];
myFlatten([[H|T]|G])->myFlatten([H|T])++myFlatten(G);
myFlatten([H|T])->[H|myFlatten(T)].

compress([])->[];
compress([H,H|T])->compress([H|T]);
compress([H|T])->[H|compress(T)].

pack(L)->packAux(L,[],[]).

packAux([],_G,P)->P;
packAux([H,H|T],G,P)->packAux([H|T],[H|G],P);
packAux([H|T],G,P)->packAux(T,[],P++[[H|G]]).

encode(L)->[[llenght([H|T]),H]||[H|T]<-pack(L)].

encodeModify(L)->encodeModifyAux(encode(L)).

encodeModifyAux([])->[];
encodeModifyAux([[1,R]|T])->[R|encodeModifyAux(T)];
encodeModifyAux([H|T])->[H|encodeModifyAux(T)].

makeList(_E,0)->[];
makeList(E,N)->[E|makeList(E,N-1)].

decode([])->[];
decode([[C,E]|T])->makeList(E,C)++decode(T);
decode([H|T])->[H|decode(T)].

encodeDirectly(L)-> encodeDirectlyAux(L,[]).
encodeDirectlyAux([],_A)->[];
encodeDirectlyAux([H,H|T],A)-> encodeDirectlyAux([H|T],[H|A]);
encodeDirectlyAux([H|T],[])-> [H|encodeDirectlyAux(T,[])];
encodeDirectlyAux([H|T],A)-> L = llenght(A)+1, [[L,H]|encodeDirectlyAux(T,[])].   

dupli([])->[];
dupli([H|T])->[H,H|dupli(T)].

repli([],_K)->[];
repli([H|T],K)->makeList(H,K)++repli(T,K).

drop([_H|T],0)->T;
drop([H|T],K)->[H|drop(T,K-1)].

split(L,N)->splitAux(L,N,[]).

splitAux(L,0,P)->[P]++[L];
splitAux([H|T],N,P)->splitAux(T,N-1,P++[H]).

slice(L,I,J)->[_M,N] = split(L,I), [P,_Q] = split(N,J-I),P.

rotate(L,N)->LEN = llenght(L), [P,Q] = split(L,(LEN+(N rem LEN)) rem LEN), Q++P.

removeAt([_H|T],0)->T;
removeAt([H|L],N)->[H|removeAt(L,N-1)].

insertAt([H|T],E,0)->[H,E|T];
insertAt([H|T],E,N)->[H|insertAt(T,E,N-1)].

rrange(J,J)->[J];
rrange(I,J)->[I|rrange(I+1,J)].

rndSelect(_L,0)->[[]];
rndSelect(L,N)-> Len = llenght(L), R = rand:uniform(Len), E = elementAt(L,R), L1 = removeAt(L,R), [E|rndSelect(L1,N-1)].

rndPermu(L)-> Len = llenght(L), R = rand:uniform(Len), rotate(L,R).

combination(_L,0)->[[]];
combination(L,K) when length(L) == K -> [L];
combination([H|T],K)-> [[H|C] || C <- combination(T,K-1)] ++ combination(T,K).

group([],[])->[[]];
group(L,[H|T])-> [[C|S]|| C<-combination(L,H), S<-group(L--C,T)].

isPrime(2)-> false;
isPrime(3)-> true;
isPrime(N) when (N rem 2) == 0 orelse N == 1 -> false;
isPrime(N)-> isPrimeAux(N,3). 
isPrimeAux(N,K) when (N rem K) == 0 -> false;
isPrimeAux(N,K) when N =< K*K -> true;
isPrimeAux(N,K)->isPrimeAux(N,K+2).

gcd(A,0)->A;
gcd(A,B)->gcd(B, A rem B).

coprime(A,B)-> G = gcd(A,B), G == 1.

totientPhi(A)->llenght([X|| X <- rrange(0,A), coprime(X,A)]).

primeFactors(A) when (A rem 2) == 0 -> [2|primeFactors(A div 2)];
primeFactors(A)->primeFactorsAux(A,3).
primeFactorsAux(1,_B)->[];
primeFactorsAux(A,B)when A rem B == 0-> isPrime(B), [B | primeFactorsAux((A div B),B)];
primeFactorsAux(A,B)-> primeFactorsAux(A,B+2).

encodeReves(L)->[[H,llenght([H|T])]||[H|T]<-pack(L)].

primeFactorsMult(A)-> encodeReves(primeFactors(A)).

phi(N)->phiAux(primeFactorsMult(N)).
phiAux([])->1;
phiAux([[P,M]|T])-> ((P-1)*math:pow(P,M-1))*phiAux(T).

primeList(I,J)->[X||X<-rrange(I,J),isPrime(X)].

goldbach(N)-> goldbachAux(N,primeList(3,N)).
goldbachAux(N,L)-> elementAt([[X,Y]|| X<-L,Y<-L,X+Y == N],0).

goldbachList(I,J)->[goldbach(X)|| X<-rrange(I,J), (X rem 2) == 0].

isTree([])->true;
isTree([_R,I,D])->isTree(I), isTree(D), true;
isTree(_A)->false.

reverseHijos([])->[];
reverseHijos([[_R,I,D]|T])->[[1,I,D],[1,D,I]|reverseHijos(T)].

cbalTree(0)->[[]];
cbalTree(1)->[[1,[],[]]];
cbalTree(N) when ((N-1)rem 2) == 1 -> reverseHijos([[1,I,D]||I<-cbalTree((N-1)div 2),D<-cbalTree(1+((N-1)div 2))]);
cbalTree(N)->[[1,I,D]||I<-cbalTree((N-1)div 2), D<-cbalTree((N-1)div 2)].

isSymetric([_R,I,D])-> isSymetric(I,D).
isSymetric([],[])->true;
isSymetric([],_D)->false;
isSymetric(_I,[])->false;
isSymetric([_RI,II,ID],[_DR,DI,DD])-> VI = isSymetric(II,DD), VD = isSymetric(ID,DI), VI and VD.

partir(_E,[],Me,Ma)->[rreverse(Me),rreverse(Ma)];
partir(E,[H|T],Me,Ma)when H < E -> partir(E,T,[H|Me],Ma);
partir(E,[H|T],Me,Ma)-> partir(E,T,Me,[H|Ma]). 

construir([])->[];
construir([H|T])-> [Me,Ma] = partir(H,T,[],[]), [H,construir(Me),construir(Ma)].

symCbalTree([])->[];
symCbalTree([H|T])-> [X|| X<-[H|T], isSymetric(X)];
symCbalTree(N)-> symCbalTree(cbalTree(N)).

hbalTree(-1)->[[]];
hbalTree(0)->[[1,[],[]]];
hbalTree(N)->[[1,X,Y]||X<-hbalTree(N-1),Y<-hbalTree(N-1)] ++ reverseHijos([[1,X,Y]||X<-hbalTree(N-1), Y<-hbalTree(N-2)]).

isNTree([])->true;
isNTree([_R,[]])->true;
isNTree([R,[H|T]])->isNTree(H) and isNTree([R,T]);
isNTree(_A)->false.

nNodes([_R,[]])->1;
nNodes([R,[H|T]])-> nNodes(H)+nNodes([R,T]).

pila(L,[H|T],0)->[[H|T],L];
pila([H|T],R,N) when H == 94 ->pila(T,R++[94],N-1);
pila([H|T],R,N)->pila(T,R++[H],N+1).

stringT([])->[];
stringT([H|T])->[H, treeString(T)].

treeString([94])->[];
treeString(L)-> [N,L1] = pila(L,[],0), [stringT(N)|treeString(L1)]. 

adyacencia(E,[[E,A]|_T])->A;
adyacencia(E,[_H|T])-> adyacencia(E,T).

caminos(_G,B,B,C)->[[B|C]];
caminos(G,A,B,C)->lists:append([caminos(G,X,B,[A|C])||X<-adyacencia(A,G), not(lists:member(X,C))]).
