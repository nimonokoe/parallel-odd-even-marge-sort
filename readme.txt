
Exercise 2:
Implement parallel sort algorithm and check scalability.
(1) Implement odd-even sort (or any parallelizable sort algorithm you like) 
    by rewriting sortprog() in SortProg.c
(2) Parallelize your sort algorithm with OpenMP etc.
(3) Evaluate scalability by changing definition of NUM_THREADS in Sort1.c.
    (Scalability means speed-up when # of processors (threads) increases.)
    And calculate the ratio of parallelizable part of your sort program
    in the sense of Amdahl's law.
(4) Submit your sortprog.c and document explaining your algorithm, scalability
    and the ratio of parallelizable part.

readme.txt: this file
Sort1.c: main program
SortProg.c: bubble sort program
FileOp.c: functions for file operation
SortData100000_0.txt: imput file
Result100000_0.txt: "answer"
