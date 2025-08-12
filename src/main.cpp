#include <iostream>
#include <iomanip>  

#include "AdjacencyList.h"

using namespace std;

int main() {
    int no_of_lines, power_iterations;
    cin >> no_of_lines >> power_iterations;
    cin.ignore(); // ignore leftover newline

    AdjacencyList graph;

    // Read each edge (from and to) and add it to the graph
    for (int i = 0; i < no_of_lines; ++i) {
        string line;
        getline(cin, line);
        istringstream in(line);

        string from, to;
        in >> from >> to;

        // Add edge to AdjacencyList
        graph.addEdge(from, to);

    }

    // Calculate PageRank and print output
    graph.PageRank(power_iterations);

    return 0;
}

