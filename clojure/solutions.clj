
;; Solution #1
(reduce + (filter (fn [x] (or 
                           (zero? (mod x 5)) 
                           (zero? (mod x 3)))) 
                  (range 1000)))

;; Solution #6
(- (* (reduce + (range 101)) (reduce + (range 101)))  
   (reduce + (for [i (range 101)] (* i i))))

;; Solution #9
(first 
 (for [i (range 1 332) 
       j (range i 664) 
       k (range (- 1000 i j) 1000)
       :when (and (= (+ (* i i) (* j j)) (* k k))
                  (= (+ i j k) 1000))] 
   (* i j k)))
;; [a b c] = [200 375 425]
;; In what range should each truly HAVE to search?

;; Solution #10
(apply + (filter (reduce (prime? (range 2N 2000000N)))))

;; Solution #20
(apply + (digit-split (apply * (for [i (range 1N 101N)] i)) []))

;; Solution #21
(apply + 
       (for [i (range 10000) 
             :let [a (apply + (divisors i)) 
                   b (apply + (divisors a))] 
             :when (and (= b i) (not= a b))] 
         i))


(apply + ((fn [x] (for [n x :when (prime? n)] n)) (range 2000000)))
((fn [x] (for [n x :when (prime? n)] n)) (range 200))




;;;;;;;;;; FUNCTIONS ;;;;;;;;;;
;; Divisors function:
(defn divisors [x] 
  (for [i (range 1 (+ (/ x 2) 1)) 
        :when (zero? (mod x i))] 
    i))

;; digit-split function
(defn digit-split [n out]
  (if (= n 0) out
    (let [d (rem n 10)
          r (quot n 10)]
      (recur r (cons d out)))))

;; working on prime function
(defn prime? [n]
				(cond (= 2 n) true 
							(= 3 n) true
							(even? n) false
						  (not-any? false? 
                        (for [i (range 2N (+' (Math/sqrt n) 1N))
                              :when (zero? (mod n i))] false))
              true
              :else false))

;; prime-divisors function
(defn prime-divisors [n] 
  (for [i (range 2 (+ (Math/sqrt n) 1)) 
        :let [a (mod n i)]
        :when (zero? a)] i))
