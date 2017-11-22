//
//  main.cpp
//  3Coloring
//
//  Created by whoami on 11/22/17.
//  Copyright © 2017 Mountain Viewer. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Graph.hpp"

using namespace std;

void readInputData(Graph &graph) {
    int n, m, a, b;
    cin >> n >> m;
    graph.setSize(n);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph.addEdge(a, b);
    }
}

void solveTask() {
    Graph graph;
    readInputData(graph);
    graph.updateThreeColoringSets();
    cout << graph.getCanThreeColoring() << endl;
    if (graph.getCanThreeColoring()) {
        graph.printAnswer();
    }
}

void testThreeColoringCorrect() {
    int times = 100;
    int N = 8;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back(make_pair(i, j));
        }
    }
    bool checkSets, checkFullBust;
    for (int i = 0; i < times; ++i) {
        Graph graph(N);
        int numberOfEdges = rand()%(edges.size());
        random_shuffle(edges.begin(), edges.end());
        for (int j = 0; j < numberOfEdges; ++j) {
            graph.addEdge(edges[j]);
        }
        graph.updateThreeColoringSets();
        checkSets = graph.getCanThreeColoring();
        graph.updateThreeColoringFullBust();
        checkFullBust = graph.getCanThreeColoring();
        if (checkSets != checkFullBust) {
            cout << "ERROR" << "\n";
            exit(0);
        }
    }
    cout << "Correct is ok" << "\n";
}

void testThreeColoringTimer() {
    int N = 30;
    int times = 10;
    vector < pair <int, int> > edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.push_back(make_pair(i, j));
        }
    }
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    for (int i = 0; i < times; ++i) {
        Graph graph(N);
        int numberOfEdges = rand()%(edges.size());
        random_shuffle(edges.begin(), edges.end());
        for (int j = 0; j < numberOfEdges; ++j) {
            graph.addEdge(edges[j]);
        }
        graph.updateThreeColoringSets();
    }
    
    end = std::chrono::system_clock::now();
    cout << "Time for " << times << " times and " << N << " vertices : ";
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
}

int main(int argc, const char * argv[]) {
    testThreeColoringCorrect();
    testThreeColoringTimer();
    solveTask();
    return 0;
}
