(defun set-equal(s1 s2)
    (and    (subsetp s1 s2)
            (subsetp s2 s1)))

(set-equal '(1 2 3) '(1 2))
; NIL

(set-equal '(1 2 3) '(1 3 2))
; T

(set-equal '() '())
; T