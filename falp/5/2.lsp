(defun sq(x)
    (*  x 
        x))

(defun sqlst(lst)
    (mapcar #'sq 
            lst))

(sqlst '(-1 0 1 2 5))
; (1 0 1 4 25)