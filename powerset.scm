(define append (lambda (ls1 ls2)
	(if (null ls1) ls2 
	    (cons (car ls1) 
		      (append (cdr ls1) ls2)))))	
				
(define map (lambda (fn ls) 
	(if (null ls) ls 
	    (cons (fn (car ls))
			  (map fn (cdr ls))))))

(define powerset (lambda (ls) 
	(if (null ls) (list ls) 
		(append (powerset (cdr ls)) 
		        (map (lambda (subset) (cons (car ls) subset)) 
				     (powerset (cdr ls)))))))

				
