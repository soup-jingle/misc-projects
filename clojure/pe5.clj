;; #127

(defn prime-factors
  ([n] (prime-factors n 2 ()))
  ([n k acc] 
     (if (= 1 n)
       acc
       (if (= 0 (rem n k))
         (recur (quot n k) k (cons k acc))
         (recur n (inc k) acc)))))

(defn radical [n]
  (reduce * (set (prime-factors n))))

(defn gcd
	([a b] 
     (if (zero? b) a
         (recur b (mod a b))))
	([a b & more] 
     (if (empty? (rest more)) (gcd a (gcd b (first more)))
         (recur (gcd a b) (first more) (rest more)))))

;;Not correct
(defn abc-hits [n]
  (for [a (range 1 (dec n))
        b (range (inc a) n)
        :let [c (+ a b)
              r (radical (* a b c))]
        :when (and (= (gcd a b) (gcd b c) (gcd a c))
                   (< r c))]
    c))


;; #187
;; Takes forever
(count (filter #(= (count (prime-factors %)) 2) (range 2 (reduce * (repeat 8 10)))))


;; #439
(defn d [n]
  (reduce +' (prime-factors n)))
(defn t [n]
  (for [i (range n) j (range n)
        :let [a (inc i) b (inc j)]] (*' a b)))
(defn s [n]
  (reduce +' (map d (t n))))
