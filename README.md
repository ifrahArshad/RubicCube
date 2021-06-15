# RubicCube
Introduction:
We use two algorithms to solve the Rubik’s cube that is Iterative-Deepening and A* algorithm. The methodology and results are discussed. 
Methodology:
Firstly, we make the 12 moves of the Rubik’s Cube. The we applied both algorithms on the given state to reach the target.
In Iterative-Deepening we used depth first search (DFS) but we limit the depth through which it finds the solution after a certain depth we stop. We make a wrapper function to give different depths to the DFS. We perform DFS to a certain depth. After each move, we compare with output and after that further movements are applied to the given depth.
In A* queue is used we perform 12 moves after each move cube is compared and after that further 12 moves are applied and compared and so on. A* uses a heuristic function to decide. In the heuristic function the current state of cube is compared to target and different colors on each phase is counted and then divided by 12. This heuristic is used in A* algorithm.  
