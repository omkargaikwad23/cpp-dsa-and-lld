/*
Roll no: 31126
Graph coloring using M(3) colors
time: O(N^M);
space: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

class Graph{
    int N;
    vector<int> *g;
public:
    Graph(int N){
        this->N = N;
        g = new vector<int>[N];
    }
    
    void addEdge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool isPossible(int node, vector<int> &color, int col){
        for(auto adj : g[node]){
            if(adj!=node && color[adj]==col){
                return false;
            }
        }
        return true;
    }

    bool solve(int node, vector<int> &color, int M){
        if(node == N) return true;

        for(int i=1; i<=M; i++){
            if(isPossible(node, color, i)){
                color[node] = i;
                if(solve(node+1, color, M)) return true;
                color[node] = 0; // erase color
            }
        }
    }

    vector<int> colourTheGraph(int M){
        // no colors initally assigned 
        vector<int> color(N, 0);

        if(solve(0, color, M)) 
            return color;

        return {};
    }
};

int main(){
    int N = 4, M = 3;
    Graph g(N);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(0, 2);
    g.addEdge(0, 3);

    vector<int> colouring = g.colourTheGraph(M);

    if(colouring.size() == 0){
        cout << "Graph cannot be coloured using M colors";
    }else{
        cout << "Coloring is possible\n";
        for(int i=0; i<N; i++){
            cout << "Node " << i << " gets " << " colour " << colouring[i] << endl;
        }
    }
}

/*
OUTPUT:
Coloring is possible
Node 0 gets  colour 1
Node 1 gets  colour 2
Node 2 gets  colour 3
Node 3 gets  colour 2
*/