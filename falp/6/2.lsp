(defun f (lst)
	(cond   (   (atom lst) 
                lst)
		    (   (atom (car lst)) 
                (f (cdr lst)))
		    (   t 
                (car lst))))	
