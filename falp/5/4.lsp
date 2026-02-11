(defun ispal(lst)
    (reduce (lambda (a b) 
                    (and  a
                        b))
            (mapcar #'equal
                    lst
                    (reverse lst))))

(ispal '(1 0 1))
; T

(ispal '(1 0 -1))
; NIL

(ispal '(1 0 0 1))
; T