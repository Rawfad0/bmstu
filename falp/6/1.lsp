; (defun move-to (lst result)
; 	(cond   (   (null lst) 
;                 result)
; 		    (   t 
;                 (move-to    (cdr lst) 
;                             (cons   (car lst) 
;                                     result)))))

; (defun my-reverse (lst)
; 	(move-to    lst 
;                 Nil))

; (defun my-reverse (lst)
;     (if (null lst)
;         nil
;         (append (my-reverse (cdr lst)) 
;                 (list (car lst)))))

(defun my-reverse (lst)
    (cond   (   (null lst)
                nil)
            (   t
                `(  ,@(my-reverse (cdr lst)) 
                    ,(car lst)))))

(defun my-reverse (lst)
    `(  ,@(my-reverse (cdr lst))
        ,(car lst)))

(defun my-reverse (lst &optional (res nil))
    (cond   (   (null lst)
                res)
            (   t
                (my-reverse (cdr lst) 
                            (cons   (car lst)
                                    res)))))

; (defun my-reverse (lst)
;     (if (null lst)
;         nil
;         (cons (my-reverse (cdr lst)) (car lst))))