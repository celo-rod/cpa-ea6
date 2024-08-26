#include "Graph.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

Graph::Graph (int V) {
  this->V = V;
  adj.resize(V, vector<int>());
}

Graph::Graph (const string& filename) {
  loadGraph(filename);
}

Graph::~Graph () {
  adj.clear();
}

void Graph::addEdge (int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

bool Graph::loadGraph (const string& filename) {
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Error: File not found" << endl;
    return false;
  }

  file >> V;
  if (file.fail()) {
    cerr << "Error: Number of vertices not found" << endl;
    return false;
  }

  adj.resize(V, vector<int>());

  int u, v;
  while (file >> u >> v) {
    if ((u >= 0 && u < V) && (v >= 0 && v < V)) {
      addEdge(u, v);
    } else {
      cerr << "Error: Vertex out of bounds" << endl;
      return false;
    }
  }

  if (file.bad()) {
    cerr << "Error: File read error" << endl;
    return false;
  }

  file.close();
  return true;
}

bool Graph::isSafe (int v, vector<int>& c, int color) {
  // Check if the color is already assigned to an adjacent vertex
  for (int i =0; i < adj[v].size(); i++) {
    if (c[adj[v][i]] == color) {
      return false;
    }
  }

  return true;
}

bool Graph::backtrackingColoringUtil(int m, vector<int>&c, int v){
  // Base case: If all vertices are assigned a color
  if (v == V) {
    return true;
  }

  // Try all colors
  for (int color = 0; color < m; color++) {
    if (isSafe(v, c, color)) {
      c[v] = color;
      if (backtrackingColoringUtil(m, c, v + 1)) {
        return true;
      }
      c[v] = -1;
    }
  }

  return false;
}

vector<int> Graph::backtrackingColoring () {
  vector<int> c(V, -1);
  int m = 1;

  while (!backtrackingColoringUtil(m, c, 0)) {
    m++;
  }

  return c;
}

vector<int> Graph::dsaturColoring () {
  int u;
  vector<int> c(V, -1);
  vector<set<int>> adjColors(V);
  set<VertexInfo, CompareVertex> pq;
  set<VertexInfo, CompareVertex>::iterator maxSatVertex;

  // Initialize priority queue
  for (int i = 0; i < V; i++) {
    adjColors[i] = set<int>();
    pq.emplace(VertexInfo(0, adj[i].size(), i));
  }

  while (!pq.empty()) {
    maxSatVertex = pq.begin();
    u = maxSatVertex->vertex;
    pq.erase(maxSatVertex);

    // Assign the min possible color to u
    set<int> usedColors;
    for (int v : adj[u]) {
      if (c[v] != -1) {
        usedColors.insert(c[v]);
      }
    }

    int color = 0;
    while (usedColors.find(color) != usedColors.end()) {
      color++;
    }
    c[u] = color;

    // Update saturation degree and priority queue
    for (int v : adj[u]) {
      if (c[v] == -1) {
        pq.erase(VertexInfo(adjColors[v].size(), adj[v].size(), v));
        adjColors[v].insert(color);
        pq.emplace(VertexInfo(adjColors[v].size(), adj[v].size(), v));
      }
    }
  }

  return c;
}

void Graph::printColors (vector<int> c) const {
  for (int i = 0; i < V; i++) {
    cout << "Vertex " << i << "-> Color " << c[i] << endl;
  }
  cout << "k colors: " << *max_element(c.begin(), c.end()) + 1 << endl;
}