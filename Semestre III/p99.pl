% https://www.ic.unicamp.br/~meidanis/courses/mc336/problemas-lisp/L-99_Ninety-Nine_Lisp_Problems.html
myLast([H],H):-!.
myLast([_H|T],E):-myLast(T,E).

myButLast([H,K],[H,K]):-!.
myButLast([_H|T],R):-myButLast(T,R).

elementAt([H|_T],0,H):-!.
elementAt([_H|T],N,E):-K is N-1, elementAt(T,K,E).

llenght([],0):-!.
llenght([_H|T],N):-llenght(T,K),N is K+1.

rreverse([],[]):-!.
rreverse([H|T],E):-rreverse(T,L), append(L,[H],E).

palindromo(L):-rreverse(L,L).

myFlatten([],[]):-!.
myFlatten([[H|T]|S],R):-!,myFlatten([H|T],G),myFlatten(S,F),append(G,F,R).
myFlatten([H|T],[H|S]):-myFlatten(T,S).

compress([],[]):-!.
compress([H,H|T],E):-!,compress([H|T],E).
compress([H|T],[H|E]):-compress(T,E).

ppack(L,X):-packAux(L,[],[],X).
packAux([],_N,M,R):-!, rreverse(M,R).
packAux([H,H|T],E,M,R):-!, packAux([H|T],[H|E],M,R).
packAux([H|T],E,M,R):- packAux(T,[],[[H|E]|M],R).

encode(L,R):-ppack(L,X),encodeAux(X,R).
encodeAux([],[]):-!.
encodeAux([[H|T]|G],[[S,H]|R]):- llenght([H|T],S) , encodeAux(G,R).     

encodeModified(L,R):-encode(L,X),encodeModifiedAux(X,R).
encodeModifiedAux([],[]):-!.
encodeModifiedAux([[1,J]|E],[J|R]):-!,encodeModifiedAux(E,R).
encodeModifiedAux([H|T],[H|R]):-encodeModifiedAux(T,R).

nList(_E,0,[]):-!.
nList(E,N,[E|R]):- N1 is N-1,nList(E,N1,R).

decode([],[]):-!.
decode([[H|F]|T],R):-!, nList(F,H,L), decode(T,R1), append(L,R1,R).
decode([H|T],R):- decode(T,R1), R is [H|R1]. 

encodeDirectly(L,R):-encodeDirectly(L,[],R).
encodeDirectly([],_A,[]):-!.
encodeDirectly([H,H|T],A,R):-!,encodeDirectly([H|T],[H|A],R).
encodeDirectly([H|T],[],[H|R]):-!, encodeDirectly(T,[],R).
encodeDirectly([H|T],A,R):- llenght(A,L), L1 is L+1, encodeDirectly(T,[],Y), append([[L1,H]],Y,R). 

dupli([],[]):-!.
dupli([H|T],[H,H|R]):-dupli(T,R).

repli([],_N,[]):-!.
repli([H|T],N,R):-nList(H,N,S), repli(T,N,F), append(S,F,R).

drop(L,N,R):-drop(L,N,0,R).
drop([],_N,_A,[]):-!.
drop([_H|T],N,N,R):-!, drop(T,N,0,R).
drop([H|T],N,A,[H|R]):-A1 is A+1, drop(T,N,A1,R).

split(L,N,R):-split(L,N,[],R).
split([H|T],0,A,[A,[H|T]]):-!.
split([H|T],N,A,R):- N1 is N-1, append(A,[H],A1) ,split(T,N1,A1,R).

slice(L,I,J,R):-split(L,I,[_H,T]), J1 is J-I, split(T,J1,[R,_G]).

rotate(L,N,R):-llenght(L,L1), N1 is (L1 + (N mod L1)) mod L1, split(L,N1,[S,W]), append(W,S,R).

removeAt([_H|T],0,T):-!.
removeAt([H|T],N,[H|R]):- N1 is N-1,removeAt(T,N1,R).

