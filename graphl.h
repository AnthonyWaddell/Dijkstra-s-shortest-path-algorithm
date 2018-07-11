#ifndef GRAPHL_H
#define GRAPHL_H
//----------------------------------------------------------------------------
// File: graphl.h
// 
// Description: Function outlines for the GraphL class
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

using namespace std;
const int MAX_NODES = 101;

class GraphL
{

public:
	// Constructor and destructor
	GraphL();	
	~ GraphL();

	// Build graph from file
	void buildGraph(ifstream &sin);

	// Dsiplay graph to console
	void displayGraph();

	// DFS and helper function
	void depthFirstSearch();
	void depthFirstSearch_Helper(int node);
	
private:
	
	struct EdgeNode;		// forward reference for the compiler
	struct GraphNode 
	{		
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};

	struct EdgeNode 
	{
		int adjGraphNode;	// subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

	// Graph and size property for number of nodes
	GraphNode spanning_Graph[MAX_NODES];
	int size; 
};
#endif