19/10/2019 note : realized that the algorithm should probably be called "Ant System" and not "Ant Colony System"

# An implementation and visualization of the Ant Colony System algorithm.

## Introduction
This is a project about visualizing the Ant Colony System algorithm (with some local search improvements) using C++ with Qt. It was done as a project to learn how to create a little software. It was coded with Qt Creator.

Ant Colony System is an algorithm to optimize the Traveling Salesman Problem (TSP) : finding the shortest hamiltonian cycle in a complete graph.

### Problem to optimize
Here we will more precisely try to find the shortest cycle to visit n points on the 2D plane.

### Screenshot
Here's what the main window looks like while the algorithm is running :
![image](https://raw.githubusercontent.com/Bleuje/antcolonysystem-tsp-qt/master/vwindow.png)

## Algorithm
I found details about the Ant Colony System algorithm in this french paper :
http://www.i3s.unice.fr/~crescenz/publications/travaux_etude/colonies_fourmis-200605-rapport.pdf

Then I added a local search (it is still optional) after each ant walk : it tries to reverse or shift subsequences of the permutation many times to improve it. It greatly increases the quality of results. Actually most of the important work seems to be done by local search, and ant pheromones can be seen as an improvement of local search.

## Graphical user interface
### Defining the set of points to work with.
The user can launch many colonies at the same time to optimize the problem. Since the algorithm is based on randomness, it can show different results.
You can choose the number of colonies.
Then you can either load an existing set of points, or generate a new one. The width and height requested define the size of the rectangle in which points will be selected randomly (integer coordinates), and also the size of the view in pixel (although this is limited).
The set of points you used will be automatically saved in the folder '/problems' in a .txt file.
Format : number of points, followed by the coordinates of each point.

### Definining parameters
On the next window, the user can choose the parameters of the algorithm. The previous pdf file should clarify the meaning of most paramters.
The elite field is the number of times the pheromones of the best ant will be added again, at each iteration.
The number of local search iterations is the number of tries to try to improve each ant random walk.
The maximum number of neighbors can be used to consier only the closest vertex as next possible positions. The problem with this is that it can prevent you from completing a cycle.

### Visualization window
Now the algorithm is ready to be launched using the button "Run". You can pause it and modify the parameters for each colony at any time. The amount of pheromones is represented in grean, you can hide it to increase performance if there are too many edges. At the end the best permutation will be saved in the folder '/results'.
Format : length of the path, followed by the indexes of the points in the path.

## How to run the program
With this repository you should have all the source files necessary to compile the code in Qt Creator like me :
Open ants2.pro with Qt Creator.

## Results
The algorithm with right parameters can achieve a distance less than 12.5 in a few seconds on 250 points from this benchmark (french website) :

http://labo.algo.free.fr/defi250/classement.php?id=1

It achieved 11.87 (best cycle seems to be about 11.8), without looking seriously for good parameters. The other results on the website are old, but the complexity of the problem is such that the algorithm should be still more important than computer speed.

## Known flaws / future improvements
- There shouldn't be as many constants that haven't been clearly defined.
- The architecture of the code regarding the use of buttons could be better.
- Long-term improvement : apply ant colony to other problems than TSP.
