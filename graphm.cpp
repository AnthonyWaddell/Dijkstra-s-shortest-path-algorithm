//-----------------------------------------------------------------------------
// File:		graphm.cpp
// Programmer:	Anthony Waddell
// Resources:	For findShortestPath
//					https://en.wikipedia.org/wiki/Johnson%27s_algorithm
//					http://www.coderslexicon.com/dijkstras-algorithm-for-c/
//-----------------------------------------------------------------------------
#include "graphm.h"

//-----------------------------------------------------------------------------
// Function:	GraphM::GraphM()
// Title:		Constructor
// Description: Constructs an empty Graph object, fills cost adjacency matrix
//					with max values, node adjacency matrix with max values, 
//					and sets all nodes visited to false. Assumes maximum of 
//					100 nodes
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		N/A
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
GraphM::GraphM()
{
	// Assume max array of 100 values with index 0 not being used
	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			// Instantiate all values with infinity and set all visited to false
			C[i][j] = INT_MAX;
			T[i][j].dist = INT_MAX;
			T[i][j].path = INT_MAX;
			T[i][j].visited = false;
		}
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::buildGraph(ifstream & sin)
// Title:		Build graph from file
// Description: Reads data in from file and uses it to build a graph of
//					vertices and edges with associated weights. Stops when
//					file reads values 0 0 
//
// Programmer:	Anthony Waddell
//
// Parameters:	ifstream & sin; reference to input stream/file
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::buildGraph(ifstream & sin)
{

	unsigned int source = 0;
	unsigned int destination = 0;
	unsigned int weight = 0;
	int exit_value = 0;
	string nodeName;
	string s_size;

	// Get number of nodes in the graph and run to next line
	sin >> size;
	getline(sin, s_size);

	// Read in and build array of vertex names
	for (int i = 1; i <= size; i++)
	{
		getline(sin, nodeName);
		NodeData *temp = new NodeData(nodeName);
		data[i] = *temp;
		delete temp;
	}

	// Fill adjacency matrix with associated costs
	while (sin >> source >> destination >> weight)
	{
		// Only fill values if not terminating sequence
		if (source != exit_value || destination != exit_value)
		{
			C[source][destination] = weight;
		}
		// If terminating sequence, leave
		else
		{
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Function:	bool GraphM::insertEdge(int source, int destination, int weight)
// Title:		Inserts an edge
// Description: Inserts an edge between two vertices with supplied weight
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; the source vertice
//				int destination; the destination vertice
//				int weight; the associated weight of the edge
// Returns:		bool; true if edge inserted, false if not
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
bool GraphM::insertEdge(int source, int destination, int weight)
{
	bool inserted = false;

	// If either vertice is out of bounds, or trying to insert source to source
	// with weight greater than 0 do not insert
	if (source < 1 || destination < 1 || source > size || destination > size 
		|| weight < 0 || (source = destination && weight != 0))
	{
		return inserted;
	}
	// Else, insert edge and weight
	else
	{
		C[source][destination] = weight;
		inserted = true;
		return inserted;
	}
}

//-----------------------------------------------------------------------------
// Function:	bool GraphM::removeEdge(int source, int destination)
// Title:		Removes an edge
// Description: Removes an edge between two vertices
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; the source vertice
//				int destination; the destination vertice
// Returns:		bool; true if edge removed, false if not
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
bool GraphM::removeEdge(int source, int destination)
{
	bool removed = false;

	// If either vertice is out of bounds or removing source to source
	if (source < 1 || destination < 1 || source > size || destination > size 
		|| source == destination)
	{
		return removed;
	}
	// Else, remove edge by setting value to infinity in cost matrix
	else
	{
		C[source][destination] = INT_MAX;
		removed = true;
		return removed;
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::findShortestPath()
// Title:		Finds the shortest path
// Description: Finds shortest  available path between all nodes to all other
//					nodes
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/12/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	int v = 0;

	// Populate array of structs with available paths and weights
	fill_List();

	// For all nodes to all other nodes
	for (int source = 1; source <= size; source++)
	{
		// Mark distance from source to source as 0 and begin by visiting node
		T[source][source].dist = 0;
		T[source][source].visited = true;

		// Begin looking for lowest weights among neighboring vertice
		do 
		{
			// Find next lowest cost vertex, if none exists, break
			if (!(v = find_V(source)))
			{
				break;
			}
			// If next lowest cost found, mark visited
			else
			{
				T[source][v].visited = true;
			}
			// For all nodes adjacent to v
			for (int w = 1; w <= size; ++w)
			{
				// If they haven't been visited yet and are an actual path
				if (T[source][w].visited || C[v][w] == INT_MAX)
				{
					continue;
				}
				// If cost of getting to this node is less than cost of source
				// to vertex + cost of vertex to this node
				int swapped = T[source][w].dist;
				T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);
				if (swapped != T[source][w].dist)
				{
					T[source][w].path = v;
				}
			}
		}
		// While there are neighbor vertex to look at
		while (v);
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::fill_List()
// Title:		Populates adjacency list
// Description: Populates adjacency list with known values for path's between
//					nodes and their associated weights
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/11/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::fill_List()
{
	for (int source = 1; source <= size; source++)
	{
		// Populate the adjacency list with relevant neighbor nodes and their
		// associated weights
		for (int i = 1; i <= size; i++)
		{

			if (C[source][i] != INT_MAX)
			{
				T[source][i].dist = C[source][i];
				T[source][i].path = source;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Function:	int GraphM::find_V(int source)
// Title:		Finds adjacent vertex with lowest cost
// Description: Looks at all adjacent nodes to array index node represented by
//					source. Returns lowest cost adjacent vertex represented by 
//					array index value. 
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; array index of the source node
// Returns:		int next_vertice; the next vertice to visit
// History Log: 02/13/18 AW Completed Function
//-----------------------------------------------------------------------------
int GraphM::find_V(int source)
{
	int next_vertice = 0;
	int minimum = INT_MAX;
	for (int i = 1; i <= size; i++)
	{
		// If it hasn't been visited and has least cost begining with infinity
		if (!T[source][i].visited && (C[source][i] < minimum))
		{
			minimum = C[source][i];
			next_vertice = i;
		}
	}
	// Return the next lowest cost vertice
	return next_vertice;
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::displayAll()
// Title:		Displays shortest paths
// Description: Displays shortest paths beween all nodes, if path exists
//
// Programmer:	Anthony Waddell
//
// Parameters:	N/A
// Returns:		void
// History Log: 02/12/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::displayAll()
{
	string s_path = "";
	string false_path = "----";
	
	// Display formatting
	cout << "Description" << setw(18) << "From node" << setw(10) << "To node"
		<< setw(13) << "Djikstra's" << setw(9) << "Path" << endl;
	for (int i = 1; i <= size; i++)
	{
		// Display the current source node
		cout << data[i] << endl;
		for (int j = 1; j <= size; j++)
		{
			// Do not display path from same *this node to *this node
			if (i != j)
			{
				// If valid path, display the source and destination indices
				cout << setw(25) << i << setw(10) << j;
				if (T[i][j].dist != INT_MAX)
				{
					// If if valid path, display the asociated cost
					cout << setw(10) << T[i][j].dist;
					s_path = path(i, j);
				}
				else
				{
					// If no path exists
					cout << setw(10) << false_path;
				}
				cout << endl;
			}
		}
		cout << endl;
	}
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::display(int source, int destination)
// Title:		Display the lowest cost and path from one node to another
// Description: Recursively finds the lowest cost path from one source node
//					to destination node if path exists
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; array index of the source node
//				int destination; the array index of the destination node
// Returns:		void
// History Log: 02/13/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::display(int source, int destination)
{
	string path_values = "";
	string false_path = "----";
	
	// If source or destination is out of bounds or is from *this node to 
	// *this node
	if (source < 1 || destination < 1 || source > size || destination > size 
		|| source == destination)
	{
		// Display invalid path
		cout << setw(5) << source << setw(10) << destination << setw(10) << 
			false_path << endl;
	}
	// If source and destination are both in bounds
	else
	{
		// Display the valid nodes indices
		cout << setw(5) << source << setw(10) << destination;
		{
			if (T[source][destination].dist != INT_MAX)
			{
				// If path exists, display weight and get the path
				cout << setw(10) << T[source][destination].dist;
				path_values = path(source, destination);
				cout << endl;
				get_Names(path_values);
			}
			else
			{
				// Otherwise display invalid path
				cout << setw(10) << false_path << endl;
			}
		}
	}
	cout << endl;
}

//-----------------------------------------------------------------------------
// Function:	void GraphM::path(int source, int destination)
// Title:		Recursively finds path
// Description: Recursively finds the lowest cost path from one source node
//					to destination node if path exists
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; array index of the source node
//				int destination; the array index of the destination node
// Returns:		void
// History Log: 02/13/18 AW Completed Function
//-----------------------------------------------------------------------------
string GraphM::path(int source, int destination)
{
	string temp = "";

	// If this was valid path
	if (T[source][destination].dist != INT_MAX)
	{
		// If somewhere along path, not at source
		if (source != destination)
		{
			// Recurse back through path until at source
			int m_path = destination;
			destination = T[source][destination].path;
			temp = path(source, destination);
			// Display path and track path
			cout <<  " " << m_path;
			temp.append(to_string(m_path));
		}
		// Base case, when back at source
		else
		{
			// Display source and track path
			cout << "\t\t " << source;
			temp.append(to_string(source));
			return temp;
		}
	}
	// If ivalid path
	else
	{
		return temp;
	}
	return temp;
}


//-----------------------------------------------------------------------------
// Function:	void GraphM::get_Names(int source, int destination)
// Title:		Prints out names of nodes
// Description: Given source and destination node values represented as array
//					indices, displays the node data of each node visited
//					in the shortest path between source and destination
//
// Programmer:	Anthony Waddell
//
// Parameters:	int source; array index of the source node
//				int destination; array index of the destination node
// Returns:		void
// History Log: 02/13/18 AW Completed Function
//-----------------------------------------------------------------------------
void GraphM::get_Names(string path)
{
	char c;
	char ascii_offset = '0';

	// Get names of vertices from path
	for (int i = 0; i < path.length(); i++)
	{
		c = path[i];
		// Convert from char to int and display the corresponding node name
		int index = c - ascii_offset;
		if (isdigit(c))
		{
			cout << data[index] << endl;
		}
	}
}