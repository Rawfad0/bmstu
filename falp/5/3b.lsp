(defun mulnlst(lst n)
    (mapcar #'(lambda (x) 
                (cond   (   (numberp x)
                            (*  x 
                                n))
                        (   T 
                            x)))
            lst))

(mulnlst '(-1 0 a 1 2 5) 3)
; (-3 0 A 3 6 15)

(mulnlst '(-1 0 1 b 2 5) 0)
; (0 0 0 B 0 0)

(mulnlst '(-1 0 1 2 c 5) -1)
; (1 0 -1 -2 C -5)