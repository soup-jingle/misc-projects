(ns pe)
(defn is-palindrome? [n]
  (let [s (str n)
        f (seq s)
        r (reverse s)]
    (= f r)))

(defn to-binary [n]
  (Integer/toBinaryString n))
(defn to-decimal [bs]
  (Integer/parseInt bs 2))

(let [dp (filter is-palindrome? (range 1 1000000))
      bn (map to-binary dp)
      bp (filter is-palindrome? bn)
      dbp (map to-decimal bp)]
  (reduce + dbp))
;; Time: 1773.648083msec
