//
//  Graph.cpp
//  3Coloring
//
//  Created by whoami on 11/22/17.
//  Copyright © 2017 Mountain Viewer. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"

using namespace std;

Graph::Graph() { }

Graph::Graph(int size) {
    this->size = size;
    edges.resize(size);
}

Graph::~Graph() {
    for (int i = 0; i < size; ++i) {
        edges[i].clear();
    }
    edges.clear();
}

int Graph::getSize() {
    return size;
}

void Graph::setSize(int size) {
    this->size = size;
    edges.resize(size);
}

void Graph::addEdge(int a, int b) {
    --a; --b;
    edges[a].push_back(b);
    edges[b].push_back(a);
}

void Graph::addEdge(pair<int, int> e) {
    int a = e.first - 1;
    int b = e.second - 1;
    edges[a].push_back(b);
    edges[b].push_back(a);
}

vector<int>& Graph::getEdgesOfVertex(int i) {
    return edges[i];
}

void Graph::updateThreeColoringSets() {
    canThreeColoring = false;
    vector <int> used;
    used.resize(size);
    for (int i = 0; i < size; ++i) {
        used[i] = -1;
    }
    maximalIndependentSets(used);
}

bool Graph::getCanThreeColoring() {
    return canThreeColoring;
}

int Graph::getMinimumDegreeVertex(vector<int> &used) {
    int numberOfVertex = -1, numberOfNeighbors = -1, cnt;
    for (int i = 0; i < size; ++i) {
        if (used[i] == -1) {
            cnt = 0;
            for (auto element : edges[i]) {
                if (used[element] == -1) {
                    cnt++;
                }
            }
            if (cnt > numberOfNeighbors) {
                numberOfVertex = i;
                numberOfNeighbors = cnt;
            }
        }
    }
    return numberOfVertex;
}

void Graph::dfs(int vertex, vector<int> &used, bool &can, int colour) {
    used[vertex] = colour;
    for (auto element : edges[vertex]) {
        if (used[element] == colour) {
            can = false;
        }
        if (used[element] == 0) {
            dfs(element, used, can, 5 - colour);
        }
    }
}

void Graph::maximalIndependentSets(vector<int> &used) {
    int numberOfVertex = getMinimumDegreeVertex(used);
    if (numberOfVertex == -1) {
        bool can = true;
        for (int i = 0; i < size; ++i) {
            if (used[i] == 0) {
                dfs(i, used, can, 2);
            }
        }
        if (can) {
            canThreeColoring = true;
            colour.resize(size);
            for (int i = 0; i < size; ++i) {
                colour[i] = used[i];
            }
        }
        for (int i = 0; i < size; ++i) {
            if (used[i] != 1) {
                used[i] = 0;
            }
        }
    } else {
        vector<int> neigborsElement;
        neigborsElement.push_back(numberOfVertex);
        for (auto element : edges[numberOfVertex]) {
            if (used[element] == -1) {
                neigborsElement.push_back(element);
            }
        }
        for (auto element : neigborsElement) {
            vector <int> neigborsVertex;
            neigborsVertex.push_back(element);
            for (auto vertex : edges[element]) {
                if (used[vertex] == -1) {
                    neigborsVertex.push_back(vertex);
                }
            }
            for (auto paintable : neigborsVertex) {
                used[paintable] = (paintable == element) ? 1 : 0;
            }
            maximalIndependentSets(used);
            for (auto paintable : neigborsVertex) {
                used[paintable] = -1;
            }
        }
    }
}

void Graph::updateThreeColoringFullBust() {
    canThreeColoring = false;
    vector <int> used;
    used.resize(size);
    paint(used, 0);
}

void Graph::paint(vector<int> &used, int number) {
    if (number == size) {
        bool can = true;
        for (int i = 0; i < size; ++i) {
            for (auto to : edges[i]) {
                if (used[i] == used[to]) {
                    can = false;
                }
            }
        }
        if (can) {
            canThreeColoring = true;
        }
    } else {
        for (int colour = 1; colour <= 3; ++colour) {
            used[number] = colour;
            paint(used, number + 1);
        }
    }
}

void Graph::printVector(vector<int> &used) {
    for (auto colour : used) {
        cout << colour << " ";
    }
    cout << "\n";
}

void Graph::printAnswer() {
    if (!canThreeColoring) {
        return;
    }
    
    for (auto x : colour) {
        cout << x << " ";
    }
    cout << "\n";
}






