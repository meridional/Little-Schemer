(define even
  (lambda (x)
    (if (equal x 0)
	true
	(if (equal x 1)
	    false
	    (odd (subtract x 1))))))

(define odd
  (lambda (x)
    (if (equal x 1)
	true
	(if (equal x 0)
	    false
	    (even (subtract x 1))))))