/*
================================================================================
                FILE SYSTEM SIZE (Google Interview)
================================================================================

PROBLEM:
Given a file system represented as a dictionary/tree structure.
Each node is either a FILE (has size) or DIRECTORY (has children).

Implement get_size(key) that returns total size for a given key.

================================================================================
                         EXAMPLES
================================================================================

File System:
{
  1: { type="directory", name="root", children=[2, 3] },
  2: { type="directory", name="dir", children=[4, 5] },
  4: { type="file", name="file1", size=100 },
  5: { type="file", name="file2", size=200 },
  3: { type="file", name="file3", size=300 }
}

get_size(1) → 600 (100 + 200 + 300)
get_size(2) → 300 (100 + 200)
get_size(4) → 100

================================================================================
                         APPROACH
================================================================================

BASIC: DFS to sum sizes recursively
OPTIMIZED: Cache results for repeated queries

TIME:  O(n) for single query, O(1) with caching for repeated
SPACE: O(n) for cache + O(h) for recursion stack

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class FileSystem {
private:
    struct Node {
        string type;  // "file" or "directory"
        string name;
        int size;     // Only for files
        vector<int> children;  // Only for directories
    };
    
    unordered_map<int, Node> fs;
    unordered_map<int, int> sizeCache;  // Cache for optimized queries
    
public:
    void addFile(int id, string name, int size) {
        fs[id] = {"file", name, size, {}};
    }
    
    void addDirectory(int id, string name, vector<int> children) {
        fs[id] = {"directory", name, 0, children};
    }
    
    // Basic DFS approach
    int getSize(int key) {
        if (fs.find(key) == fs.end()) return 0;
        
        Node& node = fs[key];
        
        if (node.type == "file") {
            return node.size;
        }
        
        // Directory: sum of all children
        int totalSize = 0;
        for (int child : node.children) {
            totalSize += getSize(child);
        }
        
        return totalSize;
    }
    
    // Optimized with caching
    int getSizeWithCache(int key) {
        if (fs.find(key) == fs.end()) return 0;
        
        // Check cache first
        if (sizeCache.count(key)) {
            return sizeCache[key];
        }
        
        Node& node = fs[key];
        
        if (node.type == "file") {
            sizeCache[key] = node.size;
            return node.size;
        }
        
        int totalSize = 0;
        for (int child : node.children) {
            totalSize += getSizeWithCache(child);
        }
        
        sizeCache[key] = totalSize;
        return totalSize;
    }
    
    // Invalidate cache when file system changes
    void invalidateCache(int key) {
        sizeCache.clear();  // Simple approach: clear all
        // Better approach: only invalidate ancestors
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    FileSystem fs;
    
    // Build the file system
    fs.addDirectory(1, "root", {2, 3});
    fs.addDirectory(2, "dir", {4, 5});
    fs.addFile(4, "file1", 100);
    fs.addFile(5, "file2", 200);
    fs.addFile(3, "file3", 300);
    
    cout << "File System Structure:\n";
    cout << "root (1)\n";
    cout << "├── dir (2)\n";
    cout << "│   ├── file1 (4): 100 bytes\n";
    cout << "│   └── file2 (5): 200 bytes\n";
    cout << "└── file3 (3): 300 bytes\n\n";
    
    cout << "Size queries:\n";
    cout << "getSize(1) = " << fs.getSize(1) << " (expected: 600)\n";
    cout << "getSize(2) = " << fs.getSize(2) << " (expected: 300)\n";
    cout << "getSize(4) = " << fs.getSize(4) << " (expected: 100)\n";
    cout << "getSize(3) = " << fs.getSize(3) << " (expected: 300)\n";
    
    return 0;
}

/*
================================================================================
                         DISCUSSION POINTS
================================================================================

FILE SYSTEM INVARIANTS:
1. No cycles: a directory cannot include itself directly or indirectly
2. Every file belongs to at least one directory
3. No two directories share the same child
4. No directory contains a non-existent child key

FOLLOW-UP QUESTIONS:
1. How to handle cache invalidation efficiently?
   → Track parent pointers, invalidate from changed node to root
   
2. What if we need to support adding/deleting files?
   → Invalidate cache, update parent sizes incrementally
   
3. What if file system is very large?
   → Lazy loading, pagination, or database-backed storage

4. Concurrent access?
   → Read-write locks, or use atomic operations for cache

================================================================================
*/

