;https://www.ic.unicamp.br/~meidanis/courses/mc336/problemas-lisp/L-99_Ninety-Nine_Lisp_Problems.html
;1
(define my-last
 (lambda (L)
  (cond ((null? L) null)
   (else(cond ((null? (cdr L)) (car L))
          (else( my-last(cdr L))))))))
;2
(define my-but-last
  (lambda (L)
    (cond ((null? L) L)
          ((null? (cdr (cdr L))) L)
          (else (my-but-last (cdr L))))))
;3
(define element-at
  (lambda (L n)
    (cond((null? L)L)
         ((zero? n) (car L))
         (else (element-at (cdr L) (- n 1))))))
;4
(define longitud
  (lambda (L)
    (cond ((null? L) 0)
          (else (+ 1 (longitud (cdr L)))))))
;5
(define reversed
  (lambda (L K)
    (cond ((null? L) K)
          (else (reversed (cdr L) (cons (car L) K))))))
;6
(define palindromo
  (lambda (L)
    (equal? L (reversed L '()))))
;7               
(define my-flatten
  (lambda (L)
    (cond ((null? L)L)
          ((list? (car L)) (append(my-flatten(car L)) (my-flatten(cdr L))))
          (#t (cons (car L) (my-flatten (cdr L)))))))
;8
(define compress
  (lambda (L)
    (cond((null? L)L)
         ((null? (cdr L))L)
         ((= (car L) (cadr L))(compress (cdr L)))
         (#t(cons (car L) (compress (cdr L)))))))
;9
(define pack
  (lambda (L)
    (pack-aux L '() '())))

(define pack-aux
  (lambda (L M K)
    (cond((null? (cdr L))(append K (list (cons (car L) M))))
         ((= (car L) (cadr L)) (pack-aux(cdr L) (cons (car L) M) K))
         (#t(pack-aux (cdr L) '() (append K (list(cons (car L) M))))))))
;10
(define encode
  (lambda (L)
    (encode-aux (pack L) '())))

(define encode-aux
  (lambda (L K)
    (cond ((null? L) K)
          (#t(encode-aux(cdr L) (append K (list(list(length (car L)) (caar L)))))))))
;11
(define encode-modified
  (lambda (L)
    (encode-modified-aux (encode L) '())))

(define encode-modified-aux
  (lambda (L K)
    (cond((null? L)K)
         ((= 1 (caar L)) (encode-modified-aux(cdr L)(append K (list(cadr(car L))))))
         (#t(encode-modified-aux(cdr L)(append K (list(car L))))))))
;12
(define decode
  (lambda (L)
    (cond((null? L)L)
         ((list? (car L)) (append (make-list (caar L) (cadar L)) (decode (cdr L))))
         (#t(append (list(car L)) (decode(cdr L)))))))

(define make-list
  (lambda (n c)
    (cond((zero? n) '())
         (#t(cons c (make-list(- n 1) c))))))

;13
(define encode-direct
  (lambda (L)
    (encode-direct-aux L 0 '())))

(define encode-direct-aux
  (lambda (L c K)
    (cond((null? L) K)
         ((or (null? (cdr L)) (not(eq? (car L) (cadr L))))
          (cond((= 1 (+ c 1)) (encode-direct-aux (cdr L) 0 (append K (list(car L)))))
               (else(encode-direct-aux (cdr L) 0 (append K (list(list (+ c 1) (car L))))))))
         (else(encode-direct-aux (cdr L) (+ 1 c) K)))))

;14
(define dupli
  (lambda (L)
    (dupli-aux L 1 '())))

(define dupli-aux
  (lambda (L c K)
    (cond((null? L) K)
         ((or (null? (cdr L)) (not(eq? (car L) (cadr L)))) (dupli-aux (cdr L) 1 (append K (make-list (* c 2) (car L)))))
         (#t(dupli-aux (cdr L) (+ 1 c) K)))))

;15
(define repli
  (lambda (L n)
    (cond((null? L) L)
         (#t(append (make-list n (car L)) (repli (cdr L) n))))))

;16
(define drop
  (lambda (L n)
    (drop-aux L n n)))

(define drop-aux
  (lambda (L n c)
    (cond((null? L) L)
         ((zero? n) (drop-aux (cdr L) c c))
         (#t(append (list(car L)) (drop-aux (cdr L) (- n 1) c)))))) 

;17
(define split
  (lambda (L n)
    (split-aux L n '())))

(define split-aux
  (lambda (L n K)
    (cond((or (null? L) (zero? n)) (list K L))
         (#t(split-aux (cdr L) (- n 1) (append K (list(car L))))))))

;18
(define slice
  (lambda (L n m)
    (cond((or (null? L) (zero? m)) '())
         ((= 1 n) (cons (car L) (slice (cdr L) n (- m 1))))
         (#t(slice (cdr L) (- n 1) (- m 1))))))
    

;19
(define rotate
  (lambda (L n)
    (cond((< n 0) (rotate-aux (split L (+ (longitud L) n))))
         ((zero? n) L)
         (#t(> n 0) (rotate-aux (split L n))))))

(define rotate-aux
  (lambda (L)
    (append (cadr L) (car L))))


;20
(define remove-at
  (lambda (L n)
    (cond((or (null? L) (zero? n)) (cdr L))
         (#t(append (list(car L)) (remove-at (cdr L) (- n 1)))))))

;21
(define insert-at
  (lambda (c L n)
    (cond((null? L) L)
         ((zero? n) (append (list c) L))
         (#t(append (list(car L)) (insert-at c (cdr L) (- n 1)))))))  

;22
(define range
  (lambda (n m)
    (cond((eq? n m) (list m))
         (#t(cons n (range (+ n 1) m))))))

;23
(define rnd-select
  (lambda (L n)
    (rnd-select-aux L n (longitud L) (random (longitud L)))))

(define rnd-select-aux
  (lambda (L n s r)
    (cond((null? L)L)
         ((= n 1) (list(car L)))
         (#t(cons (element-at L r) (rnd-select-aux (remove-at L r) (- n 1) (- s 1) (random (- s 1))))))))

;24
(define lotto-select
  (lambda (n m)
    (rnd-select (range 1 m) n)))

;25
(define rnd-permu
  (lambda (L)
    (rnd-select L (longitud L))))

;26
(define comb
  (lambda (L k)
    (cond((zero? k) '(()))
         ((= k (length L))(list L))
         (#t(append (map (lambda (c)(cons (car L) c)) (comb (cdr L) (- k 1))) (comb (cdr L) k))))))

;27
(define resta
  (lambda (L M)
    (filter (lambda (k) (not(list?(member k M)))) L)))

(define group
  (lambda (L G)
    (cond((null? L) L)
         (#t(map(lambda (e) (append '() e (group (resta L e) (cdr G)))) (comb L (car G)))))))

;28
(define lfsort
  (lambda (L)
    (cond((or (null? L) (= 1 (longitud L)))L)
         (#t(append (lfsort (filter(lambda (e) (>= (car L) e)) (cdr L)))
                    (list(car L))
                    (lfsort (filter(lambda (e) (< (car L) e)) (cdr L)))))))) 
;31
(define is-prime
  (lambda (T)
    (cond((= 1 T) #f)
         ((= T 2)#t)
         ((= (remainder T 2) 0) #f)
         (#t(is-prime-aux T 3)))))

(define is-prime-aux
  (lambda (n k)
    (cond((= (modulo n k) 0) #f)
         ((>= (* k k) n) #t)
         (#t(is-prime-aux n (+ k 2))))))

;32
(define gcd
  (lambda (n m)
    (cond((zero? m) n)
         (#t(gcd m (remainder n m))))))

;33
(define coprime
  (lambda (n m)
    (cond((= 1 (gcd n m))#t)
         (else #f))))

;34
(define totien-phi
  (lambda (n)
    (totien-phi-aux n (- n 1))))

(define totien-phi-aux
  (lambda (n m)
    (cond ((= 1 m)1)
          ((= (gcd n m) 1) (+ 1 (totien-phi-aux n (- m 1))))
          (#t(totien-phi-aux n (- m 1))))))

;35
(define prime-factors
  (lambda (n)
    (prime-factors-aux n 2)))

(define prime-factors-aux
  (lambda (n m)
    (cond((= n 1) '())
         ((and (= (remainder n m) 0) (is-prime m))(cons m (prime-factors-aux (/ n m) m)))
         (#t(prime-factors-aux n (+ m 1))))))

;36
(define encode-reves
  (lambda (L)
    (encode-reves-aux (pack L) '())))

(define encode-reves-aux
  (lambda (L K)
    (cond ((null? L) K)
          (#t(encode-reves-aux(cdr L) (append K (list(list (caar L) (length (car L))))))))))

(define prime-factors-mult
  (lambda (n)
    (encode-reves (prime-factors n))))

;37
(define expo-log
  (lambda (a n)
    (cond((zero? n)1)
         ((odd? n)(*(expo-log a (quotient n 2)) (expo-log a (quotient n 2)) a))
         (#t(*(expo-log a (quotient n 2)) (expo-log a (quotient n 2)))))))

(define phi
  (lambda (n)
    (phi-aux (prime-factors-mult n))))

(define phi-aux
  (lambda (L)
    (cond((null? L)1)
         (#t(* (- (caar L) 1) (expo-log (caar L) (- (cadar L) 1)) (phi-aux (cdr L)))))))

;39
(define prime-list
  (lambda (n m)
    (cond((> n m) '())
         ((is-prime n)(cons n (prime-list (+ n 1) m)))
         (#t(prime-list (+ n 1) m)))))

;40
(define goldbach
  (lambda (n)
    (goldbach-aux n 3)))

(define goldbach-aux
  (lambda (n m)
    (cond((> m (/ n 2)) '())
         ((and (is-prime m) (is-prime (- n m))) (list m (- n m)))
         (#t(goldbach-aux n (+ m 2))))))

;41
(define goldbach-list
  (lambda (n m)
    (cond((odd? n)(goldbach-list-aux (+ 1 n) m))
         (#t(goldbach-list-aux n m)))))

(define goldbach-list-aux
  (lambda (n m)
    (cond((> n m) '())
         (#t(cons (goldbach n) (goldbach-list-aux (+ 2 n) m)))))) 


;54
(define is-tree
  (lambda (A)
    (cond((null? A)#t)
         ((not(list? A))#f)
         ((and (= (longitud A) 3) (is-tree (cadr A)) (is-tree (caddr A)))#t)
         (#t #f))))
;55

(define revertir
  (lambda (A)
    (list (car A) (caddr A)  (cadr A))))
    
(define for1
  (lambda (L K f)
    (cond((null? L)L)
         (#t(append (for2 (car L) K f) (for1 (cdr L) K f))))))

(define for2
  (lambda (L K f)
    (cond((null? K)K)
         ((= f 1) (append (list(list 1 L (car K))) (list(revertir(list 1 L (car K)))) (for2 L (cdr K) f)))
         (#t(cons (list 1 L (car K)) (for2 L (cdr K) f))))))
             

(define cbal-tree
  (lambda (n)
    (cond((zero? n)'(()))
         ((= 1 n)'((1 () ())))
         ((odd? (- n 1)) (for1 (cbal-tree(quotient (- n 1) 2)) (cbal-tree(+ 1 (quotient (- n 1) 2))) 1))
         (#t(for1(cbal-tree(quotient (- n 1) 2)) (cbal-tree (quotient (- n 1) 2)) 0)))))

;56
(define symmetric
  (lambda (A)
    (cond((and (null? (cadr A)) (null? (caddr A))) #t)
         ((equal? (symmetric-aux (cadr A) (caddr A)) #t) #t)
         (else #f))))
    

(define symmetric-aux
  (lambda (I D)
    (cond((and (null? I) (null? D))#t)
         ((null? I)#f)
         ((null? D)#f)
         ((and (symmetric-aux (cadr I) (caddr D)) (symmetric-aux (cadr D) (caddr I))) #t)
         (else #f))))

;57
(define construir
  (lambda (L)
    (cond((null? L)L)
         (#t(append (list (car L)) (list(construir(filter (lambda (e) (< e (car L))) (cdr L)))) (list(construir(filter (lambda (e) (> e (car L))) (cdr L)))))))))

;58
(define sim-cbal-trees
  (lambda (n)
    (filter symmetric (cbal-tree n))))

;59
(define hbal-tree
  (lambda (n)
    (cond((= -1 n)'(()))
         ((zero? n) '((1 () ())))
         (#t(append (for1 (hbal-tree(- n 2)) (hbal-tree(- n 1)) 1) (list(hbal-tree(- n 1))(hbal-tree(- n 1))))))))

;70b
(define istreen
  (lambda (A)
    (cond((null? A)#t)
         ((not(list? A))#f)
         ((list? (car A)) #f)
         (#t(andmap istreen (cdr A))))))
;70c
(define nnodes
  (lambda (A)
    (cond((null? A)0)
         (#t(+ 1 (apply + (map nnodes (cdr A))))))))

;70
(define tree-string
  (lambda (s)
    (tree-string-aux (substring s 1) (list(list (string-ref s 0))))))

(define tree-string-aux
  (lambda (s p)
    (cond((null? (substring s 1)) p)
         ((char=? #\^ (string-ref s 0)) (tree-string-aux (substring s 1) (cons (append (cadr p) (list (car p))) (cddr p))))
         (#t(tree-string-aux (substring s 1) (cons (list (string-ref s 0)) p))))))

;81
(define AppendMap
  (lambda (fun L)
    (cond ((null? L) '())
          (else (append (fun (car L)) (AppendMap fun (cdr L)))))))

(define path
  (lambda (G a b)
    (path-aux G b '() a '())))

(define path-aux
  (lambda (G b V a C)
    (cond((= b a) (list(append C (list a))))
         ((member a V) '())
         (#t(AppendMap (lambda(c) (path-aux G b (cons a V) c (append C (list a)))) (cadr(assoc a G)))))))

(path '((1 (2 3)) (2 (1 4)) (3 (1 4)) (4 (2 3))) 1 4)        
