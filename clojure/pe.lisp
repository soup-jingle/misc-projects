(+ (* 3 891) ;; 891 times "and" needs to be included
   (length 
    (remove #\- 
	    (remove #\space 
		    (apply #'concatenate 'string 
			   (mapcar #'(lambda (n) 
				       (format nil "~r" n)) 
				   (range 1 1001)))))))
