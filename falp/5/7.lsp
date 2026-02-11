(defun cartesian(lst1 lst2)
    (mapcan #'(lambda (x) 
                    (mapcar #'(lambda (y) 
                                    (cons   x 
                                            y)) 
                            lst2)) 
            lst1))

(cartesian '(1 2) '(3 4))
; ((1 . 3) (1 . 4) (2 . 3) (2 . 4))