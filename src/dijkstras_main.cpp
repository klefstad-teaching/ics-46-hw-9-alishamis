#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <graph_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    Graph G;

    try {
        file_to_graph(filename, G);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        std::vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}

