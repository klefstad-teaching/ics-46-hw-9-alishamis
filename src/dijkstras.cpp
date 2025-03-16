#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> dists(G.numVertices, INF);
    previous.assign(G.numVertices, -1);
    dists[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > dists[u]) continue;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (dists[u] + weight < dists[v]) {
                dists[v] = dists[u] + weight;
                previous[v] = u;
                pq.push({dists[v], v});
            }
        }
    }

    return dists;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    if (distances[destination] == INF)
        return path;

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    return path;
}


void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}