insertAt([H|T],E,0,[E,H|T]):-!.
insertAt([H|T],E,N,[H|R]):- N1 is N-1, insertAt(T,E,N1,R).

range(J,J,[J]):-!.
range(I,J,[I|R]):-I1 is I+1, range(I1,J,R).

rndSelect(_L,0,[]):-!.
rndSelect(L,N,R):- N1 is N-1, llenght(L,Len), random(0,Len,A), elementAt(L,A,E), removeAt(L,A,L1), rndSelect(L1,N1,F), append([E],F,R). 

rndPermu(L,R):- llenght(L,Len), random(0,Len,A), rotate(L,A,R).

combination(_L,0,[]):-!.
combination(L,K,L):-llenght(L,K),!.
combination([H|T],K,[H|C]):- K2 is K-1, combination(T,K2,C).
combination([_H|T],K,C):- combination(T,K,C).

resta([],_M,[]):-!.
resta([H|T],M,R):- member(H,M),!,resta(T,M,R).
resta([H|T],M,[H|R]):- resta(T,M,R).

group([],[],[]):-!.
group(L,[H|T],[C|S]):- combination(L,H,C), resta(L,C,L1), group(L1,T,S).

isPrime(3):-!.
isPrime(N):- N > 2, \+(0 is (N mod 2)), \+(1 is N), isPrimeAux(N,3). 
isPrimeAux(N,K):- N =< K * K, (N mod K) =\= 0, !.   
isPrimeAux(N,K):- (N mod K) =\= 0, K1 is K+1, isPrimeAux(N,K1).

gcd(A,0,A):-!.
gcd(A,B,R):- M is A mod B, gcd(B,M,R).

coprime(A,B):- 1 is gcd(A,B).

totientPhi(N,R):-totientPhiAux(N,N,R).
totientPhiAux(_N,0,0):-!.
totientPhiAux(N,K,R):- coprime(K,N),!, K1 is K-1, totientPhiAux(N,K1,S), R is S+1.
totientPhiAux(N,K,R):- K1 is K-1, totientPhiAux(N,K1,R).

primeFactors(N,[2|R]):- 0 is N mod 2, !, N1 is (N div 2), primeFactors(N1,R).
primeFactors(N,R):-primeFactorsAux(N,3,R).
primeFactorsAux(1,_K,[]):-!.
primeFactorsAux(N,K,[K|R]):- 0 is (N mod K), isPrime(K), N1 is (N div K),!,primeFactorsAux(N1,K,R).
primeFactorsAux(N,K,R):- K1 is K+2, primeFactorsAux(N,K1,R).

encodeR(L,R):-ppack(L,X),encodeRAux(X,R).
encodeRAux([],[]):-!.
encodeRAux([[H|T]|G],[[H,S]|R]):- llenght([H|T],S) , encodeRAux(G,R). 

primeFactorsMult(X,R):- primeFactors(X,F), encodeR(F,R).

phi(N,R):-primeFactorsMult(N,L), phiAux(L,R).
phiAux([],1):-!.
phiAux([[P,M]|T],R):- phiAux(T,S), R is S*((P-1)*(P**(M-1))).

primeList(I,J,R):-range(I,J,L), primeListAux(L,R).
primeListAux([],[]):-!.
primeListAux([H|T],[H|R]):- isPrime(H),!, primeListAux(T,R).
primeListAux([_H|T],R):- primeListAux(T,R).

goldbach(N,R):-goldbachAux(N,3,R).
goldbachAux(N,K,[K,R]):- isPrime(K), R is N-K, isPrime(R),!.
goldbachAux(N,K,R):- K1 is K+2, goldbachAux(N,K1,R).

goldbachList(I,J,R):-I1 is I + (I mod 2),goldbachListAux(I1,J,R).
goldbachListAux(I,J,[]):-I>J,!.
goldbachListAux(I,J,[G|R]):- goldbach(I,G), I1 is I+2, goldbachListAux(I1,J,R).

