# Futoshiki-Solver
A program for testing a conjecture regarding solvable Futoshiki puzzles.

Conjecture 3.5.6. from Edmond J. Gao's thesis, "Futoshiki: A Latin Square Puzzle Variant":
    In a blank n by n Futoshiki with less than n inequalities with no loops, there exists at least one solution.

This program attempts to generate all such Futoshiki puzzles for a particular n, then solve them. 
If it finds a counterexample, it will output it in the terminal.

It has currently proven the conjecture true for n <= 5. It requires more performance optimisation to go further 
than this in a reasonable amount of time. There are a few methods by which this can occur:

1. Making the solver itself smarter; currently it uses a simple DFS backtracking algorithm, but it could be 
enhanced with constraint-satisfaction logic. Namely, keeping track of all the possibilities for each cell,
and gradually ruling them out. Space complexity should be kept in mind when doing this; for example, making a 
copy of the possibilities for each step of the recursion tree would probably result in a heap crash.

2. Remove redundant Futoshikis. Some Futoshiki puzzles are equivalent to each other; e.g. flipping or 
rotating along the centre of the grid, or inverting all the inequalities. If I can find a way of efficiently
categorising "equivalence classes" of Futoshiki, I can reduce the work by a factor of 32.

3. Using more performant STL/Ranges methods for iteration, as opposed to C-style loops and logic.