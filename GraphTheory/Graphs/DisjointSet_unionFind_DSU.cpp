#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Time Complexity: O(4 * α) ~ O(1)
struct DSU {
    vector<int> parent;
    vector<int> rank;
    vector<ll> size;
    int n;

    DSU(int _n) {
        n = _n;
        parent.assign(n + 1, 0);
        rank.assign(n + 1, 0);
        size.assign(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; // Each node starts as its own component
        }
    }

    int findParent(int node) {
        if (parent[node] == node) return node;
        return parent[node] = findParent(parent[node]); // Path compression
    }

    void merge(int u, int v) {
        u = findParent(u);
        v = findParent(v);
        if (u == v) return; // Already in the same component

        // Union by rank
        if (rank[u] < rank[v]) { 
            swap(u, v); 
        }
        parent[v] = u; // Attach v under u by setting parent[v] = u
        size[u] += size[v]; // Update the size of the new root

        if (rank[u] == rank[v]) {
            rank[u]++;
        }
    }

    // Function to get the size of a component
    int getSize(int node) {
        return size[findParent(node)];
    }
};

int main() {
    DSU ds(1000);
    ds.merge(1, 2);
    ds.merge(2, 3);
    ds.merge(3, 4);
    ds.merge(5, 6);

    int parentA = ds.findParent(1);
    int parentB = ds.findParent(6);

    if (parentA == parentB) {
        cout << "In same component\n";
    } else {
        cout << "In different component\n";
    }

    cout << "Size of component containing node 1: " << ds.getSize(1) << "\n";
    cout << "Size of component containing node 5: " << ds.getSize(5) << "\n";

    return 0;
}


/*
    **Union by Rank Explanation**
    
    - In Disjoint Set Union (DSU), the `rank` of a node represents an 
      approximation of the height of the tree rooted at that node.
      
    - When merging two components (trees), we want to attach the **smaller**
      tree under the **larger** tree to keep the overall structure balanced.

    **Why do we check and swap ranks before merging?**
    - If `rank[u] < rank[v]`, it means the tree rooted at `u` is **shorter** than
      the tree rooted at `v`.
    - Swapping ensures that `u` is always the **larger** tree.
    - This prevents unnecessary growth in tree height and improves efficiency.

    **Example:**
    
       Initially:
          1       5
         / \     /
        2   3   6
       
       `rank[1] = 2`, `rank[5] = 1`
       
       If we merge `3` and `6`, we find:
          `findParent(3) = 1`
          `findParent(6) = 5`
       
       Since `rank[1] > rank[5]`, we **do not swap** and merge as:
       
          1
         /|\
        2 3 5
            |
            6

    **What if we don't swap?**
    - If we mistakenly attach a taller tree under a shorter one, it increases 
      the depth, making `findParent()` operations slower.

    **Key Takeaways:**
    ✅ Rank ≈ Height of Tree  
    ✅ Swapping ensures smaller trees attach under larger ones  
    ✅ Prevents unnecessary increase in tree height  
    ✅ Keeps DSU operations efficient (`O(α(n))`)
*/
