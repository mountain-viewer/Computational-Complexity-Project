//
//  Graph.hpp
//  3Coloring
//
//  Created by whoami on 11/22/17.
//  Copyright © 2017 Mountain Viewer. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Graph {
public:
    // Constructors
    Graph();
    Graph(int size);
    
    // Destructor
    ~Graph();
    
    // Basic methods
    int getSize();
    void setSize(int size);
    void addEdge(int a, int b);
    void addEdge(pair<int, int> e);
    
    // Main methods
    vector<int>& getEdgesOfVertex(int i);
    void updateThreeColoringSets();
    bool getCanThreeColoring();
    int getMinimumDegreeVertex(vector<int> &used);
    void dfs(int vertex, vector<int> &used, bool &can, int colour);
    void maximalIndependentSets(vector<int> &used);
    void updateThreeColoringFullBust();
    void paint(vector<int> &used, int number);
    
    // Print methods
    void printVector(vector<int> &used);
    void printAnswer();
    void printGraph();
    
private:
    int size;
    vector<vector<int>> edges;
    bool canThreeColoring;
    vector <int> colour;
};


#endif /* Graph_hpp */
