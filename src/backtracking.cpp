#include "Graph.h"
#include <iostream>
#include <chrono>

using namespace std;

int main (int argc, char* argv[]) {
  auto start = chrono::high_resolution_clock::now();
  string inputFile = argv[1];
  Graph g(inputFile);
  g.printColors(g.backtrackingColoring());
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Time: " << duration.count() << " ms" << endl;
  return 0;
}