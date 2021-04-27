;; Solution to # 52

(defn same-digits? 
  ([a b c d e f] (= (into #{} (str a)) (into #{} (str b))
                    (into #{} (str c)) (into #{} (str d))
                    (into #{} (str e)) (into #{} (str f)))))

(first (for [i (range) 
             :when (and (same-digits? i (* 2 i)
                                      (* 3 i) (* 4 i)
                                      (* 5 i) (* 6 i))
                        (> i 0))] i))



;; Solution to #81

(defn go-x [x y matrix]
  (if (< (+ (get-in matrix [y x]) (get-in matrix [y (dec x)]))
         (+ (get-in matrix [y x]) (get-in matrix [(dec y) x])))
    true))

#_(defn move-up [matrix]
  (conj (vec (butlast (butlast matrix)))
        (vec (map + (last matrix) (last (butlast matrix))))))

#_(defn transpose [matrix]
  (apply mapv vector matrix))

#_(defn move-left [matrix]
  (transpose (move-up (transpose matrix))))

(defn move-up [x y matrix]
  (conj (vec (butlast (butlast matrix)))
        (conj (vec (replace (last (butlast matrix)) (range x)))
              (+ (get-in matrix [y x]) (get-in matrix [(dec y) x])))))

(defn move-left [x y matrix]
  (conj (vec (butlast matrix))
        (conj (vec (replace (last matrix) (range (dec x))))
              (+ (get-in matrix [y x]) (get-in matrix [y (dec x)])))))

(defn least-path [x y matrix]
  (cond (= 0 x y) (get-in matrix [0 0])
        (= 0 y) (recur (dec x) y (move-left x y matrix))
        (= 0 x) (recur x (dec y) (move-up x y matrix))
        (go-x x y matrix) (least-path (dec x) y (conj (vec (butlast matrix)) 
                                                      (vec (replace (nth matrix y) (range x)))))
        :else (least-path (dec x) y (vec (butlast matrix)))))

(def example81-mat [[131 673 234 103 18]
              [201 96 342 965 150]
              [630 803 746 422 111]
              [537 699 497 121 956]
              [805 732 524 37 331]])
