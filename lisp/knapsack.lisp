;; Reading from file
(defun add-to-list (line)
	(let* ((dollar-sign (position #\$ line))
				 (weight (subseq line 0 dollar-sign))
				 (value (subseq line (1+ dollar-sign)))
				 (ns (read-from-string (concatenate 'string "(" weight ". " value ")"))))
		ns))

(defun read-knapsack-file (filename)
	(let* ((file (open filename))
				;(list nil)
				 (weight (car (read-from-string
									(concatenate 'string "(" (read-line file nil) ")")))))
		(loop for line = (read-line file nil) while line
					collecting (add-to-list line) into l
					finally (return (list weight l)))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Generate test problems
(defun gen-prob (size)
	(let ((weight (floor (* size (1+ (random size)) (/ 1 (log size))))))
		(loop for i from 1 upto size
					collecting (cons (* (1+ (random size)) 2)
													 (floor (* (/ (log size) (log 2))
																		 (1+ (random size)))))
					into items
					finally (return (list weight items)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Brute Force
(defun combinations (l)
	(if (null l) '(nil)
		(let* ((head (car l))
					 (tail (cdr l))
					 (tail-combo (combinations tail))
					 (m (mapcar (lambda (c) (cons head c)) tail-combo)))
			(append tail-combo m))))

(defun total-wt-val (l)
	(let ((wv (cons 0 0)))
		(map nil
				 #'(lambda (x)
						 (if (null x) 0
							 (progn
								 (setf (car wv) (+ (car wv) (car x)))
								 (setf (cdr wv) (+ (cdr wv) (cdr x))))))
				 l)
		wv))

(defun bf-knapsack (list)
	(let* ((weight (car list))
				 (c (combinations (cadr list)))
				 (r (reduce #'(lambda (a b) ;; Note the first 'a' is empty list
												(let ((awv (total-wt-val a))
															(bwv (total-wt-val b)))
													(cond
													 ((> (car bwv) weight) a)
													 ((> (cdr awv) (cdr bwv)) a)
													 (t b))))
										c))
				 (twv (total-wt-val r)))
		(list (car twv) (cdr twv) r)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Dynamic Programming ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defmacro memo (a b) `(if ,a ,a
										 (setf ,a ,b)))

(defun dpk* (cap items memo-array)
	(if (null items) (return-from dpk* (list 0 0 '()))
		(memo (aref memo-array cap (length items))
					(let* ((item (car items))
								 (w (car item))
								 (v (cdr item))
								 (rec1 (dpk* cap (cdr items) memo-array))) ;; recur
						(if (> w cap)
								rec1
							(let* ((rec2 (dpk* (- cap w) (cdr items) memo-array))
										 (v2 (+ v (car rec2))))
								(if (> (car rec1) v2) rec1
									(list v2 (+ w (cadr rec2)) (cons item (caddr rec2))))))))))

(defun dp-knapsack (list)
	(let* ((w (car list))
				 (l (cadr list))
				 (n (length l))
				 (memo-array (make-array (list (1+ w) (1+ n)) :initial-element nil)))
		(dpk* w l memo-array)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Branch and Bound ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun vpw (item)
	(if (null item) (list 0 item)
		(list (/ (cdr item) (car item)) item)))

(defun upper-bound (best-vpw cap value)
	(+ (* best-vpw cap) value))

(defun branch (cap weight value items sorted-list)
	(when (null sorted-list) items)
	(let* ((item (car sorted-list))
				 (w (caadr item))
				 (v (cdadr item))
				 (tail (cdr sorted-list)))
		(if (and
				 (> cap (+ weight w))
				 (> (upper-bound (caar tail) (- cap (+ weight w)) (+ value v))
						(upper-bound (caar tail) cap value)))
				(branch (- cap w) (+ weight w) (+ value v) (cons (cadr item) items) tail)
			(branch cap weight value items tail))))
		;(cond
		 ;((< cap (+ weight w)) (branch cap weight value items tail))
		 ;((< (upper-bound (caar tail) (- cap (+ weight w)) (+ value v))
		;		 (upper-bound (caar tail) cap value)) (branch cap weight value items tail))
		 ;(t (branch (- cap w) (+ weight w) (+ value v) (cons (cadr item) items) tail)))))

(defun bb-knapsack (list)
	(let* ((weight (car list))
				 (items (cadr list))
				 ;; Technically sorting is not necessary:
				 (vpw-l (sort (map 'list #'vpw items) #'> :key #'car)))
		(branch weight 0 0 nil vpw-l)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Greedy Approximation ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun add-best (max-weight sorted-list)
	(let ((current-weight 0)
				(current-value 0)
				(items '()))
		(loop for item in sorted-list
					when (< (+ current-weight (caadr item)) max-weight)
					do (progn (setf items (cons (cadr item) items))
										(setf current-weight (+ (caadr item) current-weight))
										(setf current-value (+ (cdadr item) current-value)))
					finally (return (list current-weight current-value items)))))

(defun ga-knapsack (list)
	(let* ((weight (car list))
				 (l (cadr list))
				 (vpw-l (map 'list #'vpw l)))
		(add-best weight (sort vpw-l #'> :key #'car))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Test
(defun get-runtime (function)
	(let ((then (get-internal-real-time)))
			(funcall function)
			(/ (- (get-internal-real-time) then)
				 (* internal-time-units-per-second 1.0))))

(defun test-bf ()
	(loop for i from 5 upto 22
				do (progn
						 (format t "~a ~a~a"
										 i (get-runtime (lambda () (bf-knapsack (gen-prob i)))) #\newline)
						 (force-output))))

(defun test-ga ()
	(loop for i from 5 upto 22
				do (progn
						 (format t "~a ~a~a"
										 i (get-runtime (lambda () (bf-knapsack (gen-prob i)))) #\newline)
						 (force-output))))

(defun test-dp ()
	(loop for i from 40 upto 400 by 40
				do (progn
						 (format t "~a ~a~a"
										 i (get-runtime (lambda () (dp-knapsack (gen-prob i)))) #\newline)
						 (force-output))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main

(defun do-knapsack (L)
	(let* ((file (open "output.txt" :direction :output :if-exists :supersede))
				 (weight (car L))
				 (bf (get-runtime (lambda () (bf-knapsack L))))
				 (dp (get-runtime (lambda () (dp-knapsack L))))
				 (r (dp-knapsack L))
				 (v (car r))
				 (w (cadr r))
				 (i (caddr r))
				 (ga (get-runtime (lambda () (ga-knapsack L))))
				 (r2 (ga-knapsack L))
				 (w2 (car r2))
				 (v2 (cadr r2)))
		(progn
			(format file "Maximum weight: ~a~a" weight #\newline)
			(map nil #'(lambda (i) (format file "~a ~a " (car i) (cdr i))) i)
			(format file "~aExhaustive: ~as~aDynamic: ~as~aBranch and Bound: (error)~aGreedy Approx.: ~as~a"
							#\newline bf #\newline dp #\newline #\newline ga #\newline)
			(format file "Optimum Weight: ~a~aOptimum Value: ~a~aApproximate Weight: ~a~aApproximate Value: ~a~aApproximation Accuracy: ~a~a" w #\newline v #\newline w2 #\newline v2 #\newline (/ v2 v) #\newline)
			(close file)
			(format t "output.txt written...~a" #\newline))))

(defun main ()
	(if (= (length sb-ext:*posix-argv*) 3)
			(let ((file (open (nth 2 sb-ext:*posix-argv*))))
				(do-knapsack (read-knapsack-file file)))
		(format t "Must include a file name!")))

(main)

