(defun multlst (x lst)
    (cond   (   (null lst)
                nil)
            (   t
                (cons   (*  (car lst)
                            x)
                        (multlst    x
                                    (cdr lst))))))

(defun multlst (x lst)
    (cond   (   (null lst)
                nil)
            (   (numberp (car lst))
                (cons   (*  (car lst)
                            x)
                        (multlst    x
                                    (cdr lst))))
            (   t
                (cons   (car lst)
                        (multlst    x
                                    (cdr lst))))))
