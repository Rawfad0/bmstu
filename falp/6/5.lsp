; (defun rec-add (lst)
;     (if (null lst)
;         0
;         (+  (car lst)
;             (rec-add (cdr lst)))))

(defun rec-add (lst)
    (cond   (   (null lst)
                0)
            (   t
                (+  (car lst)
                    (rec-add (cdr lst))))))


(defun rec-add (lst)
    (cond   (   (null lst)
                0)
            (   (numberp (car lst))
                (+  (car lst)
                    (rec-add (cdr lst))))
            (   t
                (+  (rec-add (car lst))
                    (rec-add (cdr lst))))))