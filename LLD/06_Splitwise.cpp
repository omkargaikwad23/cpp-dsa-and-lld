/*
================================================================================
                    LOW-LEVEL DESIGN: SPLITWISE (EXPENSE SHARING)
================================================================================

PROBLEM:
  Design an expense sharing application where users can add expenses,
  split costs in different ways, and simplify debts.

REQUIREMENTS:
  1. Add users to the system
  2. Add expenses with different split strategies:
     - EQUAL: Split equally among all participants
     - EXACT: Specify exact amount for each participant
     - PERCENT: Specify percentage for each participant
  3. Track balances between every pair of users
  4. Show individual user balances (who owes whom)
  5. Simplify debts (minimize number of transactions)

DESIGN PATTERNS:
  - Strategy Pattern: Different split strategies (Equal, Exact, Percent)
  - Graph-based debt simplification: Net balances + greedy matching

CLASSES:
  User           - id, name, email, phone
  Split          - base class for split logic
  EqualSplit     - divides equally
  ExactSplit     - user-specified amounts
  PercentSplit   - percentage-based
  Expense        - paid by, amount, splits, description
  ExpenseManager - add expenses, track balances, show debts

================================================================================
                              TODO: IMPLEMENT
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════════════════

enum class SplitType { EQUAL, EXACT, PERCENT };

// ═══════════════════════════════════════════════════════════════════════════
// USER
// ═══════════════════════════════════════════════════════════════════════════

class User {
    string userId;
    string name;
    string email;

public:
    User(const string& id, const string& name, const string& email)
        : userId(id), name(name), email(email) {}

    string getId() const { return userId; }
    string getName() const { return name; }
};

// ═══════════════════════════════════════════════════════════════════════════
// SPLIT - BASE CLASS AND STRATEGIES
// ═══════════════════════════════════════════════════════════════════════════

class Split {
protected:
    string userId;
    double amount; // The amount this user owes

public:
    Split(const string& userId) : userId(userId), amount(0) {}

    string getUserId() const { return userId; }
    double getAmount() const { return amount; }
    void setAmount(double amt) { amount = amt; }

    virtual ~Split() = default;
};

class EqualSplit : public Split {
public:
    EqualSplit(const string& userId) : Split(userId) {}
};

class ExactSplit : public Split {
public:
    ExactSplit(const string& userId, double amount) : Split(userId) {
        this->amount = amount;
    }
};

class PercentSplit : public Split {
    double percent;

public:
    PercentSplit(const string& userId, double percent)
        : Split(userId), percent(percent) {}

    double getPercent() const { return percent; }
};

// ═══════════════════════════════════════════════════════════════════════════
// EXPENSE
// ═══════════════════════════════════════════════════════════════════════════

class Expense {
    string paidBy;       // userId of the payer
    double totalAmount;
    string description;
    SplitType splitType;
    vector<Split*> splits;

public:
    Expense(const string& paidBy, double amount, const string& desc,
            SplitType type, vector<Split*> splits)
        : paidBy(paidBy), totalAmount(amount), description(desc),
          splitType(type), splits(splits) {}

    string getPaidBy() const { return paidBy; }
    double getTotalAmount() const { return totalAmount; }
    const vector<Split*>& getSplits() const { return splits; }

    bool validate() const {
        // TODO: Validate that splits add up to total amount
        // For EQUAL: auto-calculate each share
        // For EXACT: sum of exact amounts == total
        // For PERCENT: sum of percentages == 100
        return false;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// EXPENSE MANAGER
// ═══════════════════════════════════════════════════════════════════════════

class ExpenseManager {
    unordered_map<string, User*> users;

    // balances[A][B] = amount A owes B (positive means A owes B)
    unordered_map<string, unordered_map<string, double>> balances;

public:
    void addUser(User* user) {
        // TODO: Register user in the system
    }

    void addExpense(const Expense& expense) {
        // TODO: Process expense and update balances
        // For each split: the split user owes the payer their share
        // Update balances[splitUser][payer] += splitAmount
    }

    void showBalances() const {
        // TODO: Print all non-zero balances
        // Format: "Alice owes Bob: 250.00"
    }

    void showBalancesForUser(const string& userId) const {
        // TODO: Print balances for a specific user
    }

    void simplifyDebts() {
        // TODO: Minimize transactions using net balance approach
        // 1. Calculate net balance for each user (total owed - total owing)
        // 2. Match positive and negative balances greedily
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN - DEMO
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // TODO: Create users, add expenses with different split types, show balances

    cout << "===== SPLITWISE =====" << endl;
    cout << "(Stub — implement the TODOs above)" << endl;

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

BALANCE TRACKING:
  balances[A][B] > 0 means A owes B that amount.
  When A pays and B is in the split:
    balances[B][A] += B's share

DEBT SIMPLIFICATION ALGORITHM:
  1. Compute net balance for each user:
     net[u] = sum(others owe u) - sum(u owes others)
  2. Separate into creditors (net > 0) and debtors (net < 0)
  3. Greedily match largest debtor with largest creditor
  4. This minimizes the number of transactions

EXAMPLE:
  Users: Alice, Bob, Charlie
  Expense 1: Alice pays 300, split EQUAL among all three
    -> Bob owes Alice 100, Charlie owes Alice 100
  Expense 2: Bob pays 150, split EQUAL among Bob and Charlie
    -> Charlie owes Bob 75

  Net: Alice = +200, Bob = -100 + 75 = -25, Charlie = -100 - 75 = -175
  Simplified: Charlie pays Alice 175, Bob pays Alice 25

EXTENSIBILITY:
  - Group expenses (expense belongs to a group)
  - Expense categories and reports
  - Currency conversion
  - Payment integration (mark debts as settled)

================================================================================
*/
