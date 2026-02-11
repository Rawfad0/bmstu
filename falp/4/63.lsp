(defun roll ()
    (cons (+ (random 6) 
             1)
          (cons (+ (random 6) 
                   1) 
                Nil)))

(defun roll_sum (roll)
    (+ (car roll) (cadr roll)))

(defun instawin_check (roll)
    (or (=  (roll_sum roll) 
            7) 
        (=  (roll_sum roll) 
            11)))

(defun reroll_check (roll)
    (or (=  (roll_sum roll) 
            2) 
        (=  (roll_sum roll) 
            12)))

(defun second_roll (r1 r2)
    (print `(2nd rolled ,(car r2) ,(cadr r2)))
    (cond   (   (instawin_check r2)
                (print `(2nd player won)))
            (   (reroll_check r2)
                (second_roll    r1
                                (roll)))
            (   (<  (roll_sum r1) 
                    (roll_sum r2))
                (print `(,(roll_sum r1) < ,(roll_sum r2) -> 2nd player won)))
            (   (>  (roll_sum r1) 
                    (roll_sum r2))
                (print `(,(roll_sum r1) > ,(roll_sum r2) -> 1st player won)))
            (   T 
                (first_roll (roll)))))

(defun first_roll (r1)
    (print `(1st rolled ,(car r1) ,(cadr r1)))
    (cond   (   (instawin_check r1)
                (print `(1st player won)))
            (   (reroll_check r1)
                (first_roll (roll)))
            (   T
                (second_roll    r1
                                (roll)))))

(defun dice_game ()
    (first_roll (roll)))
    
(dice_game)
