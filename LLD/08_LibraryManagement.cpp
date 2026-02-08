/*
================================================================================
                    LOW-LEVEL DESIGN: LIBRARY MANAGEMENT SYSTEM
================================================================================

PROBLEM:
  Design a library management system that allows members to borrow and
  return books, with fine calculation for overdue books.

REQUIREMENTS:
  1. Add/remove books from the library catalog
  2. Register members with different membership types
  3. Search books by title, author, or ISBN
  4. Borrow books (with max limit per member type)
  5. Return books with overdue fine calculation
  6. Reserve books that are currently checked out
  7. Send notifications when reserved books become available

DESIGN PATTERNS:
  - Observer Pattern: Notify members when reserved books are returned
  - Strategy Pattern: Different fine calculation strategies
  - Enum Types: BookStatus, MemberType

CLASSES:
  Book             - ISBN, title, author, status
  Member           - id, name, type, borrowed books, reservations
  BookLending      - tracks who borrowed what and when (due date, return date)
  Library          - catalog, members, lending operations, search
  NotificationService - observer for reservation notifications

================================================================================
                              TODO: IMPLEMENT
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <ctime>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// ENUMS
// ═══════════════════════════════════════════════════════════════════════════

enum class BookStatus { AVAILABLE, CHECKED_OUT, RESERVED, LOST };
enum class MemberType { BASIC, PREMIUM };  // BASIC: 2 books, PREMIUM: 5 books

// ═══════════════════════════════════════════════════════════════════════════
// BOOK
// ═══════════════════════════════════════════════════════════════════════════

class Book {
    string isbn;
    string title;
    string author;
    BookStatus status;

public:
    Book(const string& isbn, const string& title, const string& author)
        : isbn(isbn), title(title), author(author), status(BookStatus::AVAILABLE) {}

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    BookStatus getStatus() const { return status; }
    void setStatus(BookStatus s) { status = s; }

    void display() const {
        string statusStr;
        switch (status) {
            case BookStatus::AVAILABLE: statusStr = "Available"; break;
            case BookStatus::CHECKED_OUT: statusStr = "Checked Out"; break;
            case BookStatus::RESERVED: statusStr = "Reserved"; break;
            case BookStatus::LOST: statusStr = "Lost"; break;
        }
        cout << "[" << isbn << "] " << title << " by " << author
             << " (" << statusStr << ")" << endl;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MEMBER
// ═══════════════════════════════════════════════════════════════════════════

class Member {
    string memberId;
    string name;
    MemberType type;
    vector<string> borrowedISBNs;

public:
    Member(const string& id, const string& name, MemberType type)
        : memberId(id), name(name), type(type) {}

    string getId() const { return memberId; }
    string getName() const { return name; }
    MemberType getType() const { return type; }
    const vector<string>& getBorrowedBooks() const { return borrowedISBNs; }

    int getMaxBooks() const {
        return (type == MemberType::PREMIUM) ? 5 : 2;
    }

    bool canBorrow() const {
        return (int)borrowedISBNs.size() < getMaxBooks();
    }

    void addBorrowedBook(const string& isbn) {
        borrowedISBNs.push_back(isbn);
    }

    void removeBorrowedBook(const string& isbn) {
        borrowedISBNs.erase(
            remove(borrowedISBNs.begin(), borrowedISBNs.end(), isbn),
            borrowedISBNs.end());
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// BOOK LENDING - TRACKS BORROW/RETURN
// ═══════════════════════════════════════════════════════════════════════════

class BookLending {
    string isbn;
    string memberId;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;

public:
    BookLending(const string& isbn, const string& memberId, int lendingDays = 14)
        : isbn(isbn), memberId(memberId), returnDate(0) {
        borrowDate = time(nullptr);
        dueDate = borrowDate + (lendingDays * 24 * 60 * 60);
    }

    bool isOverdue() const {
        // TODO: Check if current time > dueDate and not yet returned
        return false;
    }

    double calculateFine(double ratePerDay = 1.0) const {
        // TODO: Calculate fine based on overdue days
        return 0.0;
    }

    void markReturned() {
        returnDate = time(nullptr);
    }

    string getISBN() const { return isbn; }
    string getMemberId() const { return memberId; }
};

// ═══════════════════════════════════════════════════════════════════════════
// LIBRARY - MAIN CONTROLLER
// ═══════════════════════════════════════════════════════════════════════════

class Library {
    unordered_map<string, Book> catalog;             // isbn -> book
    unordered_map<string, Member> members;            // memberId -> member
    vector<BookLending> lendings;                     // active lendings
    unordered_map<string, queue<string>> reservations; // isbn -> queue of memberIds

public:
    // ── Catalog Management ───────────────────────────────────────────────

    void addBook(const string& isbn, const string& title, const string& author) {
        // TODO: Add book to catalog
    }

    void removeBook(const string& isbn) {
        // TODO: Remove book (only if available)
    }

    // ── Member Management ────────────────────────────────────────────────

    void registerMember(const string& id, const string& name, MemberType type) {
        // TODO: Add member to system
    }

    // ── Search ───────────────────────────────────────────────────────────

    vector<Book> searchByTitle(const string& title) const {
        // TODO: Search catalog by title (partial match)
        return {};
    }

    vector<Book> searchByAuthor(const string& author) const {
        // TODO: Search catalog by author
        return {};
    }

    Book* searchByISBN(const string& isbn) {
        // TODO: Exact lookup by ISBN
        return nullptr;
    }

    // ── Borrow / Return ──────────────────────────────────────────────────

    bool borrowBook(const string& memberId, const string& isbn) {
        // TODO: Validate member can borrow, book is available
        // Create BookLending, update book status, update member
        return false;
    }

    double returnBook(const string& memberId, const string& isbn) {
        // TODO: Find lending, calculate fine if overdue
        // Update book status, notify reservation queue if any
        return 0.0;
    }

    // ── Reservations ─────────────────────────────────────────────────────

    bool reserveBook(const string& memberId, const string& isbn) {
        // TODO: Add member to reservation queue for this book
        return false;
    }

    void notifyNextInQueue(const string& isbn) {
        // TODO: Notify first member in reservation queue
        // that the book is now available
    }

    // ── Display ──────────────────────────────────────────────────────────

    void displayCatalog() const {
        // TODO: Print all books
    }

    void displayMemberInfo(const string& memberId) const {
        // TODO: Print member details and borrowed books
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN - DEMO
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // TODO: Create library, add books, register members,
    //       borrow/return books, search, reserve

    cout << "===== LIBRARY MANAGEMENT SYSTEM =====" << endl;
    cout << "(Stub — implement the TODOs above)" << endl;

    return 0;
}

/*
================================================================================
                         DESIGN NOTES
================================================================================

FINE CALCULATION:
  - Default: Rs. 1 per day overdue
  - Premium members: 50% discount on fines
  - Max fine cap: Rs. 100

RESERVATION FLOW:
  1. Member tries to borrow a checked-out book
  2. System adds them to reservation queue for that ISBN
  3. When book is returned, first member in queue is notified
  4. Reserved book is held for 24 hours before going to next in queue

EXTENSIBILITY:
  - Multiple copies of same book (track by copy ID)
  - E-book lending (no physical return needed, auto-expire)
  - Librarian role with special permissions
  - Late return notifications via email/SMS (Observer pattern)
  - Book recommendations based on borrowing history

================================================================================
*/
