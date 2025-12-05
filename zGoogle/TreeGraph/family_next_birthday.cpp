#include <bits/stdc++.h>
using namespace std;

/*
Given a tree of family members and their Date of birth. We have to come up with data structure or fuction which should output the name of member whose birthday is next from given date, the sequence should be circular.


   Tree node representing a family member.
   Each member has:
   - name
   - date of birth (month, day)
   - children (tree structure)
*/
struct Member {
    string name;
    int month, day;
    vector<Member*> children;

    Member(string n, int m, int d) : name(n), month(m), day(d) {}
};

class BirthdayLookup {
private:
    vector<pair<int, string>> birthdays; // (dayOfYear, name)

    // Days before each month (non-leap year) (1-indexed months)
    vector<int> prefix = {0,
        0, 31, 59, 90, 120, 151,
        181, 212, 243, 273, 304, 334
    };

    // Convert (month, day) → day number in year (1–365)
    int toDayOfYear(int month, int day) {
        return prefix[month] + day;
    }

    // DFS traversal of the tree to collect birthdays
    void dfs(Member* root) {
        if (!root) return;

        int dayOfYear = toDayOfYear(root->month, root->day);
        birthdays.push_back({dayOfYear, root->name});

        for (Member* child : root->children)
            dfs(child);
    }

public:
    // Build lookup structure
    BirthdayLookup(Member* root) {
        dfs(root);
        sort(birthdays.begin(), birthdays.end());  // sort by dayOfYear
    }

    // Query: Get the next birthday on or after a given date
    string nextBirthday(int currMonth, int currDay) {
        if (birthdays.empty()) return "";  // Handle empty tree
        
        int current = toDayOfYear(currMonth, currDay);

        // Binary search for first birthday >= current day (use lower_bound)
        auto it = lower_bound(birthdays.begin(), birthdays.end(), current,
                              [](const auto& p, int val) {
                                  return p.first < val;
                              });

        if (it == birthdays.end()) return birthdays[0].second; // wrap-around
        return it->second;
    }
};


//// ------------------ DEMO USAGE ------------------ ////

int main() {
    // Build a small sample family tree for demonstration.
    Member* root = new Member("Alice", 1, 15);
    Member* child1 = new Member("Bob", 2, 3);
    Member* child2 = new Member("Charlie", 12, 1);
    Member* child3 = new Member("Daisy", 1, 1);

    root->children.push_back(child3);
    root->children.push_back(child1);
    child1->children.push_back(child2);

    // Build the lookup system
    BirthdayLookup bl(root);

    // Query examples
    // Birthdays: Daisy(Jan 1), Alice(Jan 15), Bob(Feb 3), Charlie(Dec 1)
    
    cout << "Next birthday on/after Jan 20: "
         << bl.nextBirthday(1, 20) << "\n";  // → Bob (Feb 3)

    cout << "Next birthday on/after Dec 10: "
         << bl.nextBirthday(12, 10) << "\n"; // → Daisy (Jan 1, wrap-around)

    cout << "Next birthday on/after Jan 1: "
         << bl.nextBirthday(1, 1) << "\n";   // → Daisy (Jan 1, includes today!)
    
    cout << "Next birthday on/after Jan 15: "
         << bl.nextBirthday(1, 15) << "\n";  // → Alice (Jan 15, includes today!)

    return 0;
}
