;; Problem 32, 38, 104 (pandigital)
(defn pandigital? [n r]
  (= (set (range 1 (inc r))) (splitter n #{})))
(defn splitter [n s]
  (if (zero? n) s
      (splitter (quot n 10) (conj s (rem n 10)))))


;; Problem 14 ---------------------------------------------------
(defn collatz-seq [n]
				(loop [n n acc []]
					(cond 
					 (= 1 n) (conj acc n)
					 (even? n) (recur (/ n 2) (conj acc n))
					 :else (recur (inc (* n 3)) (conj acc n)))))
(defn cs [m]
  (loop [n m acc 0]
    (cond 
     (= 1 n) acc
     (even? n) (recur (/ n 2) (inc acc))
     :else (recur (inc (* n 3)) (inc acc)))))
(defn cs2 [a]
  (loop [x 1 y (sorted-map-by >)]
    (if (= x (inc a)) y
        (recur (inc x) (assoc y (cs x) x)))))
(defn cs3 [a]
  (loop [x 1 y [1 1]]
    (let [cx (cs x)]
      (cond (= x (inc a)) y
            (> cx (y 1)) (recur (inc x) (vector x cx))
            :else (recur (inc x) y)))))
;; time: 30309.291128msecs

;; Problem 17 ---------------------------------------------------
;; Done! in sbcl

;; Problem 24 ---------------------------------------------------
(require '[clojure.math.combinatorics :as combo])
(nth (combo/permutations [0 1 2 3 4 5 6 7 8 9]) 999999)
