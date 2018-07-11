#ifndef GRAPHM_H
#define GRAPHM_H
//----------------------------------------------------------------------------
// File: graphm.h
// 
// Description: Function outlines for the GraphM class
// 
// Programmer:	Anthony Waddell
// 
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015, g++
//-----------------------------------------------------------------------------
#include "nodedata.h"
#include <algorithm>
#include <iomanip>
#include <limits.h>
#include <string>

const int MAXNODES = 101;

using namespace std;
class GraphM 
{
	// Struct to keep the shortest distance and associated path info
	struct TableType
	{
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};

public:
	 
	// Constructor
	GraphM();

	// Build graph from file
	void buildGraph(ifstream &sin);

	// Insert and remove edges of graph
	bool insertEdge(int source, int destination, int weight);	
	bool removeEdge(int source, int destination);

	// Find shortest path and helper functions
	void findShortestPath();
	void fill_List();
	int find_V(int source);

	// Display functions and helper functions
	void displayAll();											
	void display(int source, int destination);
	string path(int source, int destination);
	void get_Names(string path);

private:

	NodeData data[MAXNODES];              // data for graph nodes 
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path. 
};
#endif