isTree([]):-!.
isTree([_R,I,D]):-isTree(I), isTree(D).

cbalTree(0,[]):-! .
cbalTree(1,[1,[],[]]):-! .
cbalTree(N,R):- 0 is ((N-1) rem 2), !, N1 is ((N-1) div 2), cbalTree(N1,S), cbalTree(N1,F) ,append([1|[F]],[S],R).
cbalTree(N,R):- N1 is ((N-1) div 2), 
    N2 is (N1+1), cbalTree(N1,S), cbalTree(N2,F), append([1|[S]],[F],R).
cbalTree(N,R):-  N1 is ((N-1) div 2), 
    N2 is (N1+1), cbalTree(N2,S), cbalTree(N1,F), append([1|[S]],[F],R).

isSymmetric([]):- !.
isSymmetric([_R,I,D]):- isSymmetric(I,D).

isSymmetric([], []):- !.
isSymmetric([_IR,II,ID],[_DR,DI,DD]):- isSymmetric(II,DD), isSymmetric(ID,DI).

partir(_E,[],[],[]):- !.
partir(E, [H|T], [H|L], R):- H<E, !, partir(E, T, L, R).
partir(E, [H|T], L, [H|R]):- partir(E, T, L, R).

construct([],[]):-!.
construct([H|T],R):- partir(H,T,Me,Ma), construct(Me,R1), 
    construct(Ma,R2), append([H|[R1]],[R2],R).

symCbalTree(N,R):- cbalTree(N,R), isSymmetric(R).

hbalTree(-1,[]):-!.
hbalTree(0, [1,[],[]]):- !.
hbalTree(H, X):- H1 is H-1, hbalTree(H1,X1), hbalTree(H1,X2), append([1|[X1]],[X2],X).
hbalTree(H, X):- H1 is H-1, H2 is H1-1, hbalTree(H2, X1), hbalTree(H1,X2), append([1|[X1]],[X2],X).
hbalTree(H, X):- H1 is H-1, H2 is H1-1, hbalTree(H1, X1), hbalTree(H2,X2), append([1|[X2]],[X1],X).

isNTree([]):-!.
isNTree([_R,[]]):-!.
isNTree([R,[H|T]]):- isNTree(H),isNTree([R|[T]]).

nNodes([_R,[]],1):-!.
nNodes([R,[H|T]],CN):- nNodes(H,C1), nNodes([R|[T]],C2), CN is C1+C2. 

stringT([],[]):- !.
stringT([H|T],[H,R]):- treeString(T,R).

treeString(['^'],[]):-!.
treeString(L,R):- pila(L,0,[],Ra,L1), stringT(Ra,Z), treeString(L1,X), append([Z],X,R). 

pila(L,0,[H|T],G,L):-!, rreverse([H|T],G).
pila([H|T],N,R,X,Y):- (H) == ('^'),!, N1 is N-1, pila(T,N1,[H|R],X,Y).
pila([H|T],N,R,X,Y):- N1 is N+1, pila(T,N1,[H|R],X,Y).

camino(G,A,B,C,[B,A|C]):- \+(member(B,C)), \+(member(A,C)), member([A,X],G), member(B,X).
camino(G,A,B,C,R):- \+(member(A,C)), member([A,Y],G), member(X,Y),camino(G,X,B,[A|C],R).

% member([1, X], G)
% G=[[1, []], [2, []]]

% nreinas(N,L):-iota(N,P), nreinasAux(P,[],L).
% nreinasAux([],S,S).
% nreinasAux(P,T,R):-member(H,P), pponer(H,T),delete(P,H,PsH), nreinasAux(PsH,[H|T],R).

% pponer(E,T):-length(T,LT),pponer(E,0,LT,T).
% pponer(E,I,P,[]):-!.
% pponer(E,I,P,[H|T]):- A is abs(E-H), \+A is abs(P-I), !, I2 is  I+1, pponer(E,I2,P,T)\