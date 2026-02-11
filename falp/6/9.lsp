(defun squares (lst)
    (if (null lst)
        lst
        (cons   (*  (car lst)
                    (car lst))
                (squares (cdr lst)))))