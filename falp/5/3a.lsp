(defun mulnlst(lst n)
    (mapcar #'(lambda   (x) 
                        (*  x 
                            n)) 
            lst))

(mulnlst '(-1 0 1 2 5) 3)
; (-3 0 3 6 15)

(mulnlst '(-1 0 1 2 5) 0)
; (0 0 0 0 0)

(mulnlst '(-1 0 1 2 5) -1)
; (1 0 -1 -2 -5)