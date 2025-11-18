#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
 * VECTOR STL - Complete Reference
 * ===============================
 * 
 * Vector is a dynamic array that can resize itself automatically.
 * It provides random access, dynamic size, and efficient insertion/deletion at end.
 */

void printVector(const vector<int>& v, const string& name) {
    cout << name << ": ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    cout << "=== VECTOR METHODS DEMONSTRATION ===\n\n";
    
    // ============================================
    // 1. CONSTRUCTORS
    // ============================================
    cout << "1. CONSTRUCTORS:\n";
    
    vector<int> v1;                    // Empty vector
    vector<int> v2(5);                 // Vector of size 5 (all zeros)
    vector<int> v3(5, 10);             // Vector of size 5, all values 10
    vector<int> v4{1, 2, 3, 4, 5};     // Initializer list
    vector<int> v5(v4.begin(), v4.end()); // Copy from another vector
    
    printVector(v2, "v2 (size 5)");
    printVector(v3, "v3 (size 5, all 10)");
    printVector(v4, "v4 (initializer list)"); // v4 = {1, 2, 3, 4, 5}
    printVector(v5, "v5 (copy of v4)");
    cout << endl;
    
    // ============================================
    // 2. ELEMENT ACCESS
    // ============================================
    cout << "2. ELEMENT ACCESS:\n";
    
    vector<int> v{10, 20, 30, 40, 50};
    printVector(v, "v");
    
    cout << "  v[0] = " << v[0] << endl;              // Random access (no bounds check)
    cout << "  v.at(1) = " << v.at(1) << endl;         // Random access (with bounds check)
    cout << "  v.front() = " << v.front() << endl;     // First element
    cout << "  v.back() = " << v.back() << endl;       // Last element
    cout << "  v.data() = " << v.data() << " (pointer to internal array)" << endl;
    cout << "  *v.data() = " << *v.data() << " (first element via pointer)" << endl;
    cout << endl;
    
    // ============================================
    // 3. CAPACITY METHODS
    // ============================================
    cout << "3. CAPACITY METHODS:\n";
    
    vector<int> v6;
    cout << "  v6.empty() = " << (v6.empty() ? "true" : "false") << endl;
    cout << "  v6.size() = " << v6.size() << endl;
    cout << "  v6.capacity() = " << v6.capacity() << endl;
    cout << "  v6.max_size() = " << v6.max_size() << endl;
    
    v6.reserve(10);  // Reserve capacity for 10 elements
    cout << "  After reserve(10): capacity = " << v6.capacity() << endl; // capacity = 10
    
    v6.push_back(1);
    v6.push_back(2);
    v6.push_back(3);
    cout << "  After adding 3 elements: size = " << v6.size() << ", capacity = " << v6.capacity() << endl; // size = 3, capacity = 10
    
    v6.shrink_to_fit();  // Reduce capacity to fit size
    cout << "  After shrink_to_fit(): capacity = " << v6.capacity() << endl;
    cout << endl;
    
    // ============================================
    // 4. MODIFIERS - Adding Elements
    // ============================================
    cout << "4. MODIFIERS - Adding Elements:\n";
    
    vector<int> v7{1, 2, 3};
    printVector(v7, "v7 (initial)");
    
    v7.push_back(4);                    // Add element at end
    printVector(v7, "v7 (after push_back(4))"); // v7 = {1, 2, 3, 4}
    
    v7.emplace_back(5);                 // Construct element in place (C++11)
    printVector(v7, "v7 (after emplace_back(5))"); // v7 = {1, 2, 3, 4, 5}
    
    v7.insert(v7.begin() + 2, 99);     // Insert at position 2
    printVector(v7, "v7 (after insert at pos 2)"); // v7 = {1, 2, 99, 3, 4, 5}
    
    v7.insert(v7.end(), 3, 100);       // Insert 3 copies of 100 at end
    printVector(v7, "v7 (after insert 3 copies of 100)"); // v7 = {1, 2, 99, 3, 4, 5, 100, 100, 100}
    
    vector<int> temp{200, 300};
    v7.insert(v7.begin() + 1, temp.begin(), temp.end());  // Insert range
    printVector(v7, "v7 (after insert range)");
    cout << endl;
    
    // ============================================
    // 5. MODIFIERS - Removing Elements
    // ============================================
    cout << "5. MODIFIERS - Removing Elements:\n";
    
    vector<int> v8{10, 20, 30, 40, 50, 60};
    printVector(v8, "v8 (initial)");
    
    v8.pop_back();                      // Remove last element
    printVector(v8, "v8 (after pop_back())");
    
    v8.erase(v8.begin() + 1);           // Erase element at position 1
    printVector(v8, "v8 (after erase at pos 1)");
    
    v8.erase(v8.begin() + 1, v8.begin() + 3);  // Erase range [1, 3)
    printVector(v8, "v8 (after erase range [1,3))");
    
    v8.clear();                         // Remove all elements
    cout << "  v8.size() after clear() = " << v8.size() << endl;
    cout << endl;
    
    // ============================================
    // 6. ASSIGNMENT METHODS
    // ============================================
    cout << "6. ASSIGNMENT METHODS:\n";
    
    vector<int> v9{1, 2, 3};
    vector<int> v10{100, 200, 300, 400};
    
    printVector(v9, "v9 (before assign)");
    v9.assign(5, 10);                   // Assign 5 copies of 10
    printVector(v9, "v9 (after assign(5, 10))");
    
    v9.assign(v10.begin(), v10.end() - 1);  // Assign from range
    printVector(v9, "v9 (after assign from v10 range)");
    
    v9 = v10;                           // Copy assignment
    printVector(v9, "v9 (after v9 = v10)");
    cout << endl;
    
    // ============================================
    // 7. ITERATORS
    // ============================================
    cout << "7. ITERATORS:\n";
    
    vector<int> v11{10, 20, 30, 40, 50};
    
    // Forward iteration
    cout << "  Forward: ";
    for (vector<int>::iterator it = v11.begin(); it != v11.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Reverse iteration
    cout << "  Reverse: ";
    for (vector<int>::reverse_iterator it = v11.rbegin(); it != v11.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Const iterators
    cout << "  Const forward: ";
    for (vector<int>::const_iterator it = v11.cbegin(); it != v11.cend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Range-based for loop (C++11)
    cout << "  Range-based: ";
    for (int x : v11) {
        cout << x << " ";
    }
    cout << endl;
    cout << endl;
    
    // ============================================
    // 8. SWAP METHOD
    // ============================================
    cout << "8. SWAP METHOD:\n";
    
    vector<int> v12{1, 2, 3};
    vector<int> v13{100, 200};
    
    printVector(v12, "v12 (before swap)");
    printVector(v13, "v13 (before swap)");
    
    v12.swap(v13);
    
    printVector(v12, "v12 (after swap)");
    printVector(v13, "v13 (after swap)");
    cout << endl;
    
    // ============================================
    // 9. USEFUL ALGORITHMS WITH VECTORS
    // ============================================
    cout << "9. USEFUL ALGORITHMS:\n";
    
    vector<int> v14{30, 10, 50, 20, 40};
    printVector(v14, "v14");
    
    cout << "  min_element: " << *min_element(v14.begin(), v14.end()) << endl;
    cout << "  max_element: " << *max_element(v14.begin(), v14.end()) << endl;
    cout << "  accumulate (sum): " << accumulate(v14.begin(), v14.end(), 0) << endl;
    
    sort(v14.begin(), v14.end());
    printVector(v14, "v14 (after sort)");
    
    reverse(v14.begin(), v14.end());
    printVector(v14, "v14 (after reverse)");
    
    cout << "  find(30): " << (find(v14.begin(), v14.end(), 30) != v14.end() ? "Found" : "Not found") << endl;
    cout << "  count(20): " << count(v14.begin(), v14.end(), 20) << endl;
    cout << endl;
    
    // ============================================
    // 10. 2D VECTOR
    // ============================================
    cout << "10. 2D VECTOR:\n";
    
    vector<vector<int>> v2d(3, vector<int>(4, 0));  // 3x4 matrix filled with 0
    v2d[0][0] = 1;
    v2d[1][1] = 2;
    v2d[2][2] = 3;
    
    cout << "  2D Vector (3x4):\n";
    for (int i = 0; i < 3; i++) {
        cout << "    ";
        for (int j = 0; j < 4; j++) {
            cout << v2d[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}