
(define (search str k c i j indexes l)
  (if (eq? str '())
    (begin (display (list j k))(newline)
           (if (> j k) l 0))
    (begin (display (list i (car str) k "c=" c j))(newline)
           (if (eq? (car str) c)
             i
             (search (cdr str) k c (+ i 1) j indexes l))
           )
    ))

(define (main args)
  (if (< (length args) 3) 1
   (begin (display 0)(newline))
    ;(begin (display (search (string->list (cadr args)) (caddr args) "1" 0 0 '() 0)) (newline))
    ))
