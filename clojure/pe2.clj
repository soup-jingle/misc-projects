;; #31

(def combos 
  (for [pnd2 [0 1]
        pnd1 (range (inc (/ (- 200 (* 200 pnd2)) 100)))
        p50 (range (inc (/ (- 200 (* 200 pnd2) 
                              (* 100 pnd1)) 50)))
        p20 (range (inc (/ (- 200 (* 200 pnd2) 
                              (* 100 pnd1) (* 50 p50)) 20)))
        p10 (range (inc (/ (- 200 (* 200 pnd2) (* 100 pnd1)
                              (* 50 p50) (* 20 p20)) 10)))
        p5 (range (inc (/ (- 200 (* 200 pnd2) (* 100 pnd1) 
                             (* 50 p50)(* 20 p20) 
                             (* 10 p10)) 5)))
        p2 (range (inc (/ (- 200 (* 200 pnd2) (* 100 pnd1) 
                             (* 50 p50) (* 20 p20) 
                             (* 10 p10) (* 5 p5)) 2)))
        :let [p1 (- 200 (* 200 pnd2) (* 100 pnd1) (* 50 p50) 
                    (* 20 p20) (* 10 p10) (* 5 p5) 
                    (* 2 p2))]
        :when (> p1 -1)]
    (vector pnd2 pnd1 p50 p20 p10 p5 p2 p1)))
              
;; #40

(defn get-int [n s]
  (read-string (str (nth s n))))

(def pe40 (apply str (range 1 1000001)))

(* (get-int 0 pe40) (get-int 9 pe40)
   (get-int 99 pe40) (get-int 999 pe40)
   (get-int 9999 pe40) (get-int 99999 pe40)
   (get-int 999999 pe40))
