/*
================================================================================
                FAMILY NEXT BIRTHDAY (Google Interview)
================================================================================

PROBLEM:
Given a tree of family members with their date of birth (month, day).
Implement a function that returns the name of the member whose birthday
is NEXT from a given date. The sequence should be circular (wraps around year).

================================================================================
                         EXAMPLES
================================================================================

Family Tree:
- Alice (Jan 15)
  ├── Daisy (Jan 1)
  └── Bob (Feb 3)
      └── Charlie (Dec 1)

Query: Next birthday on/after Jan 20 → Bob (Feb 3)
Query: Next birthday on/after Dec 10 → Daisy (Jan 1, wrap-around)
Query: Next birthday on/after Jan 1  → Daisy (Jan 1, includes today)

================================================================================
                         APPROACH
================================================================================

PREPROCESSING:
1. DFS to collect all (dayOfYear, name) pairs
2. Sort by dayOfYear

QUERY:
1. Convert query date to dayOfYear
2. Binary search for first birthday >= query
3. If not found, wrap to first birthday in list

TIME:  O(n log n) preprocessing, O(log n) per query
SPACE: O(n) for birthday list

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct Member {
    string name;
    int month, day;
    vector<Member*> children;
    
    Member(string n, int m, int d) : name(n), month(m), day(d) {}
};

class BirthdayLookup {
private:
    vector<pair<int, string>> birthdays;  // (dayOfYear, name)
    
    // Days before each month (1-indexed, non-leap year)
    vector<int> prefix = {0,
        0, 31, 59, 90, 120, 151,
        181, 212, 243, 273, 304, 334
    };
    
    int toDayOfYear(int month, int day) {
        return prefix[month] + day;
    }
    
    void dfs(Member* root) {
        if (!root) return;
        
        int dayOfYear = toDayOfYear(root->month, root->day);
        birthdays.push_back({dayOfYear, root->name});
        
        for (Member* child : root->children) {
            dfs(child);
        }
    }
    
public:
    BirthdayLookup(Member* root) {
        dfs(root);
        sort(birthdays.begin(), birthdays.end());
    }
    
    string nextBirthday(int queryMonth, int queryDay) {
        if (birthdays.empty()) return "";
        
        int queryDayOfYear = toDayOfYear(queryMonth, queryDay);
        
        // Binary search for first birthday >= query
        auto it = lower_bound(birthdays.begin(), birthdays.end(), 
                              queryDayOfYear,
                              [](const pair<int, string>& p, int val) {
                                  return p.first < val;
                              });
        
        // If not found, wrap around to first birthday
        if (it == birthdays.end()) {
            return birthdays[0].second;
        }
        
        return it->second;
    }
    
    // Get all birthdays in order (for debugging)
    void printAllBirthdays() {
        for (auto& [day, name] : birthdays) {
            cout << name << " (day " << day << ")\n";
        }
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Build family tree
    Member* root = new Member("Alice", 1, 15);      // Jan 15
    Member* daisy = new Member("Daisy", 1, 1);      // Jan 1
    Member* bob = new Member("Bob", 2, 3);          // Feb 3
    Member* charlie = new Member("Charlie", 12, 1); // Dec 1
    
    root->children.push_back(daisy);
    root->children.push_back(bob);
    bob->children.push_back(charlie);
    
    // Build lookup
    BirthdayLookup bl(root);
    
    cout << "=== Family Birthdays (sorted) ===\n";
    bl.printAllBirthdays();
    cout << "\n";
    
    // Queries
    cout << "=== Queries ===\n";
    cout << "Next after Jan 20: " << bl.nextBirthday(1, 20) << " (expected: Bob)\n";
    cout << "Next after Dec 10: " << bl.nextBirthday(12, 10) << " (expected: Daisy)\n";
    cout << "Next after Jan 1:  " << bl.nextBirthday(1, 1) << " (expected: Daisy)\n";
    cout << "Next after Jan 15: " << bl.nextBirthday(1, 15) << " (expected: Alice)\n";
    cout << "Next after Feb 5:  " << bl.nextBirthday(2, 5) << " (expected: Charlie)\n";
    
    // Clean up
    delete charlie;
    delete bob;
    delete daisy;
    delete root;
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

PREPROCESSING:
- DFS traversal: O(n)
- Sorting: O(n log n)

QUERY:
- Binary search: O(log n)

SPACE: O(n) for birthday list

FOLLOW-UP QUESTIONS:
1. Handle leap years? → Adjust prefix array, or use library
2. What if multiple people share same birthday? → Return all or first alphabetically
3. What if we need K next birthdays? → Return iterator range from binary search

================================================================================
*/

