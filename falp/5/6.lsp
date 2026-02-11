(defun select-between(lst a b)
    (remove-if  #'(lambda   (x) 
                            (or (<= x a)
                                (>= x b)))
                lst))

            
                    
(select-between '(-1 0 1 2 5) -1 1)
; (0)

(select-between '(-1 0 1 2 5) -1 3)
; (0 1 2)