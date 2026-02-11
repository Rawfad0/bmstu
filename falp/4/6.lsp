(defun roll_dice ()
    (+ (random 6) 1))

(defun roll_two_dices ()
    (cons (roll_dice)
        (cons (roll_dice) Nil)))

(defun roll_sum (roll)
    (+ (car roll) (cadr roll)))

(defun second_roll_process (r1 r2)
    (cond   (   (or (=  (roll_sum r2) 
                        7) 
                    (=  (roll_sum r2) 
                        11))
                (print `(1st rolled ,(car r1) ,(cadr r1) \\ 2nd rolled ,(car r2) ,(cadr r2) and won)))
            (   (> (roll_sum r2) (roll_sum r1))
                (print `(1st rolled ,(car r1) ,(cadr r1) \\ 2nd rolled ,(car r2) ,(cadr r2) \\ 2nd won)))
            (   T
                (print `(1st rolled ,(car r2) ,(cadr r2) \\ 2nd rolled ,(car r2) ,(cadr r2) \\ 1st won)))))

(defun reroll_process (r1 r12)
    (cond   (   (or (=  (roll_sum r12) 
                        7) 
                    (=  (roll_sum r12) 
                        11))
                (print `(1st player rolled ,(car r1) ,(cadr r1) \\ rerolled ,(car r12) ,(cadr r12) and won)))
            (   T
                (second_roll_process    r12
                                        (roll_two_dices)))))

(defun first_roll_process (r1)
    (cond   (   (or (=  (roll_sum r1) 
                        7) 
                    (=  (roll_sum r1) 
                        11))
                (print `(1st player rolled ,(car r1) ,(cadr r1) and won)))
            (   (or (=  (roll_sum r1) 
                        2) 
                    (=  (roll_sum r1) 
                        12))
                (reroll_process r1
                                (roll_two_dices)))
            (   T
                (second_roll_process    r1
                                        (roll_two_dices)))))

(defun dice_game ()
    (first_roll_process (roll_two_dices)))
    
(dice_game)
