/*
================================================================================
                    C++ STL ALGORITHMS - COMPLETE REFERENCE
================================================================================

The <algorithm> header provides many useful functions for manipulating 
sequences (arrays, vectors, strings, etc.)

Categories:
1. Sorting & Ordering
2. Searching
3. Counting
4. Min/Max
5. Modifying
6. Numeric (from <numeric>)
7. Set Operations
8. Permutations

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
using namespace std;

/*
================================================================================
                    1. SORTING & ORDERING
================================================================================
*/

void sortingAlgorithms() {
    cout << "=== Sorting & Ordering ===" << endl;
    
    // SORT - O(n log n)
    vector<int> v = {5, 2, 8, 1, 9};
    
    sort(v.begin(), v.end());                     // Ascending: 1 2 5 8 9
    sort(v.begin(), v.end(), greater<int>());     // Descending: 9 8 5 2 1
    
    // Custom comparator
    sort(v.begin(), v.end(), [](int a, int b) {
        return abs(a) < abs(b);  // Sort by absolute value
    });
    
    // Sort strings
    vector<string> words = {"apple", "Banana", "cherry"};
    sort(words.begin(), words.end());  // Case-sensitive: Banana apple cherry
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        return tolower(a[0]) < tolower(b[0]);  // Case-insensitive by first char
    });
    
    // PARTIAL_SORT - O(n log k) - Sort first k elements only
    vector<int> v2 = {5, 2, 8, 1, 9, 3, 7};
    partial_sort(v2.begin(), v2.begin() + 3, v2.end());
    // First 3 are sorted: 1 2 3 | rest unsorted: 8 9 5 7
    
    // NTH_ELEMENT - O(n) - Put nth element in correct position
    vector<int> v3 = {5, 2, 8, 1, 9, 3, 7};
    nth_element(v3.begin(), v3.begin() + 3, v3.end());
    // v3[3] is the 4th smallest, left elements are smaller, right are larger
    
    // STABLE_SORT - O(n log n) - Maintains relative order of equal elements
    stable_sort(v.begin(), v.end());
    
    // IS_SORTED - O(n)
    bool sorted = is_sorted(v.begin(), v.end());
    
    // REVERSE - O(n)
    reverse(v.begin(), v.end());
    
    // ROTATE - O(n) - Rotate left by k positions
    vector<int> v4 = {1, 2, 3, 4, 5};
    rotate(v4.begin(), v4.begin() + 2, v4.end());  // 3 4 5 1 2
    
    // SHUFFLE - O(n)
    random_device rd;
    mt19937 gen(rd());
    shuffle(v.begin(), v.end(), gen);
}


/*
================================================================================
                    2. SEARCHING
================================================================================
*/

void searchingAlgorithms() {
    cout << "\n=== Searching ===" << endl;
    
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // FIND - O(n) - Returns iterator to first occurrence
    auto it = find(v.begin(), v.end(), 5);
    if (it != v.end()) {
        cout << "Found 5 at index: " << (it - v.begin()) << endl;
    }
    
    // FIND_IF - O(n) - Find first element satisfying condition
    auto it2 = find_if(v.begin(), v.end(), [](int x) { return x > 5; });
    // First element > 5
    
    // FIND_IF_NOT - O(n) - Find first element NOT satisfying condition
    auto it3 = find_if_not(v.begin(), v.end(), [](int x) { return x < 5; });
    
    // BINARY_SEARCH - O(log n) - Requires sorted container
    bool found = binary_search(v.begin(), v.end(), 5);  // true
    
    // LOWER_BOUND - O(log n) - First element >= value
    auto lb = lower_bound(v.begin(), v.end(), 5);  // Points to 5
    
    // UPPER_BOUND - O(log n) - First element > value
    auto ub = upper_bound(v.begin(), v.end(), 5);  // Points to 6
    
    // EQUAL_RANGE - O(log n) - Returns pair of lower_bound and upper_bound
    auto range = equal_range(v.begin(), v.end(), 5);
    // range.first = lower_bound, range.second = upper_bound
    
    // ALL_OF, ANY_OF, NONE_OF - O(n)
    bool allPositive = all_of(v.begin(), v.end(), [](int x) { return x > 0; });
    bool anyEven = any_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    bool noneNegative = none_of(v.begin(), v.end(), [](int x) { return x < 0; });
}


/*
================================================================================
                    3. COUNTING
================================================================================
*/

