/*---------------------------------------*/
/*         Algorithms - Project 1        */
/*  Implementing Minimum Spanning Tree   */
/*          Kruskal's Algorithm          */
/*       Date Completed: 11/22/2016      */
/*---------------------------------------*/
/*
 * Name: Benjamin Cooper
 * Purpose: To implement Kruskal's MST algorithm in C++
 * Method: 
 * 
 * First standard input will be parsed in order to form a graph.
 * Each of the points will be seperated in a disjoint set.
 * Then the array of edges will be sorted and iterated through.
 * If the edge connects two disjointed sets, take it and merge
 * the two sets. Add the edge to the array of edges, and print
 * it afer there is only one set.
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
#include <queue>
#include <algorithm>

using namespace std;

struct node {
  int weight;
  int target;
};

struct edge {
  int weight;
  int t1, t2;
};

struct LessThanByWeight
{
  bool operator()(const edge& lhs, const edge& rhs) const
  {
    return lhs.weight > rhs.weight;
  }
};

void getInput(list<node>*&,int&,priority_queue<edge, vector<edge>, LessThanByWeight>&);
void printGraph(list<node>*,int);
void mst(list<node>*,int,priority_queue<edge, vector<edge>, LessThanByWeight>);

int main(){
  //cout << "hello world\n";
  priority_queue<edge, vector<edge>, LessThanByWeight> pq;
  list<node>* graph;
  int count;
  getInput(graph,count,pq);
  //printGraph(graph,count);
  mst(graph,count,pq);
  //cout << "MST Completed.\n";
}

/* 
 * This function grabs formatted input as
 * stated in assumptions in order to form
 * a graph in the format list<node> array
 */
void getInput(list<node>*& ret, int& count,priority_queue<edge, vector<edge>, LessThanByWeight>& pq){
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
      edge e;
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
      e.weight = x.weight;
      e.t1 = addressX;
      e.t2 = addressY;
      //cout << "Node added. \n";
      pq.push(e); //pushes the edge to the priority queue

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
void mst(list<node>* graph, int size,priority_queue<edge, vector<edge>, LessThanByWeight> pq){
  /*rudimentary disjointed set, could be optimized with a better disjointed set.*/
  /* 
   * This method:
   * Array of sets each node is located in, initially 1:count
   * Upon merge the lower number is taken.
   */
  int groups[size]; //contains the group numbers for each node
  for(int i=0; i<size; i++){ /*group initialization*/
    groups[i] = i+1;
  }
  int totalWeight = 0; //tracks total weight
  int edgeCount = 0;   //counter for the mst edges
  int minGroup = 0;    //holds minimum group number
  int maxGroup = 0;    //holds maximum group number
  pair<int,int> edges[size-1];  //contains the edges for the mst
  while(!pq.empty())  //loops until the number of edges is empty
  {
    if(groups[pq.top().t1-1] != groups[pq.top().t2-1])  //if they are in seperate groups...
    {
      totalWeight += pq.top().weight;	//include this edge
      edges[edgeCount].first = pq.top().t1;
      edges[edgeCount].second = pq.top().t2;
      edgeCount++;
      if(groups[pq.top().t1-1] < groups[pq.top().t2-1]) //calculate group number
      {
        minGroup = groups[pq.top().t1-1];
	maxGroup = groups[pq.top().t2-1];
      }
      else
      {
        minGroup = groups[pq.top().t2-1];
	maxGroup = groups[pq.top().t1-1];
      };
      for(int i=0; i<size; i++)	//assign group number as needed
      {
        if(groups[i] == maxGroup)
	  groups[i] = minGroup;
      }
    }
    pq.pop();	//remove this edge from the priority queue
  }
  for(int i=0; i<size; i++){	//verify that the MST was formed
    if(groups[i] != 1)
    {
      cout << "ERROR: Could not find MST -- Disconnected?\n";
      return;
    };
  };
  cout << totalWeight << "\n";   //output the total weight
  /* 
   * Sort the MST nodes appropriately
   * 
   * Sorting Rules:
   * Lower number first in the pair,
   * Sort from low to high by first.
   * Tie break by printing the lower of the second.
   */
  for(int i=0; i<size-1; i++){
    if(edges[i].first>edges[i].second){
      swap(edges[i].first,edges[i].second);
    }
  }
  sort(edges,edges+sizeof edges / sizeof *edges);
  for(int i=0; i<size-1; i++){ //Print the nodes
    cout << edges[i].first << " " << edges[i].second << '\n';
  }
  return;  //return
}
