# CS302-FP
CSS302 Final Project
Vincent Pham & Prim Wandeevong

Creation of graph data structure under alias of cities, neighbors, and distances for vertices, edges, and weights, respectively. This project
was done using a bunch of STL containers including std::pair and std::vector. As by project guidelines, we solved this problem using the brute force
method which has a max runtime of O(!n) since we are permuting every single city and back. There was no limits on number of traversals per edge, but
I kept them at 2 nodes.

Prim was in charge of creating the input of the main driver, and some of the Cities.h functions. I created and implemented the base graph classes, the
TSP problem printPaths(), permutePaths(), permuteBack(), etc. To do so, I first tried to use the std::next_permutation() which didn't work with my custom
graphing classes. It only works on a sorted array as it functions based on the < operator. I then tried to do a recursive call to std::rotate(), that didn't
work with my classes because it also uses < operators. I then tried to create my own vectorRotate() function but that failed since I could not get the iterators
to pass by reference. My final solution (permutePath()) was simply creating a vector<pair<city_node, bool>> which kept track of each city that was traversed, so
they wouldn't be traversed twice. I traversed every city, setting each bool to true as there was a recursive call to each. Then once all the bools were true, it 
would call another recursive function, permuteBack(), which was the same except the base case was the final city being the same as the starting city, returning
the salesman to where he started. This function would also keep track of the min cost and it's corresponding path.

