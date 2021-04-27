(first
 (filter #(>  % 500) 
         (for [i (range)]
           (count (divisors (reduce + (range i)))))))

(loop [i 1]
  (if (> (count (divisors (reduce +' (range i)))) 500)
    (reduce +' (range i))
    (recur (inc i))))

;; Code I used:
(def triangles (lazy-cat [0] (map + triangles (iterate inc 1))))

(defn divisors [n] (* 2 (count (filter #(zero? (rem n %))
                                       (range 1 (Math/sqrt n))))))

(first (filter #(> (divisors %) 500) triangles))