void countingAlgorithms() {
    cout << "\n=== Counting ===" << endl;
    
    vector<int> v = {1, 2, 2, 3, 2, 4, 2, 5};
    
    // COUNT - O(n) - Count occurrences of value
    int count2 = count(v.begin(), v.end(), 2);  // 4
    
    // COUNT_IF - O(n) - Count elements satisfying condition
    int countEven = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    
    cout << "Count of 2: " << count2 << endl;
    cout << "Count of evens: " << countEven << endl;
}


/*
================================================================================
                    4. MIN/MAX
================================================================================
*/

void minMaxAlgorithms() {
    cout << "\n=== Min/Max ===" << endl;
    
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // MIN/MAX - O(1) - Compare two values
    int minVal = min(3, 5);  // 3
    int maxVal = max(3, 5);  // 5
    
    // MIN/MAX with initializer list
    int minOfThree = min({3, 1, 4});  // 1
    int maxOfThree = max({3, 1, 4});  // 4
    
    // MINMAX - O(1) - Returns pair
    auto [lo, hi] = minmax(5, 3);  // lo=3, hi=5
    
    // MIN_ELEMENT/MAX_ELEMENT - O(n) - Returns iterator
    auto minIt = min_element(v.begin(), v.end());
    auto maxIt = max_element(v.begin(), v.end());
    
    cout << "Min: " << *minIt << " at index " << (minIt - v.begin()) << endl;
    cout << "Max: " << *maxIt << " at index " << (maxIt - v.begin()) << endl;
    
    // MINMAX_ELEMENT - O(n) - Returns pair of iterators
    auto [minIt2, maxIt2] = minmax_element(v.begin(), v.end());
    
    // CLAMP - O(1) - Clamp value to range [lo, hi]
    int clamped = clamp(10, 0, 5);  // 5 (clamped to max)
}


/*
================================================================================
                    5. MODIFYING ALGORITHMS
================================================================================
*/

void modifyingAlgorithms() {
    cout << "\n=== Modifying ===" << endl;
    
    // FILL - O(n)
    vector<int> v(5);
    fill(v.begin(), v.end(), 10);  // 10 10 10 10 10
    
    // FILL_N - O(n)
    fill_n(v.begin(), 3, 5);  // 5 5 5 10 10
    
    // GENERATE - O(n)
    int counter = 0;
    generate(v.begin(), v.end(), [&counter]() { return counter++; });
    // 0 1 2 3 4
    
    // IOTA - O(n) - Fill with incrementing values (from <numeric>)
    iota(v.begin(), v.end(), 1);  // 1 2 3 4 5
    
    // COPY - O(n)
    vector<int> dest(5);
    copy(v.begin(), v.end(), dest.begin());
    
    // COPY_IF - O(n)
    vector<int> evens;
    copy_if(v.begin(), v.end(), back_inserter(evens), 
            [](int x) { return x % 2 == 0; });
    
    // TRANSFORM - O(n)
    vector<int> doubled(5);
    transform(v.begin(), v.end(), doubled.begin(), [](int x) { return x * 2; });
    
    // REPLACE - O(n)
    replace(v.begin(), v.end(), 2, 20);  // Replace all 2s with 20
    
    // REPLACE_IF - O(n)
    replace_if(v.begin(), v.end(), [](int x) { return x < 0; }, 0);
    
    // REMOVE - O(n) - Moves elements, returns new end
    v = {1, 2, 3, 2, 4, 2, 5};
    auto newEnd = remove(v.begin(), v.end(), 2);
    v.erase(newEnd, v.end());  // Actually remove: 1 3 4 5
    
    // REMOVE_IF - O(n)
    v = {1, 2, 3, 4, 5, 6};
    newEnd = remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    v.erase(newEnd, v.end());  // 1 3 5
    
    // UNIQUE - O(n) - Remove adjacent duplicates (sort first for all duplicates)
    v = {1, 1, 2, 2, 2, 3, 3};
    newEnd = unique(v.begin(), v.end());
    v.erase(newEnd, v.end());  // 1 2 3
    
    // SWAP - O(1)
    int a = 5, b = 10;
    swap(a, b);  // a=10, b=5
    
    // SWAP_RANGES - O(n)
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {4, 5, 6};
    swap_ranges(v1.begin(), v1.end(), v2.begin());
}


/*
================================================================================
                    6. NUMERIC ALGORITHMS (<numeric>)
================================================================================
*/

