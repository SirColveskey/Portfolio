/*---------------------------------------*/
/*         Algorithms - Project 1        */
/*  Implementing Minimum Spanning Tree   */
/*            Prim's Algorithm           */
/*       Date Completed: 11/22/2016      */
/*---------------------------------------*/
/*
 * Name: Benjamin Cooper
 * Purpose: To implement Prim's MST algorithm in C++
 * Method: 
 * 
 * First standard input will be parsed in order to form a graph.
 * Then a point will be selected on the graph as the root node.
 * We will proceed to grow the tree by tracking what the cheapest
 * way to add a point to our current tree is.
 * This will be implemented by updating an array of tuples, one for
 * each node, containing the weight of the transition and the parent
 * it would connect to.
 * Upon adding a point the table will be updated to consider the
 * children of the new point which was added.
 * 
 * The tree will be stored as an array of linked lists.
 * The edges used will be stored in an array, and the
 * table of possible edges an array of tuples.
 * The current working tree will be stored in an array
 * of booleans.
 *
 * Assumptions: 
 *
 * Data will be provided in standard
 * input using the following form:
 * n (number of nodes)
 * start# weight# end# (representing an edge in the graph)
 *
 * This algorithm assumes a connected undirected graph. 
 * Error checking for this condition is handled.
 * Other erroneous input not handled.
 */

#include <cstdlib>
#include <list>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
  int weight;
  int target;
};

void getInput(list<node>*&,int&);
void printGraph(list<node>*,int);
void mst(list<node>*,int);

int main(){
  //cout << "hello world\n";
  list<node>* graph;
  int count;
  getInput(graph,count);
  //printGraph(graph,count);
  mst(graph,count);
  //cout << "MST Completed.\n";
}

/* 
 * This function grabs formatted input as
 * stated in assumptions in order to form
 * a graph in the format list<node> array
 */
void getInput(list<node>*& ret, int& count){
  //cout << "Input count.\n";
  cin >> count;
  ret = new list<node>[count];
  //cout << "Input tree.\n";
  string line;
  int addressX; //because the input is undirected
  int addressY; //we create x and y nodes to insert
  node x;       //on reciprocal nodes
  node y;
  while(true){  //this loop will read untill eof
      cin >> addressX;
      y.target = addressX;
      cin >> x.target;
      addressY = x.target;
      cin >> x.weight;
      y.weight = x.weight;
      if(cin.eof()){
        break;}
      ret[addressX-1].push_front(x);
      ret[addressY-1].push_front(y);
      //cout << "Node added. \n";
  }
  //cout << "Graph Creation Complete\n";
  //printGraph(ret,count);
  return;
}

/*iterative graph printing function for debugging.*/
void printGraph(list<node>* graph,int size){
  for(int i = 0; i < size; i++){
    cout << "Edges from " << i+1 << endl;
    for (list<node>::const_iterator iterator = graph[i].begin(), 
      end = graph[i].end(); iterator != end; ++iterator) {
        cout << iterator->weight << " " << iterator->target << endl;
	}
    cout << endl;
  }
}

/* Calculates and prints mst */
void mst(list<node>* graph, int size){
  //cout << "Starting MST\n";
  int mstCounter = 0;
  int parent = 0;
  bool mySet[size];		//contains the set of included points
  node lightEdge[size];		//contains the lighetest transition to
  				//the index point
  int totalWeight=0;		//contains the weight of all selected edges
  pair<int,int> mst[size-1];	//contains the selected edges
  for(int i = 0; i < size; i++){ /* Initialize to blank */
    mySet[i] = false;
    lightEdge[i].weight = 99999999; //very large int
    lightEdge[i].target = 0;  //0 is not a valid node
  }
  mySet[0] = true;		//first point selected
  int next = 1;			//start at first point
  while(true){
    for (list<node>::const_iterator iterator = graph[next-1].begin(),
    end = graph[next-1].end(); iterator != end; ++iterator) {	//iterate through edges from the point
      if(iterator->weight < lightEdge[iterator->target-1].weight){ //if the new edge is lighter
        //cout << "Replacing Edge\n";	//replace the edge
        lightEdge[iterator->target-1].weight = iterator->weight;
	lightEdge[iterator->target-1].target = next; //target represents the parent in this case
      }
    }
    node min;  //node to hold the lightest node of the bunch
    min.weight = 99999999; //arbitrarily large int
    min.target = 0;  //0 is a flagging target
    for (int i=0; i<size; i++){
      //cout << "Tick\n";
      if(mySet[i]) //if we already have the point, continue on.
        continue;
      if(min.weight > lightEdge[i].weight){ //in the light edge
        //cout << "Tock\n";
        min.weight = lightEdge[i].weight;
	min.target = i+1;
	parent = lightEdge[i].target;};		//find the lightest
    }
    //cout << "Min Target: " <<min.target<<" of weight  "<<min.weight << endl;
    if(min.target == 0) //exit condition
    {
      for(int i=0; i<size; i++){ //if all nodes aren't touched, not a connected tree
        if(!mySet[i]){
	  cout << "ERROR: Unsolvable Graph -- Disconnected?\n";
	  return;}
      }
      cout << totalWeight << endl; //prints total weight
      for(int i=0; i<size-1; i++){ //Sort appropriately
        /*
	 * Sorting Rules:
	 * Lower number first in the pair,
	 * Sort from low to high by first.
	 * Tie break by printing the lower of the second.
	 */
	if(mst[i].first>mst[i].second){
          swap(mst[i].first,mst[i].second);
	}
      }
      sort(mst,mst+sizeof mst / sizeof *mst);
      for(int i=0; i<size-1; i++){ //Prints out edges
        cout << mst[i].first << " " << mst[i].second << endl;
      }
      return;
    }//Processes data:
    totalWeight += min.weight;	//Increments weight 
    mst[mstCounter].first = min.target;	//Sets pair into MST
    mst[mstCounter].second = parent;	//Sets pair into MST
    mstCounter++;		//Increments counter
    next = min.target;	//sets the next node to address
    mySet[min.target-1] = true;	//Sets the node as included
  }
}
