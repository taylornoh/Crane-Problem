# Project 2: Dynamic vs. Exhaustive - Crane unloading problem
# Group Members:
* Michael Chhun mchhun2@csu.fullerton.edu
* Taylor Noh taylornoh@csu.fullerton.edu
* Chenhao Wei chenhao.wei@csu.fullerton.edu
* Quan Tru Thai miket126@csu.fullerton.edu
# CPSC 335 - Algorithm Engineering
# Spring 2023
# Instructor: Himani Tawade

**Clone This repository into your repository and implement the code, along with a document with required details mentioned at the last, a demo video, readme file and .gitignore file. Submission will be a git repo link with all the requirements updated to repo on canvas.**

# Abstract

In this project you will implement two algorithms that both solve the crane unloading problem. The first algorithm uses exhaustive optimization and takes exponential time. The second algorithm uses dynamic programming, and takes cubic time. Check back here regularly (and especially before your final submission), to make sure your submission complies with any changes or edits. You may check the top of the document, where the date of the last edit will be noted.

# The Hypothesis

This experiment will test the following hypothesis:
Polynomial-time dynamic programming algorithms are more efficient than exponential-time exhaustive search algorithms that solve the same problem.

# The Problem

Both algorithms will be used to solve another interesting problem related to containers and loading them into ships. Suppose that you have arrived at the seaport and need to navigate among buildings to reach various cranes that will take your containers and load them into various ships. 

Each truck is allowed to follow only one route and it can drive only south or east, but cannot drive north nor west. We will represent the seaport drivable area as a 2D grid. A truck starts at row 0 and column 0, i.e. coordinate (0, 0), at the top-left corner. Each c cell represents a crane, each X represents a building, and each . cell represents a passable space. A truck’s goal is to plan a route for driving that maximizes the number of cranes that can be reached, while avoiding buildings. 

In this diagram, the + cells represent passable space that the truck drove through, and the capital C cells represent cranes that the truck reached and had cargo unloaded. A . still represents passable space that was never visited, and lower-case c still represents cranes that were neither reached nor used. Observe that the path starts at (0, 0), and moves east and south, but not in any other direction. Also note that there is no valid path in this grid that would reach more than 7 cranes.

# The Exhaustive Optimization Algorithm

Our first algorithm solving the crane unloading problem is exhaustive. The output definition says that the number of cranes reached must be maximized, so this is an exhaustive optimization algorithm (not exhaustive search).

Since all paths start at (0, 0) and the only valid moves are east and south, paths are never west or north. So the longest possible path is one that reaches the bottom-right corner of the grid. The grid has r rows and c columns, so this longest path involves (r-1) down moves and (c-1) right moves, for a total of
r + c - 2 moves.

There are two kinds of moves, east → and south ↓. Coincidentally there are two kinds of bits, 0 and 1. So we can generate move sequences by generating bit strings, using the same method that we used to generate subsets in section 7.5 of the ADITA textbook. We loop through all binary numbers from 0 through 2n-1, and interpret the bit at position k as the east/south step at index k.

A candidate path is valid when it follows the rules of the crane unloading problem. That means that the path stays inside the grid, and never crosses a building (X) cell.

This is a very slow algorithm.

# The Dynamic Programming Algorithm

This problem can also be solved by a dynamic programming algorithm. This dynamic programming array A stores partial solutions to the problem. In particular,

A[r][c] = the crane-maximizing path that starts at (0, 0) and ends at (r, c); or None if (r, c) is unreachable

Recall that in this problem, some cells are occupied by buildings and are therefore to be avoided by trucks.

The base case is the solution for A[0][0], which is the trivial path that starts and takes no subsequent steps.

A[0][0] = [start]

We can build a solution for a general case based on pre-existing shorter paths. Trucks can only drive east and south. So there are two ways a truck path could reach (i, j).

The truck path above (i, j) could add a southward step.

The truck path to the left of (i, j) could add an eastward step.

The algorithm should pick whichever of these two alternatives is optimal, which in this problem means whichever of the two candidate paths reach more cranes.

However, neither of these paths is guaranteed to exist. The from-above path (1) only exists when we are not on the top row (so when i>0), and when the cell above (i, j) is not a building. Symmetrically, the from-west path (2) only exists when we are not on the leftmost column (so when j>0) and when the cell left of (i, j) is not a building

Finally, observe that A[i][j] must be None when G[i][j]==X, because a path to (i, j) is only possible when (i, j) is not a building.

Altogether, the general solution is:

G[i][j] = None		if G[i][j]==X

G[i][j] = whichever of from_above and from_left is non-None and reaches most cranes where

from_above = None if i=0 or G[i-1][j]==X; or G[i-1][j] + [↓] otherwise

from_left = None if j=0 or G[i][j-1]==X; or G[i][j-1] + [→] otherwise

The optimal solution is not required to end at (r-1, c-1). Indeed, the optimal path may end anywhere. So after the main dynamic programming loop, there is a post-processing step to find the path reaching most cranes.


The time complexity of this algorithm is dominated by the general-case loops. The outer loop repeats n times, the inner loop repeats n times, and creating each of from_above and from_left takes O(n) time to copy paths, for a total of O(n3) time. While O(n3) is not the fastest time complexity out there, it is polynomial so considered tractible, and is drastically faster than the exhaustive algorithm.

# To Do:

# I. Create a Document with the following 
- Exhastive Algorithm Soltuion Psuedocode and time analysis
- Plot a graph for time vs input size for the algorthm
- Dynamic Algorithm Soltuion Psuedocode and time analysis
- Plot a graph for time vs input size for the algorthm
- Answer the below question based on the algorithm run time observations

Questions
1.	Is there a noticeable difference in the performance of the two algorithms? Which is faster, and by how much? Does this surprise you?

2.	Are your empirical analyses consistent with your mathematical analyses? Justify your answer.

3.	Is this evidence consistent or inconsistent with hypothesis 1? Justify your answer.

4.	Is this evidence consistent or inconsistent with hypothesis 2? Justify your answer.


# II. Create video demo for a running implementation format is same as Project 1

# III. Complete the todo sections in the cranes_algs.hpp, update the readme file with team member names and email ID.



