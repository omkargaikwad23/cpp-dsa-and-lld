/*
================================================================================
                    LOW-LEVEL DESIGN: VENDING MACHINE
================================================================================

PROBLEM:
  Design a vending machine that sells products, accepts coins/notes,
  dispenses products, and returns change.

REQUIREMENTS:
  1. Display available products with prices and quantities
  2. Accept coins and notes (1, 2, 5, 10, 20, 50, 100)
  3. Select a product by code
  4. Dispense product if sufficient money inserted
  5. Return change using available denominations
  6. Admin: restock products, collect money, add change

DESIGN PATTERNS:
  - State Pattern: Machine states (IDLE, ACCEPTING_MONEY, DISPENSING, RETURNING_CHANGE)
  - Each state defines valid transitions and actions

CLASSES:
  Product         - name, price, code
  Inventory       - product stock management
  CoinManager     - tracks available coins, calculates change
  VendingMachine  - state machine, orchestrates the flow

================================================================================
                              TODO: IMPLEMENT
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════════════════

enum class MachineState { IDLE, ACCEPTING_MONEY, DISPENSING };

// ═══════════════════════════════════════════════════════════════════════════
// PRODUCT
// ═══════════════════════════════════════════════════════════════════════════

class Product {
    string code;
    string name;
    double price;

public:
    Product() : price(0) {}

    Product(const string& code, const string& name, double price)
        : code(code), name(name), price(price) {}

    string getCode() const { return code; }
    string getName() const { return name; }
    double getPrice() const { return price; }
};

// ═══════════════════════════════════════════════════════════════════════════
// INVENTORY - PRODUCT STOCK MANAGEMENT
// ═══════════════════════════════════════════════════════════════════════════

class Inventory {
    unordered_map<string, Product> products; // code -> product
    unordered_map<string, int> stock;        // code -> quantity

public:
    void addProduct(const Product& product, int quantity) {
        // TODO: Add or restock product
    }

    bool isAvailable(const string& code) const {
        // TODO: Check if product exists and has stock > 0
        return false;
    }

    Product* getProduct(const string& code) {
        // TODO: Return product by code
        return nullptr;
    }

    void dispense(const string& code) {
        // TODO: Reduce stock by 1
    }

    void displayProducts() const {
        // TODO: Show all products with code, name, price, stock
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// COIN MANAGER - CHANGE CALCULATION
// ═══════════════════════════════════════════════════════════════════════════

class CoinManager {
    map<int, int, greater<int>> coinStock; // denomination -> count (desc order)

public:
    CoinManager() {
        // Initialize with some change
        vector<int> denominations = {100, 50, 20, 10, 5, 2, 1};
        for (int d : denominations) {
            coinStock[d] = 0;
        }
    }

    void addCoins(int denomination, int count) {
        // TODO: Add coins to stock
    }

    bool canMakeChange(double amount) const {
        // TODO: Check if we have enough coins to return this amount
        return false;
    }

    vector<pair<int, int>> makeChange(double amount) {
        // TODO: Greedy — use largest denominations first
        // Return list of (denomination, count) pairs
        return {};
    }

    void addInsertedMoney(int denomination) {
        // TODO: Add user-inserted money to coin stock
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// VENDING MACHINE - STATE MACHINE
// ═══════════════════════════════════════════════════════════════════════════

class VendingMachine {
    Inventory inventory;
    CoinManager coinManager;
    MachineState state;
    double insertedAmount;
    string selectedProduct;

public:
    VendingMachine() : state(MachineState::IDLE), insertedAmount(0) {}

    void displayProducts() const {
        // TODO: Show available products
    }

    void selectProduct(const string& code) {
        // TODO: Validate product exists and is in stock
        // Transition: IDLE -> ACCEPTING_MONEY
    }

    void insertMoney(int denomination) {
        // TODO: Accept money, update inserted amount
        // Only valid in ACCEPTING_MONEY state
    }

    void dispense() {
        // TODO: Check if enough money inserted
        // Dispense product, calculate and return change
        // Transition: ACCEPTING_MONEY -> DISPENSING -> IDLE
    }

    void cancel() {
        // TODO: Return all inserted money, go back to IDLE
    }

    // Admin functions
    void restock(const string& code, int quantity) {
        // TODO: Add stock for a product
    }

    void addChange(int denomination, int count) {
        // TODO: Add change to machine
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN - DEMO
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // TODO: Create machine, stock products, simulate purchase flow

    cout << "===== VENDING MACHINE =====" << endl;
    cout << "(Stub — implement the TODOs above)" << endl;

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

STATE TRANSITIONS:
  IDLE -> selectProduct() -> ACCEPTING_MONEY
  ACCEPTING_MONEY -> insertMoney() -> ACCEPTING_MONEY (accumulate)
  ACCEPTING_MONEY -> dispense() -> DISPENSING -> IDLE
  ACCEPTING_MONEY -> cancel() -> IDLE (return money)

CHANGE ALGORITHM (Greedy):
  For amount = 73:
    100: skip (too large)
    50: 1 coin -> remaining 23
    20: 1 coin -> remaining 3
    10: skip
    5: skip
    2: 1 coin -> remaining 1
    1: 1 coin -> remaining 0
  Result: [50x1, 20x1, 2x1, 1x1]

EXTENSIBILITY:
  - Card/UPI payment (new PaymentMethod interface)
  - Product categories (drinks, snacks)
  - Temperature zones (cold, warm)
  - Remote monitoring and alerts
  - Discount codes / promotions

================================================================================
*/
