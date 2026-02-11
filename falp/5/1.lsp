(defun sub10(x)
    (-  x 
        10))

(defun sub10lst(lst)
    (mapcar #'sub10 
            lst))

(sub10lst '(-1 0 1 9 10 11)) 

; (-11 -10 -9 -1 0 1)