void numericAlgorithms() {
    cout << "\n=== Numeric ===" << endl;
    
    vector<int> v = {1, 2, 3, 4, 5};
    
    // ACCUMULATE - O(n) - Sum (or fold)
    int sum = accumulate(v.begin(), v.end(), 0);  // 15
    
    // With custom operation (product)
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    
    // PARTIAL_SUM - O(n) - Prefix sums
    vector<int> prefix(5);
    partial_sum(v.begin(), v.end(), prefix.begin());  // 1 3 6 10 15
    
    // ADJACENT_DIFFERENCE - O(n) - Differences between adjacent
    vector<int> diff(5);
    adjacent_difference(v.begin(), v.end(), diff.begin());  // 1 1 1 1 1
    
    // INNER_PRODUCT - O(n) - Dot product
    vector<int> v2 = {2, 2, 2, 2, 2};
    int dotProduct = inner_product(v.begin(), v.end(), v2.begin(), 0);
    // 1*2 + 2*2 + 3*2 + 4*2 + 5*2 = 30
    
    // REDUCE (C++17) - Like accumulate but can be parallelized
    // int sum2 = reduce(v.begin(), v.end(), 0);
    
    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;
    cout << "Dot Product: " << dotProduct << endl;
}


/*
================================================================================
                    7. SET OPERATIONS (on sorted ranges)
================================================================================
*/

void setOperations() {
    cout << "\n=== Set Operations ===" << endl;
    
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {3, 4, 5, 6, 7};
    vector<int> result;
    
    // SET_UNION - Elements in either
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    // result: 1 2 3 4 5 6 7
    
    result.clear();
    
    // SET_INTERSECTION - Elements in both
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    // result: 3 4 5
    
    result.clear();
    
    // SET_DIFFERENCE - Elements in a but not b
    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    // result: 1 2
    
    result.clear();
    
    // SET_SYMMETRIC_DIFFERENCE - Elements in exactly one set
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    // result: 1 2 6 7
    
    // INCLUDES - Check if a contains all of b
    bool aContainsB = includes(a.begin(), a.end(), b.begin(), b.end());  // false
    
    // MERGE - Merge two sorted ranges
    result.clear();
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    // result: 1 2 3 3 4 4 5 5 6 7
}


/*
================================================================================
                    8. PERMUTATIONS
================================================================================
*/

void permutationAlgorithms() {
    cout << "\n=== Permutations ===" << endl;
    
    vector<int> v = {1, 2, 3};
    
    // NEXT_PERMUTATION - O(n) - Modifies to next lexicographic permutation
    cout << "All permutations of [1,2,3]:" << endl;
    do {
        for (int x : v) cout << x << " ";
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
    
    // PREV_PERMUTATION - O(n) - Previous permutation
    v = {3, 2, 1};
    prev_permutation(v.begin(), v.end());  // 3 1 2
    
    // IS_PERMUTATION - O(n²) - Check if one is permutation of another
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {3, 1, 2};
    bool isPerm = is_permutation(v1.begin(), v1.end(), v2.begin());  // true
}


// ============== MAIN ==============
int main() {
    sortingAlgorithms();
    searchingAlgorithms();
    countingAlgorithms();
    minMaxAlgorithms();
    modifyingAlgorithms();
    numericAlgorithms();
    setOperations();
    permutationAlgorithms();
    
    return 0;
}

/*
================================================================================
                          QUICK REFERENCE
================================================================================

SORTING:
  sort(begin, end)                    - O(n log n)
  partial_sort(begin, mid, end)       - O(n log k)
  nth_element(begin, nth, end)        - O(n)
  stable_sort(begin, end)             - O(n log n)

SEARCHING (sorted range):
  binary_search(begin, end, val)      - O(log n), returns bool
  lower_bound(begin, end, val)        - O(log n), first >= val
  upper_bound(begin, end, val)        - O(log n), first > val

SEARCHING (unsorted):
  find(begin, end, val)               - O(n)
  find_if(begin, end, pred)           - O(n)

COUNTING:
  count(begin, end, val)              - O(n)
  count_if(begin, end, pred)          - O(n)

MIN/MAX:
  min_element(begin, end)             - O(n)
  max_element(begin, end)             - O(n)
  minmax_element(begin, end)          - O(n)

MODIFYING:
  fill(begin, end, val)               - O(n)
  transform(begin, end, dest, func)   - O(n)
  replace(begin, end, old, new)       - O(n)
  remove(begin, end, val)             - O(n)
  unique(begin, end)                  - O(n)

NUMERIC:
  accumulate(begin, end, init)        - O(n)
  partial_sum(begin, end, dest)       - O(n)
  iota(begin, end, start)             - O(n)

================================================================================
*/

