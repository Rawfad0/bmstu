(ns hello-world.core)

(println "Hello world!")

(reverse '(a b c))
(reverse ())
(reverse '(a b (c (d))))
(reverse '(a))

(last '(a b c))
(last '(a b (c)))
(last '(a))
(last ())
(last '((a b c)))

(defn get_last1 [lst] (last lst))
(defn get_last2 [lst] (first (reverse lst)))

(defn del_last [lst] (reverse (next (reverse lst))))

(defn swap-first-last [lst] (concat (list (last lst)) (reverse (next (reverse (next lst)))) (list (first lst))))

(defn is_palindrome [lst]
    (=  lst
        (reverse lst)))

(defn get_capital [table contry]
    (next   (assoc  country
                    table)))

;; 6
(defn roll []
    (list   (+  (rand-int 6) 
                1)
            (+  (rand-int 6) 
                1)))

(defn roll_sum [roll]
    (+ (first roll) (second roll)))

(defn instawin_check [roll]
    (or (=  (roll_sum roll) 
            7) 
        (=  (roll_sum roll) 
            11)))

(defn reroll_check [roll]
    (or (=  (roll_sum roll) 
            2) 
        (=  (roll_sum roll) 
            12)))

(defn second_roll [r1 r2]
    (println `(second rolled ~(first r2) ~(second r2)))
    (cond   (instawin_check r2) 
            (println `(second player won))
            (reroll_check r2)   
            (second_roll    r1
                            (roll))
            (<  (roll_sum r1) 
                (roll_sum r2))
            (println `(~(roll_sum r1) < ~(roll_sum r2) -> second player won))
            (>  (roll_sum r1) 
                (roll_sum r2))
            (println `(~(roll_sum r1) > ~(roll_sum r2) -> first player won))
            :else 
            (first_roll (roll))))

(defn first_roll [r1]
    (println `(first rolled ~(first r1) ~(second r1)))
    (cond   (instawin_check r1)
            (println `(first player won))
            (reroll_check r1)
            (first_roll (roll))
            :else
            (second_roll    r1
                            (roll))))

(defn dice_game []
    (first_roll (roll)))
    
(dice_game)
