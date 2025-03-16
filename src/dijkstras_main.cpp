#include "dijkstras.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <graph_file> <source> <destination>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int source = std::stoi(argv[2]);
    int destination = std::stoi(argv[3]);
    Graph G;

    try {
        file_to_graph(filename, G);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, source, previous);
    std::vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);

    return 0;
}
