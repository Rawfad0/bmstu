; 1
((lambda (ar1 ar2 ar3 ar4)
    (list (list ar1 ar2) (list ar3 ar4)))
    'A 'B 'C 'D)
; ((A B) (C D))
(defun f(ar1 ar2 ar3 ar4)
    (list (list ar1 ar2) (list ar3 ar4)))
(f 'A 'B 'C 'D)
; ((A B) (C D))

(defun f(ar1 ar2 ar3 ar4)
    (cons (cons ar1 (cons ar2 Nil))
        (cons (cons ar3 (cons ar4 Nil)) Nil)))

; 2
((lambda (ar1 ar2)
    (list (list ar1) (list ar2)))
    'A 'B)
; ((A) (B))
(defun f(ar1 ar2)
    (list (list ar1) (list ar2)))
(f 'A 'B)
; ((A) (B))

(defun f(ar1 ar2)
    ((cons (cons ar1 Nil)
        (cons (cons ar2 Nil) Nil))))

(defun f(ar1 ar2)
    (cons(cons(cons ar1 Nil) Nil) Nil))
    
; 3
((lambda (ar1)
    (list (list (list ar1))))
    'A)
; (((A)))
(defun f(ar1)
    (list (list (list ar1))))
(f 'A)
; (((A)))
