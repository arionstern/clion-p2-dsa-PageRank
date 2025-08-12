
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include "AdjacencyList.h"

using namespace std;

// Adds an edge from "from" to "to"
void AdjacencyList::addEdge(const string& from, const string& to) {
    outgoingEdges[from].push_back(to);
    incomingEdges[to].push_back(from);
    allPages.insert(from);
    allPages.insert(to);
}

// Calculates and returns PageRank result as string
string AdjacencyList::PageRank(int power_iterations) {
    string result;
    map<string, double> ranks;
    int N = allPages.size();
    double initial_rank = 1.0 / N;

    //Initialize all ranks to 1/N
    for (const string& page : allPages) {
        ranks[page] = initial_rank;
    }

    //Power Iteration Algorithm
    for (int iter = 1; iter < power_iterations; ++iter) {
        map<string, double> newRanks;

        for (const string& page : allPages) {
            double sum = 0.0;
            for (const string& in : incomingEdges[page]) {
                int outdeg = outgoingEdges[in].size();
                if (outdeg > 0) {
                    sum += ranks[in] / outdeg;
                }
            }
            newRanks[page] = sum;
        }

        ranks = newRanks;
    }

    // Step 3: Sort output alphabetically
    ostringstream out;
    out << fixed << showpoint << setprecision(2);
    vector<string> sortedPages(allPages.begin(), allPages.end());
    sort(sortedPages.begin(), sortedPages.end());

    for (const string& page : sortedPages) {
        out << page << " " << ranks[page] << "\n";
    }

    result = out.str();
    cout << result; // For printing
    return result; // For testing
}





