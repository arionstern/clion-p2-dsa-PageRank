#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

class AdjacencyList {
private:
    unordered_map<string, vector<string>> outgoingEdges;
    unordered_map<string, vector<string>> incomingEdges;
    set<string> allPages;

public:
    void addEdge(const string& from, const string& to);
    string PageRank(int powerIterations);
};
