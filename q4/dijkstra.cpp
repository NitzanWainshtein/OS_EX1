#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Function to construct adjacency list from edge list.
// Returns: adj[u] = list of {v, weight}, for each neighbor v of u.
vector<vector<vector<int>>> constructAdj(vector<vector<int>> &edges, int V) {
    vector<vector<vector<int>>> adj(V);

    for (const auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        // Dijkstra's algorithm does not support negative weights
        if (wt < 0) {
            cerr << "Error: Dijkstra does not support negative weights.\n";
            exit(1);
        }

        // Validate that vertex indices are within valid range
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cerr << "Error: Invalid vertex index in edge.\n";
            exit(1);
        }

        // Since the graph is undirected, add both directions
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    return adj;
}

// Function to perform Dijkstra's shortest path algorithm
// Returns a vector of shortest distances from src to all vertices
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
    vector<vector<vector<int>>> adj = constructAdj(edges, V);

    // Distance array initialized with infinity
    vector<int> dist(V, INT_MAX);

    // Min-heap priority queue storing {distance, vertex}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    // Start from source node
    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top()[1];
        pq.pop();

        // Visit all neighbors of u
        for (auto x : adj[u]) {
            int v = x[0];
            int weight = x[1];

            // If shorter path to v through u is found
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    // Print welcome message and input format instructions
    cout << "\n Welcome to the Dijkstra program." << endl;
    cout << "Input example:" << endl;
    cout << "  First line: number of vertices V and number of edges E" << endl;
    cout << "  Next E lines: each line contains edge in the format: u v w" << endl;
    cout << "  Last line: source vertex" << endl;
    cout << "Example input:" << endl;
    cout << "  5 6\n 0 1 2\n 1 2 3\n 0 2 6\n 1 3 1\n 3 4 5\n 2 4 2\n 0" << endl << endl;

    for (;;) {
        int V, E;
        cout << "Enter number of vertices and edges (or Ctrl+D to exit):\n";
        if (!(cin >> V >> E)) break;

        // Validate graph size
        if (V <= 0 || E < 0) {
            cerr << "Error: Invalid number of vertices or edges.\n";
            continue;
        }

        vector<vector<int>> edges;
        cout << "Enter edges (u v w) each in separate line:\n";
        for (int i = 0; i < E; ++i) {
            int u, v, w;
            if (!(cin >> u >> v >> w)) {
                cerr << "Error: Invalid edge input.\n";
                return 1;
            }
            // Edge will be validated again inside constructAdj
            edges.push_back({u, v, w});
        }

        int src;
        cout << "Enter source vertex:\n";
        if (!(cin >> src) || src < 0 || src >= V) {
            cerr << "Error: Invalid source vertex.\n";
            return 1;
        }

        vector<int> result = dijkstra(V, edges, src);

        cout << "Shortest distances from vertex " << src << ":\n";
        for (int dist : result) {
            if (dist == INT_MAX)
                cout << "INF ";
            else
                cout << dist << " ";
        }
        cout << endl << endl;
    }

    return 0;
}
