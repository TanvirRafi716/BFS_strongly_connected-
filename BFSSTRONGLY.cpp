#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);

        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// Function to perform BFS traversal on the graph
void BFS(Graph const &graph, int v, vector<bool> &visited)
{
    queue<int> q;
    q.push(v);
    visited[v] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int w : graph.adjList[u]) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

// Function to check if the graph is strongly connected
bool isStronglyConnected(Graph const &graph, int n)
{
    // Check for connectivity from the first node
    vector<bool> visited(n, false);
    BFS(graph, 0, visited);

    // If any node is unreachable, return false
    if (find(visited.begin(), visited.end(), false) != visited.end())
        return false;

    // Reset visited for the reverse graph
    fill(visited.begin(), visited.end(), false);

    // Check for connectivity from every node to the first node
    BFS(graph, 0, visited);
    if (find(visited.begin(), visited.end(), false) != visited.end())
        return false;

    return true;
}

int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 4}, {1, 0}, {1, 2}, {2, 1}, {2, 4},
        {3, 1}, {3, 2}, {4, 3}
    };

    // total number of nodes in the graph
    int n = 5;

    // build a graph from the given edges
    Graph graph(edges, n);

    // check if the graph is strongly connected
    if (isStronglyConnected(graph, n)) {
        cout << "The graph is strongly connected";
    }
    else {
        cout << "The graph is not strongly connected";
    }

    return 0;
}

