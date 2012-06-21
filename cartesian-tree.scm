;; This file implements the cartesianTree function, as described in
;; problem 2 of the lab handout from November 8th.  A cartesian tree
;; is a binary tree structure derived from a list of numbers such that
;; the tree respects the min-heap property, and an inorder traversal
;; of the tree produces the original array sequence.

;; The tree produced by cartesianTree is of the form (root leftSubTree
;; rightSubtree).  Thus a leaf with a value of 1 would be (1 () ()).
;; A tree with a root of 2, and two leaf children, 3 and 4, would be
;; (2 (3 () ()) (4 () ())).

;; As you can see, the language you will implement is a general
;; purpose language that can solve the same types of problems you are
;; used to solving in C++.  Once you complete your interpreter, you
;; should be able to load this file via (load "cartesianTree.scm") and
;; then run the cartesianTree function.


(define INFINITY 2000000000)

;; appends elem to the end of the list ls
(define append
  (lambda (elem ls)
    (if (null ls)
	(list elem)
	(cons (car ls) (append elem (cdr ls))))))
  

(define getSubsHelper
  (lambda (ls min found before after)
    (if (null ls)
	(cons before after)
	(if (equal (car ls) min)
	    (getSubsHelper (cdr ls) min true before after)
	    (getSubsHelper (cdr ls)
			   min
			   found
			   (if found before (append (car ls) before))
			   (if found (append (car ls) after) after))))))
	    

;; splits the list ls around the element min
(define getSubs
  (lambda (ls min)
    (getSubsHelper ls min false (list) (list))))

(define findMinHelper
  (lambda (ls min)
    (if (null ls)
	min
	(findMinHelper (cdr ls)
		       (if (less (car ls) min)
			   (car ls)
			   min)))))

;; finds the minimum element in a list of unique numbers
(define findMin
  (lambda (ls)
    (findMinHelper ls INFINITY)))
  
;; creates a minheap out of a list integers such that an inorder
;; traversal of the tree will recreate the original list.
;;
;; example:
;; 
;; (cartesianTree (list 1 7 6 2 9)) -> 
;; (1 () (2 (6 (7 () ()) ()) (9 () ()))) 
(define cartesianTree
  (lambda (ls)
    (if (null ls)
	ls
	((lambda (min)
	   ((lambda (subs)
	      (list min
		    (cartesianTree (car subs))
		    (cartesianTree (cdr subs))))
	    (getSubs ls min)))
	 (findMin ls)))))
	    
       