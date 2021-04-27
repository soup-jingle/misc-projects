;; #109

(defn checkouts [n]
  (+ (reduce + (for [d (range 1 (min (inc (/ n 2)) 21))]
                 (dart-combos 2 (- n (* 2 d)))))
     (if (>= n 50) (dart-combos 2 (- n 50)) 0)))
(defn is-single? [n]
  (or (and (> n 0) (< n 21))
      (= n 25)))
(defn is-double? [n]
  (or (and (even? n) (< n 41) (> n 0))
      (= n 50)))
(defn is-triple? [n]
  (and (> n 0) (< n 61)
       (= (/ n 3) (int (/ n 3)))))

(defn dart-combos [t value]
  (cond (< value 1) 0
        (= 2 t) (reduce + (for [i (range 1 (min (inc value) 21))] 
                         (+ (dart-combos 1 (- value i))
                            (dart-combos 1 (- value (* 2 i)))
                            (dart-combos 1 (- value (* 3 i))))))
        (= 1 t) (+ (if (is-single? value) 1 0)
                   (if (is-double? value) 1 0)
                   (if (is-triple? value) 1 0))))

