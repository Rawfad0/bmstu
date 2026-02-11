(defun lollen(lol)
    (reduce #'+ (mapcar #'length lol)))

(lollen '((1 2) (1 2 3) (1)))
; 6