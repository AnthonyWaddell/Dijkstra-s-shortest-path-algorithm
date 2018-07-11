//-----------------------------------------------------------------------------
// File:		graphl.cpp
// Programmer:	Anthony Waddell
// Resources:	N/A
//-----------------------------------------------------------------------------
#include "graphl.h"

//-----------------------------------------------------------------------------
// Function:	GraphL::GraphL()
// Title:		Constructor
// Description: Constructs a graph, setting all node data values to NULL, all
//					edgeheads to NULL, and all nodes visited to false. Assumes
//					maximum of 100 nodes
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
GraphL::GraphL()
{
	// Set all pointers to NULL and visited to false, assumes 100 nodes max
	for (int i = 1; i < MAX_NODES; i++)
	{
		spanning_Graph[i].data = NULL;
		spanning_Graph[i].edgeHead = NULL;
		spanning_Graph[i].visited = false;
	}
}

//-----------------------------------------------------------------------------
// Function:	GraphL::~GraphL()
// Title:		Destructor
// Description: Destructor for GraphL class. Deletes all EdgeNode's of every
//					data node and then deletes the data nodes themselves
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
GraphL::~GraphL()
{
	// For each node
	for (int i = 1; i <= size; i++)
	{
		if (spanning_Graph[i].edgeHead != NULL)
		{
			// While there are nodes after edgehead, remove them
			while (spanning_Graph[i].edgeHead->nextEdge != NULL)
			{
				EdgeNode *temp = spanning_Graph[i].edgeHead;
				spanning_Graph[i].edgeHead = temp->nextEdge;
				delete temp;
				temp = NULL;
			}
			// Remove edgehead
			delete spanning_Graph[i].edgeHead;
			spanning_Graph[i].edgeHead = NULL;
		}
		// Remove node
		delete spanning_Graph[i].data;
		spanning_Graph[i].data = NULL;
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphL::buildGraph(ifstream & sin)
// Title:		Builds a GraphL object
// Description: Reads data in from file and uses it to build a graph of
//					vertices and edges. Stops when file reads values 0 0 
//
// Programmer:	Anthony Waddell
//
// Parameters:	ifstream & sin; reference to the input stream/file
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphL::buildGraph(ifstream & sin)
{
	string nodeName;  
	string s_size;
	int source; 
	int destination;
	int exit_value = 0;

	// Get number of nodes and move to next line
	sin >> size;
	getline(sin, s_size);

	// Assign node names to each node
	for (int i = 1; i <= size; ++i)
	{
		getline(sin, nodeName);
		NodeData* tmp = new NodeData(nodeName);
		spanning_Graph[i].data = tmp;
	}

	// While there is data to read in
	while (sin >> source >> destination)
	{
		// If actual data, not terminating values
		if (source != exit_value || destination != exit_value)
		{
			EdgeNode *temp = new EdgeNode;
			temp->adjGraphNode = destination;
			// If it's not the first adjacent node
			if (spanning_Graph[source].edgeHead != NULL)
			{
				temp->nextEdge = spanning_Graph[source].edgeHead;
				spanning_Graph[source].edgeHead = temp;
			}
			// If first adjacent node
			else
			{
				temp->nextEdge = NULL;
				spanning_Graph[source].edgeHead = temp;
			}
		}
		// If terminating values
		else
		{
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphL::displayGraph()
// Title:		Displays graph 
// Description: Displays graph data of each node and all edge nodes connected
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphL::displayGraph()
{
	// Display formatting
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "\t\t" << *spanning_Graph[i].data << endl;
		// If there are adjacent nodes
		if (spanning_Graph[i].edgeHead != NULL)
		{
			EdgeNode *temp = spanning_Graph[i].edgeHead;
			// If there are *multiple* adjacent nodes
			while (temp != NULL)
			{
				cout << setw(6) << "edge" << setw(3) << i << setw(3) << temp->adjGraphNode << endl;
				temp = temp->nextEdge;
			}
		}
	}
	cout << endl;
}

//-----------------------------------------------------------------------------
// Function:	void GraphL::depthFirstSearch()
// Title:		Initiates a depth first search of a GraphL object
// Description: Calls helper function to perform depth first dearch on a GraphL
//					object beginning from the first node
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	// Begin from the first node index
	int start = 1;
	cout << "Depth-first ordering: ";
	depthFirstSearch_Helper(start);
	cout << endl << endl;
}

//-----------------------------------------------------------------------------
// Function:	void GraphL::depthFirstSearch_Helper(int node)
// Title:		Helper function for depth first search
// Description: Recursively performs a depth first search beginning from the
//					first node. Displays results to cout
//
// Programmer:	Anthony Waddell
//
// Parameters:	int node; the node currently being traversed
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphL::depthFirstSearch_Helper(int node)
{
	// Mark this node as visited, display the visting order number
	spanning_Graph[node].visited = true;
	cout << setw(3) << node;
	EdgeNode *temp = spanning_Graph[node].edgeHead;
	while (temp != NULL)
	{
		// If there are adjacent nodes after edgehead, try to visit them
		if (spanning_Graph[temp->adjGraphNode].visited != true)
		{
			depthFirstSearch_Helper(temp->adjGraphNode);
		}
		temp = temp->nextEdge;
	}
}