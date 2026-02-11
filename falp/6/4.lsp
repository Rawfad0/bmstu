; (defun select-between(lst a b)
; 	(cond   (   (null lst)
;                 Nil)
;             (   (and    (<  a
;                             (car lst)) 
;                         (<  (car lst) 
;                             b))
;                 (cons (car lst) 
;                     (select-between (cdr lst)
;                                     a
;                                     b)))
;             (   T
;                 (select-between (cdr lst)
;                                 a
;                                 b))))

(defun f (lst res a b)
	(cond   (   (null lst)
                res)
	        (   (and    (>  (car lst) 
                            a) 
                        (<  (car lst) 
                            b)) 
                (f  (cdr lst)
                    (cons   (car lst) 
                            res) 
                    a
                    b))
		    (   t 
                (f (cdr lst) 
                    res
                    a 
                    b))))

(defun select-between (lst a b)
    (f lst Nil a b))

(print '((0 1 2 3 4 5 6) [1 4]))
(print (select-between'(0 1 2 3 4 5 6) 1 4))
(write-line "")

(print '((0 1 2 3 4 5 6) [8 9]))
(print (select-between'(0 1 2 3 4 5 6) 8 9))
(write-line "")

(print '((0 8 3 6 4 5 2 7) [3 7]))
(print (select-between'(0 8 3 6 4 5 2 7) 3 7))
(write-line "")