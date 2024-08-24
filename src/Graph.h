#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

struct VertexInfo {
  int sat;
  int deg;
  int vertex;

  VertexInfo (int sat, int deg, int vertex) : sat(sat), deg(deg), vertex(vertex) {}
};

struct CompareVertex {
  bool operator() (const VertexInfo& a, const VertexInfo& b) const {
    if (a.sat != b.sat) {
      return a.sat < b.sat;
    } else if (a.deg != b.deg) {
      return a.deg < b.deg;
    } else {
      return a.vertex > b.vertex;
    }
  }
};

class Graph {
  private:
    int V;
    vector<vector<int>> adj;

    bool loadGraph (const string& filename);
    bool backtrackingColoringUtil (int m, vector<int>& c, int v);
    bool isSafe (int v, vector<int>& c, int color);

  public:
    Graph (int V);
    Graph (const string& filename);
    ~Graph ();
    void addEdge (int u, int v);
    vector<int> backtrackingColoring ();
    vector<int> dsaturColoring ();
    void printColors (vector<int>) const;
};

#endif