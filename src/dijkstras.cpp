#include "dijkstras.h"
#include <algorithm>

// Function to implement Dijkstra's algorithm
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF); // Initialize distances to infinity
    previous.resize(G.numVertices, -1);        // Initialize previous nodes to -1
    distances[source] = 0;                     // Distance to source is 0

    // Min-heap priority queue: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;  // Current vertex
        int dist_u = pq.top().first; // Distance to current vertex
        pq.pop();

        if (dist_u > distances[u]) continue; // Skip outdated entries

        // Relax edges from vertex u
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }

    return distances;
}

// Extract the shortest path from source to destination using the 'previous' vector
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "\nTotal cost is " << total << "\n";
        return;
    }
    
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
