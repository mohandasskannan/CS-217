#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    
    // Read and Output File Info
    
    string filename;
    cout << "Enter the name of the file to read: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    int numVertices;
    if (!(file >> numVertices)) {
        cerr << "Error reading the number of vertices." << endl;
        return 1;
    }

    vector<pair<char, char>> edges;
    string edge;
    // Read the edges from the file
    while (file >> edge) {
        if (edge.length() == 2) {
            edges.push_back({ edge[0], edge[1] });
        }
    }
    file.close();

    
    cout << "Edges in the graph:" << endl;
    for (size_t i = 0; i < edges.size(); ++i) {
        cout << edges[i].first << edges[i].second << endl;
    }

    cout << "Number of vertices: " << numVertices << endl;
    cout << "Number of edges: " << edges.size() << endl;


    cout << endl;


    // Adjacency Matrix
    
    // Initialize an N x N matrix with 0s
    vector<vector<int>> adjMatrix(numVertices, vector<int>(numVertices, 0));

    // Populate the matrix for an undirected graph
    for (size_t i = 0; i < edges.size(); ++i) {
        int u = edges[i].first - 'A';
        int v = edges[i].second - 'A';

        // Ensure indices are within bounds
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1; // Undirected means the edge goes both ways
        }
    }

    cout << "Adjacency matrix of the graph:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }



    cout << endl;


    // Breadth-First Search
    
    cout << "Breadth-first search on the graph:" << endl;

    vector<bool> visited(numVertices, false);
    queue<int> q;

    // Start BFS at vertex 'A' (index 0)
    int startVertex = 0;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();


        for (int i = 0; i < numVertices; ++i) {
            // If there is an edge and the neighbor hasn't been visited
            if (adjMatrix[curr][i] == 1 && !visited[i]) {
                visited[i] = true;     
                q.push(i);             // Add to queue for future exploration

                // Print the edge showing the traversal path
                cout << (char)(curr + 'A') << (char)(i + 'A') << endl;
            }
        }
    }

    return 0;
}