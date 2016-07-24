# An implementation and visualization of the Ant Colony System algorithm.

## Introduction
A project about visualizing the Ant Colony System algorithm (with some local search improvements) using C++ with Qt. It was done as a project to learn how to create a little software. It was coded with Qt Creator
Ant Colony System is an algorithm to optimize the Traveling Salesman Problem (TSP) : finding the shortest hamiltonian cycle in a complete graph.

### Problem to optimize
Here we will more precisely try to find the shortest cycle to visit n points on the 2D plane.

### Screenshot
Here's what the main window looks like when the algorithm is running :
![image](https://raw.githubusercontent.com/Bleuje/antcolonysystem-tsp-qt/master/vwindow.png)

## Algorithm
I found details about the Ant Colony System algorithm in this paper :
http://www.i3s.unice.fr/~crescenz/publications/travaux_etude/colonies_fourmis-200605-rapport.pdf

Then I added a local search (it is still optional) after each ant walk : I try to reverse or shift subsequences of the permutation many times to improve it. I think it has greatly increased the quality of my results. 

## Graphical user interface
### Defining the set of points to work with.
The user can launch many colonies at the same time to optimize the problem. Since the algorithm is based on randomness, it can show different results.
You can choose the number of colonies.
Then you can either load an existing set of points, or generate a new one. The width and height requested define the size of the rectangle in which points will be selected randomly (integer coordinates), and also the size of the view in pixel (although this is limited).
The set of points you used will be automatically saved in the folder '/problems' in a .txt file.
Format : number of points, followed by the coordinates of each point.

### Definining parameters
On the next window, the user can choose the parameters of the algorithm. The previous pdf file should clarify the meaning of most paramters, although I add 10*Q/length² instead of Q/length on each edge after the ant walk is computed (I decided to increase the effect of a difference in length).
The elite field is the number of times the pheromones of the best ant will be added again, at each iteration.
The number of local search iterations is the number of tries to try to improve each ant random walk.
The maximum number of neighbors can be used to consier only the closest vertex as next possible positions. The problem with this is that it can prevent you from completing a cycle.

### Visualization window
Now the algorithm is ready to be launched using the button "Run". You can pause it and modify the parameters for each colony at any time. The amount of pheromones is represented in grean, you can hide it to increase performance if there are too many edges. At the end the best permutation will be saved in the folder '/results'.
Format : length of the path, followed by the indexes of the points in the path.

## How to run the program
With this repositary you should have all the source files necessary to compile the code in Qt Creator like me.

## Known flaws / future improvements
- The code should be completely in english, or at least in only one language.
- There should be more comments to describe methods, and to document constraints on parameters.
- Classes should be implemented in a way such that looking at the corresponding code is note necessary.
- Variables and functions should choose a strict namin convention.
- There shouldnt be as many constants that haven't been clearcly defined.
- The architecture of the code regarding the use of buttons could be much better.
