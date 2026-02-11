(defun f(x y z)
    (if (> x y) (> z x) (> x z)))

(print 'F)

(print (f 1 2 3))
(print (f 1 2 2))
(print (f 1 0 2))
(print (f 1 2 0))
(print (f 3 1 0))

(print (f 1 1 2))
(print (f 1 0 1))
(print (f 1 2 1))
(print (f 1 1 0))


(defun g(x y z)
    (cond   (   (> x y) 
                (> z x))
            (   (> x z)
                (> y x))))

(print 'G)
(print (g 1 2 3))
(print (g 1 2 2))
(print (g 1 0 2))
(print (g 1 2 0))
(print (g 3 1 0))

(print (g 1 1 2))
(print (g 1 0 1))
(print (g 1 2 1))
(print (g 1 1 0))
